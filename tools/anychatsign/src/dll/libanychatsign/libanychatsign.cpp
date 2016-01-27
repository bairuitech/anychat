#include "libanychatsign.h"
#include <time.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include "base64.h"

#if defined(WIN32)
#	include <windows.h>
#else
#	include <ctype.h>
#define _snprintf   snprintf
#endif


#if defined(WIN32)
BOOL APIENTRY DllMain( HANDLE hModule, int  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
#endif

#if !defined(WIN32)
char *_strupr_s(char *str, int size)
{
	char *ptr = str;
	while (*ptr != '\0') {
		if (islower(*ptr))
			*ptr = toupper(*ptr);
		ptr++;
	}
	return str;
}
#endif


// 对应用接入信息使用私钥进行签名
int AnyChatRsaSign(int dwUserId, const char* lpStrUserId, const char* lpAppId, const char* lpPrivateKey, char* lpOutSigStr, int dwSigStrSize, int& dwTimeStamp)
{
	int ret = -1;
	RSA* lpRsa = NULL;
	BIO* lpBioMem = NULL;
	do
	{
		if(!lpAppId || !strlen(lpAppId) || !lpPrivateKey || !strlen(lpPrivateKey) || !lpOutSigStr || !dwSigStrSize)
			break;
		char szMessage[1024] = {0};
		dwTimeStamp = (int)time(NULL);
		_strupr_s((char*)lpAppId, strlen(lpAppId)+1);
		char szStrUserId[200] = {0};
		if(lpStrUserId && strlen(lpStrUserId))
			_snprintf(szStrUserId, sizeof(szStrUserId), "%s", lpStrUserId);
		_snprintf(szMessage, sizeof(szMessage), "{\"id\":%d, \"strid\":%s, \"appid\":%s, \"timestamp\":%d}", dwUserId, szStrUserId, lpAppId, dwTimeStamp);
		unsigned char md5value[MD5_DIGEST_LENGTH] = {0};
		MD5((unsigned char*)szMessage, strlen(szMessage), md5value);
		//由公钥内存字符串转化为openssl的RSA结构
		lpBioMem = BIO_new(BIO_s_mem());
		if(!lpBioMem)
			break;
		int privateKeyLen = strlen(lpPrivateKey);
		int bioWriteLen = (int)BIO_write(lpBioMem, lpPrivateKey, privateKeyLen);
		if(bioWriteLen != privateKeyLen)
			break;
		lpRsa = PEM_read_bio_RSAPrivateKey(lpBioMem, NULL, NULL, NULL);
		if(NULL == lpRsa)
			break;
		unsigned char signRet[200];
		unsigned int signLen;
		if(RSA_sign(NID_md5, md5value, MD5_DIGEST_LENGTH, signRet, &signLen, lpRsa) != 1)
			break;

		std::string sigstr = base64_encode((unsigned char *)signRet, signLen);
		_snprintf(lpOutSigStr, dwSigStrSize, "%s", sigstr.c_str());
		ret = 0;
	} while (0);
	if(lpRsa)
		RSA_free(lpRsa);
	if(lpBioMem)
		BIO_free(lpBioMem);
	return ret;
}

// 对应用接入信息签名使用公钥进行验证
int AnyChatRsaVerify(int dwUserId, const char* lpStrUserId, const char* lpAppId, const char* lpSigStr, int dwTimeStamp, const char* lpPublicKey)
{
	int ret = -1;
	RSA* lpRsa = NULL;
	BIO* lpBioMem = NULL;
	do
	{
		if(!lpAppId || !strlen(lpAppId) || !lpSigStr || !strlen(lpSigStr) || !lpPublicKey || !strlen(lpPublicKey))
			break;
		char szMessage[1024] = {0};
		_strupr_s((char*)lpAppId, strlen(lpAppId)+1);
		char szStrUserId[200] = {0};
		if(lpStrUserId && strlen(lpStrUserId))
			_snprintf(szStrUserId, sizeof(szStrUserId), "%s", lpStrUserId);
		_snprintf(szMessage, sizeof(szMessage), "{\"id\":%d, \"strid\":%s, \"appid\":%s, \"timestamp\":%d}", dwUserId, szStrUserId, lpAppId, dwTimeStamp);
		std::string sigstr_orig = base64_decode(lpSigStr);
		unsigned char md5value[MD5_DIGEST_LENGTH] = {0};
		MD5((unsigned char*)szMessage, strlen(szMessage), md5value);

		//由公钥内存字符串转化为openssl的RSA结构
		lpBioMem = BIO_new(BIO_s_mem());
		if(!lpBioMem)
			break;
		int pubKeyLen = (int)strlen(lpPublicKey);
		int bioWriteLen = (int)BIO_write(lpBioMem, lpPublicKey, pubKeyLen);
		if(bioWriteLen != pubKeyLen)
			break;
		lpRsa = PEM_read_bio_RSA_PUBKEY(lpBioMem, NULL, NULL, NULL);
		if(NULL == lpRsa)
			break;
		//签名验证
		if(RSA_verify(NID_md5, md5value, MD5_DIGEST_LENGTH, (unsigned char*)sigstr_orig.c_str(), (unsigned int)sigstr_orig.length(), lpRsa) != 1)
			break;
		ret = 0;
	} while (0);
	if(lpRsa)
		RSA_free(lpRsa);
	if(lpBioMem)
		BIO_free(lpBioMem);
	return ret;
}



