﻿#include "UI_MainView3.h"

bool UI_MainView3::init()
{
	this->getView()->setColor(CAColor_white);
	return true;
}

void UI_MainView3::viewDidLoad()
{
	this->getNavigationController()->setNavigationBarHidden(true, false);

	//该页尺寸有问题

	CCSize _bounds = this->getView()->getBounds().size;
	CAWebView* web = CAWebView::createWithFrame(this->getView()->getBounds());
	web->loadURL("http://langyuedianzi.taobao.com/shop/view_shop.htm?spm=a1z0k.7386009.1997989141.d4915209.r9YfhL&shop_id=34271480");
	this->getView()->addSubview(web);

	CAViewController::viewDidLoad();
}
