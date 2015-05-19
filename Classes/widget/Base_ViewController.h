#ifndef BASE_VIEWCONTROLLER_H
#define BASE_VIEWCONTROLLER_H



#include "CrossApp.h"
class Base_ViewController : public CAViewController
{
public:
	~Base_ViewController();

	virtual void viewDidLoad();


	//左边按钮回调函数
	void	CallBack_LeftBtn(CAControl* con, CCPoint point);
private:
};
#endif