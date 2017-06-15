unit BRAnyChatCoreSDK;
(****************************************************************************
     BRAnyChatCoreSDK.h
****************************************************************************)

interface
uses
  Windows,MMSystem,SysUtils,Messages,Classes,Types,Graphics,
  GVMessageDefine,GVErrorCodeDefine,GVSDK;

const
  C_BRAnyChatCoreLibName = 'BRAnyChatCore.dll';

  // ��Ƶͼ���ʽ����
type BRAC_PixelFormat=(
	          BRAC_PIX_FMT_RGB24 = 0,			///< Packed RGB 8:8:8, 24bpp, RGBRGB...��MEDIASUBTYPE_RGB24��
	          BRAC_PIX_FMT_RGB32,				///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB32��Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	          BRAC_PIX_FMT_YV12,				///< ��Ӧ�ڣ�MEDIASUBTYPE_YV12��Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	          BRAC_PIX_FMT_YUY2					///< ��Ӧ�ڣ�MEDIASUBTYPE_YUY2��Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
     );

  // ��Ƶ�豸����
type BRAC_AudioDevice=(
	        BRAC_AD_WAVEIN = 0,					///< �����豸��Mic
          	BRAC_AD_WAVEOUT			     		///< ����豸��Wave
     );


  // ����ģʽ����
const
  BRAC_FUNC_VIDEO_CBDATA		=$00000001;		///< ͨ���ص����������Ƶ����
  BRAC_FUNC_VIDEO_AUTODISP		=$00000002;		///< ��SDK��������Ƶ������Ƶ��ʾ��ָ���Ĵ�����
  BRAC_FUNC_AUDIO_CBDATA		=$00000004;		///< ͨ��˳�����������Ƶ����
  BRAC_FUNC_AUDIO_AUTOPLAY		=$00000008;		///< ��SDK��������Ƶ��ֱ�Ӳ���
  BRAC_FUNC_CONFIG_LOCALINI 	=$00000010;		///< ���ɱ��������ļ���AnyChatSDK.ini��
  BRAC_FUNC_FIREWALL_OPEN   	=$00000020;		///< ����SDK����Windows����ǽ������ǰӦ�ó���������ǽ�����б�����Windows��ʾ�û��Ƿ���ֹ��ǰӦ�ó���
  BRAC_FUNC_CHKDEPENDMODULE   	=$00000040;		///< �Զ����SDK����������������Զ�ע��
  BRAC_FUNC_AUDIO_VOLUMECALC  	=$00000080;		///< ��SDK�Զ���������������
  BRAC_FUNC_AUDIO_AUTOVOLUME  	=$00000100;		///< ����SDK�Զ�����Mic¼������
  BRAC_FUNC_NET_SUPPORTUPNP   	=$00000200;		///< ����SDK���û������е�UPNP�豸������û���·�������Ƿ���ǽ֧��UPNPЭ�飬������P2P�򶴵ĳɹ���
  BRAC_FUNC_DISABLEDECODE		=$00000400;		///< ��ֹ���յ������ݽ��н���Ͳ��ţ�Ϊ����ߴ���ͻ��˵�����ת�����ܣ������øñ�־�����������øñ�־

  ANYCHAT_STREAMPLAY_CTRL_START = 1;			///< ��ʼ����
  ANYCHAT_STREAMPLAY_CTRL_PAUSE = 2;			///< ��ͣ����
  ANYCHAT_STREAMPLAY_CTRL_STOP = 3;				///< ֹͣ����
  ANYCHAT_STREAMPLAY_CTRL_SEEK = 4;				///< λ���϶�
  ANYCHAT_STREAMPLAY_CTRL_SPEEDCTRL = 5;		///< �ٶȵ���
  BRAC_SO_CORESDK_NEWGUID = 29;
  ANYCHAT_STREAMPLAY_INFO_JSONVALUE = 1;  

  BRAC_CBTYPE_NOTIFYMESSAGE = 1;				///< �첽��Ϣ֪ͨ�ص�
  BRAC_CBTYPE_VIDEODATA = 2;					///< ��Ƶ���ݻص�
  BRAC_CBTYPE_VIDEODATAEX = 3;					///< ��Ƶ������չ�ص�
  BRAC_CBTYPE_AUDIODATA = 4;					///< ��Ƶ���ݻص�
  BRAC_CBTYPE_AUDIODATAEX = 5;					///< ��Ƶ���ݻص���չ�ص�
  BRAC_CBTYPE_TEXTMESSAGE = 6;					///< ������Ϣ�ص�
  BRAC_CBTYPE_TRANSBUFFER = 7;					///< ͸��ͨ�����ݻص�
  BRAC_CBTYPE_TRANSBUFFEREX = 8;				///< ͸��ͨ��������չ�ص�
  BRAC_CBTYPE_TRANSFILE = 9;					///< �ļ�����ص�
  BRAC_CBTYPE_VOLUMECHANGE = 10;				///< �����仯�ص�
  BRAC_CBTYPE_SDKFILTERDATA = 11;				///< SDK Filterͨ�����ݻص�
  BRAC_CBTYPE_STREAMRECORD = 12;				///< ¼������������֪ͨ�ص�
  BRAC_CBTYPE_STREAMRECORDEX = 13;				///< ¼������������֪ͨ��չ�ص�
  BRAC_CBTYPE_VIDEOCALLEVENT = 14;				///< ��Ƶͨ����Ϣ֪ͨ�ص�
  BRAC_CBTYPE_DATAENCDEC = 15;					///< ���ݼ��ܡ����ܻص�
  BRAC_CBTYPE_SCREENEVENT = 16;					///< ��Ļ�¼��ص�
  BRAC_CBTYPE_OBJECTEVENT = 18;					///< ҵ������¼�֪ͨ
  BRAC_CBTYPE_VIDEODATAEX2 = 19;				///< ��Ƶ������չ�ص���֧�ֶ�·����
  BRAC_CBTYPE_AUDIODATAEX2 = 20;				

  //�ں˲�������
  BRAC_SO_AUDIO_VADCTRL			=1;	  		    ///< ��Ƶ���������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
  BRAC_SO_AUDIO_NSCTRL			=2;	    		///< ��Ƶ�������ƿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
  BRAC_SO_AUDIO_ECHOCTRL		=3;	   		    ///< ��Ƶ�����������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
  BRAC_SO_AUDIO_AGCCTRL			=4;	  			///< ��Ƶ�Զ�������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
  BRAC_SO_AUDIO_CPATUREMODE		=5;				///< ��Ƶ�ɼ�ģʽ���ã�����Ϊ��int�ͣ�0 ����ģʽ��1 �Ÿ�ģʽ��2 ����OKģʽ��3 ��·����ģʽ��
  BRAC_SO_AUDIO_MICBOOST		=6;				///< ��Ƶ�ɼ�Mic��ǿ���ƣ�����Ϊ��int�ͣ�0 ȡ����1 ѡ�У�2 �豸������[��ѯʱ����ֵ]��
  BRAC_SO_AUDIO_AUTOPARAM		=7;				///< ������Ƶ�ɼ�ģʽ���Զ�ѡ����ʵ���ز������������������������������ʲ����ȣ�����Ϊint�ͣ�1 ���ã�0 �ر�[Ĭ��]��
  BRAC_SO_AUDIO_MONOBITRATE		=8;				///< ���õ�����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
  BRAC_SO_AUDIO_STEREOBITRATE	=9;				///< ����˫����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
  BRAC_SO_AUDIO_PLAYDRVCTRL		=70;			///< ��Ƶ��������ѡ�񣨲���Ϊ��int�ͣ�0Ĭ�������� 1 DSound������ 2 WaveOut������
  BRAC_SO_AUDIO_CNGCTRL			=71;			///< �����������ɿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
  BRAC_SO_AUDIO_SOFTVOLMODE		=73;			///< �����������ģʽ���ƣ�����Ϊint�ͣ�1�򿪣�0�ر�[Ĭ��]����ʹ���������ģʽ��������ı�ϵͳ����������
  BRAC_SO_AUDIO_RECORDDRVCTRL	=74;			///< ��Ƶ�ɼ��������ƣ�����Ϊint�ͣ�0Ĭ�������� 1 DSound������ 2 WaveIn������ 3 Java�ɼ�[Androidƽ̨ʹ��]��

  BRAC_SO_RECORD_VIDEOBR		=10;	 		///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
  BRAC_SO_RECORD_AUDIOBR		=11;	  		///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
  BRAC_SO_RECORD_TMPDIR			=12;	 		///< ¼���ļ���ʱĿ¼���ã�����Ϊ�ַ���PCHAR���ͣ�
  BRAC_SO_SNAPSHOT_TMPDIR		=13;	 		///< �����ļ���ʱĿ¼���ã�����Ϊ�ַ���PCHAR���ͣ�
  BRAC_SO_RECORD_FILETYPE		=140;			///< ¼���ļ��������ã�����Ϊ��int�ͣ� 0 MP4[Ĭ��], 1 WMV, 2 FLV, 3 MP3��
  BRAC_SO_RECORD_WIDTH			=141;			///< ¼����Ƶ������ã�����Ϊ��int�ͣ��磺320��
  BRAC_SO_RECORD_HEIGHT			=142;			///< ¼���ļ��߶����ã�����Ϊ��int�ͣ��磺240��
  BRAC_SO_RECORD_FILENAMERULE	=143;			///< ¼���ļ����������򣨲���Ϊ��int�ͣ�
  
  BRAC_SO_CORESDK_TMPDIR		=14;	  		///< ����AnyChat Core SDK��ʱĿ¼������Ϊ�ַ���PCHAR���ͣ�
  BRAC_SO_CORESDK_PATH			=20;	  		///< ����AnyChat Core SDK������·��������Ϊ�ַ���PCHAR���ͣ�
  BRAC_SO_CORESDK_DUMPCOREINFO	=21;			///< ����ں���Ϣ����־�ļ��У����ڷ�������ԭ�򣨲���Ϊ��int�ͣ�1 �����
  BRAC_SO_CORESDK_EXTVIDEOINPUT	=26;			///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
  BRAC_SO_CORESDK_EXTAUDIOINPUT	=27;			///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩

  BRAC_SO_LOCALVIDEO_BITRATECTRL	=30;		///< ������Ƶ�����������ã�����Ϊint�ͣ���λbps��ͬ���������ã�VideoBitrate��
  BRAC_SO_LOCALVIDEO_QUALITYCTRL	=31;		///< ������Ƶ�����������ӿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoQuality��
  BRAC_SO_LOCALVIDEO_GOPCTRL		=32;		///< ������Ƶ����ؼ�֡������ƣ�����Ϊint�ͣ�ͬ���������ã�VideoGOPSize��
  BRAC_SO_LOCALVIDEO_FPSCTRL		=33;		///< ������Ƶ����֡�ʿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoFps��
  BRAC_SO_LOCALVIDEO_PRESETCTRL		=34;		///< ������Ƶ����Ԥ��������ƣ�����Ϊint�ͣ�1-5��
  BRAC_SO_LOCALVIDEO_APPLYPARAM		=35;		///< Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
  BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC=36;		///< ������Ƶ�ɼ��ֱ��ʿ��Ʋ��ԣ�����Ϊint�ͣ�0 �Զ�������ƥ��[Ĭ��]��1 ʹ�òɼ��豸Ĭ�Ϸֱ��ʣ��������õķֱ��ʲ����ɼ��豸֧��ʱ��Ч
  BRAC_SO_LOCALVIDEO_DEINTERLACE	=37;		///< ������Ƶ����֯�������ƣ�����Ϊint�ͣ� 0 �����з���֯����[Ĭ��]��1 ����֯��������������ƵԴ�Ǹ���ɨ��Դ��������źţ�ʱͨ������֯���������߻�������
  BRAC_SO_LOCALVIDEO_WIDTHCTRL		=38;		///< ������Ƶ�ɼ��ֱ��ʿ�ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoWidth��
  BRAC_SO_LOCALVIDEO_HEIGHTCTRL		=39;		///< ������Ƶ�ɼ��ֱ��ʸ߶ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoHeight��
  BRAC_SO_LOCALVIDEO_TVFORMAT		=104;		///< ��Ƶ�ɼ���ʽ���ã�����Ϊ��int�ͣ�����ΪDirectShow::strmif.h::AnalogVideoStandard��Ĭ��Ϊ��AnalogVideo_PAL_B��
  BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP =105; 	///< ����ʱ�����������Ƶ������Ϊ��int�ͣ� 0 ������[Ĭ��]�� 1 ���ӣ�  
  BRAC_SO_LOCALVIDEO_DEVICENAME = 106;
  

  BRAC_SO_NETWORK_P2PPOLITIC		=40;		///< ��������P2P���Կ��ƣ�����Ϊ��int�ͣ�0 ��ֹ����P2P��1 ����������P2P[Ĭ��]��2 �ϲ�Ӧ�ÿ���P2P���ӣ�3 ���轨��P2P���ӣ�
  BRAC_SO_NETWORK_P2PCONNECT		=41;		///< ������ָ���û�����P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID�������ӽ����ɹ��󣬻�ͨ����Ϣ�������ϲ�Ӧ�ã�P2P���Ʋ���=2ʱ��Ч
  BRAC_SO_NETWORK_P2PBREAK			=42;		///< �Ͽ���ָ���û���P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID��[�ݲ�֧�֣�����]
  BRAC_SO_NETWORK_TCPSERVICEPORT	=43;		///< ���ñ���TCP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
  BRAC_SO_NETWORK_UDPSERVICEPORT	=44;		///< ���ñ���UDP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
  BRAC_SO_NETWORK_MULTICASTPOLITIC	=45;		///< �鲥���Կ��ƣ�����Ϊint�ͣ�0 ִ�з�����·�ɲ��ԣ���ֹ�鲥����[Ĭ��]�� 1 ���Է�����·�ɲ��ԣ�ֻ���鲥��㲥ý������ 2 ִ�з�����·�ɲ��ԣ�ͬʱ�鲥��
  BRAC_SO_NETWORK_TRANSBUFMAXBITRATE=46;		///< ���仺�������ļ�������ʿ��ƣ�����Ϊint�ͣ�0 �����ƣ���������ʴ���[Ĭ��]�� �����ʾ�������ʣ���λΪ��bps��

  BRAC_SO_PROXY_FUNCTIONCTRL	=50;			///< �����û������ܿ��ƣ�������Ϊ��int�ͣ�1��������0�رմ���[Ĭ��]��
  BRAC_SO_PROXY_VIDEOCTRL		=51;			///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������Ϊint�ͣ���ʾ�����û���userid��
  BRAC_SO_PROXY_AUDIOCTRL		=52;			///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������ͬBRAC_SO_PROXY_VIDEOCTRL�� 
  
  BRAC_SO_STREAM_MAXBUFFERTIME	=60;			///< ���������ʱ�䣨����Ϊint�ͣ���λ�����룬ȡֵ��Χ��500 ~ 5000��Ĭ�ϣ�800��������ģʽ����ֵ������ģʽ���Զ�����һ��
  BRAC_SO_STREAM_SMOOTHPLAYMODE =61;			///< ƽ������ģʽ������Ϊint�ͣ�0 �ر�[Ĭ��], 1 �򿪣�����״̬��������Ƶ��֡ʱ��������ţ����ܳ��������ˣ������Ῠס
  
  BRAC_SO_CORESDK_TICKOUTUSER		=110;		///< �ӷ��������ߵ�ָ���û�������Ϊint�ͣ���ʾĿ���û�ID��
  BRAC_SO_CORESDK_DEVICEMODE		=130;		///< �豸ģʽ���ƣ��������豸֮����Ի���ͨ�ţ�������������������Ϊint�ͣ�0 �ر�[Ĭ��]��1 ������
  BRAC_SO_CORESDK_SCREENCAMERACTRL	=131;		///< ���湲���ܿ��ƣ�����Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 ������
  BRAC_SO_CORESDK_DATAENCRYPTION	=132;		///< ���ݼ��ܿ��ƣ�����Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 ������
  BRAC_SO_RECORD_INSERTIMAGE 		=146;		///< ¼��ͼƬ
  BRAC_SO_CORESDK_PPTHELPERINIT = 223;// PPT����������ʼ��
  BRAC_SO_CORESDK_PPTFILECTRL		=		224;// PPT�ļ�����
  BRPPT_FILECTRL_DOWNLOAD	=	$00000001;		///< �����ļ�
  BRPPT_FILECTRL_CANCEL	=	$00000002;		///< ȡ������
  BRPPT_FILECTRL_DELETE	=	$00000004;		///< ɾ���ļ�

//�ļ���Ϣ��ѯ���峣����
 BRPPT_FILEINFO_DOWNLOAD_STATUS =	$00000001;	///< ����״̬
 BRPPT_FILEINFO_PPTDETAILS	=	$00000002;	///< PPT����
 ANYCHAT_SERVERQUERY_PPTFILEINFO	  =	10;	// PPT�ļ���Ϣ
 ANYCHAT_CORESDKEVENT_PPTHELPER    = 31; //< PPTHelper�¼�


  // ����������Ϣ��������
  BRAC_TRANSTASK_PROGRESS		=1;	   			///< ����������Ȳ�ѯ������Ϊ��DOUBLE�ͣ�0.0 ~ 100.0����
  BRAC_TRANSTASK_BITRATE		=2;				///< ��������ǰ�������ʣ�����Ϊ��int�ͣ���λ��bps��
  BRAC_TRANSTASK_STATUS			=3;				///< ��������ǰ״̬������Ϊ��int�ͣ�
  BRAC_TRANSTASK_SAVEASPATH		=4;				///< �ļ������������Ϊ·�����ã�����Ϊ�ַ���TCHAR���ͣ�

  // ¼���ܱ�־����
  BRAC_RECORD_FLAGS_VIDEO		=$00000001;		///< ¼����Ƶ
  BRAC_RECORD_FLAGS_AUDIO		=$00000002;		///< ¼����Ƶ
  BRAC_RECORD_FLAGS_SERVER		=$00000004;		///< ��������¼��
  BRAC_RECORD_FLAGS_MIXAUDIO		=$00000010;		///< ¼����Ƶʱ���������˵�����������¼��
  BRAC_RECORD_FLAGS_MIXVIDEO		=$00000020;		///< ¼����Ƶʱ���������˵���Ƶ���Ӻ�¼��
  BRAC_RECORD_FLAGS_ABREAST		=$00000100;		///< ¼����Ƶʱ���������˵���Ƶ����¼��
  BRAC_RECORD_FLAGS_STEREO    = $00000200;
  BRAC_RECORD_FLAGS_SNAPSHOT 	=$00000400;		///< ����
  BRAC_RECORD_FLAGS_LOCALCB		=$00000800;		///< �������ػص�
  BRAC_RECORD_FLAGS_STREAM		=$00001000;		///< ����Ƶ������¼�ƣ�Ч�ʸߣ������ܴ�����Ƶ������ת�����⣩
  BRAC_RECORD_FLAGS_USERFILENAME = $02000;	// �û��Զ����ļ���
  BRAC_RECORD_FLAGS_MULTISTREAM = $08000;	// ֧�ֶ�·����¼�ƣ����գ�


  // �û�״̬��־����
  BRAC_USERSTATE_CAMERA			=1;				///< �û�����ͷ״̬������ΪDWORD�ͣ�
  BRAC_USERSTATE_HOLDMIC		=2;				///< �û���Ƶ�豸״̬������ΪDWORD�ͣ�����ֵ��0 ��Ƶ�ɼ��رգ� 1 ��Ƶ�ɼ�������
  BRAC_USERSTATE_SPEAKVOLUME	=3;				///< �û���ǰ˵������������ΪDOUBLE���ͣ�0.0 ~ 100.0����
  BRAC_USERSTATE_RECORDING		=4;				///< �û�¼������״̬������ΪDWORD�ͣ�
  BRAC_USERSTATE_LEVEL			=5;				///< �û����𣨲���ΪDWORD�ͣ�
  BRAC_USERSTATE_NICKNAME		=6;				///< �û��ǳƣ�����Ϊ�ַ���PCHAR���ͣ�
  BRAC_USERSTATE_LOCALIP		=7;				///< �û�����IP��ַ������������Ϊ�ַ���PCHAR���ͣ�
  BRAC_USERSTATE_INTERNETIP		=8;				///< �û�������IP��ַ������Ϊ�ַ���PCHAR���ͣ�
  BRAC_USERSTATE_VIDEOBITRATE	=9;				///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
  BRAC_USERSTATE_AUDIOBITRATE	=10;			///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
  BRAC_USERSTATE_P2PCONNECT		=11;			///< ��ѯ�����û���ָ���û��ĵ�ǰP2P����״̬������ΪDWORD���ͣ�����ֵ��0 P2P��ͨ�� 1 P2P���ӳɹ�[TCP]��2 P2P���ӳɹ�[UDP]��3 P2P���ӳɹ�[TCP��UDP]��
  BRAC_USERSTATE_NETWORKSTATUS = 12;
  BRAC_USERSTATE_PACKLOSSRATE	=14;			///< ��ѯָ���û���������ý�����ݶ����ʣ�����ΪDWORD���ͣ�����ֵ��0 - 100���磺����ֵΪ5����ʾ������Ϊ5%��
  BRAC_USERSTATE_DEVICETYPE		=15;			///< ��ѯָ���û����ն����ͣ�����ΪDWORD���ͣ�����ֵ��0 Unknow�� 1 Windows��2 Android��3 iOS��4 Web��5 Linux��6 Mac��7 Win Phone��8 WinCE��
  BRAC_USERSTATE_SELFUSERSTATUS	=16;			///< ��ѯ�����û��ĵ�ǰ״̬������ΪDWORD���ͣ�����ֵ��0 Unknow��1 Connected��2 Logined��3 In Room��4 Logouted��5 Link Closed��
  BRAC_USERSTATE_SELFUSERID		=17;			///< ��ѯ�����û���ID������ΪDWORD���ͣ����û���¼�ɹ��������û�ʵ�ʵ�userid�����򷵻�-1��

  // ��Ƶ�����¼����Ͷ��壨API��BRAC_VideoCallControl ���������VideoCallEvent�ص�������
  BRAC_VIDEOCALL_EVENT_REQUEST	=1;				///< ��������
  BRAC_VIDEOCALL_EVENT_REPLY	=2;				///< ��������ظ�
  BRAC_VIDEOCALL_EVENT_START	=3;				///< ��Ƶ���лỰ��ʼ�¼�
  BRAC_VIDEOCALL_EVENT_FINISH	=4;				///< �Ҷϣ����������лỰ

  // ��Ƶ���б�־���壨API��BRAC_VideoCallControl ���������
  BRAC_VIDEOCALL_FLAGS_AUDIO		=	$01;	///< ����ͨ��
  BRAC_VIDEOCALL_FLAGS_VIDEO		=	$02;	///< ��Ƶͨ��
  BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	=	$10;	///< ��ֹԴ�����жˣ���Ƶ
  BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	=	$20;	///< ��ֹԴ�����жˣ���Ƶ
  BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	=	$40;	///< ��ֹĿ�꣨�����жˣ���Ƶ
  BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	=	$80;	///< ��ֹĿ�꣨�����жˣ���Ƶ
  
  // Զ����Ƶ����������־����
  BRAC_ROTATION_FLAGS_MIRRORED		=	$1000;	///< ͼ����Ҫ����ת
  BRAC_ROTATION_FLAGS_ROTATION90	=	$2000;	///< ˳ʱ����ת90��
  BRAC_ROTATION_FLAGS_ROTATION180	=	$4000;	///< ˳ʱ����ת180��
  BRAC_ROTATION_FLAGS_ROTATION270	=	$8000;	///< ˳ʱ����ת270��

  // �û���Ϣ�������Ͷ��壨API��BRAC_UserInfoControl ���������
  BRAC_USERINFO_CTRLCODE_ROTATION	=	8;		///< ��ָ�����û���Ƶ����ʾʱ��ת��wParamΪ��ת�ǶȲ���
  BRAC_USERINFO_CTRLCODE_DEBUGLOG	=	9;		///< ��������û��ĵ�����־��wParamΪ������־����
  BRAC_USERINFO_CTRLCODE_LVORIENTFIX	=	10;		///< ������Ƶ�ɼ�����������wParamΪ���������lParamΪ�����Ƕ�

  // ���ݼӣ��⣩�ܱ�־���壨DataEncDec�ص�������
  BRAC_DATAENCDEC_FLAGS_ENCMODE		=	$01;	///< ����ģʽ
  BRAC_DATAENCDEC_FLAGS_DECMODE		=	$02;	///< ����ģʽ
  BRAC_DATAENCDEC_FLAGS_AUDIO		=	$10;	///< ��Ƶ��������
  BRAC_DATAENCDEC_FLAGS_VIDEO		=	$20;	///< ��Ƶ��������
  BRAC_DATAENCDEC_FLAGS_BUFFER		=	$40;	///< ͸��ͨ������
  BRAC_DATAENCDEC_FLAGS_TXTMSG		=	$80;	///< ������������

  ANYCHAT_VIDEOCLIPMODE_AUTO = 0;   //< Ĭ��ģʽ�������������вü���Ȼ�����������죬���汣�ֱ����������ü�����ϴ�
  ANYCHAT_VIDEOCLIPMODE_OVERLAP = 1;   //< �ص�ģʽ��ֻȡ�����Ч���֣��Ա�Ե���вü�
  ANYCHAT_VIDEOCLIPMODE_SHRINK = 2;   //< ��Сģʽ����С�����ʵı����������вü�
  ANYCHAT_VIDEOCLIPMODE_STRETCH = 3;   //< ƽ��ģʽ�������вü��������ܵ��»��治�ɱ���
  ANYCHAT_VIDEOCLIPMODE_DYNAMIC = 4;   //< ��̬ģʽ�����ϲ�Ӧ�ø��ݷֱ�����������ʾ���棬���ֻ��治����
  BRAC_SO_RECORD_CLIPMODE = 144;  // ¼����Ƶ�ü�ģʽ������Ϊ��int�ͣ�
type
  // ��Ƶ���ݻص���������
  BRAC_VideoData_CallBack=procedure(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD; bmiHeader:BITMAPINFOHEADER;lpUserValue:Pointer);stdcall;
    
  // ��Ƶ���ݻص���������
  BRAC_AudioData_CallBack=procedure(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD; waveFormatEx:TWaveFormatEx;lpUserValue:Pointer);stdcall;
    
  // ������Ϣ�ص���������
  BRAC_TextMessage_CallBack=procedure(dwFromUserid:DWORD;dwToUserid:DWORD; bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:DWORD;lpUserValue:Pointer);stdcall;
    
  // ͸��ͨ�����ݻص���������
  BRAC_TransBuffer_CallBack=procedure(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD; lpUserValue:Pointer);stdcall;

// ͸��ͨ��������չ�ص���������
  BRAC_TransBufferEx_CallBack=procedure(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;lParam:DWORD; dwTaskId:DWORD;lpUserValue:Pointer);stdcall;
    
  // �����仯�ص���������
  BRAC_VolumeChange_CallBack=procedure(device:BRAC_AudioDevice;dwCurrentVolume:DWORD; lpUserValue:Pointer);stdcall;

  // �ļ�����ص���������
  BRAC_TransFile_CallBack=procedure(dwUserid:DWORD;lpFileName:LPCTSTR;lpTempFilePath:LPCTSTR; dwFileLength:DWORD;wParam:DWORD;lParam:DWORD;dwTaskId:DWORD;lpUserValue:Pointer);stdcall;

  // SDK Filter ͨ�����ݻص���������
  BRAC_SDKFilterData_CallBack=procedure(lpBuf:PByte;dwLen:DWORD;lpUserValue:Pointer);stdcall;
  
  // ¼�񡢿���������ɻص���������
  BRAC_RecordSnapShot_CallBack=procedure(dwUserid:DWORD;lpFileName:LPCTSTR; dwParam:DWORD;bRecordType:BOOL;lpUserValue:Pointer);stdcall;

  // ¼�񡢿���������ɻص���������
  BRAC_RecordSnapShotEx_CallBack = procedure( dwUserid: DWORD; lpFileName: LPCTSTR; elapse, flags, dwParam: DWORD; userStr: LPCTSTR; userValue: DWORD);stdcall;

  // �첽��Ϣ֪ͨ�ص���������
  BRAC_NotifyMessage_CallBack=procedure(dwNotifyMsg:DWORD;wParam:DWORD;lParam:DWORD; lpUserValue:Pointer);stdcall;
	
  // ��Ƶͨ����Ϣ֪ͨ�ص���������
  BRAC_VideoCallEvent_CallBack=procedure(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR; lpUserValue:Pointer);stdcall;
  
  // ���ݼ��ܡ����ܻص���������
  BRAC_DataEncDec_CallBack = procedure(dwUserId:DWORD; dwFlags:DWORD; lpInBuf:PByte; dwInSize:DWORD; lpOutBuf:PByte; lpOutSize:Pointer; lpUserValue:Pointer);stdcall;

(**
 *	API��������
 *)

  // ��ȡSDK�汾��Ϣ
  function BRAC_GetSDKVersion(var dwMainVer:DWORD;var dwSubVer:DWORD;lpCompileTime:LPSTR;dwBufLen:DWORD):DWORD;cdecl;

  // ����رգ�SDK������־
  function BRAC_ActiveCallLog(bActive:BOOL):DWORD;cdecl;
  
  // ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
  function BRAC_SetServerAuthPass(lpPassword:LPCTSTR):DWORD;cdecl;

  // ��ʼ��ϵͳ
  function BRAC_InitSDK(hWnd:HWND;dwFuncMode:DWORD):DWORD;cdecl;
  

  // ������Ƶ���ݻص�����
  function BRAC_SetVideoDataCallBack(pixFmt:BRAC_PixelFormat;lpFunction:BRAC_VideoData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ������Ƶ���ݻص�����
  function BRAC_SetAudioDataCallBack(lpFunction:BRAC_AudioData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ����������Ϣ�ص�����
  function BRAC_SetTextMessageCallBack(lpFunction:BRAC_TextMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ����͸��ͨ�����ݻص�����
  function BRAC_SetTransBufferCallBack(lpFunction:BRAC_TransBuffer_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ����͸��ͨ��������չ�ص�����
  function BRAC_SetTransBufferExCallBack(lpFunction:BRAC_TransBufferEx_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // �����ļ�����ص�����
  function BRAC_SetTransFileCallBack(lpFunction:BRAC_TransFile_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ���������仯�ص�����
  function BRAC_SetVolumeChangeCallBack(lpFunction:BRAC_VolumeChange_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ����SDK Filterͨ�����ݻص���������
  function BRAC_SetSDKFilterDataCallBack(lpFunction:BRAC_SDKFilterData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ����¼������������֪ͨ�ص�����
  function BRAC_SetRecordSnapShotCallBack(lpFunction:BRAC_RecordSnapShot_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // �����첽��Ϣ֪ͨ�ص�����
  function BRAC_SetNotifyMessageCallBack(lpFunction:BRAC_NotifyMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // ������Ƶͨ����Ϣ֪ͨ�ص�����
  function BRAC_SetVideoCallEventCallBack(lpFunction:BRAC_VideoCallEvent_CallBack; lpUserValue:Pointer=nil):DWORD;cdecl;
//  // �������ݼ��ܡ����ܻص�����
//  function BRAC_SetDataEncDecCallBack(lpFunction:BRAC_DataEncDec_CallBack; lpUserValue:Pointer=nil):DWORD;cdecl;


  // ���ӷ�����
  function BRAC_Connect(lpServerAddr:LPCTSTR;dwPort:DWORD):DWORD;cdecl;
  // ��¼ϵͳ
  function BRAC_Login(lpUserName:LPCTSTR;lpPassword:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
  // ���뷿��
  function BRAC_EnterRoom(dwRoomid:DWORD;lpRoomPass:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
  // ���뷿��
  function BRAC_EnterRoomEx(lpRoomName:LPCTSTR;lpRoomPass:LPCTSTR):DWORD;cdecl;
  // �뿪����
  function BRAC_LeaveRoom(dwRoomid:DWORD):DWORD;cdecl;
  // ע��ϵͳ
  function BRAC_Logout():DWORD;cdecl;
  // �ͷ�������Դ
  function BRAC_Release():DWORD;cdecl;

  // ��ȡ��ǰ���������û��б�
  function BRAC_GetOnlineUser(lpUserIDArray:LPDWORD;var dwUserNum:DWORD):DWORD;cdecl;
  // ��ѯ�û�����ͷ��״̬
  function BRAC_GetCameraState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
  // ��ѯ�û�����״̬
  function BRAC_GetSpeakState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
  // ��ѯ�û�����
  function BRAC_GetUserLevel(dwUserid:DWORD;var dwLevel:DWORD):DWORD;cdecl;
  // ��ѯ�û�����
  function BRAC_GetUserName(dwUserid:DWORD;lpUserName:PChar;dwLen:DWORD):DWORD;cdecl;
  // ��ѯ��������
  function BRAC_GetRoomName(dwRoomId:DWORD;lpRoomName:PChar;dwLen:DWORD):DWORD;cdecl;  
  // ��ʾ������Ƶ������ڶԻ���
  function BRAC_ShowLVProperty(hParent:THandle;szCaption:LPCTSTR=nil;dwX:DWORD=0;dwY:DWORD=0):DWORD;cdecl;
  // ��ѯָ���û����״̬
  function BRAC_QueryUserState(dwUserId:DWORD;infoname:Integer;infoval:Pointer;infolen:Integer):DWORD;cdecl;


  // ö�ٱ�����Ƶ�ɼ��豸
  function BRAC_EnumVideoCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
  // ѡ��ָ������Ƶ�ɼ��豸
  function BRAC_SelectVideoCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
  // ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
  function BRAC_GetCurVideoCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
  // ö�ٱ�����Ƶ�ɼ��豸
  function BRAC_EnumAudioCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
  // ѡ��ָ������Ƶ�ɼ��豸
  function BRAC_SelectAudioCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
  // ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
  function BRAC_GetCurAudioCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;


  // �����û���Ƶ
  function BRAC_UserCameraControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
  // �����û�����
  function BRAC_UserSpeakControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
  // ������Ƶ��ʾλ��
  function BRAC_SetVideoPos(dwUserid:DWORD;hWnd:THandle;dwLeft:DWORD;dwTop:DWORD;dwRight:DWORD;dwBottom:DWORD):DWORD;cdecl;

  // ��ȡָ����Ƶ�豸�ĵ�ǰ����
  function BRAC_AudioGetVolume(device:BRAC_AudioDevice;var dwVolume:DWORD):DWORD;cdecl;
  // ����ָ����Ƶ�豸������
  function BRAC_AudioSetVolume(device:BRAC_AudioDevice;dwVolume:DWORD):DWORD;cdecl;

  // �û�������Ƶ¼��
  function BRAC_StreamRecordCtrl(dwUserId:DWORD;bStartRecord:BOOL;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
  // ���û�����Ƶ����ץ�ģ����գ�
  function BRAC_SnapShot(dwUserId:DWORD;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
  

  // ͸��ͨ�����ͻ�����
  function BRAC_TransBuffer(dwUserid:DWORD;lpBuf:PBYTE;dwLen:DWORD):DWORD;cdecl;
  // ͸��ͨ�����ͻ�������չ
  function BRAC_TransBufferEx(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
  // �����ļ�
  function BRAC_TransFile(dwUserid:DWORD;lpLocalPathName:LPCTSTR;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
  // ��ѯ�������������Ϣ
  function BRAC_QueryTransTaskInfo(dwUserid:DWORD;dwTaskId:DWORD;infoname:Integer;
    infoval:Pointer;infolen:Integer):DWORD;cdecl;
  // ȡ����������
  function BRAC_CancelTransTask(dwUserid:DWORD;dwTaskId:DWORD):DWORD;cdecl;
  // �����ı���Ϣ
  function BRAC_SendTextMessage(dwUserid:DWORD;bSecret:BOOL;lpMsgBuf:LPCTSTR;
    dwLen:DWORD):DWORD;cdecl;
  // ����SDK Filter ͨ������
  function BRAC_SendSDKFilterData(lpBuf:PByte;dwLen:DWORD):DWORD;cdecl;

  // ���ĵ�ǰ������ģʽ
  function BRAC_ChangeChatMode(dwChatMode:DWORD):DWORD;cdecl;
  // ��ȡָ���û���ǰ������ģʽ
  function BRAC_GetUserChatMode(dwUserid:DWORD;var dwChatMode:DWORD):DWORD;cdecl;
  // ������Է�˽�ģ���Է�����˽������
  function BRAC_PrivateChatRequest(dwUserid:DWORD):DWORD;cdecl;
  // �ظ��Է���˽������
  function BRAC_PrivateChatEcho(dwUserid:DWORD;dwRequestid:DWORD;bAccept:BOOL):DWORD;cdecl;
  // �ظ��Է���˽��������չ�����Ը���������룩
  function BRAC_PrivateChatEchoEx(dwUserid:DWORD;dwRequestid:DWORD;dwErrorCode:DWORD):DWORD;cdecl;
  // �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
  function BRAC_PrivateChatExit(dwUserid:DWORD):DWORD;cdecl;
  // SDK�ں˲�������
  function  BRAC_SetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;
  // SDK�ں˲���״̬��ѯ
  function BRAC_GetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;  
  
  // ��Ƶ�����¼����ƣ����󡢻ظ����Ҷϵȣ�
  function BRAC_VideoCallControl(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR):DWORD;cdecl;

  function SetUserStreamInfo(userId: DWORD; streamIndex: DWORD; infoname: DWORD; infoval: Pointer; infolen: DWORD): DWORD; cdecl;

  function SetVideoPosEx(userId: DWORD; hWnd: THandle; left, top, right, bottom, streamIndex, flags: DWORD): DWORD; cdecl;

  function BRAC_StreamPlaySetVideoPos(lpTaskGuid: LPCTSTR; hWnd: THandle; dwLeft: DWORD = 0; dwTop: DWORD = 0; dwRight: DWORD = 0; dwBottom: DWORD = 0): DWORD; cdecl;

  function UserCameraControlEx(userId: DWORD; Open: Boolean; streamIndex: DWORD; flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;

  function StreamRecordCtrlEx(userId: DWORD; startRecord: Integer; flags, param: DWORD; userstr: LPCTSTR): DWORD; cdecl;

  function BRAC_SetCallBack(dwCBType: DWORD; lpFunction: Pointer; lpUserValue: Pointer): DWORD; cdecl;

  function BRAC_StreamPlayInit(taskGuid, streamPath: LPCTSTR; flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;

  function BRAC_StreamPlayControl(taskGuid: LPCTSTR; ctrlCode, param, flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;

  function BRAC_StreamPlayGetInfo(lpTaskGuid: LPCTSTR; infoName: DWORD; infoValue: Pointer; dwSize: DWORD): DWORD; cdecl;

  function BRAC_StreamPlayDestroy(taskGuid: LPCTSTR; flags: DWORD): DWORD; cdecl;

  function BRAC_QueryInfoFromServer(dwInfoName: DWORD; lpInParam: LPSTR; dwInSize: DWORD; lpResult: LPSTR; var dwOutSize: DWORD; dwFlags: DWORD = 0):DWORD; cdecl;

implementation

  // ��ȡSDK�汾��Ϣ
  function BRAC_GetSDKVersion(var dwMainVer:DWORD;var dwSubVer:DWORD;lpCompileTime:LPSTR;dwBufLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetSDKVersion';

  // ����رգ�SDK������־
  function BRAC_ActiveCallLog(bActive:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ActiveCallLog';

  // ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
  function BRAC_SetServerAuthPass(lpPassword:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetServerAuthPass';

  // ��ʼ��ϵͳ
  function BRAC_InitSDK(hWnd:HWND;dwFuncMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_InitSDK';
  // ������Ƶ���ݻص�����
  function BRAC_SetVideoDataCallBack(pixFmt:BRAC_PixelFormat;lpFunction:BRAC_VideoData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVideoDataCallBack';
  // ������Ƶ���ݻص�����
  function BRAC_SetAudioDataCallBack(lpFunction:BRAC_AudioData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetAudioDataCallBack';
  // ����������Ϣ�ص�����
  function BRAC_SetTextMessageCallBack(lpFunction:BRAC_TextMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTextMessageCallBack';
  // ����͸��ͨ�����ݻص�����
  function BRAC_SetTransBufferCallBack(lpFunction:BRAC_TransBuffer_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransBufferCallBack';

  // ����͸��ͨ��������չ�ص�����
  function BRAC_SetTransBufferExCallBack(lpFunction:BRAC_TransBufferEx_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransBufferExCallBack';

  // �����ļ�����ص�����
  function BRAC_SetTransFileCallBack(lpFunction:BRAC_TransFile_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransFileCallBack';

  // ���������仯�ص�����
  function BRAC_SetVolumeChangeCallBack(lpFunction:BRAC_VolumeChange_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVolumeChangeCallBack';

  // ����SDK Filterͨ�����ݻص���������
  function BRAC_SetSDKFilterDataCallBack(lpFunction:BRAC_SDKFilterData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetSDKFilterDataCallBack';

  // ����¼������������֪ͨ�ص�����
  function BRAC_SetRecordSnapShotCallBack(lpFunction:BRAC_RecordSnapShot_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetRecordSnapShotCallBack';

  // �����첽��Ϣ֪ͨ�ص�����
  function BRAC_SetNotifyMessageCallBack(lpFunction:BRAC_NotifyMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetNotifyMessageCallBack';

  // ������Ƶͨ����Ϣ֪ͨ�ص�����
  function BRAC_SetVideoCallEventCallBack(lpFunction:BRAC_VideoCallEvent_CallBack; lpUserValue:Pointer=nil):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_SetVideoCallEventCallBack';


  // ���ӷ�����
  function BRAC_Connect(lpServerAddr:LPCTSTR;dwPort:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Connect';
  // ��¼ϵͳ
  function BRAC_Login(lpUserName:LPCTSTR;lpPassword:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Login';
  // ���뷿��
  function BRAC_EnterRoom(dwRoomid:DWORD;lpRoomPass:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_EnterRoom';
  // ���뷿��
  function BRAC_EnterRoomEx(lpRoomName:LPCTSTR;lpRoomPass:LPCTSTR):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_EnterRoomEx';  
  // �뿪����
  function BRAC_LeaveRoom(dwRoomid:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_LeaveRoom';
  // ע��ϵͳ
  function BRAC_Logout():DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Logout';
  // �ͷ�������Դ
  function BRAC_Release():DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Release';  

  // ��ȡ��ǰ���������û��б�
  function BRAC_GetOnlineUser(lpUserIDArray:LPDWORD;var dwUserNum:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetOnlineUser';
  // ��ѯ�û�����ͷ��״̬
  function BRAC_GetCameraState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetCameraState'; 
  // ��ѯ�û�����״̬
  function BRAC_GetSpeakState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetSpeakState';
  // ��ѯ�û�����
  function BRAC_GetUserLevel(dwUserid:DWORD;var dwLevel:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetUserLevel';
  // ��ѯ�û�����
  function BRAC_GetUserName(dwUserid:DWORD;lpUserName:PChar;dwLen:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetUserName';
  // ��ѯ��������
  function BRAC_GetRoomName(dwRoomId:DWORD;lpRoomName:PChar;dwLen:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetRoomName';  

  // ��ʾ������Ƶ������ڶԻ���
  function BRAC_ShowLVProperty(hParent:THandle;szCaption:LPCTSTR;dwX:DWORD;dwY:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ShowLVProperty';

  // ��ѯָ���û����״̬
  function BRAC_QueryUserState(dwUserId:DWORD;infoname:Integer;infoval:Pointer;infolen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_QueryUserState';             

  // ö�ٱ�����Ƶ�ɼ��豸
  function BRAC_EnumVideoCapture(lpDeviceName: PPChar; var dwDeviceNum:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_EnumVideoCapture';
  // ѡ��ָ������Ƶ�ɼ��豸
  function BRAC_SelectVideoCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SelectVideoCapture';
  // ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
  function BRAC_GetCurVideoCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetCurVideoCapture';
  // ö�ٱ�����Ƶ�ɼ��豸
  function BRAC_EnumAudioCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_EnumAudioCapture'; 
  // ѡ��ָ������Ƶ�ɼ��豸
  function BRAC_SelectAudioCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SelectAudioCapture'; 
  // ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
  function BRAC_GetCurAudioCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetCurAudioCapture';


  // �����û���Ƶ
  function BRAC_UserCameraControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_UserCameraControl';
  // �����û�����
  function BRAC_UserSpeakControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_UserSpeakControl';
  // ������Ƶ��ʾλ��
  function BRAC_SetVideoPos(dwUserid:DWORD;hWnd:THandle;dwLeft:DWORD;dwTop:DWORD;dwRight:DWORD;dwBottom:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVideoPos'; 

  // ��ȡָ����Ƶ�豸�ĵ�ǰ����
  function BRAC_AudioGetVolume(device:BRAC_AudioDevice;var dwVolume:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_AudioGetVolume';
  // ����ָ����Ƶ�豸������
  function BRAC_AudioSetVolume(device:BRAC_AudioDevice;dwVolume:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_AudioSetVolume';

  // �û�������Ƶ¼��
  function BRAC_StreamRecordCtrl(dwUserId:DWORD;bStartRecord:BOOL;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_StreamRecordCtrl';

  // ���û�����Ƶ����ץ�ģ����գ�
  function BRAC_SnapShot(dwUserId:DWORD;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SnapShot';                          

  // ͸��ͨ�����ͻ�����
  function BRAC_TransBuffer(dwUserid:DWORD;lpBuf:PBYTE;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransBuffer';

  // ͸��ͨ�����ͻ�������չ
  function BRAC_TransBufferEx(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransBufferEx';

  // �����ļ�           
  function BRAC_TransFile(dwUserid:DWORD;lpLocalPathName:LPCTSTR;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransFile';

  // ��ѯ�������������Ϣ
  function BRAC_QueryTransTaskInfo(dwUserid:DWORD;dwTaskId:DWORD;infoname:Integer;
    infoval:Pointer;infolen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_QueryTransTaskInfo';

  // ȡ����������
  function BRAC_CancelTransTask(dwUserid:DWORD;dwTaskId:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_CancelTransTask';                                           

  // �����ı���Ϣ
  function BRAC_SendTextMessage(dwUserid:DWORD;bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SendTextMessage';

  // ����SDK Filter ͨ������
  function BRAC_SendSDKFilterData(lpBuf:PByte;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SendSDKFilterData';

  // ���ĵ�ǰ������ģʽ
  function BRAC_ChangeChatMode(dwChatMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ChangeChatMode';
  // ��ȡָ���û���ǰ������ģʽ
  function BRAC_GetUserChatMode(dwUserid:DWORD;var dwChatMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetUserChatMode';
  // ������Է�˽�ģ���Է�����˽������
  function BRAC_PrivateChatRequest(dwUserid:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatRequest';
  // �ظ��Է���˽������
  function BRAC_PrivateChatEcho(dwUserid:DWORD;dwRequestid:DWORD;bAccept:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatEcho';
  // �ظ��Է���˽��������չ�����Ը���������룩
  function BRAC_PrivateChatEchoEx(dwUserid:DWORD;dwRequestid:DWORD;dwErrorCode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatEchoEx';
  // �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
  function BRAC_PrivateChatExit(dwUserid:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatExit';

  // SDK�ں˲�������
  function  BRAC_SetSDKOption(optname:Integer; optval:Pointer; optlen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetSDKOption';

  // SDK�ں˲���״̬��ѯ
  function BRAC_GetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetSDKOption';

  // ��Ƶ�����¼����ƣ����󡢻ظ����Ҷϵȣ�
  function BRAC_VideoCallControl(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_VideoCallControl';

  function GetUserStreamInfo(userId: DWORD; streamIndex: DWORD; infoname: DWORD; infoval: Pointer; infolen: DWORD): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_GetUserStreamInfo';

  function SetUserStreamInfo(userId: DWORD; streamIndex: DWORD; infoname: DWORD; infoval: Pointer; infolen: DWORD): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_SetUserStreamInfo';

  function UserCameraControlEx(userId: DWORD; Open: Boolean; streamIndex: DWORD; flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_UserCameraControlEx';

  function UserSpeakControlEx(userId: DWORD; Open: Boolean; streamIndex: DWORD; flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_UserSpeakControlEx';

  function SetVideoPosEx(userId: DWORD; hWnd: THandle; left, top, right, bottom, streamIndex, flags: DWORD): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_SetVideoPosEx';

function BRAC_StreamPlaySetVideoPos(lpTaskGuid: LPCTSTR; hWnd: THandle; dwLeft: DWORD = 0; dwTop: DWORD = 0; dwRight: DWORD = 0; dwBottom: DWORD = 0): DWORD;  cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamPlaySetVideoPos';

  function StreamRecordCtrlEx(userId: DWORD; startRecord: Integer; flags, param: DWORD; userstr: LPCTSTR): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamRecordCtrlEx';

  function BRAC_SetCallBack(dwCBType: DWORD; lpFunction: Pointer; lpUserValue: Pointer): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_SetCallBack';

  function BRAC_StreamPlayInit(taskGuid, streamPath: LPCTSTR; flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamPlayInit';

  function BRAC_StreamPlayControl(taskGuid: LPCTSTR; ctrlCode, param, flags: DWORD; strParam: LPCTSTR): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamPlayControl';

  function BRAC_StreamPlayGetInfo(lpTaskGuid: LPCTSTR; infoName: DWORD; infoValue: Pointer; dwSize: DWORD): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamPlayGetInfo';

  function BRAC_StreamPlayDestroy(taskGuid: LPCTSTR; flags: DWORD): DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_StreamPlayDestroy';       

  function BRAC_QueryInfoFromServer(dwInfoName: DWORD; lpInParam: LPSTR; dwInSize: DWORD; lpResult: LPSTR; var dwOutSize: DWORD; dwFlags: DWORD = 0):DWORD; cdecl;
      external C_BRAnyChatCoreLibName name 'BRAC_QueryInfoFromServer';
end.
