#include "UI_Goods.h"
#include "Base_WebView.h"


//商品
UI_Goods* UI_Goods::creat(const CCRect& rect, const CCSize& imageSize, int nType)
{
	UI_Goods* goods = new UI_Goods();
	goods->SetImageSize(imageSize);

	if (goods&&goods->init(rect,nType))
	{
		goods->autorelease();
		return goods;
	}

	CC_SAFE_RELEASE_NULL(goods);
	return NULL;
}


bool UI_Goods::init(const CCRect& rect, int nType)
{
	if (!CAView::initWithCenter(rect))
	{
		return false;
	}

	SetLable(nType);
	return true;
}


void UI_Goods::SetImageSize(CCSize size)
{
	m_imageSize = size;
}

bool UI_Goods::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
	return true;
}


void UI_Goods::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
	if (pTouch->isDelta())
	{
		return;
	}

	if (m_navBar)
	{
		//商品详情
		UI_GoodsView* _view = UI_GoodsView::creatWithId(atoi(m_goods._shopId.c_str()));
		m_navBar->pushViewController(_view, true);
	}
}

void UI_Goods::SetGoodsInfo(S_Good goods)
{
	m_goods = goods;

	m_name->setText(m_goods._shopname);

	std::string _price = "￥" + m_goods._shopprice;
	m_price->setText(_price);

	//商品图片
	int _tag = 1010;
	this->removeSubviewByTag(_tag);

	Base_ImageView* image = Base_ImageView::CreatWithUrl(m_goods._pic);
	image->setFrame(CCRect(0, 0, m_imageSize.width, m_imageSize.height));
	image->setTag(_tag);
	this->addSubview(image);
}

void UI_Goods::SetLable(int ntype)
{
	CCSize _bounds = this->getBounds().size;
	switch (ntype)
	{
	case 0:
	{
			  //上下
			  //商品名
			  m_name = CALabel::createWithCenter(CCRect(
				  _bounds.width / 2,
				  m_imageSize.height + (_bounds.height - m_imageSize.height) / 9 * 3,
				  _bounds.width,
				  (_bounds.height - m_imageSize.height) / 2));

			  m_name->setFontSize(_px(24));
			  m_name->setText("");
			  m_name->setTextAlignment(CATextAlignmentLeft);
			  m_name->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
			  this->addSubview(m_name);


			  //商品价格
			  m_price = CALabel::createWithCenter(CCRect(
				  _bounds.width / 2,
				  m_imageSize.height + (_bounds.height - m_imageSize.height) / 8 * 5,
				  _bounds.width,
				  (_bounds.height - m_imageSize.height) / 2));

			  m_price->setFontSize(_px(24));
			  m_price->setText("");
			  m_price->setColor(CAColor_red);
			  m_price->setTextAlignment(CATextAlignmentLeft);
			  m_price->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
			  this->addSubview(m_price);
	}
		break;
	case 1:
	{
			  //左右
			  //商品名
			  m_name = CALabel::createWithFrame(CCRect(
				  m_imageSize.width + _px(10),
				  _px(30),
				  _bounds.width - m_imageSize.width - _px(30),
				  _bounds.height / 2));

			  m_name->setFontSize(FitY(27));
			  m_name->setText("");
			  m_name->setColor(ccc4(0x08, 0x08, 0x08, 255));
			  m_name->setTextAlignment(CATextAlignmentLeft);
			  m_name->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
			  this->addSubview(m_name);


			  //商品价格
			  m_price = CALabel::createWithFrame(CCRect(
				  m_imageSize.width + _px(10),
				  _bounds.height / 2 - _px(15),
				  _bounds.width - m_imageSize.width - _px(30),
				  _bounds.height / 2));

			  m_price->setFontSize(FitY(30));
			  m_price->setText("");
			  m_price->setColor(CAColor_red);
			  m_price->setTextAlignment(CATextAlignmentLeft);
			  m_price->setVerticalTextAlignmet(CAVerticalTextAlignmentBottom);
			  this->addSubview(m_price);
	}
		break;
	default:
		break;
	}
}


//contorller
UI_GoodsView* UI_GoodsView::creatWithId(int shopId)
{
	UI_GoodsView* _good = new UI_GoodsView();
	if (_good&&_good->init(shopId))
	{
		_good->autorelease();
		return _good;
	}

	CC_SAFE_RELEASE_NULL(_good);
	return NULL;
}
bool UI_GoodsView::init(int nId)
{
	if (!CAViewController::init())
	{
		return false;
	}

	m_goodId = nId;

	this->getView()->setColor(CAColor_clear);
	this->setTitle(UTF8("商品信息"));
	return true;
}

void UI_GoodsView::viewDidLoad()
{

	m_mainScroll = CAScrollView::createWithFrame(this->getView()->getBounds());
	m_mainScroll->setBounceHorizontal(false);
	m_mainScroll->setShowsHorizontalScrollIndicator(false);
	m_mainScroll->setShowsVerticalScrollIndicator(false);
	m_mainScroll->setBackGroundColor(CAColor_white);
	this->getView()->addSubview(m_mainScroll);

	//发送消息
	Data_HttpManage* _http = Data_HttpManage::GetInstance();
	_http->PushPostData("shopid",m_goodId );
	_http->SendData(URL_ShopDetails);
	_http->SetHttpCallBack(this, HttpManager_selector(UI_GoodsView::CallBack_http_good));

	Base_ViewController::viewDidLoad();
}

void UI_GoodsView::CallBack_http_good(const char* msg)
{
	if (!m_mainScroll)
	{
		return;
	}


	Data_Json::Json_Vec_Value _vec;
	Data_Json _json(msg);
	std::string _value;
	int _height = 0;

	//滚动层数据
	_json.Json_GetVecValue("pic", _vec);
	SetScrollView(_vec,_height);


	//商品名称
	_json.Json_GetStrValue("title",_value);
	SetGoodsTitle(_value,_height);

	//商品价格
	_json.Json_GetStrValue("shopprice", _value);
	SetGoodsPrice(_value, _height);

	//商品链接
	_json.Json_GetStrValue("shopcon", _value);
	SetGoodsLink(_value, _height);

	//商品描述
	_json.Json_GetStrValue("shopintroduce", _value);
	SetGoodsShow(_value, _height);

	//商品相关
	Data_Json::Json_Vec_Dic _vec1;
	vec_Goods _goods;

	_json.Json_GetVecValue("revelist", _vec1);
	for (size_t i = 0; i < _vec1.size(); i++)
	{
		S_Good					_good;
		_vec1[i]->Json_GetStrValue("shopid", _good._shopId);
		_vec1[i]->Json_GetStrValue("pic", _good._pic);
		_vec1[i]->Json_GetStrValue("shopname", _good._shopname);
		_vec1[i]->Json_GetStrValue("shopprice", _good._shopprice);
		_vec1[i]->Json_GetStrValue("lsr", _good._lsr);
		_vec1[i]->Json_GetStrValue("lsrtime", _good._lsrtime);
		_goods.push_back(_good);
	}
	SetGoodsAbout(_goods, _height);




	m_mainScroll->setViewSize(FitSize(640,_height));
}

void UI_GoodsView::CallBack_btnCall(CAControl *sender, CCPoint pos)
{

}

void UI_GoodsView::CallBack_btnBuy(CAControl *sender, CCPoint pos)
{
	
	presentModalViewController(Base_WebViewController::creat(m_goodsLink),true);
}
void UI_GoodsView::SetScrollView(const vector<std::string>& banner,int& height)
{
	height = 371;
	CCSize _dSize = FitSize(640, height);

	CAVector<CAView*> _temp;
	for (size_t i = 0; i < banner.size(); i++)
	{
		Base_ImageView* _ima = Base_ImageView::CreatWithUrl(banner[i]);
		_temp.pushBack(_ima);
	}

	m_pageView = Base_PageView::creat(CCRect(_dSize.width / 2, _dSize.height / 2, _dSize.width, _dSize.height),
		CAPageViewDirectionHorizontal);
	m_pageView->SetPageViews(_temp);
	m_pageView->SetAutoScroll(true);
	m_mainScroll->addSubview(m_pageView);

	//添加tag
	m_mainScroll->addSubview(m_pageView->GetPageTag());
}

void UI_GoodsView::SetGoodsTitle(const std::string& value, int& height)
{
	//商品标题
	std::u16string _16;
	StringUtils::UTF8ToUTF16(value, _16);

	int _size = _16.size()/17 + (_16.size()%17==0?0:1);

	CALabel* label = CALabel::createWithFrame(FitRect(30, height + 30, 500, 40*_size));
	label->setColor(ccc4(0x3d, 0x42, 0x45, 255));
	label->setFontSize(_px(29));
	label->setText(value);
	m_mainScroll->addSubview(label);

	height += 40 * _size + 60;
}

void UI_GoodsView::SetGoodsPrice(const std::string& value, int& height)
{
	//商品价格
	CALabel* label = CALabel::createWithFrame(FitRect(30, height, 500, 40));
	label->setFontSize(_px(36));
	label->setColor(ccc4(255,80,0,255));
	std::string _price = "￥" + value + ".00";
	label->setText(_price);
	m_mainScroll->addSubview(label);
	
	height += 40 + 30;
}

void UI_GoodsView::SetGoodsLink(const std::string& value, int& height)
{
	Base_ImageView* _ima = Base_ImageView::creat("image/g_info_bg.png");
	_ima->setFrame(FitRect(0, height, 640, 124));
	m_mainScroll->addSubview(_ima);

	//购买按钮
	m_goodsLink = value;
	CAButton* btn1 = CAButton::createWithCenter(FitRect(160,72,216,63),CAButtonTypeRoundedRect);
	btn1->setTitleForState(CAControlStateAll,UTF8("购买"));
	btn1->setBackGroundViewForState(CAControlStateNormal, Base_ImageView::creat("image/g_info_gm1.png"));
	btn1->setBackGroundViewForState(CAControlStateHighlighted, Base_ImageView::creat("image/g_info_gm2.png"));
	btn1->setBackGroundViewForState(CAControlStateDisabled, Base_ImageView::creat("image/g_info_lx3.png"));
	btn1->addTarget(this, CAControl_selector(UI_GoodsView::CallBack_btnBuy), CAControlEventTouchUpInSide);
	_ima->addSubview(btn1);

	//联系卖家按钮
	CAButton* btn2 = CAButton::createWithCenter(FitRect(480, 72, 216, 63), CAButtonTypeRoundedRect);
	btn2->setTitleForState(CAControlStateAll, UTF8("联系店主"));
	btn2->setBackGroundViewForState(CAControlStateNormal, Base_ImageView::creat("image/g_info_lx1.png"));
	btn2->setBackGroundViewForState(CAControlStateHighlighted, Base_ImageView::creat("image/g_info_lx2.png"));
	btn2->setBackGroundViewForState(CAControlStateDisabled, Base_ImageView::creat("image/g_info_lx3.png"));
	btn2->setImageColorForState(CAControlStateAll, ccc4(255, 140, 2, 255));
	btn2->addTarget(this, CAControl_selector(UI_GoodsView::CallBack_btnCall), CAControlEventTouchUpInSide);
	_ima->addSubview(btn2);

	if (value.empty())
	{
		btn1->setControlState(CAControlStateDisabled);
	}

	btn2->setControlState(CAControlStateDisabled);

	//尺寸
	height += 124;
}

void UI_GoodsView::SetGoodsShow(const std::string& value, int& height)
{
	//商品价格
	CALabel* label = CALabel::createWithFrame(FitRect(30, height, 580, 170));
	label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	label->setTextAlignment(CATextAlignmentCenter);
	label->setColor(ccc4(0x7c, 0x7c, 0x7c, 255));
	label->setFontSize(_px(30));
	label->setText(value);
	m_mainScroll->addSubview(label);


	height += 170;
}

void UI_GoodsView::SetGoodsAbout(const vec_Goods& goods, int& height)
{
	//商品尺寸  290 290
	int _h  = goods.size() / 2 + (goods.size()%2==0?0:1);
	int _h1 = 50 + (290 + 20)*_h;

	Base_View* _view = Base_View::createWithFrame(FitRect(0, height,640, _h1), ccc4(235, 234, 234, 255));
	m_mainScroll->addSubview(_view);

	//title
	CALabel* label = CALabel::createWithFrame(FitRect(0, 0, 640, 50));
	label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	label->setTextAlignment(CATextAlignmentCenter);
	label->setFontSize(_px(30));
	label->setText(UTF8("相关商品"));
	label->setColor(ccc4(0x7c, 0x7c, 0x7c, 255));
	_view->addSubview(label);

	//显示相关商品
	for (size_t i = 0; i < goods.size(); i++)
	{
		UI_Goods* _good = UI_Goods::creat(FitRect(
			20+145+(290+20)*(i%2),
			50+145+(290+20)*(i/2),
			290,
			290), FitSize(290,200));

		_good->SetGoodsInfo(goods[i]);
		_good->SetNavBar(this->getNavigationController());
		_view->addSubview(_good);
	}


	//重新调整高度
	height += _h1;
}




