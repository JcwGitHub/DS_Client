#ifndef  J_C_JNI_HELPER_H
#define J_C_JNI_HELPER_H

#include <jni.h>
#include <android/log.h>
#include <string>
using namespace std;

#define  JAVAVM     J_C_Jni_Helper::getJavaVM()
#define  LOG_TAG    "J_C_Jni_Helper"
#define  LOGD(...)     __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


struct Jni_Method_Info
{
	JNIEnv *			env;
	jclass				classID;
	jmethodID		methodID;
};

class  J_C_Jni_Helper
{
public:
	static JavaVM*		getJavaVM();
	static void			setJavaVM(JavaVM *javaVM);
	static jclass			getClassID(const char *className, JNIEnv *env = 0);
	static bool			getStaticMethodInfo(Jni_Method_Info &methodinfo, const char *className, const char *methodName, const char *paramCode);
	static bool			getMethodInfo(Jni_Method_Info &methodinfo, const char *className, const char *methodName, const char *paramCode);
	static std::string jstring2string(jstring str);

private:
	static JavaVM *m_psJavaVM;
};
#endif