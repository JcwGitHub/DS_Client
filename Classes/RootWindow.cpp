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
    
	S_MainTableBar = UI_MainTabBar::create();

	
	this->setRootViewController(S_MainTableBar);


	
	this->setColor(CAColor_white);
    return true;
}