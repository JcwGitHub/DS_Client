#ifndef			C_PLATFORM_H
#define		C_PLATFORM_H

#include <string>
#include <vector>
#include "..\CCPlatformConfig.h"


#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#define  AndroidLog(...)     __android_log_print(ANDROID_LOG_DEBUG,"J_C_Jni_Helper",__VA_ARGS__)
#else
#define  AndroidLog(...)
#endif


#define J_C_PLATFORM  J_C_Platform::GetInstance()

class J_C_Delegate
{
public:
	virtual void TaoBaoUserInfoUpdate(){};
};
class J_C_Platform
{
public:
	struct TBSDKInfo
	{
		bool			_isLogin;
		std::string _userId;
		std::string _userName;
		std::string _userIcon;

		TBSDKInfo(){ _isLogin = false; _userIcon = ""; _userName = ""; _userId = ""; }
	};
public:
	static J_C_Platform* GetInstance();

	void	AddDelegate(J_C_Delegate* _delegate);
	void SendMessage(int nType);

	//Ò»¼ü²¦ºÅ
	virtual void PlatformCallPhone(std::string number) = 0;
	//ÏÔÊ¾ºÅÂë
	virtual void PlatformCallPhone_DiAl(std::string number) = 0;
public:
	static J_C_Platform*					m_platform;
	std::vector<J_C_Delegate*>		m_delegates;
	TBSDKInfo								m_tbSdkInfo;
};
#endif