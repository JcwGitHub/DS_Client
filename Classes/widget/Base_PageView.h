#ifndef BASE_PAGEVIEW_H
#define BASE_PAGEVIEW_H

#include "CrossApp.h"



class Base_PageTag;
class Base_PageView : public CAPageView, public CAPageViewDelegate
{
public:
	static Base_PageView* creat(const CCRect& rect, const CAPageViewDirection& type);

	//设置页数
	void	SetPageViews(const CAVector<CAView*>& vec);

	//获取page contorl
	Base_PageTag* GetPageTag();

	//自动滑动
	void	SetAutoScroll(bool flag = true);

	//代理
	virtual void pageViewDidBeginTurning(CAPageView* pageView);

	virtual void pageViewDidEndTurning(CAPageView* pageView);

	virtual void pageViewDidSelectPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point);
private:
	bool init(const CCRect& rect, const CAPageViewDirection& type);

	void ChangePage();

	void updateImage(float dt);
private:
	Base_PageTag*	m_pageTag;

	bool	m_autoScroll;

	//前三位置
	int				m_atIndex;

	//前三个坐标不变
	CCPoint			m_point[3];
	
	vector<CAView*>	m_views;
};


//page底页标签

class Base_PageTag : public CAView
{
public:
	static Base_PageTag* creat(int nums);


	void SetCurIndex(int index);
private:
	bool init(int nums);
private:

};
#endif