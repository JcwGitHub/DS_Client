#ifndef BASE_NAVBAR_H
#define BASE_NAVBAR_H

#include "CrossApp.h"


class Base_NavBar : public CANavigationController
{
public:
	CREATE_FUNC(Base_NavBar);

	//获取最后一个navBAr的层容器
	CAView* GetLastContainer() { return m_pContainers.back(); }

	//在bar上添加
	void			BarAddSubView(CAView* _view);
protected:
private:
	bool init();
};

#endif