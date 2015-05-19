#ifndef UI_MAIN_VIEW_1_H
#define UI_MAIN_VIEW_1_H

#include "Data_Define.h"


class UI_MainView1 : public CAViewController, 
					 public CATableViewDataSource, 
				     public CATableViewDelegate
{
public:
#define One_Page_Max 6

public:
	CREATE_FUNC(UI_MainView1);

public:
	//回调函数
	void CallBack_Left(CAControl *sender, CCPoint pos);

	//列表下拉按钮
	void CallBack_Down(CAControl *sender, CCPoint pos);

	//类型  更多
	void CallBack_More(CAControl *sender, CCPoint pos);

	//http返回回调函数
	void CallBack_http_Main(const char* msg);
public:
	//代理
	//Necessary
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int	 tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int	 numberOfRowsInSection(CATableView *table, unsigned int section);

	virtual unsigned int	 numberOfSections(CATableView *table);

	virtual CAView*			 tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);

	virtual unsigned int	 tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
private:
	virtual void	viewDidLoad();
	virtual void reshapeViewRectDidFinish();
	bool			init();

	//数据
	void			DealData(const char* msg);

	//滚动列表
	void			SetRollView();

	//活动
	void			SetListView();
private:
	Base_PageView*		m_pageView;

	Base_TableView*		m_listView;

	vec_Banner			m_vecBanner;

	vec_Lists			m_vecList;
};



#endif