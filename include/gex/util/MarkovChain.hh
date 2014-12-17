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
/// MarkovChain lets you update a value according to a markov chain. Its use case is a bit hacky, and there are some caveats to its use (no polymorphic state values allowed). This class is intended for use whenever you want to use code that accepts a pointer whose underlying value you would like to change behind the scenes. An example might be changing the particle energy of a source according to a decay scheme you have modeled as a Markov chain. See examples/ej299_compton for an example.

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
	
	virtual ~MarkovChain() 
	{
		delete current;
	}
	
	/// Add a new transition to the chain. Provide a starting state, an ending state, and a probability for this transition to occur. Note that the transition probabilities will be normalized. DANGER! Do not use polymorphic states. The object pointed to by T* must really be of type T. This is because MarkovChain relies on copying to change the state value.
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
	
	/// Call this method to advance to the next state in the MarkovChain according to the current state, its connections, and transition probabilities.
	virtual void advance()
	{
		T* next = currentNode->advance();
		currentNode = &stateMap[next];
		current->value = *next;
	}
	
	// Returns a reference to the state. The value of the state may change whenever advance() is called.
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
