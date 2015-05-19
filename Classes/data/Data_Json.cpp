#include "Data_Json.h"
#include "Data_Base64.h"



Data_Json* Data_Json::Json_GetDicValue(const std::string& sKey)
{
	return (Data_Json*)getSubDictionary(sKey.c_str());
}
void Data_Json::Json_GetStrValue(const std::string& sKey, std::string& container)
{
	container.clear();

	container = getItemStringValue(sKey.c_str());
	MY_Bbase64_Decode(container);
}

void Data_Json::Json_GetVecValue(const std::string& sKey, Json_Vec_Value& container)
{
	container.clear();
	for (size_t i = 0; i < m_cValue[sKey].size(); i++)
	{
		container.push_back(getStringValueFromArray(sKey.c_str(), i));
		MY_Bbase64_Decode(container[container.size() - 1]);
	}
}
void Data_Json::Json_GetVecValue(const std::string& sKey, Json_Vec_Dic& container)
{
	container.clear();
	for (size_t i = 0; i < m_cValue[sKey].size(); i++)
	{
		container.push_back((Data_Json*)getSubItemFromArray(sKey.c_str(), i));
	}
	
}
Data_Json::Data_Json(const std::string& str, bool isDecode)
{
	std::string _cache = str;

	if (isDecode)
	{
		MY_Bbase64_Decode(_cache);
	}	

	this->initWithDescription(_cache.c_str());

	this->Json_GetStrValue("code", _cache);

	if (atoi(_cache.c_str())!=0)
	{
		Json_GetStrValue("msg", _cache);
		CAAlertView* _al = CAAlertView::create();
		_al->setAlertMessage(_cache);
		_al->show();
	}
}