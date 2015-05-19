#ifndef BASE_TABLEVIEW_H
#define BASE_TABLEVIEW_H


#include "CrossApp.h"


class Base_TableView : public CATableView
{
public:
	//rect frame����
	static Base_TableView* creat(const CCRect& rect);

private:
	bool	init(const CCRect& rect);
};

// ˢ��
// class Base_PullReresh : public CAPullToRefreshView
// {
// public:
// protected:
// private:
// };
//tableview cell
//����ҳ�� ���cellʹ��
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

//����cell����Ϊ͸��
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