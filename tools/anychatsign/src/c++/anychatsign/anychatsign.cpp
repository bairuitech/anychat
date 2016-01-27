#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include "include/libanychatsign.h"

// 命令参数描述与示例
void usage(void)
{
	printf("demo for rsa sign or verify. Usage:\r\n");
	printf("\tanychatsign [options]\r\n");
	printf("Option:\r\n");
	printf("\t-h  help, print this message.\r\n");
	printf("\t-m  mode, 0 for rsa sign mode; 1 for rsa verify mode.\r\n");
	printf("\t-u  useid, sdk userid.\r\n");
	printf("\t-a  appid, application guid.\r\n");
	printf("\t-k  keyfile, rsa privateFile or publicFile.\r\n");
	printf("\t-s  sigfile, rsa sign data file for read or write.\r\n");
	printf("\t-t  timestamp, the timestamp by sign.\r\n");
}

int main(int argc, char* argv[])
{
	int result = -1;
	int help = 0;
	int mode = 0;
	int userid = 0;
	int timestamp = 0;
	std::string appid;
	std::string keyfile;
	std::string sigfile;
	while( (result = getopt(argc, argv, "hm:u:a:k:s:t:")) != -1 )
	{
		switch(result)
		{
		case 'h':		help = 1;					break;
		case 'm':		mode = atoi(optarg);		break;
		case 'u':		userid = atoi(optarg);		break;
		case 'a':		appid = optarg;				break;
		case 'k':		keyfile = optarg;			break;
		case 's':		sigfile= optarg;			break;
		case 't':		timestamp = atoi(optarg);	break;
		default:
			break;
		}
	}
	if(help || argc<2)
	{
		// Show usage
		usage();
		return 0;
	}
	if(!keyfile.length())
	{
		printf("must input keyfile!\r\n");
		return 0;
	}
	if(mode==1 && !sigfile.length())
	{
		printf("rsa verify mode, must input sign file!\r\n");
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
		int errorcode = AnyChatRsaSign(userid, "", appid.c_str(), szKeyBuf, szSigStr, sizeof(szSigStr), timestamp);
		printf("RSA sign result, errorcode:%d, \r\n\ttimestamp:%d, \r\n\tsigstr:%s\r\n", errorcode, timestamp, szSigStr);

		if (sigfile.length()){
			FILE* fp = fopen(sigfile.c_str(), "wb");
			if (fp){
				fwrite(szSigStr, sizeof(char), strlen(szSigStr), fp);
				fclose(fp);
				fp = NULL;
				printf("write sigfile:%s success!\r\n", sigfile.c_str());
			}else{
				printf("write sigfile:%s error!\r\n", sigfile.c_str());
			}
		}
	}
	else
	{
		char szSignBuf[1024] = {0};
		FILE* fp = NULL;
		do 
		{
			fp = fopen(sigfile.c_str(), "rb");
			if(!fp)
				break;
			fread(szSignBuf, 1, sizeof(szSignBuf)-1, fp);
		} while (false);
		if(fp)
		{
			fclose(fp);
			fp = NULL;
		}
		if(!strlen(szSignBuf))
		{
			printf("read sign file:%s failed!\r\n", sigfile.c_str());
			return 0;
		}

		int errorcode = AnyChatRsaVerify(userid, "", appid.c_str(), szSignBuf, timestamp, szKeyBuf);
		printf("RSA verify result, errorcode:%d", errorcode);
	}
	return 0;
}

