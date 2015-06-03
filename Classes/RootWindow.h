#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include "Data_Define.h"
#include <iostream>
#include "UI_MainViewContor.h"
#include "DownloadManager.h"
#include "UI_MainTabBar.h"


class RootWindow;
class UI_loginView;
#define S_Root_Window RootWindow::GetInstance()

class RootWindow: public CAWindow
{
    
public:
	//RootWindow() :S_MainDrawCon(NULL){}

	virtual ~RootWindow();
    
	static RootWindow* GetInstance();
	
    
    virtual bool init();

	void LoadMain(float t);
	void ShowMain(float t);
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

	//首页及启动层
	UI_loginView*				S_LoginView;
private:
	static RootWindow* s_root;
};


//启动页
class UI_loginView : public Base_View
{
public:
	CREATE_FUNC(UI_loginView);

	void ShowMainLayer();

	void CallBack_login(CAControl* con, CCPoint point);
private:
	bool init();

	void FirstRun(std::vector<std::string>& _vec);
private:
	bool	m_isFirst;
};
#endif /* defined(__HelloCpp__ViewController__) */
