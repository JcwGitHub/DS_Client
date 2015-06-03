#include "UI_MainView2.h"
#include "UI_Goods.h"

bool UI_MainView2::init()
{
	m_typeIndex = 0;

	this->getView()->setColor(CAColor_clear);
	this->setTitle(UTF8(" "));
	return true;
}

void UI_MainView2::viewDidLoad()
{
	//添加左边table
	m_left = Base_TableView::creat(FitRect(0, 0, 160, 1136 - DATA_BASE->m_NarBar_H - DATA_BASE->m_TabBar_H));
	//m_left->setShowsVerticalScrollIndicator(false);
	m_left->setAllowsSelection(true);
	m_left->setTableViewDataSource(this);
	m_left->setTableViewDelegate(this);
	m_left->setTag(1000);
	this->getView()->addSubview(m_left);

	//添加右边table
	m_right = Base_TableView::creat(FitRect(160, 20, 640-160, 1136 - DATA_BASE->m_NarBar_H - DATA_BASE->m_TabBar_H));
	m_right->setSeparatorColor(CAColor_clear);
	m_right->setTableViewDataSource(this);
	m_right->setTableViewDelegate(this);
	m_right->setTag(1001);
	this->getView()->addSubview(m_right);

	m_pNavigationController->setNavigationBarBackGroundColor(CAColor_red);

	//中间输入框
	Base_NavBar* Bar = (Base_NavBar*)this->getNavigationController();
	Base_SearchField* _text = Base_SearchField::Creat(CCRect(
		Bar->GetLastContainer()->getBounds().size.width / 2,
		Bar->GetLastContainer()->getBounds().size.height / 2, _px(410), _px(68)));
	_text->SetNavBar(Bar);
	Bar->BarAddSubView(_text);

	//发送消息
	Data_HttpManage* _http = Data_HttpManage::GetInstance();
	_http->SendData(URL_TypeList);
	_http->SetHttpCallBack(this, HttpManager_selector(UI_MainView2::CallBack_http_Left));

	CAViewController::viewDidLoad();
}

void UI_MainView2::CallBack_http_Left(const char* msg)
{
	Data_Json _json(msg);
	Data_Json::Json_Vec_Dic _vecList;
	S_TypeList _list;
	S_Good     _goods;

	_json.Json_GetVecValue("lists", _vecList);
	for (size_t i = 0; i < _vecList.size(); i++)
	{
		_list._goods.clear();
		_vecList[i]->Json_GetStrValue("typeid", _list._typeId);
		_vecList[i]->Json_GetStrValue("typename", _list._typeName);
		// 		_vecList[i]->Json_GetStrValue("shopid", _goods._shopId);
		// 		_vecList[i]->Json_GetStrValue("pic", _goods._pic);
		// 		_vecList[i]->Json_GetStrValue("shopname", _goods._shopname);
		// 		_vecList[i]->Json_GetStrValue("shopprice", _goods._shopprice);
		// 		_vecList[i]->Json_GetStrValue("lsr", _goods._lsr);
		// 		_vecList[i]->Json_GetStrValue("lsrtime", _goods._lsrtime);

		m_typeList.push_back(_list);
	}


	//刷新左边数据
	m_left->reloadData();
	m_left->setSelectRowAtIndexPath(0, 0);
	tableViewDidSelectRowAtIndexPath(m_left,0,0);
}

void UI_MainView2::CallBack_http_Right(const char* msg)
{
	Data_Json _json(msg);

	Data_Json::Json_Vec_Dic _josnVec;
	S_Good					_good;

	_json.Json_GetVecValue("lists", _josnVec);
	for (size_t i = 0; i < _josnVec.size(); i++)
	{
		_josnVec[i]->Json_GetStrValue("shopid", _good._shopId);
		_josnVec[i]->Json_GetStrValue("pic", _good._pic);
		_josnVec[i]->Json_GetStrValue("shopname", _good._shopname);
		_josnVec[i]->Json_GetStrValue("shopprice", _good._shopprice);
		_josnVec[i]->Json_GetStrValue("lsr", _good._lsr);
		_josnVec[i]->Json_GetStrValue("lsrtime", _good._lsrtime);

		m_typeList[m_typeIndex]._goods.push_back(_good);
	}


	//刷新右边数据
	m_right->reloadData();
}

void UI_MainView2::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	if (table->getTag() == 1000)
	{
		//left
		m_typeIndex = row;

		int _size = m_typeList[row]._goods.size();
		if (_size<1)
		{
			//发送消息
			Data_HttpManage* _http = Data_HttpManage::GetInstance();
			_http->PushPostData("typeid",m_typeList[row]._typeId);
			_http->PushPostData("pageshow", PageNums);
			_http->PushPostData("page", _size/PageNums + 1);
			_http->SendData(URL_TypeShopList);
			_http->SetHttpCallBack(this, HttpManager_selector(UI_MainView2::CallBack_http_Right));
		}
		else
		{
			m_right->reloadData();
		}
	}
}

void UI_MainView2::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	if (table->getTag() == 1000)
	{
		//left
	}
	else
	{

	}
}

CATableViewCell* UI_MainView2::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	int _tag = table->getTag();
	std::string _key = _tag == 1000 ? "cellLeft" : "cellRight";
	CATableViewCell* _cell = table->dequeueReusableCellWithIdentifier(_key.c_str());

	if ( _tag == 1000 )
	{
		//left
		if (!_cell)
		{
			_cell = Base_Cell::creatWith(_key.c_str());
			CALabel* label = CALabel::createWithCenter(CCRect(cellSize.width/2, cellSize.height / 2, cellSize.width, cellSize.height));
			label->setTag(100);
			label->setFontSize(_px(24));
			label->setText("");
			label->setTextAlignment(CATextAlignmentCenter);
			label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
			_cell->addSubview(label);
		}

		CALabel* label = (CALabel*)_cell->getSubviewByTag(100);
		label->setText(m_typeList[row]._typeName);
	}
	else
	{
		if (!_cell)
		{
			_cell = CATableViewCell::create(_key.c_str());

			//图片尺寸
			CCSize _size = FitSize(208, 208);


			for (size_t i = 0; i < 2; i++)
			{
				UI_Goods* goods = UI_Goods::creat(CCRect(
					table->getBounds().size.width / 4 + (table->getBounds().size.width / 2) * i,
					cellSize.height/2,
					_size.width,
					cellSize.height),_size);

				goods->SetNavBar(this->getNavigationController());
				goods->setTag(100 + i);
				_cell->addSubview(goods);
			}
		}

		for (size_t i = 0; i < 2; i++)
		{
			UI_Goods* goods = (UI_Goods*)_cell->getSubviewByTag(100 + i);

			int _nums = row * 2 + i;
			if (_nums >= (m_typeList[m_typeIndex]._goods.size()))
			{
				//超过数量
				goods->setVisible(false);
			}
			else
			{
				goods->setVisible(true);
				goods->SetGoodsInfo(m_typeList[m_typeIndex]._goods[_nums]);
			}

		}
	}

	return _cell;
}

unsigned int UI_MainView2::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	if (table->getTag()==1000)
	{
		//left
		return FitY(row == 0 ? 120 : 100);
	}
	else
	{
		return FitY(208 + 86);
	}
}

unsigned int UI_MainView2::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	if (table->getTag() == 1000)
	{
		//left
		return m_typeList.size();
	}
	else
	{
		if (m_typeIndex<m_typeList.size())
		{
			int _size = m_typeList[m_typeIndex]._goods.size();
			return  _size % 2 == 0 ? _size / 2 : _size / 2 + 1;
		}
	}

	return 0;
}
