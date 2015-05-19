#ifndef UI_MAINTABBAR_H
#define UI_MAINTABBAR_H


#include "Data_Define.h"


class UI_MainTabBar : public CATabBarController
{
public:
	CREATE_FUNC(UI_MainTabBar);
protected:
private:
	bool init();

	virtual void viewDidLoad();
};
#endif