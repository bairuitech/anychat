#if !defined(_ANYCHAT_SIGN_H_INCLUDED_)
#define _ANYCHAT_SIGN_H_INCLUDED_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
#	define DLL_EXPORT_API extern "C" __declspec(dllexport)
#else
#	define DLL_EXPORT_API extern "C"
#endif



// 对应用接入信息使用私钥进行签名
DLL_EXPORT_API int AnyChatRsaSign(int dwUserId, const char* lpAppId, const char* lpPrivateKey, char* lpOutSigStr, int dwSigStrSize, int& dwTimeStamp);
// 对应用接入信息签名使用公钥进行验证
DLL_EXPORT_API int AnyChatRsaVerify(int dwUserId, const char* lpAppId, const char* lpSigStr, int dwTimeStamp, const char* lpPublicKey);



#endif //_ANYCHAT_SIGN_H_INCLUDED_
