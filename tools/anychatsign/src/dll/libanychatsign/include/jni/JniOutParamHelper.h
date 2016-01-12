#if !defined(_ANYCHAT_JNI_OUTPARAM_HELPER_H_INCLUDE_)
#define _ANYCHAT_JNI_OUTPARAM_HELPER_H_INCLUDE_

#include "jniutils.h"

/**
 *	Java回传参数封装类
 *	用于操作Java层的AnyChatOutParam类
 */
class CJniOutParamHelper
{
public:
	CJniOutParamHelper() {}
	virtual ~CJniOutParamHelper() {};

private:
	static JavaVM* g_jvm;

public:
	// 初始化
	static void SetJavaVM(JavaVM* vm)	{	g_jvm = vm;	}

public:
	// 设置整型参数
	static void SetIntValue(int iValue, jobject outParamObj)
	{
		GET_JNIENV_BEGIN;
		do
		{
			if(jniEnv==NULL)
				break;
			jclass cls = jniEnv->GetObjectClass(outParamObj);
			if(cls==NULL)
				break;
			jmethodID mid = jniEnv->GetMethodID(cls, "SetIntValue", "(I)V");
			if(mid==NULL)
				break;
			jniEnv->CallVoidMethod(outParamObj, mid, iValue);
			jniEnv->DeleteLocalRef(cls);
		} while (FALSE);
		GET_JNIENV_END;
	}

	// 设置字符串参数
	static void SetStrValue(CHAR* szValue, jobject outParamObj)
	{
		if(!szValue || !strlen(szValue))
			return;
		GET_JNIENV_BEGIN;
		do
		{
			if(jniEnv==NULL)
				break;
			jclass cls = jniEnv->GetObjectClass(outParamObj);
			if(cls==NULL)
				break;
			jmethodID mid = jniEnv->GetMethodID(cls, "SetStrValue", "(Ljava/lang/String;)V");
			if(mid==NULL)
				break;
			jstring str = CJniUtils::ConvertMbcs2Unicode(jniEnv, szValue);
			jniEnv->CallVoidMethod(outParamObj, mid, str);
			jniEnv->DeleteLocalRef(cls);
			jniEnv->DeleteLocalRef(str);
		} while (FALSE);
		GET_JNIENV_END;
	}

	// 设置整型数组参数
	static void SetIntArray(DWORD* lpIntArray, DWORD dwNums, jobject outParamObj)
	{
		if(!lpIntArray || !dwNums)
			return;
		GET_JNIENV_BEGIN;
		do
		{
			if(jniEnv==NULL)
				break;
			jclass cls = jniEnv->GetObjectClass(outParamObj);
			if(cls==NULL)
				break;
			jmethodID mid = jniEnv->GetMethodID(cls, "SetIntArray", "([I)V");
			if(mid==NULL)
				break;
			jintArray iArray = jniEnv->NewIntArray(dwNums);
			jniEnv->SetIntArrayRegion(iArray, 0, dwNums, (const jint*)lpIntArray);
			jniEnv->CallVoidMethod(outParamObj, mid, iArray);
			jniEnv->DeleteLocalRef(cls);
			jniEnv->DeleteLocalRef(iArray);
		} while (FALSE);
		GET_JNIENV_END;
	}
};


JavaVM* CJniOutParamHelper::g_jvm = NULL;


#endif // !defined(_ANYCHAT_JNI_OUTPARAM_HELPER_H_INCLUDE_)
