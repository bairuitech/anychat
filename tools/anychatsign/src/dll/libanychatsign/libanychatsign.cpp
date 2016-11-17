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

/**
 *	对字符串进行MD5加密
 *	@return 成功返回0，否则为出错代码
 */ 
int MD5_EncryptMessage(const char * message, std::string &encrystr)
{
	if(!message || !strlen(message))
		return -1;
	char digest[33] = {0};
	unsigned char md5value[MD5_DIGEST_LENGTH] = {0};
	MD5((unsigned char*)message, strlen(message), md5value);
	for (int i=0; i<16; i++)
		_snprintf(digest+i*2, 3, "%02x", md5value[i]);
	encrystr = digest;
	return 0;
}

/**
 *	使用私钥对字符串进行RSA加密
 *	@return 加密成功返回0，否则为出错代码
 */
int RSA_PrivateEncrypt(const char * privKey, const unsigned char * from, int flen, unsigned char * to, int& tlen)
{
	int ret = -1;
	RSA* lpRsa = NULL;
	BIO* lpBioMem = NULL;
	do
	{
		if(!privKey || !strlen(privKey) || !from || flen<=0 || !to)
			break;
		//由公钥内存字符串转化为openssl的RSA结构
		lpBioMem = BIO_new(BIO_s_mem());
		if(!lpBioMem)
			break;
		int privateKeyLen = strlen(privKey);
		int bioWriteLen = (int)BIO_write(lpBioMem, privKey, privateKeyLen);
		if(bioWriteLen != privateKeyLen)
			break;
		lpRsa = PEM_read_bio_RSAPrivateKey(lpBioMem, NULL, NULL, NULL);
		if(NULL == lpRsa)
			break;
		int iRSASize = RSA_size(lpRsa);
		int iBlockSize = iRSASize - RSA_PKCS1_PADDING_SIZE;
		int iBlockNum = flen / iBlockSize + ((flen%iBlockSize) == 0 ? 0 : 1);
		int iEncryptSize = iRSASize * iBlockNum;
		if (tlen < iEncryptSize){
			tlen = iEncryptSize;	
			ret = -2;	// 加密缓存不够大！
			break;
		}

		bool bEncryptSuccess = true;
		int fromLenTemp = flen;
		const unsigned char* lpRawTemp = from;
		unsigned char* lpEncryptTemp = to;
		int outlen = 0;
		while(fromLenTemp > 0)
		{
			int fromLen = fromLenTemp;
			if(fromLen > iBlockSize)
				fromLen = iBlockSize;
			int len = RSA_private_encrypt(fromLen, lpRawTemp, lpEncryptTemp, lpRsa, RSA_PKCS1_PADDING);
			if(len < 0){
				bEncryptSuccess = false;
				break;
			}
			lpRawTemp += fromLen;
			lpEncryptTemp += len;
			outlen += len;
			fromLenTemp -= fromLen;
		}
		if(!bEncryptSuccess){
			ret = -3;	// 加密数据失败！
			break;
		}
		tlen = outlen;
		ret = 0;
	} while (0);
	if(lpRsa)
		RSA_free(lpRsa);
	if(lpBioMem)
		BIO_free(lpBioMem);
	return ret;
}

/**
 *	使用公钥对字符串进行RSA解密
 *	@return 解密成功返回0，否则为出错代码
 */
int RSA_PublicDecrypt(const char * pubKey, const unsigned char * from, int flen, unsigned char * to, int& tlen)
{
	int ret = -1;
	RSA* lpRsa = NULL;
	BIO* lpBioMem = NULL;
	do
	{
		if(!pubKey || !strlen(pubKey) || !from || flen<=0 || !to)
			break;
		if(tlen<flen){
			ret = -2; //解密缓冲区至少大于加密缓存区
			break;
		}
		//由公钥内存字符串转化为openssl的RSA结构
		lpBioMem = BIO_new(BIO_s_mem());
		if(!lpBioMem)
			break;
		int pubKeyLen = (int)strlen(pubKey);
		int bioWriteLen = (int)BIO_write(lpBioMem, pubKey, pubKeyLen);
		if(bioWriteLen != pubKeyLen)
			break;
		lpRsa = PEM_read_bio_RSA_PUBKEY(lpBioMem, NULL, NULL, NULL);
		if(NULL == lpRsa)
			break;

		int iRSASize = RSA_size(lpRsa);
		if (flen%iRSASize != 0){
			ret = -4;	//数据不正常
			break;
		}

		bool bDecryptSuccess = true;
		int fromLenTemp = flen;
		const unsigned char* lpEncryptTemp = from;
		unsigned char* lpDecryptTemp = to;
		int outlen = 0;
		while(fromLenTemp > 0)
		{
			int len = RSA_public_decrypt(iRSASize, lpEncryptTemp, lpDecryptTemp, lpRsa, RSA_PKCS1_PADDING);
			if(len < 0){
				bDecryptSuccess = false;
				break;
			}

			outlen += len;
			lpDecryptTemp += len;
			lpEncryptTemp += iRSASize;
			fromLenTemp -= iRSASize;
		}
		if(!bDecryptSuccess){
			ret = -3;	// 解密数据失败！
			break;
		}
		tlen = outlen;
		ret = 0;
	} while (0);
	if(lpRsa)
		RSA_free(lpRsa);
	if(lpBioMem)
		BIO_free(lpBioMem);
	return ret;
}

// 对应用接入信息使用私钥进行签名
int AnyChatRsaSign(int dwUserId, const char* lpStrUserId, const char* lpAppId, const char* lpPrivateKey, char* lpOutSigStr, int dwSigStrSize, int& dwTimeStamp)
{
	int ret = -1;
	do
	{
		if(!lpAppId || !strlen(lpAppId) || !lpPrivateKey || !strlen(lpPrivateKey) || !lpOutSigStr || !dwSigStrSize)
			break;
		char szMessage[1024] = {0};
		time_t tNow = time(NULL);
		struct tm *gmt = gmtime(&tNow);		// 采用格林威治(GMT)时间
		dwTimeStamp = (int)mktime(gmt);
		dwTimeStamp = 1479337006;
		_strupr_s((char*)lpAppId, strlen(lpAppId)+1);
		char szStrUserId[200] = {0};
		if(lpStrUserId && strlen(lpStrUserId))
			_snprintf(szStrUserId, sizeof(szStrUserId), "%s", lpStrUserId);
		_snprintf(szMessage, sizeof(szMessage), "{\"id\":%d, \"strid\":\"%s\", \"appid\":\"%s\", \"timestamp\":%d}", dwUserId, szStrUserId, lpAppId, dwTimeStamp);
		
		// md5 加密
		std::string strMD5Value; 
		MD5_EncryptMessage(szMessage, strMD5Value);

		// rsa 加密
		unsigned char szEncrypt[1024] = {0};
		int encryptLen = sizeof(szEncrypt);
		ret = RSA_PrivateEncrypt(lpPrivateKey, (const unsigned char *)strMD5Value.c_str(), strMD5Value.size(), szEncrypt, encryptLen);
		if(ret != 0)
			break;

		// base64加密
		std::string sigstr = base64_encode(szEncrypt, encryptLen);
		_snprintf(lpOutSigStr, dwSigStrSize, "%s", sigstr.c_str());
		ret = 0;
	} while (0);
	return ret;
}

// 对应用接入信息签名使用公钥进行验证
int AnyChatRsaVerify(int dwUserId, const char* lpStrUserId, const char* lpAppId, const char* lpSigStr, int dwTimeStamp, const char* lpPublicKey)
{
	int ret = -1;
	do
	{
		if(!lpAppId || !strlen(lpAppId) || !lpSigStr || !strlen(lpSigStr) || !lpPublicKey || !strlen(lpPublicKey))
			break;
		char szMessage[1024] = {0};
		_strupr_s((char*)lpAppId, strlen(lpAppId)+1);
		char szStrUserId[200] = {0};
		if(lpStrUserId && strlen(lpStrUserId))
			_snprintf(szStrUserId, sizeof(szStrUserId), "%s", lpStrUserId);
		_snprintf(szMessage, sizeof(szMessage), "{\"id\":%d, \"strid\":\"%s\", \"appid\":\"%s\", \"timestamp\":%d}", dwUserId, szStrUserId, lpAppId, dwTimeStamp);
		
		// md5 加密
		std::string strMD5Value; 
		MD5_EncryptMessage(szMessage, strMD5Value);

		// base64 解密
		std::string sigstr_orig = base64_decode(lpSigStr);

		// rsa 解密
		unsigned char szDecrypt[1024] = {0};
		int decryptLen = sizeof(szDecrypt);
		ret = RSA_PublicDecrypt(lpPublicKey, (const unsigned char *)sigstr_orig.c_str(), sigstr_orig.size(), szDecrypt, decryptLen);
		if(ret != 0)
			break;

		// 比较md5值校验
		if(strcmp(strMD5Value.c_str(), (const char*)szDecrypt) != 0){
			ret = -1;
			break;
		}
		ret = 0;
	} while (0);
	return ret;
}
