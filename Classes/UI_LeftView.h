#ifndef UI_LeftView_H
#define UI_LeftView_H

#include "Data_Define.h"

class UI_LeftView : public CAViewController , public J_C_Delegate
{
public:
	CREATE_FUNC(UI_LeftView);
	virtual void TaoBaoUserInfoUpdate();

private:
	bool init();
};
#endif