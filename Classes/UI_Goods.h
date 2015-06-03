#ifndef UI_GOODS_H
#define UI_GOODS_H

#include "CrossApp.h"
#include "Data_Define.h"

//单个商品
class Base_ImageView;
class UI_Goods : public CAView
{
public:
	UI_Goods() :
		m_navBar(NULL){}

	//坐标是center
	//ntype 0上下显示 1左右显示
	static UI_Goods* creat(const CCRect& rect, const CCSize& imageSize,int nType = 0);

	//商品信息
	void SetGoodsInfo(S_Good goods);

	//设置商品样式


	//设置navBar
	void SetNavBar(CANavigationController* bar) { m_navBar = bar; }
private:
	bool init(const CCRect& rect,int nType);

	//设置图片尺寸大小
	void SetImageSize(CCSize size);

	//获取 文字位置
	void SetLable(int ntype);

	virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
private:
	//图片大小
	CCSize						m_imageSize;

	CALabel*					m_name;
	CALabel*					m_price;
	
	//商品信息
	S_Good						m_goods;

	//push的navbar
	CANavigationController*		m_navBar;
};



//商品信息界面
class UI_GoodsView : public Base_ViewController
{
public:
	static UI_GoodsView* creatWithId(int shopId);

	//回调函数
	void CallBack_http_good(const char* msg);

	void CallBack_btnCall(CAControl *sender, CCPoint pos);
	void CallBack_btnBuy(CAControl *sender, CCPoint pos);
private:
	bool init(int nId);

	void viewDidLoad();

	//显示滚动层
	void SetScrollView(const vector<std::string>& banner,int& height);

	//商品title
	void SetGoodsTitle(const std::string& value,int& height);

	//商品价格
	void SetGoodsPrice(const std::string& value, int& height);

	//商品售卖
	//value   店铺连接
	//value2 电话号码
	void SetGoodsLink( int& height);

	//商品简介
	void SetGoodsShow(const std::string& value, int& height);

	//相关商品
	void SetGoodsAbout(const vec_Goods& goods, int& height);
private:
	//商品id
	int				m_goodId;

	//商品链接
	std::string		m_goodsLink[2];

	CAScrollView*	m_mainScroll;


	//滚动展示层
	Base_PageView*		m_pageView;
};
#endif