#include "UI_MoreView.h"
#include "UI_Goods.h"

bool UI_MoreViewContro::init()
{
	if (!Base_ViewController::init())
	{
		return false;
	}

	this->setTitle(UTF8("更多商品"));

	//默认类型
	for (size_t i = 0; i < 4; i++)
	{
		m_sort[i] = 0;
	}
	return true;
}

void UI_MoreViewContro::viewDidLoad()
{
	if (m_isHotKey)
	{
		//添加search
		Base_NavBar* Bar = (Base_NavBar*)this->getNavigationController();
		m_searchText = Base_SearchField::Creat(CCRect(
			Bar->GetLastContainer()->getBounds().size.width / 2, 
			Bar->GetLastContainer()->getBounds().size.height / 2, _px(410), _px(68)));
		m_searchText->SetNavBar(Bar);
		m_searchText->SetSearchResultCon(this);
		Bar->BarAddSubView(m_searchText);
	}


	//选择头
	UI_HeadContorll* head = UI_HeadContorll::createFrame(FitRect(0,0,640,100),4);
	head->SetDelegate(this);
	this->getView()->addSubview(head);

	//tableview
	m_tableView = Base_TableView::creat(FitRect(0, 100, 640, 1136 - DATA_BASE->m_NarBar_H - DATA_BASE->m_TabBar_H - 100));
	//m_left->setShowsVerticalScrollIndicator(false);
	m_tableView->setAllowsSelection(false);
	m_tableView->setTableViewDataSource(this);
	m_tableView->setTableViewDelegate(this);
	m_tableView->setScrollViewDelegate(this);
	this->getView()->addSubview(m_tableView);

	//head
	CAPullToRefreshView* _pull = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeHeader);
	m_tableView->setFooterRefreshView(_pull);

	
	ReloadData();
	Base_ViewController::viewDidLoad();
}
void UI_MoreViewContro::CallBack_Goods(const char* msg)
{
	std::string _key = C_IntToString(m_sortIndex) + C_IntToString(m_sort[m_sortIndex]) + C_IntToString(m_sort[3]);
	map<std::string, vec_Goods>::iterator _itor;
	_itor = m_goods.find(_key);
	if (_itor == m_goods.end())
	{
		return;
	}

	Data_Json::Json_Vec_Dic   _josnVec;
	Data_Json							_josn(msg);

	//商品列表
	_josn.Json_GetVecValue("lists", _josnVec);

		//_jsonVec1  该分类商品数
	for (size_t i = 0; i < _josnVec.size(); i++)
	{
		S_Good					_good;
		_josnVec[i]->Json_GetStrValue("shopid", _good._shopId);
		_josnVec[i]->Json_GetStrValue("pic", _good._pic);
		_josnVec[i]->Json_GetStrValue("shopname", _good._shopname);
		_josnVec[i]->Json_GetStrValue("shopprice", _good._shopprice);
		_josnVec[i]->Json_GetStrValue("lsr", _good._lsr);
		_josnVec[i]->Json_GetStrValue("lsrtime", _good._lsrtime);

		_itor->second.push_back(_good);
	}


	//刷新数据
	SetTableViewBgColor();
	m_tableView->reloadData();
	if (_josnVec.size()==0)
	{
		//表示无数据
		if (_key == "000"
			&&_itor->second.empty()
			&&m_isHotKey)
		{
			AddSearchNothing();
		}
	}
}

void UI_MoreViewContro::SetSort(int nType, int nSorts)
{
	if (nType!=3)
	{
		m_sortIndex = nType;
		m_sort[m_sortIndex] = nSorts;
	}
	else
	{
		m_sort[3] = nSorts;
	}
	

	//key 类型 + 升降 + 图文
	m_mapKey  = C_IntToString(m_sortIndex) + C_IntToString(m_sort[m_sortIndex]) + C_IntToString(m_sort[3]);
	map<std::string, vec_Goods>::iterator _itor;
	_itor = m_goods.find(m_mapKey);
	if (_itor==m_goods.end())
	{
		vec_Goods _goods;
		m_goods[m_mapKey] = _goods;


		SendMessage_Goods();
	}
	else
	{
		SetTableViewBgColor();
		m_tableView->reloadData();
	}
}

void UI_MoreViewContro::SendMessage_Goods()
{
	//清空预留消息
	Data_HttpManage::GetInstance()->RemoveHttpCallBack(this);

	map<std::string, vec_Goods>::iterator _itor;
	_itor = m_goods.find(m_mapKey);
	if (_itor == m_goods.end())
	{
		return;
	}

	int nums = m_goods[m_mapKey].size() / OnePageNums + 1 + (m_goods[m_mapKey].size() % OnePageNums == 0 ? 0 : 1);

	//发送消息
	Data_HttpManage* _http = Data_HttpManage::GetInstance();
	if (m_isHotKey)
		_http->PushPostData("keyword", m_typeId);
	else
		_http->PushPostData("acid", m_typeId);

	_http->PushPostData("ordertype", m_sortIndex+1);
	_http->PushPostData("pageshow", OnePageNums);
	_http->PushPostData("page", nums);
	_http->PushPostData("mode", m_sort[3]+1);
	_http->PushPostData("orderby", m_sort[m_sortIndex]);

	if (m_isHotKey)
		_http->SendData(URL_SerchList);
	else
		_http->SendData(URL_ActivShop);
	
	_http->SetHttpCallBack(this, HttpManager_selector(UI_MoreViewContro::CallBack_Goods));
}

void UI_MoreViewContro::SetTableViewBgColor()
{
	if (m_sort[3]==0)
	{
		m_tableView->setBackGroundColor(CAColor_clear);
	}
	else
	{
		m_tableView->setBackGroundColor(ccc4(0x9b, 0x9b, 0x9b, 255));
	}
}

CATableViewCell* UI_MoreViewContro::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	map<std::string, vec_Goods>::iterator _itor;
	_itor = m_goods.find(m_mapKey);
	if (_itor == m_goods.end())
	{
		return NULL;
	}

	CATableViewCell* _cell;


	//图文显示
	if (m_sort[3]==0)
	{
		_cell = table->dequeueReusableCellWithIdentifier("cell");
		if (!_cell)
		{
			_cell = Base_Cell1::creatWith("cell");

			//图片尺寸
			CCSize _size = FitSize(243, 243);
			UI_Goods* goods = UI_Goods::creat(FitRect(320, 243/2 +10, 600, 243), _size, 1);

			goods->SetNavBar(this->getNavigationController());
			goods->setTag(100);
			_cell->addSubview(goods);
		}

		UI_Goods* goods = (UI_Goods*)_cell->getSubviewByTag(100);
		goods->SetGoodsInfo(_itor->second[row]);
	}









	//大图显示
	else
	{
		_cell = table->dequeueReusableCellWithIdentifier("cell1");
		if (!_cell)
		{
			_cell = Base_Cell1::creatWith("cell1");
			//图片尺寸
			CCSize _size = FitSize(300, 288);


			for (size_t i = 0; i < 2; i++)
			{
				UI_Goods* goods = UI_Goods::creat(CCRect(
					table->getBounds().size.width / 4 + (table->getBounds().size.width / 2) * i,
					cellSize.height / 2 + _px(20),
					_size.width,
					cellSize.height - _px(20)), _size);

				goods->SetNavBar(this->getNavigationController());
				goods->setTag(100 + i);
				_cell->addSubview(goods);
			}
		}

		//设置属性
		for (size_t i = 0; i < 2; i++)
		{
			UI_Goods* goods = (UI_Goods*)_cell->getSubviewByTag(100 + i);

			int _nums = row * 2 + i;
			if (_nums >= (_itor->second.size()))
			{
				//超过数量
				goods->setVisible(false);
			}
			else
			{
				goods->setVisible(true);
				goods->SetGoodsInfo(_itor->second[_nums]);
			}

		}
	}

	return _cell;
}

unsigned int UI_MoreViewContro::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	if (m_sort[3]==0)
	{
		//图文
		return FitY(253);
	}
	else
	{
		return FitY(504);
	}
}

unsigned int UI_MoreViewContro::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	map<std::string, vec_Goods>::iterator _itor;
	_itor = m_goods.find(m_mapKey);
	if (_itor == m_goods.end())
	{
		return 0;
	}

	if (m_sort[3]==0)
	{
		return _itor->second.size();
	}


	return _itor->second.size()/2;
}

void UI_MoreViewContro::scrollViewHeaderBeginRefreshing(CAScrollView* view)
{

}

void UI_MoreViewContro::scrollViewFooterBeginRefreshing(CAScrollView* view)
{
	SendMessage_Goods();
}

void UI_MoreViewContro::AddSearchNothing(bool flag /*= true*/)
{
	
	if (flag)
	{
		if (this->getView()->getSubviewByTag(200))
		{
			return;
		}

		Base_View* view = Base_View::createWithFrame(this->getView()->getBounds(), CAColor_white);
		view->setTag(200);
		this->getView()->addSubview(view);

		//图片
		Base_ImageView* _image = Base_ImageView::creat("image/search-5.png");
		_image->setFrame(CCRect(
			FitX(118),
			FitY(209),
			_px(385),_px(364)));
		view->addSubview(_image);

		//文字
		CALabel* label = CALabel::createWithFrame(CCRect(
			FitX(118),
			FitY(258) + _image->getBounds().size.height,
			FitX(500), FitY(50)));

		label->setFontSize(_px(36));
		label->setColor(ccc4(0x0a, 0x0a, 0x0a, 255));
		label->setText(UTF8("暂时没有您搜索的商品哦~"));
		view->addSubview(label);
		return;
	}
	else
	{
		this->getView()->removeSubviewByTag(200);
	}
}

void UI_MoreViewContro::SetTypeId(const std::string& typeId, bool isHotKey /*= false*/)
{
	m_typeId = typeId; 
	m_isHotKey = isHotKey; 
}

void UI_MoreViewContro::ReloadData()
{
	//清除数据
	m_goods.clear();

	//综合 正序
	SetSort(0, 0);
	SetTableViewBgColor();

	if (m_isHotKey)
	{
		//显示输入框内容
		m_searchText->SetTextField(m_typeId);
	}

	AddSearchNothing(false);
}

//标题头

UI_HeadContorll* UI_HeadContorll::createFrame(CCRect rect, int index)
{
	UI_HeadContorll* head = new UI_HeadContorll();
	if (head&&head->init(rect,index))
	{
		head->autorelease();
		return head;
	}

	CC_SAFE_RELEASE_NULL(head);
	return NULL;
}

bool UI_HeadContorll::init(CCRect rect,int index)
{
	if (!Base_View::initWithFrame(rect, CAColor_white))
	{
		return false;
	}

	std::string title[4] = { UTF8("综合"), UTF8("销量"), UTF8("价格"), UTF8(" ") };

	//创建分割线,title
	for (size_t i = 0; i < index; i++)
	{
		m_isDown[i] = true;

		Base_ImageView* ima = Base_ImageView::creat("image/m_t_list_l.png");
		ima->setCenter(CCRect(rect.size.width / 4 * i, rect.size.height/2, FitX(2), rect.size.height/2));
		this->addSubview(ima);

		//文字
		CALabel* label = CALabel::createWithCenter(CCRect(
			rect.size.width / index/2 + (rect.size.width /index)*i, 
			rect.size.height/2,
			rect.size.width / index, rect.size.height));

		label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		label->setTextAlignment(CATextAlignmentCenter);
		label->setColor(ccc4(0x3d, 0x42, 0x45, 255));
		label->setFontSize(_px(30));
		label->setText(title[i]);
		this->addSubview(label);

		//箭头 tag 100-103  前三个有箭头
		if (i!=3)
		{
			ima = Base_ImageView::creat("image/m_t_list4.png");
			ima->setCenter(CCRect(
				rect.size.width / 4 * (i + 1) - FitX(24),
				rect.size.height / 2,
				_px(24),
				_px(13)));
			ima->setTag(100 + i);
			this->addSubview(ima);
		}
		else
		{
			ima = Base_ImageView::creat("image/f-1.png");
			ima->setCenter(CCRect(
				rect.size.width / 4 * (i + 1) - FitX(50),
				rect.size.height / 2,
				_px(40),
				_px(40)));
			ima->setTag(100 + i);
			this->addSubview(ima);
		}
	}

	

	return true;
}

void UI_HeadContorll::TouchUpInsid(CCPoint _point)
{
	Base_View::TouchUpInsid(_point);

	int _index = (int)(_point.x / (this->getBounds().size.width / 4));
	m_isDown[_index] = !m_isDown[_index];

	Base_ImageView* _view = (Base_ImageView*)this->getSubviewByTag(_index + 100);
	if (_index < 3)
		_view->setRotation(_view->getRotation() + 180);
	else
	{
		std::string str = "image/f-2.png";
		if (m_isDown[_index])
			str = "image/f-1.png";
		_view->setImage(CAImage::create(str));
	}
		
	//通知
	int sortType = m_isDown[_index] == true ? 0 : 1;
	m_delegate->SetSort(_index, sortType);
}
