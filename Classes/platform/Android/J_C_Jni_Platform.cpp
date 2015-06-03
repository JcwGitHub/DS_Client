#include "J_C_Jni_Platform.h"
#include "platform/Android/J_C_Jni_Helper.h"
#include <jni.h>

#define  J_C_ClassName		"other/third/files/JniHelper"


J_C_Platform* J_C_Platform::GetInstance()
{
	if (!m_platform)
	{
		m_platform = new J_C_Jni_Platform();
	}

	return m_platform;
}

/************************************************************************/
void J_C_Jni_Platform::PlatformCallPhone(std::string number)
{
	Jni_Method_Info t;
	if (J_C_Jni_Helper::getStaticMethodInfo(t, J_C_ClassName, "JniHelper_CallPhone", "(Ljava/lang/String;)V")) {
		jstring stringArg1 = t.env->NewStringUTF(number.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);

		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void J_C_Jni_Platform::PlatformCallPhone_DiAl(std::string number)
{
	Jni_Method_Info t;
	if (J_C_Jni_Helper::getStaticMethodInfo(t, J_C_ClassName, "JniHelper_CallPhone_DiAl", "(Ljava/lang/String;)V")) {
		jstring stringArg1 = t.env->NewStringUTF(number.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);

		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}


/************************************************************************/




/************************************************************************/
/* 淘宝                                                                     */
/************************************************************************/
extern "C" {

	//用户信息
	JNIEXPORT void JNICALL Java_other_third_files_JniTaoBaoSdk_NativeSetInfo(
		JNIEnv*  env, jobject thiz, jstring uId, jstring uname, jstring uicon, jboolean islogin) {

		AndroidLog("tao bao user info success!");
// 		const char* str;
// 		str = env->GetStringUTFChars(uId, false);

		J_C_Platform::GetInstance()->m_tbSdkInfo._userId = env->GetStringUTFChars(uId, false);
		J_C_Platform::GetInstance()->m_tbSdkInfo._userName = env->GetStringUTFChars(uname, false);
		J_C_Platform::GetInstance()->m_tbSdkInfo._userIcon = env->GetStringUTFChars(uicon, false);
		J_C_Platform::GetInstance()->m_tbSdkInfo._isLogin = islogin;

		//通知
		AndroidLog("111");
		J_C_Platform::GetInstance()->SendMessage(1);
		AndroidLog("2222");
	}
}

/************************************************************************/
/* 淘宝                                                                     */
/************************************************************************/
