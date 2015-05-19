#include "Base_View.h"




Base_View* Base_View::createWithFrame(const CCRect& rect, const CAColor4B& color4B)
{
	Base_View* view = new Base_View();
	if (view&&view->initWithFrame(rect,color4B))
	{
		view->autorelease();
		return view;
	}

	CC_SAFE_RELEASE_NULL(view);
	return NULL;
}

bool Base_View::init()
{
	if (!CAView::init())
	{
		return false;
	}

	return true;
}

bool Base_View::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{

	return true;
}

void Base_View::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
	int a = 0;
}

void Base_View::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
	if (pTouch->isDelta())
	{
		return;
	}

	TouchUpInsid(pTouch->getLocation());
}

void Base_View::ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent)
{
	int a = 0;
}

void Base_View::AddTouchEvent(CAObject *target, SEL_CAControl selector)
{
	m_touchDelegate = target;
	m_sel = selector;
}

void Base_View::TouchUpInsid(CCPoint _point)
{
	if (m_touchDelegate&&m_sel)
	{
		(m_touchDelegate->*m_sel)((CAControl*)this, _point);
	}
}
