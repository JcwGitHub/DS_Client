#ifndef UI_MOREVIEW_H
#define UI_MOREVIEW_H


#include "Data_Define.h"
#define OnePageNums 6
class UI_MoreViewContro : 
	public Base_ViewController,
	CATableViewDataSource,
	CATableViewDelegate,
	CAScrollViewDelegate
{
public:
	CREATE_FUNC(UI_MoreViewContro);

	//设置商品类型id
	void	SetTypeId(const std::string& typeId, bool isHotKey = false);

	//设置排序方式
	//nType 0综合，1销量，2价格
	//nSorts 0正序，1倒序
	void	SetSort(int nType, int nSorts);

	//回调函数
	void	CallBack_Goods(const char* msg);
	
	//重新舒心数据
	void	ReloadData();
protected:
	//Necessary
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	//Necessary
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);

	virtual void scrollViewHeaderBeginRefreshing(CAScrollView* view);

	virtual void scrollViewFooterBeginRefreshing(CAScrollView* view);
private:
	bool init();

	virtual void viewDidLoad();

	//设置tableview背景
	void	SetTableViewBgColor();

	//发送消息
	void	SendMessage_Goods();

	void AddSearchNothing(bool flag = true);
private:
	int												 m_sort[4];

	int												 m_sortIndex;

	bool												 m_isHotKey;

	std::string									 m_typeId;

	std::string									 m_mapKey;

	//数据类型
	map<std::string,vec_Goods>	 m_goods;

	//tableview
	Base_TableView*						 m_tableView;

	//搜索页面显示
	Base_SearchField*						m_searchText;
};

class UI_HeadContorll : public Base_View
{
public:
	static UI_HeadContorll* createFrame(CCRect rect,int index);

	void SetDelegate(UI_MoreViewContro* deleagte) { m_delegate = deleagte; }
protected:
	virtual void TouchUpInsid(CCPoint _point);

private:
	bool init(CCRect rect,int index);

private:
	//是否为降序(正序)
	bool		m_isDown[4];

	UI_MoreViewContro* m_delegate;
};
#endif