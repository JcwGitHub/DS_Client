#ifndef BASE_TABLEVIEW_H
#define BASE_TABLEVIEW_H


#include "CrossApp.h"


class Base_TableView : public CATableView
{
public:
	//rect frame创建
	static Base_TableView* creat(const CCRect& rect);

private:
	bool	init(const CCRect& rect);
};

// 刷新
// class Base_PullReresh : public CAPullToRefreshView
// {
// public:
// protected:
// private:
// };
//tableview cell
//分类页面 左边cell使用
class Base_Cell : public CATableViewCell
{
public:
	static Base_Cell* creatWith(const std::string& key);

	void normalTableViewCell();

	void highlightedTableViewCell();

	void selectedTableViewCell();
protected:
private:
	bool init(const std::string& key);
};

//设置cell背景为透明
class Base_Cell1 : public CATableViewCell
{
public:
	static Base_Cell1* creatWith(const std::string& key);

	void SetBgColor(CAColor4B color);

	virtual void normalTableViewCell();

	virtual void highlightedTableViewCell();

	virtual void selectedTableViewCell();

	virtual void disabledTableViewCell();

private:
	bool initWith(const std::string& key);
private:
	CAColor4B			m_bgColor;
};
#endif