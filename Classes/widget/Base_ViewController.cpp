#include "Base_ViewController.h"
#include "Data_Define.h"


void Base_ViewController::viewDidLoad()
{
	CAViewController::viewDidLoad();
}

void Base_ViewController::CallBack_LeftBtn(CAControl* con, CCPoint point)
{
	this->getNavigationController()->popViewControllerAnimated(true);
}

Base_ViewController::~Base_ViewController()
{
	Data_HttpManage::GetInstance()->RemoveHttpCallBack(this);
}
