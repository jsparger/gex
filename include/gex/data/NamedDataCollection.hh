#ifndef GEX_DATA_NAMED_DATA_COLLECTION_HH
#define GEX_DATA_NAMED_DATA_COLLECTION_HH

#include "gex/data/IData.hh"
#include "gex/data/NamedData.hh"
#include <vector>
#include <map>
#include <string>

namespace gex {
namespace data {

/// \class NamedDataCollection
/// \brief NamedDataCollection is a vector of uniquely identified NamedData.
///
/// NamedDataCollection provides a way to store and retrieve multiple NamedData based on a unique key. This is useful when you wish to use a different NamedData for different detectors in a simulation. NamedDataCollection will allow you to store a NamedData based on a unique string identifying the detector. The actual NamedData are stored in a vector, presumably for faster access or easier iteration. The indices are available via the map.
struct NamedDataCollection : public IData
{
	virtual ~NamedDataCollection() {;}
	virtual void reset()
	{
		vec.clear();
		keyIndexTable.clear();
	}
	
	virtual IData* clone()
	{
		return new NamedDataCollection(*this);
	}
	
	virtual std::string getDataType()
	{
		return "gex::data::NamedDataCollection";
	}
	
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		std::vector<std::string> namedDataTypes = NamedData::GetDictionaryTypes();
		types.insert(types.end(), namedDataTypes.begin(), namedDataTypes.end());
		types.push_back("std::vector<gex::data::NamedData>");
		types.push_back("gex::data::NamedDataCollection");
		return types;
	}
	
	static std::vector<std::string> GetDictionaryHeaders()
	{
		std::vector<std::string> headers = IData::GetDictionaryHeaders();
		std::vector<std::string> namedDataHeaders = NamedData::GetDictionaryHeaders();
		headers.insert(headers.end(), namedDataHeaders.begin(), namedDataHeaders.end());
		headers.push_back("vector");
		headers.push_back("map");
		headers.push_back(__FILE__);
		return headers;
	}
	
	virtual std::vector<std::string> getDictionaryTypes()
	{
		return GetDictionaryTypes();
	}
	
	virtual std::vector<std::string> getDictionaryHeaders()
	{
		return GetDictionaryHeaders();
	}
	
	// static std::string GetDictionaryTypes()
	// {
	// 	std::string types = "std::vector<gex::data::NamedData>;"
	// 						//"std::pair<std::string,int>;" // root already knows about these types and will crash splendidly if you ask for them again.
	// 						//"std::map<std::string,int>;"
	// 						"gex::data::NamedDataCollection;";
	// 	return 	IData::GetDictionaryTypes() + 
	// 			NamedData::GetDictionaryTypes() + types;
	// }
	// 
	// static std::string GetDictionaryHeaders()
	// {
	// 	std::string headers = "vector;map;" __FILE__ ";";
	// 	return 	IData::GetDictionaryHeaders() +
	// 			NamedData::GetDictionaryHeaders() + headers;
	// }
	
	
	std::vector<NamedData> vec;
	std::map<std::string, int> keyIndexTable;
	
};
	
} // namespace data 
} // namespace gex 

#endif
