#include "UI_MainView1.h"
#include "RootWindow.h"
#include "UI_Goods.h"
#include "UI_MoreView.h"




bool UI_MainView1::init()
{
	this->getView()->setColor(CAColor_white);
	this->setTitle(" ");
	return true;
}

void UI_MainView1::viewDidLoad()
{
	m_pNavigationController->setNavigationBarBackGroundColor(CAColor_red);

	//中间输入框
	Base_NavBar* Bar = (Base_NavBar*)this->getNavigationController();
	Base_SearchField* _text = Base_SearchField::Creat(CCRect(
		Bar->GetLastContainer()->getBounds().size.width / 2,
		Bar->GetLastContainer()->getBounds().size.height / 2, _px(410), _px(55)));
	_text->SetSearchLogo(Base_SearchField::P_Right);
	_text->SetNavBar(Bar);
	Bar->BarAddSubView(_text);


	//发送消息
	Data_HttpManage* _http = Data_HttpManage::GetInstance();
	_http->SendData(URL_index);
	_http->SetHttpCallBack(this,HttpManager_selector(UI_MainView1::CallBack_http_Main));

	CAViewController::viewDidLoad();
}

// void UI_MainView1::btnCallBack(CAControl *sender, CCPoint pos)
// {
// 	
// // 	UI_MainView2* view2 = UI_MainView2::create();
// // 
// // 	this->getNavigationController()->pushViewController(view2,true);
// // 	CAView*view = CAView::createWithColor(CAColor_black);
// // 	view->setFrame(CCRectMake(0,0,640,960));
// // 	CAApplication::getApplication()->getRootWindow()->insertSubview(view, CAWindowZoderTop);
// // 	this->dismissModalViewController(true);
// }



void UI_MainView1::CallBack_Left(CAControl *sender, CCPoint pos)
{
	S_Root_Window->S_MainDrawCon->showLeftViewController(true);
}

void UI_MainView1::CallBack_http_Main(const char* msg)
{
	//处理首页数据
	DealData(msg);

	//加载滚动层
 	SetRollView();
// 	Base_ImageView* url = Base_ImageView::CreatWithUrl("http://img.uuu.net/207/10091/10031/10108/D068817080A7E861D4D6BCE46A775067.jpg");
// 	url->setCenterOrigin(CCPointMake(200,200));
// 	this->getView()->addSubview(url);

	//加载商品层
	SetListView();
}

void UI_MainView1::DealData(const char* msg)
{
	m_vecBanner.clear();
	m_vecList.clear();

	Data_Json::Json_Vec_Dic _josnVec;
	Data_Json::Json_Vec_Dic	_josnVec1;
	
	S_Banner				_banner;
	S_List					_lists;
	Data_Json				_josn(msg);


	//banner
	_josn.Json_GetVecValue("banner",_josnVec);
	for (size_t i = 0; i < _josnVec.size(); i++)
	{
		_josnVec[i]->Json_GetStrValue("pic", _banner._pic);
		_josnVec[i]->Json_GetStrValue("shopid", _banner._shopId);
		m_vecBanner.push_back(_banner);
	}

	//商品列表
	_josn.Json_GetVecValue("typelists", _josnVec);
	for (size_t i = 0; i < _josnVec.size(); i++)
	{
		//每个分类
		_lists._lists.clear();

		if (i == 0)
		{_lists._isOpen = true;}
		else
		{_lists._isOpen = false;}
		_josnVec[i]->Json_GetStrValue("typeid", _lists._typeId);
		_josnVec[i]->Json_GetStrValue("typename", _lists._typeName);
		_josnVec[i]->Json_GetVecValue("lists", _josnVec1);

		//_jsonVec1  该分类商品数
		for (size_t i = 0; i < _josnVec1.size(); i++)
		{
			if (i>=One_Page_Max) break;  //最多显示6个

			S_Good					_good;
			_josnVec1[i]->Json_GetStrValue("shopid", _good._shopId);
			_josnVec1[i]->Json_GetStrValue("pic", _good._pic);
			_josnVec1[i]->Json_GetStrValue("shopname", _good._shopname);
			_josnVec1[i]->Json_GetStrValue("shopprice", _good._shopprice);
			_josnVec1[i]->Json_GetStrValue("lsr", _good._lsr);
			_josnVec1[i]->Json_GetStrValue("lsrtime", _good._lsrtime);

			_lists._lists.push_back(_good);
		}

		m_vecList.push_back(_lists);
	}
}

void UI_MainView1::SetListView()
{
	m_listView = Base_TableView::creat(FitRect(0,202,640,1136-210-98-98));
	m_listView->setTableViewDataSource(this);
	m_listView->setTableViewDelegate(this);
	m_listView->setSeparatorColor(CAColor_white);
	this->getView()->addSubview(m_listView);
}
void UI_MainView1::SetRollView()
{
	CCSize _dSize = FitSize(640, 210);

	CAVector<CAView*> _temp;
	for (size_t i = 0; i < m_vecBanner.size(); i++)
	{
		Base_ImageView* _ima = Base_ImageView::CreatWithUrl(m_vecBanner[i]._pic);
		_temp.pushBack(_ima);
	}

	m_pageView = Base_PageView::creat(CCRect(_dSize.width/2,_dSize.height/2,_dSize.width,_dSize.height),
		CAPageView::CAPageViewDirectionHorizontal);
	m_pageView->SetPageViews(_temp);
	m_pageView->SetAutoScroll(true);
	this->getView()->addSubview(m_pageView);


	//添加tag
	this->getView()->addSubview(m_pageView->GetPageTag());
}

CATableViewCell* UI_MainView1::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	std::string _key = "cell";
	CATableViewCell* _cell = table->dequeueReusableCellWithIdentifier(_key.c_str());
	if (!_cell)
	{
		_cell = CATableViewCell::create(_key.c_str());

		CCSize _size = FitSize(184, 134);


		for (size_t i = 0; i < 3; i++)
		{
			UI_Goods* goods = UI_Goods::creat(FitRect(
				22+184/2 + (184+22)*i,
				241/2,
				184,
				241),_size);

			goods->SetNavBar(this->getNavigationController());
			goods->setTag(100 + i);
			_cell->addSubview(goods);
		}
	}


	for (size_t i = 0; i < 3; i++)
	{
		UI_Goods* goods = (UI_Goods*)_cell->getSubviewByTag(100 + i);

		int _nums = row * 3 + i;
		if (_nums>=(m_vecList[section]._lists.size()))
		{
			//超过数量
			goods->setVisible(false);
		}
 		else
		{
			goods->setVisible(true);
			goods->SetGoodsInfo(m_vecList[section]._lists[_nums]);
		}

	}

	return _cell;
}

unsigned int UI_MainView1::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return FitY(241);
}

unsigned int UI_MainView1::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	if (m_vecList[section]._isOpen)
	{
		return m_vecList[section]._lists.size() / 3 + (m_vecList[section]._lists.size()%3==0?0:1);
	}

	return 0;
}

unsigned int UI_MainView1::numberOfSections(CATableView *table)
{
	return m_vecList.size();
}

CAView* UI_MainView1::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	Base_View* view = Base_View::create();
	view->setColor(CAColor_clear);
	view->setTag(1000 + section);

	


	char logoPath[64] = "";

	//当前状态
	if (!m_vecList[section]._isOpen)
	{
		//导航事件
		view->AddTouchEvent(this, CAControl_selector(UI_MainView1::CallBack_Down));

		//没打开
		Base_ImageView* _line = Base_ImageView::creat("image/m_t_list.png");
		_line->setFrame(FitRect(640 - 540, 62,540,1));
		view->addSubview(_line);

		//类型图片
		Base_ImageView*ima = Base_ImageView::creat("image/m_t_list4.png");
		ima->setCenter(CCRect(FitX(640 - 20), FitY(62 / 2), _px(24), _px(13)));
		view->addSubview(ima);

		sprintf(logoPath, "image/m_t_list%d.png", section);
	}
	else
	{
		//导航事件
		view->AddTouchEvent(this, CAControl_selector(UI_MainView1::CallBack_More));

		//类型图片
		Base_ImageView*ima = Base_ImageView::creat("image/m_t_list_r.png");
		ima->setCenter(FitRect(610, 62 / 2, 50, 10));
		view->addSubview(ima);

		sprintf(logoPath, "image/m_t_list%dp.png", section);
	}

	//logo背景线
	Base_ImageView* _line = Base_ImageView::creat("image/m_t_list_l.png");
	_line->setCenter(FitRect(50, 62 / 2, 2, 61));
	view->addSubview(_line);


	//类型logo
	Base_ImageView* _logo = Base_ImageView::creat(logoPath);
	_logo->setCenter(CCRect(FitX(50), FitY(62 / 2), _px(45), _px(45)));
	_logo->setTag(1000);
	view->addSubview(_logo);

	//类型名
	CALabel* header = CALabel::createWithCenter(FitRect(150, 62/2, 100, 62));
	header->setFontSize(_px(27));
	header->setText(m_vecList[section]._typeName);
	header->setTextAlignment(CATextAlignmentLeft);
	header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	view->addSubview(header);
	return view;
}

void UI_MainView1::CallBack_Down(CAControl *sender, CCPoint pos)
{
	int _section = sender->getTag() - 1000;
	if (m_vecList[_section]._isOpen)
	{
		return;
	}

	for (size_t i = 0; i < m_vecList.size(); i++)
	{
		m_vecList[i]._isOpen = _section == i ? true : false;
	}


	m_listView->reloadData();
}

void UI_MainView1::CallBack_More(CAControl *sender, CCPoint pos)
{
	//创建更多页面
	UI_MoreViewContro* more = UI_MoreViewContro::create();
	for (size_t i = 0; i < m_vecList.size(); i++)
	{
		if (m_vecList[i]._isOpen)
		{
			more->SetTypeId(m_vecList[i]._typeId);
			break;
		}
	}
	this->getNavigationController()->pushViewController(more,true);	
}

unsigned int UI_MainView1::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return FitY(62);
}

void UI_MainView1::reshapeViewRectDidFinish()
{
	CCLog("reshape");
}