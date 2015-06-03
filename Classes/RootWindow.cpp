#include "RootWindow.h"
#include "UI_MainViewContor.h"
#include "UI_LeftView.h"
#include "UI_MainTabBar.h"
#include "UI_MainView1.h"
#include "Data_Define.h"
#include "DownloadManager.h"

RootWindow* RootWindow::s_root = NULL;
RootWindow* RootWindow::GetInstance()
{
	if (s_root == NULL)
	{
		s_root = new RootWindow();
		s_root->init();
	}

	return s_root;
}
// RootWindow* RootWindow::create()
// {
// 	RootWindow* _window = new RootWindow();
// 	_window->init();
// 	_window->autorelease();
// 	return _window;
// }


RootWindow::~RootWindow()
{

}

bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
	this->setColor(CAColor_white);

	//展示层
	S_LoginView = UI_loginView::create();
	S_LoginView->setZOrder(10);
	this->addSubview(S_LoginView);

	//开启定时器
	CAScheduler::schedule(schedule_selector(RootWindow::LoadMain), this, 0.5f, 0, 0.5f);
	CAScheduler::schedule(schedule_selector(RootWindow::ShowMain), this, 2.5f, 0, 2.5f);
    return true;
}

void RootWindow::LoadMain(float t)
{
	S_MainTableBar = UI_MainTabBar::create();


	this->setRootViewController(S_MainTableBar);
}

void RootWindow::ShowMain(float t)
{
	S_LoginView->ShowMainLayer();
}


//启动页
bool UI_loginView::init()
{
	if (!Base_View::init())
	{
		return false;
	}

	this->setFrame(CCRect(0, 0, C_ViewSize().width, C_ViewSize().height));
 	std::vector<std::string>	_paths;
 	FirstRun(_paths);
 
 	CAVector<CAView*> _temp;
	for (size_t i = 0; i < _paths.size(); i++)
 	{
 		Base_ImageView* _ima = Base_ImageView::creat(_paths[i]);
 		_temp.pushBack(_ima); 
 	}
 
	Base_PageView* _page = Base_PageView::creat(CCRect(
		C_ViewSize().width/2,
		C_ViewSize().height/2,
		C_ViewSize().width,
		C_ViewSize().height), 
		CAPageViewDirectionHorizontal);
	_page->SetPageViews(_temp);
	
 	this->addSubview(_page);


	//
	CCRect _rect = FitRect(320,900,548,84);
	Base_ImageView* _ima1 = Base_ImageView::creat("image/login1.png");
	_ima1->setCenter(_rect);
	Base_View* _ima2 = Base_View::create();
	_ima2->setCenter(_rect);
	_ima2->setColor(CAColor_clear);
	_page->getSubViewAtIndex(_paths.size() - 1)->addSubview(_ima1);
	_page->getSubViewAtIndex(_paths.size() - 1)->addSubview(_ima2);

	if (DATA_BASE->m_firstLogin)
	{
		_page->ShowPageTag(this, 1);
		_ima2->AddTouchEvent(this, CAControl_selector(UI_loginView::CallBack_login));
	}
	return true;
}

void UI_loginView::FirstRun(std::vector<std::string>& _vec)
{
	if (Data_Base::GetInstance()->m_firstLogin)
	{
		_vec.push_back("image/login.jpg");
		_vec.push_back("image/login1.jpg");
		_vec.push_back("image/login2.jpg");
	}
	_vec.push_back("image/login3.jpg");
}

void UI_loginView::ShowMainLayer()
{
	if (Data_Base::GetInstance()->m_firstLogin)
	{
		return;
	}
	else
	{
		this->removeFromSuperview();
	}	
}

void UI_loginView::CallBack_login(CAControl* con, CCPoint point)
{
	this->removeFromSuperview();
}
