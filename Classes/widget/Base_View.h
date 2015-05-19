#ifndef BASE_VIEW_H
#define BASE_VIEW_H


#include "CrossApp.h"

class Base_View : public CAView
{
public:
	Base_View():
	m_touchDelegate(NULL),
	m_sel(NULL){}

	CREATE_FUNC(Base_View);

	static Base_View* createWithFrame(const CCRect& rect, const CAColor4B& color4B);

	void		 AddTouchEvent(CAObject *target, SEL_CAControl selector);

protected:
	virtual void TouchUpInsid(CCPoint _point);

	virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
protected:
	virtual bool init();
private:
	CAObject*		m_touchDelegate;
	SEL_CAControl	m_sel;
};
#endif