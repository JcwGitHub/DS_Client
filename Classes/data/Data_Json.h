#ifndef DATA_JSON_H
#define DATA_JSON_H

#include "CSContentJsonDictionary.h"

class Data_Json : public CrossApp::extension::CSJsonDictionary
{
public:
	typedef vector<std::string>			Json_Vec_Value;

	typedef vector<Data_Json*>			Json_Vec_Dic;
public:
	//构造
	//str base64 加密数据
	Data_Json(const std::string& str,bool isDecode = true);

	Data_Json() {}

	//返回字典
	Data_Json*  Json_GetDicValue(const std::string& sKey);

	//返回字符串值
	void		Json_GetStrValue(const std::string& sKey, std::string& container);

	//返回数组
	//container 接受数据的数组
	void		Json_GetVecValue(const std::string& sKey, Json_Vec_Value& container);

	void        Json_GetVecValue(const std::string& sKey, Json_Vec_Dic& container);
};

#endif