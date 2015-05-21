#include "UI_MainView4.h"

bool UI_MainView4::init()
{
	this->getView()->setColor(CAColor_white);
	return true;
}

void UI_MainView4::viewDidLoad()
{
	this->getNavigationController()->setNavigationBarHidden(true,false);

	//该页尺寸有问题

	CCSize _bounds = this->getView()->getBounds().size;
	CAWebView* web = CAWebView::createWithFrame(this->getView()->getBounds());
	web->loadURL("http://h5.m.taobao.com/awp/mtb/mtb.htm?spm=0.0.0.0#!/awp/mtb/mtb.htm");
	this->getView()->addSubview(web);

	CAViewController::viewDidLoad();
}
