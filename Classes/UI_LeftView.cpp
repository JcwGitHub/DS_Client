#include "UI_LeftView.h"

bool UI_LeftView::init()
{

	//设置navBar
	CANavigationBarItem* _item = CANavigationBarItem::create(UTF8("dasd"));
	this->setNavigationBarItem(_item);
	
	
	J_C_PLATFORM->AddDelegate(this);
	TaoBaoUserInfoUpdate();
	return true;
}


void UI_LeftView::TaoBaoUserInfoUpdate()
{
	this->getView()->removeAllSubviews();

	//背景
	Base_ImageView* ima = Base_ImageView::creat("image/loginbg.png");
	ima->setFrame(FitRect(0, 0, 427, 250));
	this->getView()->addSubview(ima);

	if (J_C_PLATFORM->m_tbSdkInfo._isLogin)
	{
		//登录
	}
	else
	{
		//未登录
		//ima->removeFromSuperview();
	}
	AndroidLog("3333");
}
