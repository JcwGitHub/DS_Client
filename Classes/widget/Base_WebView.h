#ifndef BASE_WEBVIEW_H
#define BASE_WEBVIEW_H
#include "Base_ViewController.h"


class Base_WebViewController :public Base_ViewController
{
public:
	static Base_WebViewController* creat(const std::string& url);


	//回调函数
	void CallBack(CAControl *sender, CCPoint pos);
private:
	bool init(const std::string& url);

	virtual void viewDidLoad();
private:
	std::string m_url;
};
#endif