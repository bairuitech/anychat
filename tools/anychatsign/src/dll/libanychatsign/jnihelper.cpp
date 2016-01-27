#include "libanychatsign.h"


#if defined(WIN32)
#	include <windows.h>
#else
typedef unsigned int DWORD;
typedef char CHAR;
typedef long	BOOL;
#	define TRUE		1
#	define FALSE	0
#endif

#include <jni/jniutils.h>
#include <jni/JniOutParamHelper.h>



#ifdef   __cplusplus
extern   "C"   {
#endif

static const char* kAnyChatSignPathName		=	"com/bairuitech/anychat/AnyChatSign";


// 对应用接入信息使用私钥进行签名
JNIEXPORT jint JNICALL jniAnyChatRsaSign(JNIEnv* env, jobject clazz, jint dwUserId, jstring lpStrUserId, jstring lpAppId, jstring lpPrivateKey, jobject result)
{
	char szStrUserId[200] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpStrUserId, szStrUserId, sizeof(szStrUserId));
	char szAppId[100] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpAppId, szAppId, sizeof(szAppId));
	char szPrivateKey[1024] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpPrivateKey, szPrivateKey, sizeof(szPrivateKey));

	int timestamp = 0;
	char szOutBuf[1024] = {0};
	int errorcode = AnyChatRsaSign(dwUserId, szStrUserId, szAppId, szPrivateKey, szOutBuf, sizeof(szOutBuf), timestamp);
	if(errorcode == 0)
	{
		CJniOutParamHelper::SetIntValue(timestamp, result);
		CJniOutParamHelper::SetStrValue(szOutBuf, result);
	}
	return errorcode;
}

// 对应用接入信息签名使用公钥进行验证
JNIEXPORT jint JNICALL jniAnyChatRsaVerify(JNIEnv* env, jobject clazz, jint dwUserId, jstring lpStrUserId, jstring lpAppId, jstring lpSigStr, jint dwTimeStamp, jstring lpPublicKey)
{
	char szStrUserId[200] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpStrUserId, szStrUserId, sizeof(szStrUserId));
	char szAppId[100] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpAppId, szAppId, sizeof(szAppId));
	char szSigStr[1024] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpSigStr, szSigStr, sizeof(szSigStr));
	char szPublicKey[1024] = {0};
	CJniUtils::ConvertUnicode2Mbcs(env, lpPublicKey, szPublicKey, sizeof(szPublicKey));

	return AnyChatRsaVerify(dwUserId, szStrUserId, szAppId, szSigStr, dwTimeStamp, szPublicKey);
}


static JNINativeMethod gMethods[] = {
	{ "RsaSign", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Lcom/bairuitech/anychat/AnyChatOutParam;)I", (void*)jniAnyChatRsaSign },
	{ "RsaVerify", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)I", (void*)jniAnyChatRsaVerify },
};



/**
 *	Register several native methods for one class.
 */
static int registerNativeMethods(JNIEnv* env, const char* className,JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;
	clazz = env->FindClass(className);
	if (clazz == NULL) {
		fprintf(stderr, "Native registration unable to find class '%s'\r\n", className);
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
		fprintf(stderr, "RegisterNatives failed for '%s'\r\n", className);
		return JNI_FALSE;
	}

	return JNI_TRUE;
}

/**
 *	Register native methods for all classes we know about.
 */
static int registerNatives(JNIEnv* env)
{
	return registerNativeMethods(env, kAnyChatSignPathName, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
}

/**
 *	This is called by the VM when the shared library is first loaded.
 *	Returns the JNI version on success, -1 on failure.
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;

	if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		return -1;
	if(env == NULL)
		return -1;

	if (!registerNatives(env))
		return -1;

	CJniOutParamHelper::SetJavaVM(vm);
	/* success -- return valid version number */
	return JNI_VERSION_1_4;
}

#ifdef   __cplusplus
}
#endif



