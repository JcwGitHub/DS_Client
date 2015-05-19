#ifndef UI_MAIN_VIEW_2_H
#define UI_MAIN_VIEW_2_H

#include "Data_Define.h"


class UI_MainView2 : 
	public CAViewController, 
	public CATableViewDataSource,
	public CATableViewDelegate
{
public:
	//每页商品数
#define  PageNums 20 

public:
	CREATE_FUNC(UI_MainView2);


	//回调函数
	void CallBack_http_Left(const char* msg);

	void CallBack_http_Right(const char* msg);
public:
	//代理
	virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	//Necessary
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
private:
	bool init();
	virtual void viewDidLoad();
private:
	Base_TableView* m_left;
	Base_TableView* m_right;

	//数据
	vec_TypeList	m_typeList;

	//当前查看id
	int				m_typeIndex;
};
#endif