#include "UI_LeftView.h"

bool UI_LeftView::init()
{

	//设置navBar
	CANavigationBarItem* _item = CANavigationBarItem::create(UTF8("dasd"));
	this->setNavigationBarItem(_item);

	return true;
}
