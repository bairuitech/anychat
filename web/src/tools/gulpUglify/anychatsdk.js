// AnyChat for Web SDK
// ��Ҫ�Ը��ļ������κ��޸ģ�������SDKʱ���°汾����ֱ�Ӹ��Ǿɰ汾

/********************************************
 *				�������岿��				*
 *******************************************/

// ��Ƶ�豸���壨API��BRAC_AudioGetVolume��BRAC_AudioSetVolume ���������
var BRAC_AD_WAVEIN = 						0;	// �����豸��Mic
var BRAC_AD_WAVEOUT = 						1;	// ����豸��Wave

// �豸���Ͷ��壨API��BRAC_EnumDevices ���������
var BRAC_DEVICE_VIDEOCAPTURE = 				1;	// ��Ƶ�ɼ��豸
var BRAC_DEVICE_AUDIOCAPTURE = 				2;	// ��Ƶ�ɼ��豸
var BRAC_DEVICE_AUDIOPLAYBACK = 			3;	// ��Ƶ�����豸

// �ں˲������壨API��BRAC_SetSDKOption��BRAC_GetSDKOption ���������
var BRAC_SO_AUDIO_VADCTRL = 				1;	// ��Ƶ���������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
var BRAC_SO_AUDIO_NSCTRL = 					2;	// ��Ƶ�������ƿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
var BRAC_SO_AUDIO_ECHOCTRL = 				3;	// ��Ƶ�����������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
var BRAC_SO_AUDIO_AGCCTRL = 				4;	// ��Ƶ�Զ�������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
var BRAC_SO_AUDIO_CAPTUREMODE = 			5;	// ��Ƶ�ɼ�ģʽ���ã�����Ϊ��int�ͣ�0 ����ģʽ��1 �Ÿ�ģʽ��2 ����OKģʽ��3 ��·����ģʽ��
var BRAC_SO_AUDIO_MICBOOST = 				6;	// ��Ƶ�ɼ�Mic��ǿ���ƣ�����Ϊ��int�ͣ�0 ȡ����1 ѡ�У�2 �豸������[��ѯʱ����ֵ]��
var BRAC_SO_AUDIO_AUTOPARAM = 				7;	// ������Ƶ�ɼ�ģʽ���Զ�ѡ����ʵ���ز������������������������������ʲ����ȣ�����Ϊint�ͣ�1 ���ã�0 �ر�[Ĭ��]��
var BRAC_SO_AUDIO_MONOBITRATE = 			8;	// ���õ�����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
var BRAC_SO_AUDIO_STEREOBITRATE = 			9;	// ����˫����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
var BRAC_SO_AUDIO_PLAYDRVCTRL = 			70;	// ��Ƶ��������ѡ�񣨲���Ϊ��int�ͣ�0Ĭ�������� 1 DSound������ 2 WaveOut������ 3 Java����[Androidƽ̨ʹ��]��
var BRAC_SO_AUDIO_CNGCTRL = 				71;	// �����������ɿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
var BRAC_SO_AUDIO_CODECID = 				72;	// ������Ƶ������ID���ã�����Ϊint�ͣ�-1��ʾĬ�ϣ�������õı�����ID�����ڣ����ں˻����Ĭ�ϵı�������
var BRAC_SO_AUDIO_SOFTVOLMODE = 			73;	// �����������ģʽ���ƣ�����Ϊint�ͣ�1�򿪣�0�ر�[Ĭ��]����ʹ���������ģʽ��������ı�ϵͳ����������
var BRAC_SO_AUDIO_RECORDDRVCTRL = 			74;	// ��Ƶ�ɼ��������ƣ�����Ϊint�ͣ�0Ĭ�������� 1 DSound������ 2 WaveIn������ 3 Java�ɼ�[Androidƽ̨ʹ��]��
var BRAC_SO_AUDIO_ECHODELAY	=				75;	// ��Ƶ���������ӳٲ������ã�����Ϊint�ͣ���λ��ms��
var BRAC_SO_AUDIO_NSLEVEL	=				76;	// ��Ƶ��������ˮƽ�������ã�����Ϊint�ͣ�0 - 3��Ĭ��Ϊ2��ֵԽ������ˮƽԽ�ߣ���������������Խǿ��
var BRAC_SO_AUDIO_CBCODEC	=				77;	// ��Ƶ���ݻص����������ͣ�����Ϊint�ͣ�
var BRAC_SO_AUDIO_ECHOLEVEL	=				78;	// ��Ƶ��������ˮƽ�������ã�����Ϊint�ͣ�0 - 4��Ĭ��Ϊ4��ֵԽ�������������Խǿ��
var BRAC_SO_AUDIO_PLAYCAPTURE	=			79;	// ��Ƶ���Ųɼ��������ã�����Ϊint�ͣ�0 �ر�[Ĭ��]��1 ������


var BRAC_SO_RECORD_VIDEOBR = 				10;	// ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
var BRAC_SO_RECORD_AUDIOBR = 				11;	// ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
var BRAC_SO_RECORD_TMPDIR = 				12;	// ¼���ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
var BRAC_SO_SNAPSHOT_TMPDIR = 				13;	// �����ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
var BRAC_SO_RECORD_FILETYPE	=				140;// ¼���ļ��������ã�����Ϊ��int�ͣ� 0 MP4[Ĭ��], 1 WMV, 2 FLV, 3 MP3��
var BRAC_SO_RECORD_WIDTH	=				141;// ¼����Ƶ������ã�����Ϊ��int�ͣ��磺320��
var BRAC_SO_RECORD_HEIGHT	=				142;// ¼���ļ��߶����ã�����Ϊ��int�ͣ��磺240��
var BRAC_SO_RECORD_FILENAMERULE	=			143;// ¼���ļ����������򣨲���Ϊ��int�ͣ�
var BRAC_SO_RECORD_CLIPMODE	=				144;// ¼����Ƶ�ü�ģʽ������Ϊ��int�ͣ�
var BRAC_SO_RECORD_DISABLEDATEDIR =			145;// ¼���ļ��������ڷ�Ŀ¼���棬ȫ��������ָ���ļ����У�����Ϊ��int�ͣ� 0��ֹ[Ĭ��] 1 ������
var BRAC_SO_RECORD_INSERTIMAGE	=			146;// ¼�ƹ����в���ͼƬ��Json�ַ�������

var BRAC_SO_CORESDK_TMPDIR = 				14;	// ����AnyChat Core SDK��ʱĿ¼������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
var BRAC_SO_CORESDK_MAGICADJUST = 			15;	// �ں˵��Բ���
var BRAC_SO_CORESDK_LOADCODEC = 			16;	// �����ⲿ�������������Ϊ�ַ���TCHAR���ͣ������������ľ���·���������ļ�����������ļ����ľ���·����
var BRAC_SO_CORESDK_USEARMV6LIB = 			17;	// ǿ��ʹ��ARMv6ָ��Ŀ⣬androidƽ̨ʹ�ã�����Ϊ��int�ͣ�1ʹ��ARMv6ָ��� 0�ں��Զ��ж�[Ĭ��]��
var BRAC_SO_CORESDK_USEHWCODEC = 			18;	// ʹ��ƽ̨����Ӳ���������������Ϊint�ͣ�0 ��ʹ��Ӳ���������[Ĭ��]  1 ʹ������Ӳ�����������
var BRAC_SO_CORESDK_REMOTEDEBUG = 			19;	// Զ�̵��ԣ�����Ϊint�ͣ���ʾĿ���û�ID�����ò�������Ϊ�������Ͳ�����

var BRAC_SO_CORESDK_PATH = 					20;	// ����AnyChat Core SDK������·��������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
var BRAC_SO_CORESDK_DUMPCOREINFO = 			21;	// ����ں���Ϣ����־�ļ��У����ڷ�������ԭ�򣨲���Ϊ��int�ͣ�1 �����
var BRAC_SO_CORESDK_MAINVERSION = 			22;	// ��ѯSDK���汾�źţ�����Ϊint�ͣ�
var BRAC_SO_CORESDK_SUBVERSION = 			23;	// ��ѯSDK�Ӱ汾�ţ�����Ϊint�ͣ�
var BRAC_SO_CORESDK_BUILDTIME = 			24;	// ��ѯSDK����ʱ�䣨����Ϊ�ַ���TCHAR���ͣ�
var BRAC_SO_CORESDK_ACTIVESTATE = 			25;	// Ӧ�ó���״̬���ƣ�����Ϊint�ͣ� 1 Ӧ�ó����ڻ״̬�� 0 Ӧ�ó����ڷǻ״̬����������iPhone���豸����ɺ�̨���еĳ���
var BRAC_SO_CORESDK_EXTVIDEOINPUT = 		26;	// �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
var BRAC_SO_CORESDK_EXTAUDIOINPUT = 		27;	// �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
var BRAC_SO_CORESDK_LOWDELAYCTRL = 			28;	// ���ӳ�ģʽ���ƣ�����Ϊint�ͣ�0 �رյ��ӳ�ģʽ[Ĭ��]�� 1 ���õ��ӳ�ģʽ��
var BRAC_SO_CORESDK_NEWGUID	=				29;	// �����µ�GUID�ַ���

var BRAC_SO_LOCALVIDEO_BITRATECTRL = 		30;	// ������Ƶ�����������ã�����Ϊint�ͣ���λbps��ͬ���������ã�VideoBitrate��
var BRAC_SO_LOCALVIDEO_QUALITYCTRL = 		31;	// ������Ƶ�����������ӿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoQuality��
var BRAC_SO_LOCALVIDEO_GOPCTRL = 			32;	// ������Ƶ����ؼ�֡������ƣ�����Ϊint�ͣ�ͬ���������ã�VideoGOPSize��
var BRAC_SO_LOCALVIDEO_FPSCTRL = 			33;	// ������Ƶ����֡�ʿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoFps��
var BRAC_SO_LOCALVIDEO_PRESETCTRL = 		34;	// ������Ƶ����Ԥ��������ƣ�����Ϊint�ͣ�1-5��
var BRAC_SO_LOCALVIDEO_APPLYPARAM = 		35;	// Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
var BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC = 	36;	// ������Ƶ�ɼ��ֱ��ʿ��Ʋ��ԣ�����Ϊint�ͣ�0 �Զ�������ƥ��[Ĭ��]��1 ʹ�òɼ��豸Ĭ�Ϸֱ��ʣ��������õķֱ��ʲ����ɼ��豸֧��ʱ��Ч
var BRAC_SO_LOCALVIDEO_DEINTERLACE = 		37;	// ������Ƶ����֯�������ƣ�����Ϊint�ͣ� 0 �����з���֯����[Ĭ��]��1 ����֯��������������ƵԴ�Ǹ���ɨ��Դ��������źţ�ʱͨ������֯���������߻�������
var BRAC_SO_LOCALVIDEO_WIDTHCTRL = 			38;	// ������Ƶ�ɼ��ֱ��ʿ�ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoWidth��
var BRAC_SO_LOCALVIDEO_HEIGHTCTRL = 		39;	// ������Ƶ�ɼ��ֱ��ʸ߶ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoHeight��
var BRAC_SO_LOCALVIDEO_FOCUSCTRL = 			90;	// ������Ƶ����ͷ�Խ����ƣ�����Ϊint�ͣ�1��ʾ�Զ��Խ��� 0��ʾ�ֶ��Խ���
var BRAC_SO_LOCALVIDEO_PIXFMTCTRL = 		91;	// ������Ƶ�ɼ����ȸ�ʽ���ƣ�����Ϊint�ͣ�-1��ʾ����ƥ�䣬�������Ȳ���ָ����ʽ���ο���BRAC_PixelFormat��
var BRAC_SO_LOCALVIDEO_OVERLAY = 			92;	// ������Ƶ����Overlayģʽ������Ϊint�ͣ�1��ʾ����Overlayģʽ�� 0��ʾ��ͨģʽ[Ĭ��]��
var BRAC_SO_LOCALVIDEO_CODECID = 			93;	// ������Ƶ������ID���ã�����Ϊint�ͣ�-1��ʾĬ�ϣ�������õı�����ID�����ڣ����ں˻����Ĭ�ϵı�������
var BRAC_SO_LOCALVIDEO_ROTATECTRL = 		94;	// ������Ƶ��ת���ƣ�����Ϊint�ͣ�0��ʾ��������ת��1��ʾ��ֱ��ת��
var BRAC_SO_LOCALVIDEO_CAPDRIVER = 			95;	// ������Ƶ�ɼ��������ã�����Ϊint�ͣ�0��ʾ�Զ�ѡ��[Ĭ��]�� 1 Video4Linux, 2 DirectShow, 3 Java�ɼ�[Androidƽ̨ʹ��]��
var BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA = 		96;	// ������Ƶ�ɼ���ɫƫɫ������Ϊint�ͣ�0��ʾ�ر�[Ĭ��]��1 ������
var BRAC_SO_LOCALVIDEO_TVFORMAT	=			104;// ��Ƶ�ɼ���ʽ���ã�����Ϊ��int�ͣ�����ΪDirectShow::strmif.h::AnalogVideoStandard��Ĭ��Ϊ��AnalogVideo_PAL_B��
var BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP	=	105;// ����ʱ�����������Ƶ������Ϊ��int�ͣ� 0 ������[Ĭ��]�� 1 ���ӣ�
var BRAC_SO_LOCALVIDEO_DEVICENAME =			106;// ������Ƶ�ɼ��豸���ƣ��������ô�ָ������ͷ�豸������Ϊ�ַ������ͣ�
var BRAC_SO_LOCALVIDEO_CLIPMODE	=			107;// ������Ƶ�ü�ģʽ������Ϊint�ͣ� 0 �Զ�[Ĭ��]����ֹ�Զ���תʱ��Ч��
var BRAC_SO_LOCALVIDEO_SCREENHWND	=		108;// ��Ļ�ɼ����ھ��
var BRAC_SO_LOCALVIDEO_SCREENFLAGS	=		109;// ��Ļ�ɼ���־������Ϊint�ͣ�
var BRAC_SO_LOCALVIDEO_VIRTUALBK	=		111;// ������Ƶ�������ⱳ�����ַ������ͣ�JSON��ʽ���������ⱳ��·�����Ƿ����Լ����������
var BRAC_SO_LOCALVIDEO_VIDEOCOLOR	=		112;// ��Ƶ��ɫ���ƣ��ַ������ͣ�����ΪJSON��

var BRAC_SO_NETWORK_P2PPOLITIC = 			40;	// ��������P2P���Կ��ƣ�����Ϊ��int�ͣ�0 ��ֹ����P2P��1 ����������P2P[Ĭ��]��2 �ϲ�Ӧ�ÿ���P2P���ӣ�3 ���轨��P2P���ӣ�
var BRAC_SO_NETWORK_P2PCONNECT = 			41;	// ������ָ���û�����P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID�������ӽ����ɹ��󣬻�ͨ����Ϣ�������ϲ�Ӧ�ã�P2P���Ʋ���=2ʱ��Ч
var BRAC_SO_NETWORK_P2PBREAK = 				42;	// �Ͽ���ָ���û���P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID��[�ݲ�֧�֣�����]
var BRAC_SO_NETWORK_TCPSERVICEPORT = 		43;	// ���ñ���TCP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
var BRAC_SO_NETWORK_UDPSERVICEPORT = 		44;	// ���ñ���UDP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
var BRAC_SO_NETWORK_MULTICASTPOLITIC = 		45;	// �鲥���Կ��ƣ�����Ϊint�ͣ�����Ϊ������BRAC_MCPOLITIC_XXXX��
var BRAC_SO_NETWORK_TRANSBUFMAXBITRATE = 	46;	// ���仺�������ļ�������ʿ��ƣ�����Ϊint�ͣ�0 �����ƣ���������ʴ���[Ĭ��]�� �����ʾ�������ʣ���λΪ��bps��
var BRAC_SO_NETWORK_AUTORECONNECT	=		47;	// ��������Զ��������ܿ��ƣ�����Ϊint�ͣ�0 �رգ� 1 ����[Ĭ��]��
var BRAC_SO_NETWORK_MTUSIZE			=		48;	// ���������MTU��С������Ϊint�ͣ�
var BRAC_SO_NETWORK_UDPSTATUS		=		49;	// UDP����ͨ��״̬��ѯ������Ϊint�ͣ�
var BRAC_SO_NETWORK_LARGEDELAY		=		53;	// ������ӳ�ģʽ���������������绷��������Ϊint�ͣ�
var BRAC_SO_NETWORK_IPV6DNS			=		54;	// IPv6�����������ƣ�����Ϊint�ͣ�0 �رգ� 1����[Ĭ��]������ͳ���磨IPv4���£�����IPv6��������������ٶ�


var BRAC_SO_PROXY_FUNCTIONCTRL = 			50;	// �����û������ܿ��ƣ�������Ϊ��int�ͣ�1��������0�رմ���[Ĭ��]��
var BRAC_SO_PROXY_VIDEOCTRL = 				51;	// �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������Ϊint�ͣ���ʾ�����û���userid��
var BRAC_SO_PROXY_AUDIOCTRL = 				52;	// �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������ͬBRAC_SO_PROXY_VIDEOCTRL��

var BRAC_SO_STREAM_MAXBUFFERTIME = 			60;	// ���������ʱ�䣨����Ϊint�ͣ���λ�����룬ȡֵ��Χ��500 ~ 5000��Ĭ�ϣ�800��������ģʽ����ֵ������ģʽ���Զ�����һ��
var BRAC_SO_STREAM_SMOOTHPLAYMODE = 		61;	// ƽ������ģʽ������Ϊint�ͣ�0 �ر�[Ĭ��], 1 �򿪣�����״̬��������Ƶ��֡ʱ��������ţ����ܳ��������ˣ������Ῠס

var BRAC_SO_VIDEOSHOW_MODECTRL = 			80;	// ��Ƶ��ʾģʽ���ƣ�����Ϊ��int�ͣ�0 ��������ʾ��1 ��Ƶ������ʾ��
var BRAC_SO_VIDEOSHOW_SETPRIMARYUSER = 		81;	// ��������ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
var BRAC_SO_VIDEOSHOW_SETOVERLAYUSER = 		82;	// ���õ�����ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
var BRAC_SO_VIDEOSHOW_DRIVERCTRL = 			83;	// ��Ƶ��ʾ�������ƣ�����Ϊ��int�ͣ�0 Ĭ�������� 1 Windows DirectShow��2 Windows GDI��3 SDL, 4 Android2X��
var BRAC_SO_VIDEOSHOW_CLIPMODE =			86;	// Զ����Ƶ��ʾ��ת�ü�ģʽ������Ϊint�ͣ� 0 �Զ�[Ĭ��]��
var BRAC_SO_VIDEOSHOW_CBPIXFMT	=			87;	// ��Ƶ���ݻص���ʽ������Ϊint�ͣ�

var BRAC_SO_CORESDK_TICKOUTUSER	=			110;// �ӷ��������ߵ�ָ���û�������Ϊint�ͣ���ʾĿ���û�ID��

var BRAC_SO_CORESDK_DEVICEMODE	=			130;// �豸ģʽ���ƣ��������豸֮����Ի���ͨ�ţ�������������������Ϊint�ͣ�0 �ر�[Ĭ��]��1 ������
var BRAC_SO_CORESDK_SCREENCAMERACTRL =		131;// ���湲���ܿ��ƣ�����Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 ������
var BRAC_SO_CORESDK_UPLOADLOGINFO =			134;// �ϴ���־��Ϣ��������������Ϊ��int�ͣ�0 �ر�[Ĭ��]�� 1 ������
var BRAC_SO_CORESDK_WRITELOG	=			135;// д�������Ϣ��������־�ļ���
var BRAC_SO_CORESDK_NEWLOGFILE	=			136;// �����µ���־�ļ�
var BRAC_SO_CORESDK_SUPPORTSIP	=			137;// �жϵ�ǰ�Ƿ�֧��SIPͨ��
var BRAC_SO_CORESDK_SUPPORTHTML5	=		138;// �жϵ�ǰ�Ƿ�֧��HTML5
var BRAC_SO_CORESDK_DISABLELOGFILE	=		139;// ��ֹ���ɱ�����־�ļ�
var BRAC_SO_CORESDK_SUPPORTVIDEOCODEC =		210;// ����֧�ֵ���Ƶ������
var BRAC_SO_CORESDK_SUPPORTAUDIOCODEC =		211;// ����֧�ֵ���Ƶ������
var BRAC_SO_CORESDK_DISABLEMEDIACONSUL =	212;// ��ֹý��Э��
var BRAC_SO_CORESDK_QUERYTIMEOUTTIME =		213;// ��Ϣ��ѯ��ʱʱ�䣨����Ϊ��int�ͣ���λ��ms��Ĭ��ֵ1000��
var BRAC_SO_CORESDK_REMOTEASSISTHWND =		214;// Զ��Э�����ھ��
var BRAC_SO_CORESDK_REMOTEASSISTXPOS =		215;// Զ��Э�����ڹ�����λ�ã�X��
var BRAC_SO_CORESDK_REMOTEASSISTYPOS =		216;// Զ��Э�����ڹ�����λ�ã�Y��
var BRAC_SO_CORESDK_DISABLEDNSCONNECT=		219;// ����DNSѰַ
var BRAC_SO_CORESDK_LOGFILEROOTPATH	=		220;// ��־�ļ������·������־�ض��򣬲���Ϊ�ַ���������·����
var BRAC_SO_CORESDK_LOGFILERULE	=			221;// �ͻ�����־�ļ�������򣨲���Ϊint�ͣ�0 �Զ�����[Ĭ��] 1 �����ڱ��棬�����ǣ�
var BRAC_SO_CORESDK_FILEENCANDDEC	=		222;// �ļ��ӽ��ܿ��ƣ�����Ϊ�ַ������ͣ�JSON��ʽ��
var BRAC_SO_CORESDK_PPTHELPERINIT	=		223;// PPT����������ʼ��
var BRAC_SO_CORESDK_PPTFILECTRL		=		224;// PPT�ļ�����
var BRAC_SO_CORESDK_CBMEDIASTREAM	=		225;// �ص�ԭʼ����Ƶ��
var BRAC_SO_CORESDK_CBVIDEOSTREAM	=		226;// �ص�ԭʼ��Ƶ��
var BRAC_SO_CORESDK_CBAUDIOSTREAM	=		227;// �ص�ԭʼ��Ƶ��
var BRAC_SO_CORESDK_STREAMADAPTIVE	=		228;// ��ý������Ӧ���ƣ�����Ϊint�ͣ�0 �ر� 1 ����[Ĭ��]��
var BRAC_SO_CORESDK_MAXTRANSFILESIZE=		229;// �����������ļ���С������Ϊint�ͣ���λ��MByte��
var BRAC_SO_CORESDK_USESERVERTIME	=		230;// ʹ�÷�����ʱ���������Ϊint�ͣ�0 �ر�[Ĭ��] 1 ������
var BRAC_SO_CORESDK_APPMONITORLIST	=		231;// Ӧ�ó����б�Ӧ�ó�����ģ��ʹ�ã�����Ϊ�ַ�����
var BRAC_SO_CORESDK_SSLCERTCHAIN	=		232;// SSL֤����
var BRAC_SO_CORESDK_SUPPORTMEDIACODEC=		233;// ����֧�ֵı�������Ϣ�����ڱ���Э��
var BRAC_SO_CORESDK_SETUSERAPPINFO	=		236;// �����û�APP��Ϣ
var BRAC_SO_CORESDK_LASTERRORCODE	=		237;// ��ȡ���ĳ������



var BRAC_SO_UDPTRACE_MODE		=			160;// UDP���ݰ�����ģʽ
var BRAC_SO_UDPTRACE_PACKSIZE	=			161;// UDP���ݰ����ٵĴ�С����λ��BYTE
var BRAC_SO_UDPTRACE_BITRATE	=			162;// UDP���ݰ����ٵİ����ʣ���λ��bps
var BRAC_SO_UDPTRACE_START		=			163;// UDP���ݰ����ٿ��ƣ�����Ϊint�ͣ�1 ������ 0 ֹͣ��
var BRAC_SO_UDPTRACE_LOCALRECVNUM	=		164;// UDP���ݰ����ٱ��ؽ��հ�����
var BRAC_SO_UDPTRACE_SERVERRECVNUM	=		165;// UDP���ݰ����ٷ��������հ�����
var BRAC_SO_UDPTRACE_SOURCESENDNUM	=		166;// UDP���ݰ�����Դ��������
var BRAC_SO_UDPTRACE_SENDUSERID	=			167;// UDP���ݰ�����Դ�û�ID
var BRAC_SO_UDPTRACE_NETDELAY	=			168;// UDP���ݰ������ӳ٣���λ��ms��-1��ʾδ֪


// �û���ý�����������壨API��BRAC_GetUserStreamInfo ���������
var BRAC_STREAMINFO_VIDEOWIDTH	=			180;// ��Ƶ�����
var BRAC_STREAMINFO_VIDEOHEIGHT	=			181;// ��Ƶ���߶�
var BRAC_STREAMINFO_VIDEOFPS	=			182;// ��Ƶ��֡��
var BRAC_STREAMINFO_VIDEOBITRATE=			183;// ��Ƶ�����ʣ���λ��bps
var BRAC_STREAMINFO_VIDEOCODECID=			184;// ��Ƶ��������ID
var BRAC_STREAMINFO_VIDEOPACKLOSSRATE=		185;// ��Ƶ��������
var BRAC_STREAMINFO_VIDEODEVICENAME	=		186;// ��Ƶ�ɼ��豸����
var BRAC_STREAMINFO_AUDIOCHANNELS	=		190;// ��Ƶ��ͨ����
var BRAC_STREAMINFO_AUDIOSAMPLERATE	=		191;// ��Ƶ��������
var BRAC_STREAMINFO_AUDIOBITRATE	=		192;// ��Ƶ�����ʣ���λ��bps
var BRAC_STREAMINFO_AUDIOCODECID	=		193;// ��Ƶ��������ID
var BRAC_STREAMINFO_AUDIOPACKLOSSRATE=		194;// ��Ƶ��������
var BRAC_STREAMINFO_AUDIODEVICENAME	=		195;// ��Ƶ�ɼ��豸����

var BRAC_SO_OBJECT_INITFLAGS	=			200;// ҵ�������ݳ�ʼ��
var BRAC_SO_CLOUD_APPGUID		=			300;// ��ƽ̨Ӧ��GUID������Ϊ���ַ������ͣ����ӷ�����֮ǰ���ã�
var BRAC_SO_CLOUD_ACCTYPE		=			301;// ��ƽ̨Ӧ�ü����˺�����
var BRAC_SO_CLOUD_APPID3RD		=			302;// ��ƽ̨Ӧ�ü���ʱ������ƽ̨��Ӧ��GUID

var BRAC_SO_ENABLEWEBSERVICE 	=			11002;	// ��������Web����
var BRAC_SO_LOCALPATH2URL		=			11003;	// ������·��ת��ΪURL��ַ
var BRAC_SO_GETTASKPATHNAME		=			11004;	// ���ݴ�������ID��ȡ�ļ�·��
var BRAC_SO_VIDEOBKIMAGE		=			11006;	// ������Ƶ����ͼƬ

// ����������Ϣ�������壨API��BRAC_QueryTransTaskInfo ���������
var BRAC_TRANSTASK_PROGRESS		= 			1;	// ����������Ȳ�ѯ������Ϊ��DOUBLE�ͣ�����ֵ0.0 ~ 100.0�� �����Ϊ��DWORD�ͣ�����ֵ0 ~ 100��
var BRAC_TRANSTASK_BITRATE		= 			2;	// ��������ǰ�������ʣ�����Ϊ��int�ͣ���λ��bps��
var BRAC_TRANSTASK_STATUS		= 			3;	// ��������ǰ״̬������Ϊ��int�ͣ�
var BRAC_TRANSTASK_SAVEASPATH	= 			4;	// �ļ������������Ϊ·�����ã����ļ���������Ϊ�ַ���TCHAR���ͣ�
var BRAC_TRANSTASK_SOURCEFILE	=			5;	// Դ�ļ�������·��������Ϊ�ַ�����TCHAR���ͣ�
var BRAC_TRANSTASK_JSONSTATUS	=			6;	// ��������״̬��Json�ַ���

// ¼���ܱ�־���壨API��BRAC_StreamRecordCtrl ���������
var BRAC_RECORD_FLAGS_VIDEO		=	0x00000001;	// ¼����Ƶ
var BRAC_RECORD_FLAGS_AUDIO		=	0x00000002;	// ¼����Ƶ
var BRAC_RECORD_FLAGS_SERVER	=	0x00000004;	// ��������¼��
var BRAC_RECORD_FLAGS_MIXAUDIO 	=	0x00000010;	// ¼����Ƶʱ���������˵�����������¼��
var BRAC_RECORD_FLAGS_MIXVIDEO	=	0x00000020;	// ¼����Ƶʱ���������˵���Ƶ���Ӻ�¼��
var BRAC_RECORD_FLAGS_ABREAST	=	0x00000100;	// ¼����Ƶʱ���������˵���Ƶ����¼��
var BRAC_RECORD_FLAGS_STEREO	=	0x00000200;	// ¼����Ƶʱ���������˵��������Ϊ��������¼��
var BRAC_RECORD_FLAGS_SNAPSHOT	=	0x00000400;	// ����
var BRAC_RECORD_FLAGS_LOCALCB	=	0x00000800;	// �������ػص�
var BRAC_RECORD_FLAGS_STREAM	=	0x00001000;	// ����Ƶ������¼�ƣ�Ч�ʸߣ������ܴ�����Ƶ������ת�����⣩
var BRAC_RECORD_FLAGS_USERFILENAME=	0x00002000;	// �û��Զ����ļ���
var BRAC_RECORD_FLAGS_FILEMD5 	=	0x00040000;	// ����¼���ļ���MD5ֵ

// �ͻ��ˡ���������¼�Ʊ�־���屣��ͳһ
var ANYCHAT_RECORD_FLAGS_VIDEO	=	BRAC_RECORD_FLAGS_VIDEO;
var ANYCHAT_RECORD_FLAGS_AUDIO	=	BRAC_RECORD_FLAGS_AUDIO;
var ANYCHAT_RECORD_FLAGS_SERVER	=	BRAC_RECORD_FLAGS_SERVER;
var ANYCHAT_RECORD_FLAGS_MIXAUDIO =	BRAC_RECORD_FLAGS_MIXAUDIO;
var ANYCHAT_RECORD_FLAGS_MIXVIDEO =	BRAC_RECORD_FLAGS_MIXVIDEO;
var ANYCHAT_RECORD_FLAGS_ABREAST =	BRAC_RECORD_FLAGS_ABREAST;
var ANYCHAT_RECORD_FLAGS_STEREO	=	BRAC_RECORD_FLAGS_STEREO;
var ANYCHAT_RECORD_FLAGS_SNAPSHOT =	BRAC_RECORD_FLAGS_SNAPSHOT;
var ANYCHAT_RECORD_FLAGS_LOCALCB =	BRAC_RECORD_FLAGS_LOCALCB;
var ANYCHAT_RECORD_FLAGS_STREAM =	BRAC_RECORD_FLAGS_STREAM;
var ANYCHAT_RECORD_FLAGS_USERFILENAME = BRAC_RECORD_FLAGS_USERFILENAME;
var ANYCHAT_RECORD_FLAGS_ERRORCODE =	0x00004000;	// ֧�ֳ������
var ANYCHAT_RECORD_FLAGS_MULTISTREAM=	0x00008000;	// ֧�ֶ�·����¼�ƣ����գ�
var ANYCHAT_RECORD_FLAGS_CANCEL	=		0x00010000;	// ȡ��¼��ɾ��¼���ļ�
var ANYCHAT_RECORD_FLAGS_BUFFERCB =		0x00020000;	// ���������ݻص�
var ANYCHAT_RECORD_FLAGS_FILEMD5 =		0x00040000;	// ����¼���ļ���MD5ֵ

// ��Ƶ�ü�ģʽ����
var ANYCHAT_VIDEOCLIPMODE_UNKNOW	=		-1;	// δ֪ģʽ������Ҫ���ü�ʱʹ��
var ANYCHAT_VIDEOCLIPMODE_AUTO		=		0;	// Ĭ��ģʽ�������������вü���Ȼ�����������죬���汣�ֱ����������ü�����ϴ�
var ANYCHAT_VIDEOCLIPMODE_OVERLAP	=		1;	// �ص�ģʽ��ֻȡ�����Ч���֣��Ա�Ե���вü�
var ANYCHAT_VIDEOCLIPMODE_SHRINK	=		2;	// ��Сģʽ����С�����ʵı����������вü�
var ANYCHAT_VIDEOCLIPMODE_STRETCH	=		3;	// ƽ��ģʽ�������вü��������ܵ��»��治�ɱ���
var ANYCHAT_VIDEOCLIPMODE_DYNAMIC	=		4;	// ��̬ģʽ�����ϲ�Ӧ�ø��ݷֱ�����������ʾ���棬���ֻ��治����

// �鲥���Զ���
var BRAC_MCPOLITIC_DISABLE			=		0;	// ִ�з�����·�ɲ��ԣ���ֹ�����鲥����[Ĭ��]
var BRAC_MCPOLITIC_ONLYLOCALMC		=		1;	// ���Է�����·�ɲ��ԣ�ֻ��ͻ��˱����鲥��㲥ý����
var BRAC_MCPOLITIC_SERVERANDLOCALMC	=		2;	// ִ�з�����·�ɲ��ԣ�ͬʱ�ڿͻ��˱��ط����鲥����
var BRAC_MCPOLITIC_ONLYSERVERMC		=		3;	// ���Է�����·�ɲ��ԣ�ֻ������������鲥��㲥ý����
var BRAC_MCPOLITIC_SERVERANDSERVERMC=		4;	// ִ�з�����·�ɲ��ԣ�ͬʱ�ڷ������˷����鲥����

// �鲥���ܱ�־����
var BRAC_MCFLAGS_JOINGROUP		=	0x00000001;	// ����ಥ��
var BRAC_MCFLAGS_LEAVEGROUP		=	0x00000002;	// �뿪�ಥ��
var BRAC_MCFLAGS_SENDDATA		=	0x00000010;	// ���ݷ��ͱ�־��ָʾ�öಥ�����ڷ�������
var BRAC_MCFLAGS_RECVDATA		=	0x00000020;	// ���ݽ��ձ�־��ָʾ�öಥ�����ڽ�������

// �û�״̬��־���壨API��BRAC_QueryUserState ���������
var BRAC_USERSTATE_CAMERA 		= 			1;	// �û�����ͷ״̬������ΪDWORD�ͣ�
var BRAC_USERSTATE_HOLDMIC 		= 			2;	// �û���Ƶ�豸״̬������ΪDWORD�ͣ�����ֵ��0 ��Ƶ�ɼ��رգ� 1 ��Ƶ�ɼ�������
var BRAC_USERSTATE_SPEAKVOLUME 	= 			3;	// �û���ǰ˵������������ΪDOUBLE���ͣ�0.0 ~ 100.0����
var BRAC_USERSTATE_RECORDING 	= 			4;	// �û�¼������״̬������ΪDWORD�ͣ�
var	BRAC_USERSTATE_LEVEL 		= 			5;	// �û����𣨲���ΪDWORD�ͣ�
var BRAC_USERSTATE_NICKNAME 	= 			6;	// �û��ǳƣ�����Ϊ�ַ���TCHAR���ͣ�
var BRAC_USERSTATE_LOCALIP 		= 			7;	// �û�����IP��ַ������������Ϊ�ַ���TCHAR���ͣ�
var BRAC_USERSTATE_INTERNETIP 	= 			8;	// �û�������IP��ַ������Ϊ�ַ���TCHAR���ͣ�
var BRAC_USERSTATE_VIDEOBITRATE = 			9;	// �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
var BRAC_USERSTATE_AUDIOBITRATE = 			10;	// �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
var BRAC_USERSTATE_P2PCONNECT 	= 			11;	// ��ѯ�����û���ָ���û��ĵ�ǰP2P����״̬������ΪDWORD���ͣ�����ֵ��0 P2P��ͨ�� 1 P2P���ӳɹ�[TCP]��2 P2P���ӳɹ�[UDP]��3 P2P���ӳɹ�[TCP��UDP]��
var BRAC_USERSTATE_NETWORKSTATUS= 			12;	// ��ѯָ���û�������״̬������ΪDWORD���ͣ�����ֵ��0 ������1 �Ϻã�2 һ�㣬3 �ϲ4 �ǳ����ע����ѯ�����Ҫ>1s
var BRAC_USERSTATE_VIDEOSIZE 	= 			13;	// ��ѯָ���û�����Ƶ�ֱ��ʣ�����ΪDWORD���ͣ�����ֵ����16λ��ʾ��ȣ���16λ��ʾ�߶ȣ�
var BRAC_USERSTATE_PACKLOSSRATE = 			14;	// ��ѯָ���û���������ý�����ݶ����ʣ�����ΪDWORD���ͣ�����ֵ��0 - 100���磺����ֵΪ5����ʾ������Ϊ5%��
var BRAC_USERSTATE_DEVICETYPE 	=			15; // ��ѯָ���û����ն����ͣ�����ΪDWORD���ͣ�����ֵ��0 Unknow�� 1 Windows��2 Android��3 iOS��4 Web��5 Linux��6 Mac��7 Win Phone��8 WinCE��
var BRAC_USERSTATE_SELFUSERSTATUS=			16;	// ��ѯ�����û��ĵ�ǰ״̬������ΪDWORD���ͣ�����ֵ��0 Unknow��1 Connected��2 Logined��3 In Room��4 Logouted��5 Link Closed��
var BRAC_USERSTATE_SELFUSERID	=			17;	// ��ѯ�����û���ID������ΪDWORD���ͣ����û���¼�ɹ��������û�ʵ�ʵ�userid�����򷵻�-1��
var BRAC_USERSTATE_VIDEOROTATION=			18;	// ��ѯָ���û��ĵ�ǰ��Ƶ��ת�Ƕȣ�����ΪDWORD���ͣ����ؽǶ�ֵ��
var BRAC_USERSTATE_VIDEOMIRRORED=			19;	// ��ѯָ���û�����Ƶ�Ƿ���Ҫ����ת
var BRAC_USERSTATE_AUDIOCODECID	=			20;	// ��ѯָ���û�����Ƶ������ID
var BRAC_USERSTATE_VIDEOCODECID	=			21;	// ��ѯָ���û�����Ƶ������ID
var BRAC_USERSTATE_RESENDLOSSRATE=			22;// ����������Ķ����ʣ�����ΪDWORD���ͣ�����ֵ��0 - 100���磺����ֵΪ5����ʾ������Ϊ5%��


// SDK��Ϣ���壨����OnNotifyMessage�¼����ж��¼������ͣ�
var WM_GV = 0x0400 + 200;
var WM_GV_CONNECT			=	WM_GV + 1;		// �ͻ������ӷ�������wParam��BOOL����ʾ�Ƿ����ӳɹ�
var WM_GV_LOGINSYSTEM		=	WM_GV + 2;		// �ͻ��˵�¼ϵͳ��wParam��INT����ʾ�Լ����û�ID�ţ�lParam��INT����ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
var WM_GV_ENTERROOM			=	WM_GV + 3;		// �ͻ��˽��뷿�䣬wParam��INT����ʾ�����뷿���ID�ţ�lParam��INT����ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
var WM_GV_MICSTATECHANGE	=	WM_GV + 4;		// �û�����Ƶ�豸״̬�仯��Ϣ��wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��Ƿ��Ѵ���Ƶ�ɼ��豸
var WM_GV_USERATROOM		=	WM_GV + 5;		// �û����루�뿪�����䣬wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��ǽ��루TRUE�����뿪��FALSE������
var WM_GV_LINKCLOSE			=	WM_GV + 6;		// ���������ѹرգ�����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ������wParam��INT����ʾ���ӶϿ���ԭ��
var WM_GV_ONLINEUSER		=	WM_GV + 7;		// �յ���ǰ����������û���Ϣ�����뷿��󴥷�һ�Σ�wParam��INT����ʾ�����û����������Լ�����lParam��INT����ʾ����ID
var WM_GV_CAMERASTATE		=	WM_GV + 11;		// �û�����ͷ״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ����ͷ�ĵ�ǰ״̬������Ϊ��GV_CAMERA_STATE_XXXX
var WM_GV_CHATMODECHG		=	WM_GV + 12;		// �û�����ģʽ�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ����ģʽ
var WM_GV_ACTIVESTATE		=	WM_GV + 13;		// �û��״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ�״̬
var WM_GV_P2PCONNECTSTATE	=	WM_GV + 14;		// �����û��������û���P2P��������״̬�����仯��wParam��INT����ʾ�����û�ID�ţ�lParam��INT����ʾ�����û��������û��ĵ�ǰP2P��������״̬
var WM_GV_VIDEOSIZECHG		=	WM_GV + 15;		// �û���Ƶ�ֱ��ʷ����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û�����Ƶ�ֱ������ֵ����16λ��ʾ��ȣ���16λ��ʾ�߶ȣ�
var WM_GV_USERINFOUPDATE	=	WM_GV + 16;		// �û���Ϣ����֪ͨ��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�������
var WM_GV_FRIENDSTATUS		=	WM_GV + 17;		// ��������״̬�仯��wParam��INT����ʾ�����û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ�״̬��0 ���ߣ� 1 ����
var WM_GV_OBJECTEVENT		=	WM_GV + 18;		// �����¼�֪ͨ��wParam��INT����ʾ�������ͣ�lParam��INT����ʾ����ID
var WM_GV_SESSIONKEEP		=	WM_GV + 19;		// �Ự�����¼���wParam��INT����ʾ�Ự����״̬��0 �Ự���ֿ�ʼ�� 1 �Ự���ֽ�����lParam��INT����ʾ�������

var WM_GV_PRIVATEREQUEST	=	WM_GV + 21;		// �û�����˽������wParam��INT����ʾ�����ߵ��û�ID�ţ�lParam��INT����ʾ˽�������ţ���ʶ������
var WM_GV_PRIVATEECHO		=	WM_GV + 22;		// �û��ظ�˽������wParam��INT����ʾ�ظ��ߵ��û�ID�ţ�lParam��INT��Ϊ�������
var WM_GV_PRIVATEEXIT		=	WM_GV + 23;		// �û��˳�˽�ģ�wParam��INT����ʾ�˳��ߵ��û�ID�ţ�lParam��INT��Ϊ�������
var WM_GV_SERVERCFGUPDATE	=	WM_GV + 24;		// ���������ò�������

var WM_GV_EXTENDBTNPRESS	=	WM_GV + 31;		// �û�������չ��ť��wParam��INT����ʾ��ť����Ӧ���û�ID�ţ�lParam��DWORD��ָʾ��ť�����½ǣ�������Ļλ��(x,y)���û��������øò�����ʾ�˵���
var WM_GV_VIDEOFULLSCREEN	=	WM_GV + 32;		// �û���Ƶȫ��֪ͨ��wParam��INT����ʾ�û�ID��lParam(DWORD)��ʾ��ǰ��Ƶ�Ƿ�ȫ����ʾ

var WM_GV_SDKWARNING      	=   WM_GV + 41;		// SDK������Ϣ����SDK�����й������Լ췢���쳣״̬ʱ�������ϲ㷢�͸���Ϣ��wParam��INT����ʾ������룬����Ϊ��GV_ERR_WARNING_XXXX

var WM_GV_AUDIOPLAYCTRL		=	WM_GV + 100;	// ��Ƶ�����豸���ƣ�wParam:1 �򿪲������� 0 �رղ������� lParam��profile��androidƽ̨�ڲ�ʹ��
var WM_GV_AUDIORECCTRL		=	WM_GV + 101;	// ��Ƶ¼���豸���ƣ�wParam:1 ����Ƶ�ɼ��豸��0 �ر���Ƶ�ɼ��豸
var WM_GV_VIDEOCAPCTRL		=	WM_GV + 102;	// ��Ƶ�ɼ����ƣ�wParam: 1 ��ʼ�ɼ��� 0 �رղɼ�

// ����״̬��־���壨API��BRAC_QueryRoomState ���������
var BRAC_ROOMSTATE_ROOMNAME		=			1;	// �������ƣ�����Ϊ�ַ���TCHAR���ͣ�
var BRAC_ROOMSTATE_ONLINEUSERS	=			2;	// ���������û���������ΪDWORD�ͣ��������Լ�

// ��Ƶ�����¼����Ͷ��壨API��BRAC_VideoCallControl ���������VideoCallEvent�ص�������
var BRAC_VIDEOCALL_EVENT_REQUEST=			1;	// ��������
var BRAC_VIDEOCALL_EVENT_REPLY 	=			2;	// ��������ظ�
var BRAC_VIDEOCALL_EVENT_START 	=			3;	// ��Ƶ���лỰ��ʼ�¼�
var BRAC_VIDEOCALL_EVENT_FINISH =			4;	// �Ҷϣ����������лỰ

// ��Ƶ���б�־���壨API��BRAC_VideoCallControl ���������
var BRAC_VIDEOCALL_FLAGS_AUDIO		=	0x0001;	// ����ͨ��
var BRAC_VIDEOCALL_FLAGS_VIDEO		=	0x0002;	// ��Ƶͨ��
var BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	=	0x0010;	// ��ֹԴ�����жˣ���Ƶ
var BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	=	0x0020;	// ��ֹԴ�����жˣ���Ƶ
var BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	=	0x0040;	// ��ֹĿ�꣨�����жˣ���Ƶ
var BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	=	0x0080;	// ��ֹĿ�꣨�����жˣ���Ƶ
var BRAC_VIDEOCALL_FLAGS_ASSISTREQ	=	0x0100;	// ����Ŀ���û�Զ��Э��
var BRAC_VIDEOCALL_FLAGS_CONTROLREQ	=	0x0200;	// �������Ŀ���û�

// ������붨��
var GV_ERR_SUCCESS			=	0;				// �ɹ�
var GV_ERR_PLUGINNOINSTALL	=	1010000;		// ���û�а�װ
var GV_ERR_PLUGINOLDVERSION =	1010001;		// ����汾̫��
var GV_ERR_SESSION_QUIT		= 	100101;			// Դ�û����������Ự
var GV_ERR_SESSION_OFFLINE	= 	100102;			// Ŀ���û�������
var GV_ERR_SESSION_BUSY		= 	100103;			// Ŀ���û�æ
var GV_ERR_SESSION_REFUSE	= 	100104;			// Ŀ���û��ܾ��Ự
var GV_ERR_SESSION_TIMEOUT	= 	100105;			// �Ự����ʱ
var GV_ERR_SESSION_DISCONNECT=	100106;			// �������

// Զ����Ƶ����������־����
var BRAC_ROTATION_FLAGS_MIRRORED	=	0x1000;	// ͼ����Ҫ����ת
var BRAC_ROTATION_FLAGS_ROTATION90	=	0x2000;	// ˳ʱ����ת90��
var BRAC_ROTATION_FLAGS_ROTATION180	=	0x4000;	// ˳ʱ����ת180��
var BRAC_ROTATION_FLAGS_ROTATION270	=	0x8000;	// ˳ʱ����ת270��

// �û���Ϣ�������Ͷ��壨API��BRAC_UserInfoControl ���������
var BRAC_USERINFO_CTRLCODE_ROTATION	=		8;	// ��ָ�����û���Ƶ����ʾʱ��ת��wParamΪ��ת�ǶȲ���
var BRAC_USERINFO_CTRLCODE_DEBUGLOG	=		9;	// ��������û��ĵ�����־��wParamΪ������־����
var BRAC_USERINFO_CTRLCODE_LVORIENTFIX	=	10;	// ������Ƶ�ɼ�����������wParamΪ���������lParamΪ�����Ƕ�

// ��������Ϣ��ѯ�������壨API��BRAC_QueryInfoFromServer ���������
var ANYCHAT_SERVERQUERY_USERIDBYNAME	=	1;	// �����û��ǳƲ�ѯ�û�ID
var ANYCHAT_SERVERQUERY_USERIDBYSTRID	=	2;	// �����ַ���ID��ѯ�û�ID
var ANYCHAT_SERVERQUERY_STRIDBYUSERID	=	3;	// �����û�ID��ѯ�ַ���ID
var ANYCHAT_SERVERQUERY_NAMEBYUSERID	=	4;	// �����û�ID��ѯ�û���
var ANYCHAT_SERVERQUERY_NAMEBYSTRID		=	5;	// �����ַ���ID��ѯ�û���
var ANYCHAT_SERVERQUERY_USERINFOBYID	=	6;	// �����û�ID��ѯ�û���Ϣ
var ANYCHAT_SERVERQUERY_PPTFILEINFO		=	10;	// PPT�ļ���Ϣ
var ANYCHAT_SERVERQUERY_QUEUEAGENTINFO	=	100;// ��ѯָ�����е���ϯ������Ϣ
var ANYCHAT_SERVERQUERY_RUNNINGSTATUS	=	200;// ��ѯ����������״̬
var ANYCHAT_SERVERQUERY_ONLINEUSERS		=	201;// ��ѯ�����������û���

// SDK���Ƴ������壨API��BRAC_SDKControl ���������
var ANYCHAT_SDKCTRL_BASE				=	1;	// �������ܿ���
var ANYCHAT_SDKCTRL_USERBUFFER			=	3;	// �û��������������
var ANYCHAT_SDKCTRL_INVOKEEVENT			=	4;	// �����첽�¼�
var ANYCHAT_SDKCTRL_RECORD				=	5;	// ����Ƶ¼��
var ANYCHAT_SDKCTRL_CERTCHECK           =   6;  // ��Ȩ���ܼ��
var ANYCHAT_SDKCTRL_OBJECT				=	20;	// �������
var ANYCHAT_SDKCTRL_VIDEOCALL			=	30;	// ���п���
var ANYCHAT_SDKCTRL_USERINFO			=	40;	// �û���Ϣ����
var ANYCHAT_SDKCTRL_STREAMPLAY			=	50;	// ��ý�岥��
var ANYCHAT_SDKCTRL_MEDIAPROCESS		=	51;	// ��ý�崦�����
var ANYCHAT_SDKCTRL_NETWORK				=	60;	// �������
var ANYCHAT_SDKCTRL_MEDIA				=	70;	// ý�����
var ANYCHAT_SDKCTRL_RECORDTAG			=	71;	// ¼���ǩ
var ANYCHAT_SDKCTRL_SCREENCAPPARAM		=	72;	// ��Ļ�ɼ���������
var ANYCHAT_SDKCTRL_FILEDELETE			=	80;	// ɾ���ļ�
var ANYCHAT_SDKCTRL_FILEINFO			=	81;	// ��ȡ�ļ���Ϣ
var ANYCHAT_SDKCTRL_DISKSIZE			=	82;	// ��ȡ��������
var ANYCHAT_SDKCTRL_FILEENCRYPT			=	83;	// �ļ��ӽ��ܿ���
var ANYCHAT_SDKCTRL_DELETEDIR			=	84;	// ɾ��Ŀ¼
var ANYCHAT_SDKCTRL_CREATEDIR			=	85;	// ����Ŀ¼
var ANYCHAT_SDKCTRL_DIRCLEAN			=	86;	// Ŀ¼����
var ANYCHAT_SDKCTRL_FINDFILE			=	87;	// �����ļ�
var ANYCHAT_SDKCTRL_PPTHELPERINIT		=	90;	// PPT����������ʼ��
var ANYCHAT_SDKCTRL_PPTFILECTRL			=	91;	// PPT�ļ�����
var ANYCHAT_SDKCTRL_PPTFILEINFO			=	92;	// PPT�ļ���Ϣ
var ANYCHAT_SDKCTRL_BUSINESS			=	95;	// ҵ�����
var ANYCHAT_SDKCTRL_MEDIAFILTERINIT		=	96;	// ý���������ʼ��
var ANYCHAT_SDKCTRL_VIDEODEVICEINFO		=	97;	// ��ȡ��Ƶ�ɼ��豸��Ϣ
var ANYCHAT_SDKCTRL_UPDATERECUSERSTR	=	98;	// ����¼���û�����
var ANYCHAT_SDKCTRL_SYNCRECORD			=	99;	// ͬ��¼���������
var ANYCHAT_SDKCTRL_BUSINESSBUFFER		=	100;// ҵ�񻺳�������
var ANYCHAT_SDKCTRL_LIVESTREAM			=	101;// ֱ��ҵ�����
var ANYCHAT_SDKCTRL_AIABILITY			=	102;// AI����
var ANYCHAT_SDKCTRL_APPBUFFER			=	103;// APP�Զ��建����
var ANYCHAT_SDKCTRL_FACEEMOTIONCTRL		=	300;// ΢�������


// ý�岥���¼����Ͷ���
var ANYCHAT_STREAMPLAY_EVENT_START		=	3;	// ���ſ�ʼ�¼�
var ANYCHAT_STREAMPLAY_EVENT_FINISH		=	4;	// ���Ž����¼�

// ý�岥�ű�־���壨API��BRAC_StreamPlayInit ���������
var ANYCHAT_STREAMPLAY_FLAGS_REPLACEAUDIOINPUT 	= 0x00000001;	// ������Ƶ�����汾����Ƶ���루Mic��
var ANYCHAT_STREAMPLAY_FLAGS_REPLACEVIDEOINPUT 	= 0x00000002;	// ������Ƶ�����汾����Ƶ���루Camera��
var ANYCHAT_STREAMPLAY_FLAGS_CALLBACKDATA		= 0x00000010;	// �ص����ݸ��ϲ�
var ANYCHAT_STREAMPLAY_FLAGS_PPTPLAY			= 0x00000080;	// ˫¼���ս�ʾPPT����


// ý�岥����Ϣ���Ͷ��壨API��BRAC_StreamPlayGetInfo ���������
var ANYCHAT_STREAMPLAY_INFO_JSONVALUE	=	1;	// �������в�����Ϣ��Json�ַ���

// ý�岥�ſ������Ͷ��壨API��BRAC_StreamPlayControl ���������
var ANYCHAT_STREAMPLAY_CTRL_START		=	1;	// ��ʼ����
var ANYCHAT_STREAMPLAY_CTRL_PAUSE		=	2;	// ��ͣ����
var ANYCHAT_STREAMPLAY_CTRL_STOP		=	3;	// ֹͣ����
var ANYCHAT_STREAMPLAY_CTRL_SEEK		=	4;	// λ���϶�
var ANYCHAT_STREAMPLAY_CTRL_SPEEDCTRL	=	5;	// �ٶȵ���
var ANYCHAT_STREAMPLAY_CTRL_OPENLOOP	=	6;	// ��ѭ������
var ANYCHAT_STREAMPLAY_CTRL_CLOSELOOP	=	7;	// �ر�ѭ������


// CoreSDK�¼����Ͷ��壨�ص�������BRAC_CoreSDKEvent_CallBack������
var ANYCHAT_CORESDKEVENT_BASEEVENT		=	1;	// SDK�����¼�
var ANYCHAT_CORESDKEVENT_CONNECTHOLD	=	2;	// ���ӱ����¼�
var ANYCHAT_CORESDKEVENT_CAMERASTATE	=	10;	// ����ͷ״̬�¼�
var ANYCHAT_CORESDKEVENT_MICSTATE		=	11;	// Mic״̬�¼�
var ANYCHAT_CORESDKEVENT_TRANSFILE		=	12;	// �ļ������¼�
var ANYCHAT_CORESDKEVENT_RECORDSTATUS	=	13;	// ¼��״̬�¼�
var ANYCHAT_CORESDKEVENT_STREAMPLAY		=	30;	// ý�岥���¼�
var ANYCHAT_CORESDKEVENT_PPTHELPER		=	31;	// PPTHelper�¼�
var ANYCHAT_CORESDKEVENT_BUSINESS		=	32;	// ҵ���¼�
var ANYCHAT_CORESDKEVENT_DEVICEFAIL		=	33;	// �豸ʧ���¼�
var ANYCHAT_CORESDKEVENT_MEDIABUFFER	=	34;	// ý�建�����¼�
var ANYCHAT_CORESDKEVENT_USERBUFFER		=	35;	// �û��������¼�
var ANYCHAT_CORESDKEVENT_MEDIAPROCESS	=	36;	// ý�崦���¼�
var ANYCHAT_CORESDKEVENT_FACEEMOTION	=	40;	// ΢��������
var ANYCHAT_CORESDKEVENT_REGEDITDATA	=	41;	// ���ݽӿڷ�������
var ANYCHAT_CORESDKEVENT_REQUESTEX		=	42;	// ��չ���󷵻�����
var ANYCHAT_CORESDKEVENT_BUSINESSBUFFER	=	100;// ҵ�񻺳����¼�
var ANYCHAT_CORESDKEVENT_LIVESTREAM		=	101;// ֱ��ҵ���¼�
var ANYCHAT_CORESDKEVENT_AIABILITY		=	102;// AI�����¼�
var ANYCHAT_CORESDKEVENT_APPBUFFER		=	103;// APP�Զ��建�����¼�
var ANYCHAT_CORESDKEVENT_USERDEFINE		=	800;// �û��Զ����¼���ʼ���

// ��Ƶ��ʾ������ò���
var ANYCHATWEB_VIDEO_SO_OVERLAY		=		8;	// ����Ƶ�ϵ������֡�ͼƬ������
var ANYCHATWEB_VIDEO_SO_DISABLEFULLSCREEN = 9;	// ��ֹ˫����Ƶȫ����ʾ
var ANYCHATWEB_VIDEO_SO_EXTENDEDSCREEN	=	10;	// ��չ����ʾ��Ƶ
var ANYCHATWEB_VIDEO_SO_VIDEODISPMODE	=	11;	// ��Ƶ��ʾģʽ
var ANYCHATWEB_VIDEO_SO_REMOTEASSIST	=	12;	// Զ��Э������
var ANYCHATWEB_VIDEO_SO_PLAYTASKGUID	=	20;	// ��������ID

// ҵ�񻺳�����־����
var ANYCHAT_BUSINESSBUF_FLAGS_SYNC		=	0x01;// ͬ������

//�ļ���������峣����
var BRPPT_FILECTRL_DOWNLOAD = 0x01; 			// �����ļ�
var BRPPT_FILECTRL_CANCEL = 0x02;				// ȡ������
var BRPPT_FILECTRL_DELETE = 0x04;				// ɾ���ļ�

//�ļ���Ϣ��ѯ���峣����
var BRPPT_FILEINFO_DOWNLOAD_STATUS = 0x01;		// ����״̬
var BRPPT_FILEINFO_PPTDETAILS = 0x02;			// PPT����

// Զ��������Ʋ�������
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLECURSOR  =   0x01;                // ��ֹ�ɼ������
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLEBORDER  =   0x02;                // ��ֹ�߿���ʾ
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLETRACE   =   0x04;                // ��ֹ���׷��

// ����������汾��
var MIN_ANYCHAT_PLUGIN_VER	=	"1.0.0.6";
var MIN_VIDEO_PLUGIN_VER	=	"1.0.0.4";
var CUR_ANYCHAT_PLUGIN_VAR = "";

//VTM���ܲ���
var ANYCHAT_CERTFUNC2_VTMSUPPORT =      0x00080000; //VTM��������
var VTMResult                    = 	    '';         //vtm��Ϣ

/********************************************
 *				�������岿��				*
 *******************************************/
var anychat = null;								// AnyChat���DMO�����ⲿ��ʼ��
var bSupportStreamRecordCtrlEx = false;			// �Ƿ�֧��¼����չAPI�ӿ�
var bSupportObjectBusiness = false;				// �Ƿ�֧��ҵ�����API�ӿ�
var bSupportMultiStream = false;				// �Ƿ�֧�ֶ�·����������ͷ��API�ӿ�
var bSupportScriptObject = false;				// �Ƿ�֧��JavaScript����
var bSupportCluster = false;					// �Ƿ�֧�ּ�Ⱥϵͳ

// ��ʼ��SDK�����س������
function BRAC_InitSDK(apilevel) {	
	var anychatsdkdiv = "AnyChatSDKPluginDiv";
	try {
		// ����AnyChat SDK���
		var anychatobj = document.createElement("object")
	    if (window.ActiveXObject  || "ActiveXObject" in window)
	        anychatobj.classid = "clsid:91CC58C4-BA8A-400D-A176-856EDF42CB57";
	    else
	        anychatobj.type = "application/anychat-plugin";
		anychatobj.id = "AnyChatSDKPlugin";
		
	    // ������Ƶ��ʾ���
	    var videoobj = document.createElement("object")

	    if (window.ActiveXObject || "ActiveXObject" in window)
	        videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
	    else
	        videoobj.type = "application/anychat-video";
		videoobj.id = "AnyChatVideoPlugin";		
	    // ����һ�����Բ�
	    var insertdiv = document.createElement("div");
	    insertdiv.id = anychatsdkdiv;
		insertdiv.appendChild(anychatobj);
	    insertdiv.appendChild(videoobj);
	    document.body.appendChild(insertdiv);
		anychatobj.width = "1 px";
		anychatobj.height = "1 px";
	    // ���Բ���Ƿ�װ
	    CUR_ANYCHAT_PLUGIN_VAR = anychatobj.GetVersion(0);
	    var videopluginver = videoobj.GetVersion(0);
	    // �жϲ���İ汾�Ƿ�̫��
	    var bRightVersion = ((CUR_ANYCHAT_PLUGIN_VAR >= MIN_ANYCHAT_PLUGIN_VER) && (videopluginver >= MIN_VIDEO_PLUGIN_VER));
		// �жϲ���Ƿ�֧��¼����չAPI�ӿ�
		bSupportStreamRecordCtrlEx = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.1.0");
		// �жϲ���Ƿ�֧��ҵ�����API�ӿ�
		bSupportObjectBusiness = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.2.3");
		// �жϲ���Ƿ�֧�ֶ�·��API�ӿ�
		bSupportMultiStream = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.3.1");
		// �жϲ���Ƿ�֧�ּ�Ⱥϵͳ
		bSupportCluster = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.4.0");
		// �жϵ�ǰ��API Level�Ƿ�����ҵ������Ҫ
		if(apilevel > anychatobj.GetVersion(2))
			bRightVersion = false;
		if(bRightVersion) {
			insertdiv.removeChild(videoobj);
			anychat = anychatobj;
			// �����ص��¼�
			if(typeof(OnAnyChatNotifyMessage) == "function")
				BRAC_RegisterCallBack(anychat, 'OnNotifyMessage', 	OnAnyChatNotifyMessage);
			if(typeof(OnAnyChatTextMessage) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTextMessage', 	OnAnyChatTextMessage);
			if(typeof(OnAnyChatTransBuffer) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransBuffer', 	OnAnyChatTransBuffer);
			if(typeof(OnAnyChatTransBufferEx) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransBufferEx', 	OnAnyChatTransBufferEx);
			if(typeof(OnAnyChatTransFile) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransFile', 		OnAnyChatTransFile);
			if(typeof(OnAnyChatVolumeChange) == "function")
				BRAC_RegisterCallBack(anychat, 'OnVolumeChange', 	OnAnyChatVolumeChange);
			if(typeof(OnAnyChatSDKFilterData) == "function")
				BRAC_RegisterCallBack(anychat, 'OnSDKFilterData', 	OnAnyChatSDKFilterData);
			if(typeof(OnAnyChatVideoCallEvent) == "function")
				BRAC_RegisterCallBack(anychat, 'OnVideoCallEvent', 	OnAnyChatVideoCallEvent);
			if(typeof(OnAnyChatRecordSnapShot) == "function")
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShot', 	OnAnyChatRecordSnapShot);
			if(typeof(OnAnyChatRecordSnapShotEx) == "function" && bSupportStreamRecordCtrlEx)
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShotEx', OnAnyChatRecordSnapShotEx);
			if(typeof(OnAnyChatRecordSnapShotEx2) == "function" && bSupportCluster)
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShotEx2', OnAnyChatRecordSnapShotEx2);
			if(typeof(OnAnyChatObjectEvent) == "function" && bSupportObjectBusiness)
				BRAC_RegisterCallBack(anychat, 'OnObjectEvent', OnAnyChatObjectEvent);
			if(typeof(OnAnyChatCoreSDKEvent) == "function" && CUR_ANYCHAT_PLUGIN_VAR >= "1.0.6.0")
				BRAC_RegisterCallBack(anychat, 'OnAnyChatCoreSDKEvent', OnAnyChatCoreSDKEvent);	
		} else {
			document.body.removeChild(insertdiv);
		}
		return bRightVersion ? GV_ERR_SUCCESS : GV_ERR_PLUGINOLDVERSION;
	}
	catch (e) {
	    var insertdiv = BRAC_GetDmoObject(anychatsdkdiv);
	    if (insertdiv)
	        document.body.removeChild(insertdiv);
	    return GV_ERR_PLUGINNOINSTALL;
	}
}

// ע��ص��¼�
function BRAC_RegisterCallBack(obj, name, proc) {
	if(typeof(proc) != "function")
		return;
	if(window.ActiveXObject || "ActiveXObject" in window) {
		if(window.ActiveXObject && obj.attachEvent) {
			obj.attachEvent(name, proc);
		} else {
			BRAC_AttachIE11Event(obj, name, proc);
		}
	} else {
		obj[name] = proc;
	}
}

// ����GUID
function BRAC_NewGuid() {
	return BRAC_GetSDKOptionString(BRAC_SO_CORESDK_NEWGUID);
}

// ��ȡWeb DMO����
function BRAC_GetDmoObject(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (window[id]) {
		return window[id];
	}
	return null;
}

function BRAC_AttachIE11Event(obj, _strEventId, _functionCallback) {
	var nameFromToStringRegex = /^function\s?([^\s(]*)/;
	var paramsFromToStringRegex = /\(\)|\(.+\)/;
	var params = _functionCallback.toString().match(paramsFromToStringRegex)[0];
	var functionName = _functionCallback.name || _functionCallback.toString().match(nameFromToStringRegex)[1];
	var handler;
	try {
		handler = document.createElement("script");
		handler.setAttribute("for", obj.id);
	} catch(ex) {
		handler = document.createElement('<script for="' + obj.id + '">');
	}
	handler.event = _strEventId + params;
	handler.appendChild(document.createTextNode(functionName + params + ";"));
	document.body.appendChild(handler);
}

// ������Ƶ��ʾ���
function BRAC_NativeCreateVideoPlugin(userid, parentobj, id, streamindex) {
	try{
		var videoobj = BRAC_GetDmoObject(id);
		if(videoobj != null) {
			videoobj.SetIPCGuid(BRAC_GetIPCGuid());
			videoobj.SetUserId(userid);
			if(bSupportMultiStream)
				videoobj.SetStreamIndex(streamindex);
		} else {
			// ������Ƶ��ʾ���
			videoobj = document.createElement("object")
			if (window.ActiveXObject || "ActiveXObject" in window)
				videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
			else
				videoobj.type = "application/anychat-video";
			videoobj.id = id;
			parentobj.appendChild(videoobj);
			videoobj.width = "100%";
			videoobj.height = "100%";
			// ������AnyChat SDK
			videoobj.SetIPCGuid(BRAC_GetIPCGuid());
			videoobj.SetUserId(userid);
			if(bSupportMultiStream)
				videoobj.SetStreamIndex(streamindex);
		}			
	}catch(e){
		console.log("CreateVideoPlugin function has exception��" + e);
	}
}

// ������Ƶ��ʾλ��
function BRAC_SetVideoPos(userid, parentobj, id) {
	if(bSupportScriptObject)
		return anychat.SetVideoPos(userid, parentobj, id);
	else
		return BRAC_NativeCreateVideoPlugin(userid, parentobj, id, 0);
}

// ������Ƶ��ʾλ�ã���չ��֧�ֶ�·����
function BRAC_SetVideoPosEx(userid, parentobj, id, streamindex) {
	return BRAC_NativeCreateVideoPlugin(userid, parentobj, id, streamindex);
}

// ��ȡ�汾��
function BRAC_GetVersion(type) {
	return anychat.GetVersion(type);
}

// ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
function BRAC_SetServerAuthPass(lpPassword) {
	return anychat.SetServerAuthPass(lpPassword);
}

// ���ӷ�����
function BRAC_Connect(lpServerAddr, dwPort) {
	return anychat.Connect(lpServerAddr, dwPort);
}
// ��¼ϵͳ
function BRAC_Login(lpUserName, lpPassword, dwParam) {
	return anychat.Login(lpUserName, lpPassword, dwParam);
}
// ��¼ϵͳ����չ��
function BRAC_LoginEx(lpNickName, dwUserId, lpStrUserId, lpAppId, dwTimeStamp, lpSigStr, lpStrParam) {
	if(!bSupportCluster)
		return GV_ERR_PLUGINOLDVERSION;
	return anychat.LoginEx(lpNickName, parseInt(dwUserId), lpStrUserId, lpAppId, parseInt(dwTimeStamp), lpSigStr, lpStrParam);
}
// ���뷿��
function BRAC_EnterRoom(dwRoomid, lpRoomPass, dwParam) {
	return anychat.EnterRoom(parseInt(dwRoomid), lpRoomPass, dwParam);
}
// ���뷿��
function BRAC_EnterRoomEx(lpRoomName, lpRoomPass) {
	return anychat.EnterRoomEx(lpRoomName, lpRoomPass);
}
// �뿪����
function BRAC_LeaveRoom(dwRoomid) {
	return anychat.LeaveRoom(parseInt(dwRoomid));
}
// ע��ϵͳ
function BRAC_Logout() {
	var checkInfo = {"index":1,"flags":ANYCHAT_CERTFUNC2_VTMSUPPORT};
	VTMResult = BRAC_SDKControl(ANYCHAT_SDKCTRL_CERTCHECK,JSON.stringify(checkInfo));
	return anychat.Logout();
}

// ��ȡ��ǰ���������û��б�����һ��userid�����飩
function BRAC_GetOnlineUser() {
	if(bSupportScriptObject) {
		return anychat.GetRoomOnlineUsers(-1);
	}
	var idarray = new Array();
	var size = anychat.PrepareFetchRoomUsers();
	if(size)
	{
		var idx = 0;
		while(1)
		{
			var userid = anychat.FetchNextRoomUsers();
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// ��ȡָ�����������û��б�����һ��userid�����飩
function BRAC_GetRoomOnlineUsers(dwRoomId) {
	if(bSupportScriptObject) {
		return anychat.GetRoomOnlineUsers(dwRoomId);
	}
	var idarray = new Array();
	var size = anychat.PrepareFetchRoomUsers();
	if(size)
	{
		var idx = 0;
		while(1)
		{
			var userid = anychat.FetchNextRoomUsers();
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// ��ѯ�û�����ͷ��״̬
function BRAC_GetCameraState(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_CAMERA);
}
// ��ѯ�û�����״̬
function BRAC_GetSpeakState(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_HOLDMIC);
}
// ��ѯ�û�����
function BRAC_GetUserLevel(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_LEVEL);
}
// ��ѯ�û�����
function BRAC_GetUserName(dwUserId) {
	return anychat.QueryUserStateString(dwUserId, BRAC_USERSTATE_NICKNAME);
}
// ��ѯָ���û����״̬������ֵ״̬��
function BRAC_QueryUserStateInt(dwUserId, infoname) {
	return anychat.QueryUserStateInt(dwUserId, infoname);
}
// ��ѯָ���û����״̬���ַ���ֵ״̬��
function BRAC_QueryUserStateString(dwUserId, infoname) {
	return anychat.QueryUserStateString(dwUserId, infoname);
}

// ��ʾ������Ƶ������ڶԻ���
function BRAC_ShowLVProperty(szCaption) {
	return anychat.ShowLVProperty(szCaption);
}

// ö�ٱ����豸��Ϣ�������豸�������飩
function BRAC_EnumDevices(dwDeviceType) {
	var devicearray = new Array();
	var size = anychat.PrepareFetchDevices(dwDeviceType);
	for(var i=0; i<size; i++) {
		devicearray[i] = anychat.FetchNextDevice(dwDeviceType);
	}
	return devicearray;
}
// ѡ��ָ�����豸
function BRAC_SelectVideoCapture(dwDeviceType, szCaptureName) {
	return anychat.SelectDevice(dwDeviceType, szCaptureName);
}
// ��ȡ��ǰʹ�õ��豸
function BRAC_GetCurrentDevice(dwDeviceType) {
	return anychat.GetCurrentDevice(dwDeviceType);
}

// ���������û���Ƶ��������Զ���û���Ƶ��
function BRAC_UserCameraControl(dwUserId, bOpen) {
	return anychat.UserCameraControl(dwUserId, bOpen);
}

// ���������û���Ƶ��չ��������Զ���û���Ƶ��
function BRAC_UserCameraControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam) {
	if(bSupportMultiStream)
		return anychat.UserCameraControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam);
	else if(dwStreamIndex == 0)
		return anychat.UserCameraControl(dwUserId, bOpen);
	else
		return -1;
}

// ���������û�������������Զ���û�������
function BRAC_UserSpeakControl(dwUserId, bOpen) {
	return anychat.UserSpeakControl(dwUserId, bOpen);
}

// ���������û�������չ��������Զ���û�������
function BRAC_UserSpeakControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam) {
	if(bSupportMultiStream)
		return anychat.UserSpeakControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam);
	else if(dwStreamIndex == 0)
		return anychat.UserSpeakControl(dwUserId, bOpen);
	else
		return -1;
}

// ��ȡָ����Ƶ�豸�ĵ�ǰ����
function BRAC_AudioGetVolume(device) {
	return anychat.AudioGetVolume(device);
}
// ����ָ����Ƶ�豸������
function BRAC_AudioSetVolume(device, dwVolume) {
	return anychat.AudioSetVolume(device, dwVolume);
}

// �û�������Ƶ¼��
function BRAC_StreamRecordCtrl(dwUserId, bStartRecord, dwFlags, dwParam) {
	return anychat.StreamRecordCtrl(dwUserId, bStartRecord, dwFlags, dwParam);
}
// �û�������Ƶ¼�ƣ���չ��
function BRAC_StreamRecordCtrlEx(dwUserId, bStartRecord, dwFlags, dwParam, lpUserStr) {
	if(bSupportStreamRecordCtrlEx)
		return anychat.StreamRecordCtrlEx(dwUserId, bStartRecord, dwFlags, dwParam, lpUserStr);
	else
		return anychat.StreamRecordCtrl(dwUserId, bStartRecord, dwFlags, dwParam);
}

// ���û�����Ƶ����ץ�ģ����գ�
function BRAC_SnapShot(dwUserId, dwFlags, dwParam) {
	return anychat.SnapShot(dwUserId, dwFlags, dwParam);
}

// ͸��ͨ�����ͻ�����
function BRAC_TransBuffer(dwUserId, lpBuf) {
	return anychat.TransBuffer(dwUserId, lpBuf, 0);
}
// ͸��ͨ�����ͻ�������չ
function BRAC_TransBufferEx(dwUserId, lpBuf, wParam, lParam, dwFlags) {
	return anychat.TransBufferEx(dwUserId, lpBuf, wParam, lParam, dwFlags);
}
// �����ļ�
function BRAC_TransFile(dwUserId, lpLocalPathName, wParam, lParam, dwFlags) {
	return anychat.TransFile(dwUserId, lpLocalPathName, wParam, lParam, dwFlags);
}
// ��ѯ�������������Ϣ
function BRAC_QueryTransTaskInfo(dwUserId, dwTaskId, infoname) {
	return anychat.QueryTransTaskInfo(dwUserId, dwTaskId, infoname);
}
// ȡ����������
function BRAC_CancelTransTask(dwUserId, dwTaskId) {
	return anychat.CancelTransTask(dwUserId, dwTaskId);
}
// �����ı���Ϣ
function BRAC_SendTextMessage(dwUserId, bSecret, lpMsgBuf) {
	return anychat.SendTextMessage(dwUserId, bSecret, lpMsgBuf, 0);
}
// ����SDK Filter ͨ������
function BRAC_SendSDKFilterData(lpBuf) {
	return anychat.SendSDKFilterData(lpBuf, 0);
}

// ���ĵ�ǰ������ģʽ
function BRAC_ChangeChatMode(dwChatMode) {
	return anychat.ChangeChatMode(dwChatMode);
}
// ��ȡָ���û���ǰ������ģʽ
function BRAC_GetUserChatMode(dwUserId) {
	return anychat.GetUserChatMode(dwUserId);
}
// ������Է�˽�ģ���Է�����˽������
function BRAC_PrivateChatRequest(dwUserId) {
	return anychat.PrivateChatRequest(dwUserId);
}
// �ظ��Է���˽������
function BRAC_PrivateChatEcho(dwUserId, dwRequestId, bAccept) {
	return anychat.PrivateChatEcho(dwUserId, dwRequestId, bAccept);
}
// �ظ��Է���˽��������չ�����Ը���������룩
function BRAC_PrivateChatEchoEx(dwUserId, dwRequestId, dwErrorCode) {
	return anychat.PrivateChatEchoEx(dwUserId, dwRequestId, dwErrorCode);
}
// �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
function BRAC_PrivateChatExit(dwUserId) {
	return anychat.PrivateChatExit(dwUserId);
}

// SDK�ں˲�������
function BRAC_SetSDKOption(optname, value) {
	if(typeof value == "string")
		return anychat.SetSDKOptionString(optname, value);
	else
		return anychat.SetSDKOptionInt(optname, value);
}
// SDK�ں˲���״̬��ѯ�����β���ֵ��
function BRAC_GetSDKOptionInt(optname) {
	return anychat.GetSDKOptionInt(optname);
}
// SDK�ں˲���״̬��ѯ���ַ�������ֵ��
function BRAC_GetSDKOptionString(optname) {
	return anychat.GetSDKOptionString(optname);
}
// SDK�ں˲���״̬��ѯ���ַ�������ֵ����չ��
function BRAC_GetSDKOptionStringEx(optname, strValue, dwFlags) {
	return anychat.GetSDKOptionStringEx(optname, strValue, dwFlags);
}

// ��ȡ�ڲ�ͨ�ž��
function BRAC_GetIPCGuid() {
	var ANYCHATWEB_SO_IPCGUID = 11000; 
	return anychat.GetSDKOptionString(ANYCHATWEB_SO_IPCGUID);
}

// �鲥���ܿ���
function BRAC_MultiCastControl(lpMultiCastAddr, dwPort, lpNicAddr, dwTTL, dwFlags) {
	return anychat.MultiCastControl(lpMultiCastAddr, dwPort, lpNicAddr, dwTTL, dwFlags);
}

// ��Ƶ�����¼����ƣ����󡢻ظ����Ҷϵȣ�
function BRAC_VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr) {
	return anychat.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
}

// ��ȡ�û�����ID�б�����һ��userid�����飩
function BRAC_GetUserFriends() {
	if(bSupportScriptObject) {
		return anychat.GetUserFriends();
	}
	var idarray = new Array();
	var size = anychat.PrepareFetchUserFriends();
	if(size) {
		var idx = 0;
		while(1) {
			var userid = anychat.FetchNextUserFriend();
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// ��ȡ��������״̬
function BRAC_GetFriendStatus(dwFriendUserId) {
	return anychat.GetFriendStatus(dwFriendUserId);
}

// ��ȡ�û�����ID�б�����һ��GroupId�����飩
function BRAC_GetUserGroups() {
	if(bSupportScriptObject) {
		return anychat.GetUserGroups();
	}
	var idarray = new Array();
	var size = anychat.PrepareFetchUserGroups();
	if(size) {
		var idx = 0;
		while(1) {
			var groupid = anychat.FetchNextUserGroup();
			if(groupid == -1)
				break;
			idarray[idx++] = groupid;
		}
	}
	return idarray;
}

// ��ȡ��������ĺ����б�����һ��userid�����飩
function BRAC_GetGroupFriends(dwGroupId) {
	if(bSupportScriptObject) {
		return anychat.GetGroupFriends(dwGroupId);
	}
	var idarray = new Array();
	var size = anychat.PrepareFetchGroupFriends(dwGroupId);
	if(size) {
		var idx = 0;
		while(1) {
			var userid = anychat.FetchNextGroupFriend(dwGroupId);
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// ��ȡ�û���Ϣ
function BRAC_GetUserInfo(dwUserId, dwInfoId) {
	return anychat.GetUserInfo(dwUserId, dwInfoId);
}

// ��ȡ�û���������
function BRAC_GetGroupName(dwGroupId) {
	return anychat.GetGroupName(dwGroupId);
}

// �û���Ϣ����
function BRAC_UserInfoControl(dwUserId, dwCtrlCode, wParam, lParam, lpStrValue) {
	return anychat.UserInfoControl(dwUserId, dwCtrlCode, wParam, lParam, lpStrValue);
}

// ��ȡҵ�����ID�б�����һ��ObjectId�����飩
function BRAC_ObjectGetIdList(dwObjectType) {
	if(bSupportScriptObject) {
		return anychat.ObjectGetIdList(dwObjectType);
	}
	var idarray = new Array();
	if(!bSupportObjectBusiness)
		return idarray;
	var size = anychat.PrepareFetchObjectIds(dwObjectType);
	if(size) {
		var idx = 0;
		while(1) {
			var objectid = anychat.FetchNextObjectId(dwObjectType);
			if(objectid == -1)
				break;
			idarray[idx++] = objectid;
		}
	}
	return idarray;
}

// ��ȡҵ��������ֵ������ֵ��
function BRAC_ObjectGetIntValue(dwObjectType, dwObjectId, dwInfoName) {
	if(!bSupportObjectBusiness)
		return -1;
	return anychat.GetObjectIntValue(dwObjectType, dwObjectId, dwInfoName);
}

// ��ȡҵ��������ֵ���ַ�����
function BRAC_ObjectGetStringValue(dwObjectType, dwObjectId, dwInfoName) {
	if(!bSupportObjectBusiness)
		return -1;
	return anychat.GetObjectStringValue(dwObjectType, dwObjectId, dwInfoName);
}

// ����ҵ��������ֵ
function BRAC_ObjectSetValue(dwObjectType, dwObjectId, dwInfoName, value) {
	if(!bSupportObjectBusiness)
		return -1;
	if(typeof value == "string")
		return anychat.SetObjectStringValue(dwObjectType, dwObjectId, dwInfoName, value);
	else
		return anychat.SetObjectIntValue(dwObjectType, dwObjectId, dwInfoName, value);
}

// ҵ��������ָ��
function BRAC_ObjectControl(dwObjectType, dwObjectId, dwCtrlCode, dwParam1, dwParam2, dwParam3, dwParam4, strParam) {
	if(!bSupportObjectBusiness)
		return -1;
	return anychat.ObjectControl(dwObjectType, dwObjectId, dwCtrlCode, dwParam1, dwParam2, dwParam3, dwParam4, strParam);
}

// ����ָ���û�����Ƶ����ز�������Ҫ��Ա����û���
function BRAC_SetUserStreamInfo(dwUserId, dwStreamIndex, infoname, value) {
	if(!bSupportMultiStream)
		return -1;
	if(typeof value == "string")
		return anychat.SetUserStreamInfoString(dwUserId, dwStreamIndex, infoname, value);
	else
		return anychat.SetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname, value);
}

// ��ȡָ���û�����Ƶ����ز��������β���ֵ��
function BRAC_GetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname) {
	if(!bSupportMultiStream)
		return 0;
	return anychat.GetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname);
}

// ��ȡָ���û�����Ƶ����ز������ַ�������ֵ��
function BRAC_GetUserStreamInfoString(dwUserId, dwStreamIndex, infoname) {
	if(!bSupportMultiStream)
		return "";
	return anychat.GetUserStreamInfoString(dwUserId, dwStreamIndex, infoname);
}

// ���������̬��ѯ�����Ϣ
function BRAC_QueryInfoFromServer(dwInfoName, lpInParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.5.0")
		return "";
	return anychat.QueryInfoFromServer(dwInfoName, lpInParam);
}

// SDK����
function BRAC_SDKControl(dwCtrlCode, lpInParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.7.0")
		return JSON.stringify({"errorcode":32});
	return anychat.SDKControl(dwCtrlCode, lpInParam);
}

// �ļ�������չ�ӿ�
function BRAC_TransFileEx(lpTaskGuid, dwUserId, lpLocalPathName, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.TransFileEx(lpTaskGuid, dwUserId, lpLocalPathName, dwFlags, lpStrParam);
}

// ���������ѯ��չ�ӿ�
function BRAC_QueryTransTaskInfoEx(lpTaskGuid, dwInfoName) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.QueryTransTaskInfoEx(lpTaskGuid, dwInfoName);
}

// ȡ������������չ�ӿ�
function BRAC_CancelTransTaskEx(lpTaskGuid, dwFlags, dwErrorCode) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.CancelTransTaskEx(lpTaskGuid, dwFlags, dwErrorCode);
}

// ��ý�岥�ų�ʼ��
function BRAC_StreamPlayInit(lpTaskGuid, lpStreamPath, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayInit(lpTaskGuid, lpStreamPath, dwFlags, lpStrParam);
}

// ��ý�岥�ſ���
function BRAC_StreamPlayControl(lpTaskGuid, dwCtrlCode, dwParam, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayControl(lpTaskGuid, dwCtrlCode, dwParam, dwFlags, lpStrParam);
}

// ������ý�岥����Ƶ��ʾλ��
function BRAC_StreamPlaySetVideoPos(lpTaskGuid, parentobj, id) {
	try {
		BRAC_NativeCreateVideoPlugin(0, parentobj, id, 0);
		BRAC_GetDmoObject(id).SetSDKOptionString(ANYCHATWEB_VIDEO_SO_PLAYTASKGUID, lpTaskGuid);
	} catch(ex) {
		
	}
}

// ��ý�岥�Ż�ȡ������Ϣ
function BRAC_StreamPlayGetInfo(lpTaskGuid, dwInfoName) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return "";
	return anychat.StreamPlayGetInfo(lpTaskGuid, dwInfoName);
}

// ��ý�岥���ͷ���Դ
function BRAC_StreamPlayDestroy(lpTaskGuid, dwFlags) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayDestroy(lpTaskGuid, dwFlags);
}

// �ͷŲ��
function BRAC_Release() {
	var _anychatSDKDiv = BRAC_GetDmoObject("AnyChatSDKPluginDiv");
	if (_anychatSDKDiv) {
		if (getBrowser() == "IE") {
			// �ͷ��¼�
			if(!!VTMResult && (!VTMResult?"":(JSON.parse(VTMResult).errorcode == 0))){ 
				var eles = document.getElementsByTagName('script');
				for(var i = 0; i < eles.length ; i++){
					var ele = eles[i];
					if(ele.getAttribute('for') == 'AnyChatSDKPlugin'){
						ele.parentNode.removeChild(ele); 
						i--;
					}
				}
			}
			// ���anychat
			anychat = null;
			_anychatSDKDiv.parentNode.removeChild(_anychatSDKDiv);
			_anychatSDKDiv = null;
			var objectPlugins = document.getElementsByTagName("object");
			while (objectPlugins.length > 0 &&
				objectPlugins[0].classid == "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7") {
				objectPlugins[0].parentNode.removeChild(objectPlugins[0]);
			}
			setTimeout(CollectGarbage, 1);
			return;
		}
		document.body.removeChild(_anychatSDKDiv);
	}
}

// ��ȡ��ǰ�����
function getBrowser(){
	var browser = "unknown browser";	
	var ua = navigator.userAgent.toLowerCase();
	
	var info = {
		ie: /msie/.test(ua) && !/opera/.test(ua),
		op: !/msie/.test(ua) && /opera/.test(ua),
		sa: /version.*safari/.test(ua),
		ch: /chrome/.test(ua) && window.navigator.webkitPersistentStorage,
		ff: /firefox/.test(ua),
		qh360: /chrome/.test(ua) && !window.navigator.webkitPersistentStorage,
		qq: /qqbrowser/.test(ua),
        sg: /metasr/.test(ua)        
	};	
	
	if (info.ch){
		browser = "Chrome";
	}else if (info.ie || (!!window.ActiveXObject || "ActiveXObject" in window) ){
		browser = "IE";
	}else if (info.ff){
		browser = "Firefox";
	}else if (info.sa){
		browser = "Safari";
	}else if (info.qh360){
		browser = "360�����";
	}else if (info.op){
		browser = "Opera";
	}else if (info.qq){
		browser = "QQ�����";
	}else if (info.sg){
		browser = "�ѹ������";
	}
	
	return browser;
}


