#ifndef J_C__WIN_PLATFORM_H
#define J_C__WIN_PLATFORM_H

#include "J_C_Platform.h"

class J_C_WIN_Platform : public J_C_Platform
{
public:
	virtual void PlatformCallPhone(std::string number){}
	virtual void PlatformCallPhone_DiAl(std::string number){}
	virtual void PlatformTbInit(){}
};
#endif
