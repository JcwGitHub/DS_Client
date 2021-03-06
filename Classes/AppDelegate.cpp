﻿#include "AppDelegate.h"
#include "RootWindow.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
	Data_Base::GetInstance();
}

AppDelegate::~AppDelegate() 
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//capageview 添加默认构造函数


    // initialize director
    CAApplication* pDirector = CAApplication::getApplication();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();



    pDirector->setOpenGLView(pEGLView);

    // run
	pDirector->runWindow(S_Root_Window);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CAApplication::getApplication()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CAApplication::getApplication()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
