#include "Base_WebView.h"
#include "Data_Define.h"

Base_WebViewController* Base_WebViewController::creat(const std::string& url)
{
	Base_WebViewController* web = new Base_WebViewController();
	if (web&&web->init(url))
	{
		web->autorelease();
		return web;
	}

	CC_SAFE_RELEASE_NULL(web);
	return NULL;
}

bool Base_WebViewController::init(const std::string& url)
{
	if (!Base_ViewController::init())
	{
		return false;
	}


	m_url = url;
	return true;
}

void Base_WebViewController::viewDidLoad()
{
	//该页尺寸有问题


	CCSize _bounds = this->getView()->getBounds().size;
 	CAWebView* web = CAWebView::createWithFrame(CCRect(0, 0,_bounds.width, _bounds.height - _px(62)));
	web->setWebViewDelegate(this);
	web->loadURL(m_url);
	this->getView()->addSubview(web);
	
	CAButton* btn = CAButton::createWithFrame(CCRect(0, web->getBounds().size.height, _bounds.width, _px(50)), CAButtonTypeSquareRect);
	btn->addTarget(this, CAControl_selector(Base_WebViewController::CallBack), CAControlEventTouchUpInSide);
	btn->setTitleForState(CAControlStateAll, UTF8("返回"));
	
	this->getView()->addSubview(btn);

	Base_ViewController::viewDidLoad();
}

void Base_WebViewController::CallBack(CAControl *sender, CCPoint pos)
{
	this->dismissModalViewController(true);
}

bool Base_WebViewController::onShouldStartLoading(CAWebView* pWebView, const std::string &url)
{
	CCLog("-----------on should -----------  %s",url.c_str());
	return true;
}

void Base_WebViewController::onDidFinishLoading(CAWebView* pWebView, const std::string &url)
{
	CCLog("-----------onDidFinish -----------  %s", url.c_str());
}

void Base_WebViewController::onLoadHtmlSource(CAWebView* pWebView, const std::string &htmlSource)
{
	CCLog("-----------onLoadHtmlSource -----------  %s", htmlSource.c_str());
}

void Base_WebViewController::onDidFailLoading(CAWebView* pWebView, const std::string &url)
{
	CCLog("-----------onDidFailLoading -----------  %s", url.c_str());
}

void Base_WebViewController::onJSCallback(CAWebView* pWebView, const std::string &message)
{
	CCLog("-----------onJSCallback -----------  %s", message.c_str());
}
