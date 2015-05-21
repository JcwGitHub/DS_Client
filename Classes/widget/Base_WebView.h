#ifndef BASE_WEBVIEW_H
#define BASE_WEBVIEW_H
#include "Base_ViewController.h"


class Base_WebViewController :
	public Base_ViewController,
	public CAWebViewDelegate
{
public:
	static Base_WebViewController* creat(const std::string& url);


	//回调函数
	void CallBack(CAControl *sender, CCPoint pos);

	virtual bool onShouldStartLoading(CAWebView* pWebView, const std::string &url);

	virtual void onDidFinishLoading(CAWebView* pWebView, const std::string &url);

	virtual void onLoadHtmlSource(CAWebView* pWebView, const std::string &htmlSource);

	virtual void onDidFailLoading(CAWebView* pWebView, const std::string &url);

	virtual void onJSCallback(CAWebView* pWebView, const std::string &message);
private:
	bool init(const std::string& url);

	virtual void viewDidLoad();
private:
	std::string m_url;
};
#endif