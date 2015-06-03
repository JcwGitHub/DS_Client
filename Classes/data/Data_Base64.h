#ifndef DATA_BASE64_H
#define DATA_BASE64_H


#include <vector>
#include <string>
using namespace std;

//base64加密
void  MY_Base64_Encode(std::string& target);

//base64解密
void  MY_Bbase64_Decode(std::string& target);



//保存整体数据
#define DATA_BASE Data_Base::GetInstance()
class Data_Base
{
public:
	Data_Base();

	static Data_Base* GetInstance();

public:
	//各种高度数据
	float		m_NarBar_H;			//navbar 高度
	float		m_TabBar_H;			//tabbar 高度

	bool		m_firstLogin;			//是否首次登陆
public:
	//搜索历史
	void GetSearch(vector<std::string>& searchList){ searchList = m_searchList; }
	void PushSearch(const std::string& _key);
	void ClearSearch();


private:
	bool init();
	//默认保存
	void SaveAndGet(bool flag = true);
	//是否首次登陆
	void CheckFirstLogin();

private:
	static Data_Base*	s_DataBase;

	//搜索历史
	std::vector<std::string>	m_searchList;
};
#endif