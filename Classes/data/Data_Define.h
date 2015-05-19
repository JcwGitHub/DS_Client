#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include "CrossApp.h"

//ui
#include "Base_ViewController.h"
#include "Base_SearchField.h"
#include "Base_TableView.h"
#include "Base_PageView.h"
#include "Base_ImageView.h"
#include "Base_NavBar.h"
#include "Base_View.h"

//data
#include "Data_HttpManage.h"
#include "Data_Base64.h"
#include "Data_Json.h"
#include <string>
#include <vector>
#include <map>


using namespace CrossApp;
using namespace std;



//全局函数
static inline std::string C_IntToString(int index){
	char _Tag[8];
	sprintf(_Tag, "%d", index);
	return _Tag;
}


//获取屏幕大小
static inline CCSize C_WinSize(){
	CAApplication* pDirector = CAApplication::getApplication();

	CCSize _winSize = pDirector->getWinSize();
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
	_winSize.height = _winSize.height + _px(20);
#endif
#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32
	_winSize.height = _winSize.height - _px(30);
#endif
	return _winSize;
}

//所有输入尺寸均为 640*1136 设计尺寸下对应的尺寸
static inline float  FitX(float x)
{
	CCSize _winSize = C_WinSize();

	return _winSize.width / _px(640) *_px(x);
}
static inline float  FitY(float y)
{
	CCSize _winSize = C_WinSize();

	return _winSize.height / _px(1136) *_px(y);
}
static inline CCSize FitSize(float width, float height)
{
	CCSize _winSize = C_WinSize();
	float _w = _winSize.width / _px(640) *_px(width);
	float _h = _winSize.height / _px(1136) *_px(height);
	return CCSize(_w, _h);
}
static inline CCRect FitRect(float x, float y, float width, float height)
{
	CCSize _winSize = C_WinSize();
	float _x = _winSize.width / _px(640) *_px(x);
	float _y = _winSize.height / _px(1136) *_px(y);
	float _w = _winSize.width / _px(640) *_px(width);
	float _h = _winSize.height / _px(1136) *_px(height);
	return CCRect(_x, _y, _w, _h);
}

//账号
static const char User_Appkey[] = "A2D071EA386337486883314CCB6F5";
static const char User_UserKey[] = "4E0818C74E904E82B214A86B1CF84A77";
static const char User_UserId[] = "101";

//消息协议
static const char URL_HotKeyWord[] = "HotKeyWord.ashx";
static const char URL_TypeList[] = "TypeList.ashx";
static const char URL_TypeShopList[] = "TypeShopList.ashx";
static const char URL_index[] = "index.ashx";
static const char URL_ActivShop[] = "ActivShop.ashx";
static const char URL_SerchList[] = "SerchList.ashx";
static const char URL_ShopDetails[] = "Shopdetails.ashx";

//资源
static std::string Res_M_Tab_N[5] = { "image/a-2.png", "image/b-2.png", "image/c-2.png", "image/d-2.png", "image/e-2.png" };
static std::string Res_M_Tab_P[5] = { "image/a-1.png", "image/b-1.png", "image/c-1.png", "image/d-1.png", "image/e-1.png" };
static std::string Res_M_Tab_T[5] = { UTF8("首页"), UTF8("分类"), UTF8("淘宝"), UTF8("积分"), UTF8("我的") };













//单个商品
struct S_Good
{
	std::string			_shopId;
	std::string			_pic;
	std::string			_shopname;
	std::string			_shopprice;
	std::string			_lsr;
	std::string			_lsrtime;
};
typedef vector<S_Good>		vec_Goods;

//商品分类列表
struct S_TypeList
{
	std::string	_typeId;
	std::string _typeName;
	vec_Goods   _goods;
};
typedef vector<S_TypeList>		vec_TypeList;

//首页滚动显示
struct S_Banner
{
	std::string			_shopId;
	std::string			_pic;
};
typedef vector<S_Banner>	vec_Banner;


//首页活动分类列表
struct S_List
{
	//控制开关
	bool				_isOpen;

	//活动id
	std::string			_typeId;

	//活动名 
	std::string			_typeName;

	vec_Goods			_lists;

	S_List(){ _isOpen = false; _lists.clear(); }
};


typedef vector<S_List>		vec_Lists;
#endif

