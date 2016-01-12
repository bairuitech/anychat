#ifndef _ANYCHAT_JNIUTILS_H_INCLUDE_
#define _ANYCHAT_JNIUTILS_H_INCLUDE_

#if defined(WIN32)
#   include "win32/jni.h"
#else
#   include "linux/jni.h"
#endif

#if defined(ANDROID)
#	define JNI_ENV_ADDR_TYPE		JNIEnv**
#else
#	define JNI_ENV_ADDR_TYPE		void**
#endif



#define FIND_CLASS(var, className) \
	var = env->FindClass(className); \
	var = jclass(env->NewGlobalRef(var));

#define GET_METHOD_ID(var, clazz, methodName, fieldDescriptor) \
	var = env->GetMethodID(clazz, methodName, fieldDescriptor);

#define GET_JNIENV_BEGIN	JNIEnv* jniEnv = NULL;	\
							BOOL  isAttacked = FALSE;	\
							if(g_jvm->GetEnv((void**)&jniEnv, JNI_VERSION_1_4) != JNI_OK)	\
							{	\
								if(g_jvm->AttachCurrentThread((JNI_ENV_ADDR_TYPE)&jniEnv, NULL) != JNI_OK)		\
									return;	\
								isAttacked = TRUE;	\
							}

#define GET_JNIENV_BEGIN_RETURN_ERROR(e)		JNIEnv* jniEnv = NULL;	\
							BOOL  isAttacked = FALSE;	\
							if(g_jvm->GetEnv((void**)&jniEnv, JNI_VERSION_1_4) != JNI_OK)	\
							{	\
								if(g_jvm->AttachCurrentThread((JNI_ENV_ADDR_TYPE)&jniEnv, NULL) != JNI_OK)		\
									return e;	\
								isAttacked = TRUE;	\
							}

#define GET_JNIENV_END		if(isAttacked)	g_jvm->DetachCurrentThread();


class CJniUtils
{
public:
		CJniUtils() {};
		virtual ~CJniUtils() {};

public:
	// jstring×Ö·û´®×ª»»ÎªMBCS±àÂë
	static BOOL ConvertUnicode2Mbcs(JNIEnv* env, jstring inStr, char* outStr, int outsize)
	{
		if(!inStr)
			return FALSE;
		jclass cls = env->FindClass("java/lang/String");

		//new encode string default "GBK"
		jstring strencode = env->NewStringUTF("GBK");
		jmethodID mid = env->GetMethodID(cls, "getBytes", "(Ljava/lang/String;)[B");

		//call String.getBytes method to avoid incompatible migrating into solaris
		jbyteArray barr= (jbyteArray)env->CallObjectMethod(inStr, mid, strencode);

		jsize arraylen = env->GetArrayLength(barr);
		if(arraylen > 0)
		{
			jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
			memcpy(outStr, ba, arraylen > outsize ? outsize : arraylen);
			if(arraylen < outsize)
				outStr[arraylen] = '\0';
			env->ReleaseByteArrayElements(barr,ba,0);
		}
		env->DeleteLocalRef(barr);
		env->DeleteLocalRef(cls);
		env->DeleteLocalRef(strencode);
		return TRUE;
	}

	// jstring×Ö·û´®×ª»»ÎªUTF-8±àÂë
	static BOOL ConvertUnicode2UTF8(JNIEnv* env, jstring inStr, char* outStr, int outsize)
	{
		if(!inStr)
			return FALSE;
		jclass cls = env->FindClass("java/lang/String");

		//new encode string default "UTF-8"
		jstring strencode = env->NewStringUTF("UTF-8");
		jmethodID mid = env->GetMethodID(cls, "getBytes", "(Ljava/lang/String;)[B");

		//call String.getBytes method to avoid incompatible migrating into solaris
		jbyteArray barr= (jbyteArray)env->CallObjectMethod(inStr, mid, strencode);

		jsize arraylen = env->GetArrayLength(barr);
		if(arraylen > 0)
		{
			jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
			memcpy(outStr, ba, arraylen > outsize ? outsize : arraylen);
			if(arraylen < outsize)
				outStr[arraylen] = '\0';
			env->ReleaseByteArrayElements(barr,ba,0);
		}
		env->DeleteLocalRef(barr);
		env->DeleteLocalRef(cls);
		env->DeleteLocalRef(strencode);
		return TRUE;
	}

	// ½«MBCS±àÂë×Ö·û´®×ª»»Îªjstring¶ÔÏó
	static jstring ConvertMbcs2Unicode(JNIEnv* env, char* inStr)
	{
		jsize len = (jsize)strlen(inStr);
		jclass cls = env->FindClass("java/lang/String");

		//new encode string default "GBK"
		jstring strencode = env->NewStringUTF("GBK");
		jmethodID mid = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
		jbyteArray barr = env->NewByteArray(len);

		env->SetByteArrayRegion(barr,0,len,(jbyte*)inStr);

		//call new String(byte[] b,String encode)
		jstring outstr = (jstring)env->NewObject(cls, mid, barr, strencode);
		env->DeleteLocalRef(barr);
		env->DeleteLocalRef(cls);
		env->DeleteLocalRef(strencode);
		return outstr;
	}

};

#endif // _ANYCHAT_JNIUTILS_H_INCLUDE_
