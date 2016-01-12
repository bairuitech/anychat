#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include "libanychatsign.h"



int main(int argc, char* argv[])
{
	int result = -1;
	int help = 0;
	int mode = 0;
	int userid = 0;
	int timestamp = 0;
	std::string appid;
	std::string keyfile;
	std::string sigstr;
	while( (result = getopt(argc, argv, "hm:u:a:k:s:t:")) != -1 )
	{
		switch(result)
		{
		case 'h':		help = 1;					break;
		case 'm':		mode = atoi(optarg);		break;
		case 'u':		userid = atoi(optarg);		break;
		case 'a':		appid = optarg;				break;
		case 'k':		keyfile = optarg;			break;
		case 's':		sigstr = optarg;			break;
		case 't':		timestamp = atoi(optarg);	break;
		default:
			break;
		}
	}
	if(help)
	{
		// Show usage
		printf("anychatsign -h\r\n");
		return 0;
	}
	if(!keyfile.length())
	{
		printf("must input keyfile!\r\n");
		return 0;
	}
	if(!mode && !sigstr.length())
	{
		printf("rsa verify mode, must input sig string!\r\n");
		return 0;
	}

	char szKeyBuf[1024] = {0};
	FILE* f = NULL;
	do 
	{
		if(!keyfile.length())
			break;
		f = fopen(keyfile.c_str(), "rb");
		if(!f)
			break;
		fread(szKeyBuf, 1, sizeof(szKeyBuf)-1, f);
	} while (false);
	if(f)
	{
		fclose(f);
		f = NULL;
	}
	if(!strlen(szKeyBuf))
	{
		printf("read key file:%s failed!\r\n", keyfile.c_str());
		return 0;
	}

	if(mode == 0)
	{
		char szSigStr[1024]= {0};
		timestamp = 0;
		int errorcode = AnyChatRsaSign(userid, appid.c_str(), szKeyBuf, szSigStr, sizeof(szSigStr), timestamp);
		printf("RSA sign result, errorcode:%d, \r\n\ttimestamp:%d, \r\n\tsigstr:%s\r\n", errorcode, timestamp, sigstr);
	}
	else
	{
		int errorcode = AnyChatRsaVerify(userid, appid.c_str(), sigstr.c_str(), timestamp, szKeyBuf);
		printf("RSA verify result, errorcode:%d", errorcode);
	}
	return 0;
}

