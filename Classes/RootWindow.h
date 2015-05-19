#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include "Data_Define.h"
#include <iostream>
#include "UI_MainViewContor.h"
#include "DownloadManager.h"
#include "UI_MainTabBar.h"


class RootWindow;
#define S_Root_Window RootWindow::GetInstance()

class RootWindow: public CAWindow
{
    
public:
	//RootWindow() :S_MainDrawCon(NULL){}

	virtual ~RootWindow();
    
	static RootWindow* GetInstance();
	
    
    virtual bool init();
public:
	//首页draw
	UI_MainViewContor*   S_MainDrawCon;

	//首页tablebar
	UI_MainTabBar*		 S_MainTableBar;

// 	//首页nav
// 	Base_NavBar*		 s_NavBar1;
// 	
// 	//第二页nav
// 	Base_NavBar*		 s_NavBar2;
// 
// 	//第三页nav
// 	Base_NavBar*		 s_NavBar3;
private:
	static RootWindow* s_root;
};


#endif /* defined(__HelloCpp__ViewController__) */
