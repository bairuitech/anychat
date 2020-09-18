#include <iostream>
#include "anychat.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    CAnyChat anychat;

    DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE |
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_CONFIG_LOCALINI;

    BRAC_InitSDK(NULL,dwFuncMode);
    BRAC_Connect("demo.anychat.cn",8906);
    BRAC_Login("linux","",0);
    BRAC_EnterRoom(2,"",0);

    while(1) {
	printf("AnyChat for linux client still running, Press 'q' exit...\r\n");
	if(getchar() == 'q')
	    break;
    	usleep(100*1000);
    }

    BRAC_Release();
    return 0;
}
