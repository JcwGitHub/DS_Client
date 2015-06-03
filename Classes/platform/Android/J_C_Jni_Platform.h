#ifndef  J_C_JniPlatform_H
#define J_C_JniPlatform_H

#include "J_C_Platform.h"
#include <string>

class J_C_Jni_Platform : public J_C_Platform
{
public:
	/************************************************************************/
	/* 电话api                                                                     */
	/************************************************************************/
	virtual void PlatformCallPhone(std::string number);
	virtual void PlatformCallPhone_DiAl(std::string number);



	/************************************************************************/
	/* 淘宝api                                                                     */
	/************************************************************************/

};

#endif