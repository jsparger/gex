//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_MARKOV_CHAIN_HH
#define GEX_UTIL_MARKOV_CHAIN_HH

#include <vector>
#include <map>
#include <stdexcept>
#include <numeric>
#include <random>
#include <functional>
#include <iostream>

namespace gex {
namespace util {

/// \class MarkovChain
/// \brief Update a value according to a markov chain.
///

template <typename T>
class MarkovChain
{
protected:
	
	struct Item
	{
		Item (T* x)
			: value(*x) {}
		T value;
	};
	
	struct Node
	{
		std::vector<double> probVec;
		std::vector<T*> endVec;
		std::vector<double> cdf;
		unsigned int size;
		std::function<double(void)> rngfunc;
		double sum = 0;
		
		virtual void addEdge(T* end, double transitionProb)
		{
			sum += transitionProb;
			probVec.push_back(transitionProb);
			endVec.push_back(end);
			size = probVec.size();
			computeCdf();
			
		}
		
		virtual void computeCdf()
		{
			cdf = std::vector<double>(size);
			std::partial_sum (probVec.begin(), probVec.end(), cdf.begin());
			for (auto& val : cdf)
			{
				val /= sum;
			}
		}
		
		virtual T* advance()
		{
			double r = rngfunc();
			for (unsigned int i = 0; i < size; ++i)
			{
				if (cdf[i] >= r)
				{
					return endVec[i];
				}
			}
			
			std::cout << "r == " << r << " \n";
			for (auto x : cdf)
			{
				std::cout << x << "\n";
			}
			std::cout << "OOH MY GOOOOD\n";
			throw std::runtime_error("gex::util::MarkovChain::Node::advance(): cdf error! Destination not selected!");
		}
		
	};
	
public:
	
	MarkovChain()
	{
		std::random_device rd;
		mt = std::mt19937(rd());
		uniform = std::uniform_real_distribution<double>(0.0,1.0);
		rngfunc = [this]()->double
		{
			return this->uniform(this->mt);
		};
	}
	
	virtual ~MarkovChain() {;}
	
	virtual MarkovChain<T>& add(T* startState, T* endState, double transitionProb)
	{
		Node& start = stateMap[startState];
		if (firstTime)
		{
			currentNode = &start;
			current = new Item(startState);
			firstTime = false;
		}
		
		start.rngfunc = this->rngfunc;
		start.addEdge(endState, transitionProb);
		
		Node& end = stateMap[endState];
		end.rngfunc = this->rngfunc;
		
		
		return *this;
	}
	
	virtual void advance()
	{
		T* next = currentNode->advance();
		currentNode = &stateMap[next];
		current->value = *next;
	}
	
	virtual T& state()
	{
		return current->value;
	}
	
protected:
	Item* current;
	Node* currentNode;
	std::map<T*,Node> stateMap;
	std::mt19937 mt;
	std::uniform_real_distribution<double> uniform;
	std::function<double(void)> rngfunc;
	bool firstTime = true;
};

} // namespace util 	
} // namespace gex 

#endif
