#ifndef UI_MainViewContor_H
#define UI_MainViewContor_H

#include "Data_Define.h"


//包含左侧边栏和主界面的管理器
class UI_MainViewContor : public CADrawerController
{
public:
	CREATE_FUNC(UI_MainViewContor);

private:
	bool init();
};
#endif