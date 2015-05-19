#ifndef BASE_SEARCHFIELD_H
#define BASE_SEARCHFIELD_H

#include "CrossApp.h"

//搜索框
class UI_MoreViewContro;
class Base_TableView;
class Base_ImageView;
class Base_View;

class Base_SearchDelegate
{
public:
	virtual void CallBack_Return() = 0;

	virtual void Callback_Chose(const std::string& _key) = 0;
};
class Base_SearchField : 
	public CAView, 
	public CATextFieldDelegate,
	Base_SearchDelegate
{
public:
	enum E_Logo_P
	{
		P_Left = 1,	//左边
		P_Right,	//右边
		P_Null		//不显示
	};
public:
	//rect 中心位置
	static Base_SearchField* Creat(const CCRect& rect);

	//设置文本
	void	SetTextField(const std::string& text) { m_text->setText(text);  }

	//设置搜索结果页面
	void	SetSearchResultCon(UI_MoreViewContro* con) { m_searchCon = con;  }

	//搜索logo位置
	void	SetSearchLogo(E_Logo_P position);

	//设置当前navbar
	void SetNavBar(CANavigationController* nav) { m_nav = nav; }




	//代理
	virtual bool onTextFieldAttachWithIME(CATextField * sender);
	virtual bool onTextFieldDetachWithIME(CATextField * sender);
	virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
	virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
	virtual bool keyBoardCallBack(CATextField *sender);

	virtual void CallBack_Return() { hideAllInfo();  }
	virtual void Callback_Chose(const std::string& _key);
private:
	bool init(const CCRect& rect);

	//显示全部信息
	void ShowAllInfo();

	//取消全部信息
	void hideAllInfo();

	//输入框居中
	void SetTextCenter();
private:
	CATextField*							m_text;
	Base_ImageView*					m_logo;

	//原有尺寸
	CCRect									m_oldRect;

	//在某个navbar上
	CANavigationController*		m_nav;

	UI_MoreViewContro*				m_searchCon;
};


class Base_SearchInfo :
	public CAView,
	public CATableViewDataSource,
	public CATableViewDelegate
{
public:
	~Base_SearchInfo();
	static Base_SearchInfo* createWithFrame(const CCRect& rect);

	void SetDelagate(Base_SearchDelegate* delagate);

	//取消输入框
	void CallBack(CAControl* con, CCPoint po);

	//获取热搜索
	void CallBack_http_Main(const char* msg);

	//选择标签
	void	CallBack_View(CAControl* con, CCPoint po);

	//删除历史记录
	void CallBack_delate(CAControl* con, CCPoint po);


	//代理
	//Necessary
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);

	virtual unsigned int numberOfSections(CATableView *table);

	virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);

	virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
private:
	bool initWithFrame(const CCRect& rect);

	//刷新数据
	void ReloadData();

	//ntype 0本地，1热搜
	void	GetLabel(CATableViewCell* cell, int nType,CCSize _cellSize);
private:
	Base_TableView*			m_tableView;

	Base_SearchDelegate*	m_delegate;

	vector<std::string>	   m_hotKey[2];

	int									m_index[2];
};
#endif