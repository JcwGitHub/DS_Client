#include "Base_SearchField.h"
#include "Base_ImageView.h"
#include "Data_Define.h"
#include "UI_MoreView.h"


//搜索框


Base_SearchField* Base_SearchField::Creat(const CCRect& rect)
{
	Base_SearchField* _text = new Base_SearchField();
	if (_text&&_text->init(rect))
	{
		_text->autorelease();
		return _text;
	}

	CC_SAFE_RELEASE_NULL(_text);
	return NULL;
}

bool Base_SearchField::init(const CCRect& rect)
{
	m_searchCon = NULL;
	m_oldRect = CCRect(rect.origin.x, _px(98 / 2), rect.size.width, _px(98));

	if (!CAView::initWithCenter(m_oldRect))
	{
		return false;
	}
	this->setColor(CAColor_clear);
	

	//背景
	Base_View* _bg = Base_View::create();
	_bg->setTag(100);
	_bg->setZOrder(100);
	_bg->setCenter(CCRect(rect.size.width/2,_px(88/2),rect.size.width,rect.size.height));
	//_bg->setColor(ccc4(164, 28, 28, 255));
	_bg->setColor(CAColor_red);
	this->addSubview(_bg);

	//背景线
	Base_ImageView* _ima = Base_ImageView::creat("image/m_search1.png");
	_ima->setFrame(CCRect(0, rect.size.height - FitY(13), rect.size.width, FitY(13)));
	_bg->addSubview(_ima);


	//搜索标记
	m_logo = Base_ImageView::creat("image/m_search.png");
	m_logo->setCenter(CCRect(0, 0, _px(48), _px(48)));
	_bg->addSubview(m_logo);

	//textfield
	m_text = CATextField::createWithCenter(CCRect(0,0, rect.size.width - _px(50), rect.size.height));
	m_text->setBackgroundView(CAView::createWithColor(CAColor_clear));
	m_text->setPlaceHolder(UTF8("搜索搜索宝贝"));
	m_text->setSpaceHolderColor(ccc4(0xfa,0xb4,0xb4,255));
	m_text->setTextColor(CAColor_white);
	m_text->setFontSize(_px(38));
	m_text->setDelegate(this);
	_bg->addSubview(m_text);

	SetSearchLogo(P_Left);
	return true;
}

bool Base_SearchField::onTextFieldAttachWithIME(CATextField * sender)
{
	ShowAllInfo();
	return true;
}

bool Base_SearchField::onTextFieldDetachWithIME(CATextField * sender)
{
	//hideAllInfo();
	return true;
}

// bool Base_SearchField::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
// {
// 
// 	return false;
// }
// 
// bool Base_SearchField::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
// {
// 
// 	return false;
// }

bool Base_SearchField::keyBoardCallBack(CATextField *sender)
{
	//确认搜索
	std::string _key = ""/*sender->getText()*/;
	
	//添加本地
	Data_Base::GetInstance()->PushSearch(_key);

	this->Callback_Chose(_key);
	return true;
}

void Base_SearchField::SetSearchLogo(E_Logo_P position)
{
	CCSize _size = this->getSubviewByTag(100)->getBounds().size;

	//间隙
	float _dis		= _px(10);
	float _tWidth	= _size.width - _dis * 2 - m_logo->getBounds().size.width;

	switch (position)
	{
	case Base_SearchField::P_Left:
	{
		m_logo->setVisible(true);
		m_logo->setCenterOrigin(CCPoint(
			_dis + m_logo->getBounds().size.width / 2,
			_size.height/2));

		m_text->setCenter(CCRect(
			_tWidth/2 + _dis * 2 + m_logo->getBounds().size.width,
			_size.height/2,
			_tWidth,
			_size.height));
	}
		break;
	case Base_SearchField::P_Right:
	{
		m_text->setCenter(CCRect(
			_tWidth/2,
			_size.height/2,
			_tWidth,
			_size.height));

		m_logo->setVisible(true);
		m_logo->setCenterOrigin(CCPoint(
			_dis + m_logo->getBounds().size.width / 2 + m_text->getBounds().size.width,
			_size.height/2));
	}
		break;
	case Base_SearchField::P_Null:
	{
		 m_logo->setVisible(false);
		 m_text->setCenter(CCRect(_size.width/2,_size.height/2,_size.width,_size.height));
	}
		break;
	default:
		break;
	}
	//textfield
// 	int _dis1 = _px(_dis) + m_logo->getCenter().size.width;
// 	int _width = rect.size.width - _dis1;
}

void Base_SearchField::ShowAllInfo()
{
	if (this->getSubviewByTag(99))
	{
		return;
	}


	this->setFrame(FitRect(0, 0, 640, 1136));

	Base_SearchInfo* _info = Base_SearchInfo::createWithFrame(this->getBounds());
	_info->SetDelagate(this);
	_info->setTag(99);
	this->addSubview(_info);

	SetTextCenter();
}

void Base_SearchField::hideAllInfo()
{
	//移除信息界面
	this->removeSubviewByTag(99);
	this->setCenter(m_oldRect);

	SetTextCenter();

	if (!m_searchCon)
	{
		//清空输入框
		m_text->setText("");
	}
}

void Base_SearchField::SetTextCenter()
{
	CAView* _bg = this->getSubviewByTag(100);
	
	_bg->setCenterOrigin(CCPoint(this->getBounds().size.width / 2,_bg->getCenterOrigin().y ));
}

void Base_SearchField::Callback_Chose(const std::string& _key)
{
	this->CallBack_Return();;

	//创建更多页面
	if (m_searchCon)
	{
		m_searchCon->SetTypeId(_key, true);
		m_searchCon->ReloadData();
	}
	else
	{
		UI_MoreViewContro* more = UI_MoreViewContro::create();
		more->SetTypeId(_key, true);

		m_nav->pushViewController(more, true);
	}
}




Base_SearchInfo* Base_SearchInfo::createWithFrame(const CCRect& rect)
{
	Base_SearchInfo* _base = new Base_SearchInfo();
	if (_base&&_base->initWithFrame(rect))
	{
		_base->autorelease();
		return _base;
	}

	CC_SAFE_RELEASE_NULL(_base);
	return NULL;
}

bool Base_SearchInfo::initWithFrame(const CCRect& rect)
{
	if (!CAView::initWithFrame(rect))
	{
		return false;
	}
	this->setColor(CAColor_clear);
	m_index[0] = 0;
	m_index[1] = 0;

	//search数据
	Data_Base::GetInstance()->GetSearch(m_hotKey[0]);

	//添加导航背景
	Base_View* _bg = Base_View::createWithFrame(CCRect(0, 0, FitX(640), _px(88)), CAColor_red);
	this->addSubview(_bg);


	m_tableView = Base_TableView::creat(CCRect(0, _px(88), FitX(640), getBounds().size.height - FitY(98)));
	m_tableView->setTableViewDataSource(this);
	m_tableView->setTableViewDelegate(this);
	this->addSubview(m_tableView);

	//添加按钮
	CAButton* _btn = CAButton::createWithCenter(CCRect(_px(50), _px(98 / 2), _px(54), _px(54)), CAButtonTypeCustom);
	_btn->setImageForState(CAControlStateNormal, CAImage::create("image/btn_left_n.png"));
	_btn->setImageForState(CAControlStateHighlighted, CAImage::create("image/btn_left_p.png"));
	_btn->addTarget(this, CAControl_selector(Base_SearchInfo::CallBack), CAControlEventTouchUpInSide);
	this->addSubview(_btn);

	//发送消息
	Data_HttpManage* _http = Data_HttpManage::GetInstance();
	_http->SendData(URL_HotKeyWord);
	_http->SetHttpCallBack(this, HttpManager_selector(Base_SearchInfo::CallBack_http_Main));
	return true;
}

void Base_SearchInfo::CallBack(CAControl* con, CCPoint po)
{
	m_delegate->CallBack_Return();
}

Base_SearchInfo::~Base_SearchInfo()
{
	Data_HttpManage::GetInstance()->RemoveHttpCallBack(this);
}

CATableViewCell* Base_SearchInfo::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	Base_Cell1* _cell = (Base_Cell1*)table->dequeueReusableCellWithIdentifier("cell");
	if (!_cell)
	{
		_cell = Base_Cell1::creatWith("cell");
		_cell->SetBgColor(ccc4(0xf2, 0xf2,  0xf2, 255));
	}

	
	GetLabel(_cell, section,cellSize);

	return _cell;
}

unsigned int Base_SearchInfo::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return FitY(125);
}

unsigned int Base_SearchInfo::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	int _size = m_hotKey[section].size();

	return _size/4 + (_size%4==0?0:1);
}

unsigned int Base_SearchInfo::numberOfSections(CATableView *table)
{
	return 2;
}

CAView* Base_SearchInfo::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	std::string _title[2] = { UTF8("最近搜索"), UTF8("热门搜索") };

	CAView* _view = CAView::createWithFrame(CCRect(0,0,viewSize.width,viewSize.height));

	//添加logo
	char logoPath[64] = "";
	sprintf(logoPath, "image/search-%d.png", section+3);
	Base_ImageView* _ima = Base_ImageView::creat(logoPath);
	_ima->setCenter(CCRect(FitX(20) + _px(30/2), viewSize.height / 2, _px(30), _px(27)));
	_view->addSubview(_ima);

	//添加文字
	CALabel* label = CALabel::createWithCenter(CCRect(FitX(60)+FitX(100), viewSize.height / 2, FitX(200), viewSize.height));
	label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	label->setTextAlignment(CATextAlignmentLeft);
	label->setColor(ccc4(0x0a, 0x0a, 0x0a, 255));
	label->setFontSize(_px(27));
	label->setText(_title[section]);
	_view->addSubview(label);

	//删除搜索记录
	if (section==0)
	{
		CAButton* _btn = CAButton::createWithCenter(CCRect(
			FitX(610) - _px(30 / 2), viewSize.height / 2, _px(35), _px(34)),
			CAButtonTypeCustom);
		_btn->addTarget(this, CAControl_selector(Base_SearchInfo::CallBack_delate),CAControlEventTouchUpInSide);
		_btn->setImageForState(CAControlStateNormal, CAImage::create("image/search-1.png"));
		_btn->setImageForState(CAControlStateHighlighted, CAImage::create("image/search-2.png"));
		_view->addSubview(_btn);
	}
	return _view;
}

unsigned int Base_SearchInfo::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return FitY(75);
}

void Base_SearchInfo::CallBack_http_Main(const char* msg)
{
	//清空数据
	m_hotKey[1].clear();

	Data_Json _json(msg);
	_json.Json_GetVecValue("keyword", m_hotKey[1]);

	this->ReloadData();
}

void Base_SearchInfo::CallBack_View(CAControl* con, CCPoint po)
{
	//获得文字lable
	CALabel* _label = (CALabel*)con->getSubviewByTag(100);
	std::string _key = _label->getText();

	//保存输入
	Data_Base::GetInstance()->PushSearch(_key);

	m_delegate->Callback_Chose(_key);
}

void Base_SearchInfo::CallBack_delate(CAControl* con, CCPoint po)
{
	Data_Base::GetInstance()->ClearSearch();
	Data_Base::GetInstance()->GetSearch(m_hotKey[0]);
	
	this->ReloadData();
}

void Base_SearchInfo::GetLabel(CATableViewCell* cell, int nType, CCSize _cellSize)
{
	while (true)
	{
		CAView* _bg = cell->getSubviewByTag(99);
		if (_bg)
		{
			_bg->removeFromSuperview();
		}
		else
		{
			break;
		}
	}

	if (m_index[nType]>=m_hotKey[nType].size())
	{
		return;
	}


	float _dis = FitX(50);
	float _wid = 0;
	for (size_t i = 0; ; i++)
	{
		if (m_index[nType] >= m_hotKey[nType].size())
		{
			break;
		}

		//计算lable长度
		std::u16string _16;
		StringUtils::UTF8ToUTF16(m_hotKey[nType][m_index[nType]], _16);
		_wid = FitX(123 + ((_16.size() - 2) <= 0 ? 0 : (_16.size() - 2)) * 25);
		if ((_cellSize.width - _dis - FitX(30)) <_wid)
		{
			break;
		}

		//背景
		Base_View* _bg = Base_View::create(); 
		_bg->setColor(ccc4(0xea, 0xea, 0xea, 255));
		_bg->setCenter(CCRect(
			_dis + _wid/2,
			_cellSize.height / 2,
			_wid,
			FitY(52)));
		_bg->AddTouchEvent(this, CAControl_selector(Base_SearchInfo::CallBack_View));
		_bg->setTag(99);
		cell->addSubview(_bg);

		//文字
		CALabel* label = CALabel::createWithFrame(_bg->getBounds());
		label->setTag(100);
		label->setText(m_hotKey[nType][m_index[nType]]);
		label->setFontSize(_px(24));
		label->setColor(ccc4(0x76, 0x76, 0x76, 255));
		label->setTextAlignment(CATextAlignmentCenter);
		label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		_bg->addSubview(label);

		_dis = _dis + _wid + FitX(20);
		m_index[nType] += 1;	
	}

}

void Base_SearchInfo::SetDelagate(Base_SearchDelegate* delagate)
{
	m_delegate = delagate;
}

void Base_SearchInfo::ReloadData()
{
	m_index[0] = 0;
	m_index[1] = 0;
	m_tableView->reloadData();
}
