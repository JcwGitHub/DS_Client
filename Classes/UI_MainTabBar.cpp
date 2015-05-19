#include "UI_MainTabBar.h"
#include "UI_MainView1.h"
#include "UI_MainView2.h"
#include "UI_MainView3.h"
#include "Base_NavBar.h"
#include "UI_LeftView.h"
#include "UI_MainViewContor.h"
#include "RootWindow.h"



bool UI_MainTabBar::init()
{
	std::vector<CAViewController*> vec;

	CAApplication* pDirector = CAApplication::getApplication();


	//第一个页面
	UI_LeftView*     left = UI_LeftView::create();
	Base_NavBar*	 bar1 = Base_NavBar::create();
	//bar1->setNavigationBarHidden(true,false);
	bar1->initWithRootViewController(UI_MainView1::create());

	UI_MainViewContor*		 _viewController = UI_MainViewContor::create();
	_viewController->initWithController(left, bar1, pDirector->getWinSize().width * 4 / 6.0f);
	S_Root_Window->S_MainDrawCon = _viewController;

	//第二个页面
	Base_NavBar* bar2 = Base_NavBar::create();
	bar2->initWithRootViewController(UI_MainView2::create());
	
	//第三个页面
	Base_NavBar* bar3 = Base_NavBar::create();
	bar3->initWithRootViewController(UI_MainView3::create());
	
	vec.push_back(_viewController);
	vec.push_back(bar2);
	vec.push_back(bar3);


	CATabBarController::initWithViewControllers(vec);
	return true;
}

void UI_MainTabBar::viewDidLoad()
{	
	
	CAVector<CATabBarItem*> _vec = m_pTabBar->getItems();
	for (size_t i = 0; i < _vec.size(); i++)
	{
		_vec.at(i)->init(Res_M_Tab_T[i],CAImage::create(Res_M_Tab_N[i]),CAImage::create(Res_M_Tab_P[i]));

	}
	

	this->setTabBarBackGroundColor(CAColor_white);
	this->setTabBarSelectedBackGroundColor(CAColor_red);

	this->setTabBarTitleColorForNormal(CAColor_black);
	this->setTabBarTitleColorForSelected(CAColor_white);
	CATabBarController::viewDidLoad();
}
