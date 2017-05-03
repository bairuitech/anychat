#if !defined(_ANYCHAT_DEFINE_H__INCLUDE_)
#define _ANYCHAT_DEFINE_H__INCLUDE_

/**
 *	AnyChat SDK Client Const Define Include File
 */


// ��Ƶͼ���ʽ����
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...��MEDIASUBTYPE_RGB24��
	BRAC_PIX_FMT_RGB32,							///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB32��Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YV12��Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YUY2��Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	BRAC_PIX_FMT_YUV420P,						///< Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_RGB565,						///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB565
	BRAC_PIX_FMT_RGB555,						///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB555
	BRAC_PIX_FMT_NV12,							///< Planar YUV 4:2:0, 12bpp, Two arrays, one is all Y, the other is U and V
	BRAC_PIX_FMT_NV21,							///< Planar YUV 4:2:0, 12bpp, Two arrays, one is all Y, the other is V and U
	BRAC_PIX_FMT_NV16,							///< YUV422SP
	
	BRAC_PIX_FMT_MJPEG = 200,
	BRAC_PIX_FMT_H264,
};

// ��Ƶ�豸����
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< �����豸��Mic
	BRAC_AD_WAVEOUT,							///< ����豸��Wave
};

// ��Ƶ��ʾ��������
enum BRAC_VideoShowDriver{
	BRAC_VSD_DEFAULT = 0,						///< Ĭ����ʾ����
	BRAC_VSD_DIRECTSHOW,						///< DirectShow��ʾ����
	BRAC_VSD_WINDOWSGDI,						///< Windows GDI����
};


// ����ģʽ���壨API��BRAC_InitSDK ���������
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002	///< ��SDK��������Ƶ������Ƶ��ʾ��ָ���Ĵ�����
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008	///< ��SDK��������Ƶ��ֱ�Ӳ���
#define BRAC_FUNC_CONFIG_LOCALINI	0x00000010	///< ���ɱ��������ļ���AnyChatSDK.ini��
#define BRAC_FUNC_FIREWALL_OPEN		0x00000020	///< ����SDK����Windows����ǽ������ǰӦ�ó���������ǽ�����б�����Windows��ʾ�û��Ƿ���ֹ��ǰӦ�ó���
#define BRAC_FUNC_CHKDEPENDMODULE	0x00000040	///< �Զ����SDK����������������Զ�ע��
#define BRAC_FUNC_AUDIO_VOLUMECALC	0x00000080	///< ��SDK�Զ���������������
#define BRAC_FUNC_AUDIO_AUTOVOLUME	0x00000100	///< ����SDK�Զ�����Mic¼������
#define BRAC_FUNC_NET_SUPPORTUPNP	0x00000200	///< ����SDK���û������е�UPNP�豸������û���·�������Ƿ���ǽ֧��UPNPЭ�飬������P2P�򶴵ĳɹ���
#define BRAC_FUNC_DISABLEDECODE		0x00000400	///< ��ֹ���յ������ݽ��н���Ͳ��ţ�Ϊ����ߴ���ͻ��˵�����ת�����ܣ������øñ�־�����������øñ�־
#define BRAC_FUNC_MAINTHREADCB		0x00000800	///< ���߳̽��лص�������Ĭ���Ƕ��̻߳����µ����ݻص�
#define BRAC_FUNC_AUDIO_FORBIDCFGHW	0x00001000	///< ��ֹ�޸���ƵӲ������
#define BRAC_FUNC_CORE_FORBIDWINMSG	0x00002000	///< ��ֹʹ��windows��Ϣѭ��
#define BRAC_FUNC_AUDIO_LARGEBUFFER	0x00004000	///< ��Ƶ�󻺳���ģʽ���ʺ����ֲ�����Ӧ��
#define BRAC_FUNC_NET_LARGEDELAY	0x00010000	///< ������ӳ�ģʽ���������������绷��


// �ں˲������壨API��BRAC_SetSDKOption��BRAC_GetSDKOption ���������
#define BRAC_SO_AUDIO_VADCTRL				1	///< ��Ƶ���������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_NSCTRL				2	///< ��Ƶ�������ƿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_ECHOCTRL				3	///< ��Ƶ�����������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_AGCCTRL				4	///< ��Ƶ�Զ�������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_CAPTUREMODE			5	///< ��Ƶ�ɼ�ģʽ���ã�����Ϊ��int�ͣ�0 ����ģʽ��1 �Ÿ�ģʽ��2 ����OKģʽ��3 ��·����ģʽ��
#define BRAC_SO_AUDIO_MICBOOST				6	///< ��Ƶ�ɼ�Mic��ǿ���ƣ�����Ϊ��int�ͣ�0 ȡ����1 ѡ�У�2 �豸������[��ѯʱ����ֵ]��
#define BRAC_SO_AUDIO_AUTOPARAM				7	///< ������Ƶ�ɼ�ģʽ���Զ�ѡ����ʵ���ز������������������������������ʲ����ȣ�����Ϊint�ͣ�1 ���ã�0 �ر�[Ĭ��]��
#define BRAC_SO_AUDIO_MONOBITRATE			8	///< ���õ�����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_AUDIO_STEREOBITRATE			9	///< ����˫����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_AUDIO_PLAYDRVCTRL			70	///< ��Ƶ��������ѡ�񣨲���Ϊ��int�ͣ�0Ĭ�������� 1 DSound������ 2 WaveOut������ 3 Java����[Androidƽ̨ʹ��]��
#define BRAC_SO_AUDIO_CNGCTRL				71	///< �����������ɿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_CODECID				72	///< ������Ƶ������ID���ã�����Ϊint�ͣ�-1��ʾĬ�ϣ�������õı�����ID�����ڣ����ں˻����Ĭ�ϵı�������
#define BRAC_SO_AUDIO_SOFTVOLMODE			73	///< �����������ģʽ���ƣ�����Ϊint�ͣ�1��[Ĭ��]��0�رգ���ʹ���������ģʽ��������ı�ϵͳ����������
#define BRAC_SO_AUDIO_RECORDDRVCTRL			74	///< ��Ƶ�ɼ��������ƣ�����Ϊint�ͣ�0Ĭ�������� 1 DSound������ 2 WaveIn������ 3 Java�ɼ�[Androidƽ̨ʹ��]��
#define BRAC_SO_AUDIO_ECHODELAY				75	///< ��Ƶ���������ӳٲ������ã�����Ϊint�ͣ���λ��ms��
#define BRAC_SO_AUDIO_NSLEVEL				76	///< ��Ƶ��������ˮƽ�������ã�����Ϊint�ͣ�0 - 3��Ĭ��Ϊ2��ֵԽ������ˮƽԽ�ߣ���������������Խǿ��
#define BRAC_SO_AUDIO_CBCODEC				77	///< ��Ƶ���ݻص����������ͣ�����Ϊint�ͣ�

#define BRAC_SO_RECORD_VIDEOBR				10	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_AUDIOBR				11	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_TMPDIR				12	///< ¼���ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< �����ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_RECORD_FILETYPE				140	///< ¼���ļ��������ã�����Ϊ��int�ͣ� 0 MP4[Ĭ��], 1 WMV, 2 FLV, 3 MP3��
#define BRAC_SO_RECORD_WIDTH				141	///< ¼����Ƶ������ã�����Ϊ��int�ͣ��磺320��
#define BRAC_SO_RECORD_HEIGHT				142	///< ¼���ļ��߶����ã�����Ϊ��int�ͣ��磺240��
#define BRAC_SO_RECORD_FILENAMERULE			143	///< ¼���ļ����������򣨲���Ϊ��int�ͣ�
#define BRAC_SO_RECORD_CLIPMODE				144	///< ¼����Ƶ�ü�ģʽ������Ϊ��int�ͣ�
#define BRAC_SO_RECORD_DISABLEDATEDIR		145	///< ¼���ļ��������ڷ�Ŀ¼���棬ȫ��������ָ���ļ����У�����Ϊ��int�ͣ� 0��ֹ[Ĭ��] 1 ������
#define BRAC_SO_RECORD_INSERTIMAGE			146	///< ¼�ƹ����в���ͼƬ��Json�ַ�������

#define BRAC_SO_CORESDK_TMPDIR				14	///< ����AnyChat Core SDK��ʱĿ¼������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_CORESDK_MAGICADJUST			15	///< �ں˵��Բ���
#define BRAC_SO_CORESDK_LOADCODEC			16	///< �����ⲿ�������������Ϊ�ַ���TCHAR���ͣ������������ľ���·���������ļ�����������ļ����ľ���·����
#define BRAC_SO_CORESDK_USEARMV6LIB			17	///< ǿ��ʹ��ARMv6ָ��Ŀ⣬androidƽ̨ʹ�ã�����Ϊ��int�ͣ�1ʹ��ARMv6ָ��� 0�ں��Զ��ж�[Ĭ��]��
#define BRAC_SO_CORESDK_USEHWCODEC			18	///< ʹ��ƽ̨����Ӳ���������������Ϊint�ͣ�0 ��ʹ��Ӳ���������[Ĭ��]  1 ʹ������Ӳ�����������
#define BRAC_SO_CORESDK_REMOTEDEBUG			19	///< Զ�̵��ԣ�����Ϊint�ͣ���ʾĿ���û�ID�����ò�������Ϊ�������Ͳ�����

#define BRAC_SO_CORESDK_PATH				20	///< ����AnyChat Core SDK������·��������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_CORESDK_DUMPCOREINFO		21	///< ����ں���Ϣ����־�ļ��У����ڷ�������ԭ�򣨲���Ϊ��int�ͣ�1 �����
#define BRAC_SO_CORESDK_MAINVERSION			22	///< ��ѯSDK���汾�źţ�����Ϊint�ͣ�
#define BRAC_SO_CORESDK_SUBVERSION			23	///< ��ѯSDK�Ӱ汾�ţ�����Ϊint�ͣ�
#define BRAC_SO_CORESDK_BUILDTIME			24	///< ��ѯSDK����ʱ�䣨����Ϊ�ַ���TCHAR���ͣ�
#define BRAC_SO_CORESDK_ACTIVESTATE			25	///< Ӧ�ó���״̬���ƣ�����Ϊint�ͣ� 1 Ӧ�ó����ڻ״̬�� 0 Ӧ�ó����ڷǻ״̬����������iPhone���豸����ɺ�̨���еĳ���
#define BRAC_SO_CORESDK_EXTVIDEOINPUT		26	///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
#define BRAC_SO_CORESDK_EXTAUDIOINPUT		27	///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
#define BRAC_SO_CORESDK_LOWDELAYCTRL		28	///< ���ӳ�ģʽ���ƣ�����Ϊint�ͣ�0 �رյ��ӳ�ģʽ[Ĭ��]�� 1 ���õ��ӳ�ģʽ��
#define BRAC_SO_CORESDK_NEWGUID				29	///< �����µ�GUID�ַ���

#define BRAC_SO_LOCALVIDEO_BITRATECTRL		30	///< ������Ƶ�����������ã�����Ϊint�ͣ���λbps��ͬ���������ã�VideoBitrate��
#define BRAC_SO_LOCALVIDEO_QUALITYCTRL		31	///< ������Ƶ�����������ӿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoQuality��
#define BRAC_SO_LOCALVIDEO_GOPCTRL			32	///< ������Ƶ����ؼ�֡������ƣ�����Ϊint�ͣ�ͬ���������ã�VideoGOPSize��
#define BRAC_SO_LOCALVIDEO_FPSCTRL			33	///< ������Ƶ����֡�ʿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoFps��
#define BRAC_SO_LOCALVIDEO_PRESETCTRL		34	///< ������Ƶ����Ԥ��������ƣ�����Ϊint�ͣ�1-5��
#define BRAC_SO_LOCALVIDEO_APPLYPARAM		35	///< Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
#define BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC	36	///< ������Ƶ�ɼ��ֱ��ʿ��Ʋ��ԣ�����Ϊint�ͣ�0 �Զ�������ƥ��[Ĭ��]��1 ʹ�òɼ��豸Ĭ�Ϸֱ��ʣ��������õķֱ��ʲ����ɼ��豸֧��ʱ��Ч
#define BRAC_SO_LOCALVIDEO_DEINTERLACE		37	///< ������Ƶ����֯�������ƣ�����Ϊint�ͣ� 0 �����з���֯����[Ĭ��]��1 ����֯��������������ƵԴ�Ǹ���ɨ��Դ��������źţ�ʱͨ������֯���������߻�������
#define BRAC_SO_LOCALVIDEO_WIDTHCTRL		38	///< ������Ƶ�ɼ��ֱ��ʿ�ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoWidth��
#define BRAC_SO_LOCALVIDEO_HEIGHTCTRL		39	///< ������Ƶ�ɼ��ֱ��ʸ߶ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoHeight��
#define BRAC_SO_LOCALVIDEO_FOCUSCTRL		90	///< ������Ƶ����ͷ�Խ����ƣ�����Ϊint�ͣ�1��ʾ�Զ��Խ��� 0��ʾ�ֶ��Խ���
#define BRAC_SO_LOCALVIDEO_PIXFMTCTRL		91	///< ������Ƶ�ɼ����ȸ�ʽ���ƣ�����Ϊint�ͣ�-1��ʾ����ƥ�䣬�������Ȳ���ָ����ʽ���ο���BRAC_PixelFormat��
#define BRAC_SO_LOCALVIDEO_OVERLAY			92	///< ������Ƶ����Overlayģʽ������Ϊint�ͣ�1��ʾ����Overlayģʽ�� 0��ʾ��ͨģʽ[Ĭ��]��
#define BRAC_SO_LOCALVIDEO_CODECID			93	///< ������Ƶ������ID���ã�����Ϊint�ͣ�-1��ʾĬ�ϣ�������õı�����ID�����ڣ����ں˻����Ĭ�ϵı�������
#define BRAC_SO_LOCALVIDEO_ROTATECTRL		94	///< ������Ƶ��ת���ƣ���ʧЧ��ʹ�ã�BRAC_SO_LOCALVIDEO_CAMERAROTATION�����
#define BRAC_SO_LOCALVIDEO_CAPDRIVER		95	///< ������Ƶ�ɼ��������ã�����Ϊint�ͣ�0��ʾ�Զ�ѡ��[Ĭ��]�� 1 Video4Linux, 2 DirectShow, 3 Java�ɼ�[Androidƽ̨ʹ��]��
#define BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA	96	///< ������Ƶ�ɼ���ɫƫɫ������Ϊint�ͣ�0��ʾ�ر�[Ĭ��]��1 ������
#define BRAC_SO_LOCALVIDEO_ORIENTATION		97	///< ������Ƶ�豸���򣨲���Ϊ��int�ͣ�����Ϊ������ANYCHAT_DEVICEORIENTATION_XXXX��
#define BRAC_SO_LOCALVIDEO_AUTOROTATION		98	///< ������Ƶ�Զ���ת���ƣ�����Ϊint�ͣ� 0��ʾ�رգ� 1 ����[Ĭ��]����Ƶ��תʱ��Ҫ�ο�������Ƶ�豸���������
#define BRAC_SO_LOCALVIDEO_SURFACEROTATION	99	///< ���ñ�����ƵԤ����ʾ��ת�Ƕȣ�����Ϊint�ͣ��Ƕȣ�
#define BRAC_SO_LOCALVIDEO_CAMERAFACE		100	///< ��������ͷ����ǰ�á����ã�
#define BRAC_SO_LOCALVIDEO_CAMERAROTATION	101	///< ��������ͷ��ת�Ƕ�
#define BRAC_SO_LOCALVIDEO_DEVICEROTATION	102	///< �豸��ת�Ƕ�
#define BRAC_SO_LOCALVIDEO_DEVICEMODE		103	///< �豸����
#define BRAC_SO_LOCALVIDEO_TVFORMAT			104	///< ��Ƶ�ɼ���ʽ���ã�����Ϊ��int�ͣ�����ΪDirectShow::strmif.h::AnalogVideoStandard��Ĭ��Ϊ��AnalogVideo_PAL_B��
#define BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP	105	///< ����ʱ�����������Ƶ������Ϊ��int�ͣ� 0 ������[Ĭ��]�� 1 ���ӣ�
#define BRAC_SO_LOCALVIDEO_DEVICENAME		106	///< ������Ƶ�ɼ��豸���ƣ��������ô�ָ������ͷ�豸������Ϊ�ַ������ͣ�
#define BRAC_SO_LOCALVIDEO_CLIPMODE			107	///< ������Ƶ�ü�ģʽ������Ϊint�ͣ� 0 �Զ�[Ĭ��]����ֹ�Զ���תʱ��Ч��
#define BRAC_SO_LOCALVIDEO_SCREENHWND		108	///< ��Ļ�ɼ����ھ��
#define BRAC_SO_LOCALVIDEO_SCREENFLAGS		109	///< ��Ļ�ɼ���־������Ϊint�ͣ�
#define BRAC_SO_LOCALVIDEO_VIRTUALBK		111 ///< ������Ƶ�������ⱳ�����ַ������ͣ�JSON��ʽ���������ⱳ��·���Լ����������ΪNULL��ʾȡ�����ⱳ����

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< ��������P2P���Կ��ƣ�����Ϊ��int�ͣ�0 ��ֹ����P2P��1 ����������P2P[Ĭ��]��2 �ϲ�Ӧ�ÿ���P2P���ӣ�3 ���轨��P2P���ӣ�
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< ������ָ���û�����P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID�������ӽ����ɹ��󣬻�ͨ����Ϣ�������ϲ�Ӧ�ã�P2P���Ʋ���=2ʱ��Ч
#define BRAC_SO_NETWORK_P2PBREAK			42	///< �Ͽ���ָ���û���P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID��[�ݲ�֧�֣�����]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< ���ñ���TCP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< ���ñ���UDP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< �鲥���Կ��ƣ�����Ϊint�ͣ�����Ϊ������BRAC_MCPOLITIC_XXXX��
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< ���仺�������ļ�������ʿ��ƣ�����Ϊint�ͣ�0 �����ƣ���������ʴ���[Ĭ��]�� �����ʾ�������ʣ���λΪ��bps��
#define BRAC_SO_NETWORK_AUTORECONNECT		47	///< ��������Զ��������ܿ��ƣ�����Ϊint�ͣ�0 �رգ� 1 ����[Ĭ��]��
#define BRAC_SO_NETWORK_MTUSIZE				48	///< ���������MTU��С������Ϊint�ͣ�
#define BRAC_SO_NETWORK_UDPSTATUS			49	///< UDP����ͨ��״̬��ѯ������Ϊint�ͣ�

#define BRAC_SO_PROXY_FUNCTIONCTRL			50	///< �����û������ܿ��ƣ�������Ϊ��int�ͣ�1��������0�رմ���[Ĭ��]��
#define BRAC_SO_PROXY_VIDEOCTRL				51	///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������Ϊint�ͣ���ʾ�����û���userid��
#define BRAC_SO_PROXY_AUDIOCTRL				52	///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������ͬBRAC_SO_PROXY_VIDEOCTRL��

#define BRAC_SO_STREAM_MAXBUFFERTIME		60	///< ���������ʱ�䣨����Ϊint�ͣ���λ�����룬ȡֵ��Χ��500 ~ 5000��Ĭ�ϣ�800��������ģʽ����ֵ������ģʽ���Զ�����һ��
#define BRAC_SO_STREAM_SMOOTHPLAYMODE		61	///< ƽ������ģʽ������Ϊint�ͣ�0 �ر�[Ĭ��], 1 �򿪣�����״̬��������Ƶ��֡ʱ��������ţ����ܳ��������ˣ������Ῠס

#define BRAC_SO_VIDEOSHOW_MODECTRL			80	///< ��Ƶ��ʾģʽ���ƣ�����Ϊ��int�ͣ�0 ��������ʾ��1 ��Ƶ������ʾ��
#define BRAC_SO_VIDEOSHOW_SETPRIMARYUSER	81	///< ��������ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
#define BRAC_SO_VIDEOSHOW_SETOVERLAYUSER	82	///< ���õ�����ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
#define BRAC_SO_VIDEOSHOW_DRIVERCTRL		83	///< ��Ƶ��ʾ�������ƣ�����Ϊ��int�ͣ�0 Ĭ�������� 1 Windows DirectShow��2 Windows GDI��3 SDL, 4 Android2X, 5 Android Java��
#define BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER	84	///< ��Ƶ���ݾ���GPUֱ����Ⱦ������������Ƶ����ֱ�Ӵ��䵽GPU�������ַ������Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 �򿪣�����Ӳ��ƽ̨���
#define BRAC_SO_VIDEOSHOW_AUTOROTATION		85	///< Զ����Ƶ��ʾ�Զ���ת���ƣ�����Ϊint�ͣ� 0��ʾ�رգ� 1 ����[Ĭ��]����Ƶ��תʱ��Ҫ�ο�������Ƶ�豸���������
#define BRAC_SO_VIDEOSHOW_CLIPMODE			86	///< Զ����Ƶ��ʾ��ת�ü�ģʽ������Ϊint�ͣ� 0 �Զ�[Ĭ��]��
#define BRAC_SO_VIDEOSHOW_CBPIXFMT			87	///< ��Ƶ���ݻص���ʽ������Ϊint�ͣ�

#define BRAC_SO_CORESDK_TICKOUTUSER			110	///< �ӷ��������ߵ�ָ���û�������Ϊint�ͣ���ʾĿ���û�ID��

#define BRAC_SO_CORESDK_DEVICEMODE			130	///< �豸ģʽ���ƣ��������豸֮����Ի���ͨ�ţ�������������������Ϊint�ͣ�0 �ر�[Ĭ��]��1 ������
#define BRAC_SO_CORESDK_SCREENCAMERACTRL	131	///< ���湲���ܿ��ƣ�����Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 ������
#define BRAC_SO_CORESDK_DATAENCRYPTION		132	///< ���ݼ��ܿ��ƣ�����Ϊ��int�ͣ� 0 �ر�[Ĭ��]�� 1 ������
#define BRAC_SO_CORESDK_MEDIAUTILLIB		133	///< ��ȡbrMediaUtil.dll�Ŀ���ؾ��
#define BRAC_SO_CORESDK_UPLOADLOGINFO		134	///< �ϴ���־��Ϣ��������������Ϊ��int�ͣ�0 �ر�[Ĭ��]�� 1 ������
#define BRAC_SO_CORESDK_WRITELOG			135	///< д�������Ϣ���ͻ�����־�ļ���
#define BRAC_SO_CORESDK_NEWLOGFILE			136	///< �����µ���־�ļ�
#define BRAC_SO_CORESDK_SUPPORTSIP			137	///< �жϵ�ǰ�Ƿ�֧��SIPͨ��
#define BRAC_SO_CORESDK_SUPPORTHTML5		138	///< �жϵ�ǰ�Ƿ�֧��HTML5
#define BRAC_SO_CORESDK_SUPPORTVIDEOCODEC	210	///< ����֧�ֵ���Ƶ������
#define BRAC_SO_CORESDK_SUPPORTAUDIOCODEC	211	///< ����֧�ֵ���Ƶ������
#define BRAC_SO_CORESDK_DISABLEMEDIACONSUL	212	///< ��ֹý��Э��
#define BRAC_SO_CORESDK_QUERYTIMEOUTTIME	213	///< ��Ϣ��ѯ��ʱʱ�䣨����Ϊ��int�ͣ���λ��ms��Ĭ��ֵ1000��
#define BRAC_SO_CORESDK_REMOTEASSISTHWND	214	///< Զ��Э�����ھ��
#define BRAC_SO_CORESDK_REMOTEASSISTXPOS	215	///< Զ��Э�����ڹ�����λ�ã�X��
#define BRAC_SO_CORESDK_REMOTEASSISTYPOS	216	///< Զ��Э�����ڹ�����λ�ã�Y��
#define BRAC_SO_CORESDK_DISABLEDNSCONNECT	219	///< ����DNSѰַ
#define BRAC_SO_CORESDK_LOGFILEROOTPATH		220	///< ��־�ļ������·������־�ض��򣬲���Ϊ�ַ���������·����
#define BRAC_SO_CORESDK_KEEPALLLOGFILES		221	///< ����ͻ���������־�ļ���������֮ǰ����־�ļ���

#define BRAC_SO_UDPTRACE_MODE				160 ///< UDP���ݰ�����ģʽ
#define BRAC_SO_UDPTRACE_PACKSIZE			161	///< UDP���ݰ����ٵĴ�С����λ��BYTE
#define BRAC_SO_UDPTRACE_BITRATE			162	///< UDP���ݰ����ٵİ����ʣ���λ��bps
#define BRAC_SO_UDPTRACE_START				163	///< UDP���ݰ����ٿ��ƣ�����Ϊint�ͣ�1 ������ 0 ֹͣ��
#define BRAC_SO_UDPTRACE_LOCALRECVNUM		164 ///< UDP���ݰ����ٱ��ؽ��հ�����
#define BRAC_SO_UDPTRACE_SERVERRECVNUM		165	///< UDP���ݰ����ٷ��������հ�����
#define BRAC_SO_UDPTRACE_SOURCESENDNUM		166	///< UDP���ݰ�����Դ��������
#define BRAC_SO_UDPTRACE_SENDUSERID			167	///< UDP���ݰ�����Դ�û�ID

// �û���ý�����������壨API��BRAC_GetUserStreamInfo ���������
#define BRAC_STREAMINFO_VIDEOWIDTH			180 ///< ��Ƶ�����
#define BRAC_STREAMINFO_VIDEOHEIGHT			181	///< ��Ƶ���߶�
#define BRAC_STREAMINFO_VIDEOFPS			182	///< ��Ƶ��֡��
#define BRAC_STREAMINFO_VIDEOBITRATE		183	///< ��Ƶ�����ʣ���λ��bps
#define BRAC_STREAMINFO_VIDEOCODECID		184	///< ��Ƶ��������ID
#define BRAC_STREAMINFO_VIDEOPACKLOSSRATE	185	///< ��Ƶ��������
#define BRAC_STREAMINFO_ADUIOCHANNELS		190	///< ��Ƶ��ͨ����
#define BRAC_STREAMINFO_AUDIOSAMPLERATE		191	///< ��Ƶ��������
#define BRAC_STREAMINFO_AUDIOBITRATE		192	///< ��Ƶ�����ʣ���λ��bps
#define BRAC_STREAMINFO_AUDIOCODECID		193	///< ��Ƶ��������ID
#define BRAC_STREAMINFO_AUDIOPACKLOSSRATE	194	///< ��Ƶ��������


#define BRAC_SO_OBJECT_INITFLAGS			200	///< ҵ�������ݳ�ʼ��

#define BRAC_SO_CLOUD_APPGUID				300	///< ��ƽ̨Ӧ��GUID������Ϊ���ַ������ͣ����ӷ�����֮ǰ���ã�
#define BRAC_SO_CLOUD_ACCTYPE				301	///< ��ƽ̨Ӧ�ü����˺�����
#define BRAC_SO_CLOUD_APPID3RD				302	///< ��ƽ̨Ӧ�ü���ʱ������ƽ̨��Ӧ��GUID


// ����������Ϣ�������壨API��BRAC_QueryTransTaskInfo ���������
#define BRAC_TRANSTASK_PROGRESS				1	///< ����������Ȳ�ѯ������Ϊ��DWORD�ͣ�����ֵ0 ~ 100��
#define BRAC_TRANSTASK_BITRATE				2	///< ��������ǰ�������ʣ�����Ϊ��DWORD�ͣ���λ��bps��
#define BRAC_TRANSTASK_STATUS				3	///< ��������ǰ״̬������Ϊ��DWORD�ͣ�
#define BRAC_TRANSTASK_SAVEASPATH			4	///< �ļ������������Ϊ·�����ã����ļ���������Ϊ�ַ���TCHAR���ͣ�
#define BRAC_TRANSTASK_SOURCEFILE			5	///< Դ�ļ�������·��������Ϊ�ַ�����TCHAR���ͣ�

// ¼���ܱ�־���壨API��BRAC_StreamRecordCtrl ���������
#define BRAC_RECORD_FLAGS_VIDEO			0x00000001	///< ¼����Ƶ
#define BRAC_RECORD_FLAGS_AUDIO			0x00000002	///< ¼����Ƶ
#define BRAC_RECORD_FLAGS_SERVER		0x00000004	///< ��������¼��
#define BRAC_RECORD_FLAGS_MIXAUDIO		0x00000010	///< ¼����Ƶʱ���������˵�����������¼��
#define BRAC_RECORD_FLAGS_MIXVIDEO		0x00000020	///< ¼����Ƶʱ���������˵���Ƶ���Ӻ�¼��
#define BRAC_RECORD_FLAGS_ABREAST		0x00000100	///< ¼����Ƶʱ���������˵���Ƶ����¼��
#define BRAC_RECORD_FLAGS_STEREO		0x00000200	///< ¼����Ƶʱ���������˵��������Ϊ��������¼��
#define BRAC_RECORD_FLAGS_SNAPSHOT		0x00000400	///< ����
#define BRAC_RECORD_FLAGS_LOCALCB		0x00000800	///< �������ػص�
#define BRAC_RECORD_FLAGS_STREAM		0x00001000	///< ����Ƶ������¼�ƣ�Ч�ʸߣ�
#define BRAC_RECORD_FLAGS_USERFILENAME	0x00002000	///< �û��Զ����ļ���


// �ͻ��ˡ���������¼�Ʊ�־���屣��ͳһ
#if !defined(ANYCHAT_RECORD_FLAGS_VIDEO)
#define ANYCHAT_RECORD_FLAGS_VIDEO			BRAC_RECORD_FLAGS_VIDEO
#define ANYCHAT_RECORD_FLAGS_AUDIO			BRAC_RECORD_FLAGS_AUDIO
#define ANYCHAT_RECORD_FLAGS_SERVER			BRAC_RECORD_FLAGS_SERVER
#define ANYCHAT_RECORD_FLAGS_MIXAUDIO		BRAC_RECORD_FLAGS_MIXAUDIO
#define ANYCHAT_RECORD_FLAGS_MIXVIDEO		BRAC_RECORD_FLAGS_MIXVIDEO
#define ANYCHAT_RECORD_FLAGS_ABREAST		BRAC_RECORD_FLAGS_ABREAST
#define ANYCHAT_RECORD_FLAGS_STEREO			BRAC_RECORD_FLAGS_STEREO
#define ANYCHAT_RECORD_FLAGS_SNAPSHOT		BRAC_RECORD_FLAGS_SNAPSHOT
#define ANYCHAT_RECORD_FLAGS_LOCALCB		BRAC_RECORD_FLAGS_LOCALCB
#define ANYCHAT_RECORD_FLAGS_STREAM			BRAC_RECORD_FLAGS_STREAM
#define ANYCHAT_RECORD_FLAGS_USERFILENAME	BRAC_RECORD_FLAGS_USERFILENAME
#define ANYCHAT_RECORD_FLAGS_ERRORCODE		0x00004000	///< ֧�ֳ������
#endif


// �鲥���Զ���
#define BRAC_MCPOLITIC_DISABLE				0	///< ִ�з�����·�ɲ��ԣ���ֹ�����鲥����[Ĭ��]
#define BRAC_MCPOLITIC_ONLYLOCALMC			1	///< ���Է�����·�ɲ��ԣ�ֻ��ͻ��˱����鲥��㲥ý����
#define BRAC_MCPOLITIC_SERVERANDLOCALMC		2	///< ִ�з�����·�ɲ��ԣ�ͬʱ�ڿͻ��˱��ط����鲥����
#define BRAC_MCPOLITIC_ONLYSERVERMC			3	///< ���Է�����·�ɲ��ԣ�ֻ������������鲥��㲥ý����
#define BRAC_MCPOLITIC_SERVERANDSERVERMC	4	///< ִ�з�����·�ɲ��ԣ�ͬʱ�ڷ������˷����鲥����

// �鲥���ܱ�־����
#define BRAC_MCFLAGS_JOINGROUP		0x00000001	///< ����ಥ��
#define BRAC_MCFLAGS_LEAVEGROUP		0x00000002	///< �뿪�ಥ��
#define BRAC_MCFLAGS_SENDDATA		0x00000010	///< ���ݷ��ͱ�־��ָʾ�öಥ�����ڷ�������
#define BRAC_MCFLAGS_RECVDATA		0x00000020	///< ���ݽ��ձ�־��ָʾ�öಥ�����ڽ�������


// �û�״̬��־���壨API��BRAC_QueryUserState ���������
#define BRAC_USERSTATE_CAMERA				1	///< �û�����ͷ״̬������ΪDWORD�ͣ�
#define BRAC_USERSTATE_HOLDMIC				2	///< �û���Ƶ�豸״̬������ΪDWORD�ͣ�����ֵ��0 ��Ƶ�ɼ��رգ� 1 ��Ƶ�ɼ�������
#define BRAC_USERSTATE_SPEAKVOLUME			3	///< �û���ǰ˵������������ΪDWORD���ͣ�0 ~ 100����
#define BRAC_USERSTATE_RECORDING			4	///< �û�¼������״̬������ΪDWORD�ͣ�
#define	BRAC_USERSTATE_LEVEL				5	///< �û����𣨲���ΪDWORD�ͣ�
#define BRAC_USERSTATE_NICKNAME				6	///< �û��ǳƣ�����Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_LOCALIP				7	///< �û�����IP��ַ������������Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_INTERNETIP			8	///< �û�������IP��ַ������Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_VIDEOBITRATE			9	///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
#define BRAC_USERSTATE_AUDIOBITRATE			10	///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
#define BRAC_USERSTATE_P2PCONNECT			11	///< ��ѯ�����û���ָ���û��ĵ�ǰP2P����״̬������ΪDWORD���ͣ�����ֵ��0 P2P��ͨ�� 1 P2P���ӳɹ�[TCP]��2 P2P���ӳɹ�[UDP]��3 P2P���ӳɹ�[TCP��UDP]��
#define BRAC_USERSTATE_NETWORKSTATUS		12	///< ��ѯָ���û�������״̬������ΪDWORD���ͣ�����ֵ��0 ������1 �Ϻã�2 һ�㣬3 �ϲ4 �ǳ��
#define BRAC_USERSTATE_VIDEOSIZE			13	///< ��ѯָ���û�����Ƶ�ֱ��ʣ�����ΪDWORD���ͣ�����ֵ����16λ��ʾ��ȣ���16λ��ʾ�߶ȣ�
#define BRAC_USERSTATE_PACKLOSSRATE			14	///< ��ѯָ���û���������ý�����ݶ����ʣ�����ΪDWORD���ͣ�����ֵ��0 - 100���磺����ֵΪ5����ʾ������Ϊ5%��
#define BRAC_USERSTATE_DEVICETYPE			15	///< ��ѯָ���û����ն����ͣ�����ΪDWORD���ͣ�����ֵ��0 Unknow��1 Windows��2 Android��3 iOS��4 Web��5 Linux��6 Mac��7 Win Phone��8 WinCE��
#define BRAC_USERSTATE_SELFUSERSTATUS		16	///< ��ѯ�����û��ĵ�ǰ״̬������ΪDWORD���ͣ�����ֵ��0 Unknow��1 Connected��2 Logined��3 In Room��4 Logouted��5 Link Closed��
#define BRAC_USERSTATE_SELFUSERID			17	///< ��ѯ�����û���ID������ΪDWORD���ͣ����û���¼�ɹ��������û�ʵ�ʵ�userid�����򷵻�-1��
#define BRAC_USERSTATE_VIDEOROTATION		18	///< ��ѯָ���û��ĵ�ǰ��Ƶ��ת�Ƕȣ�����ΪDWORD���ͣ����ؽǶ�ֵ��
#define BRAC_USERSTATE_VIDEOMIRRORED		19	///< ��ѯָ���û�����Ƶ�Ƿ���Ҫ����ת
#define BRAC_USERSTATE_AUDIOCODECID			20	///< ��ѯָ���û�����Ƶ������ID
#define BRAC_USERSTATE_VIDEOCODECID			21	///< ��ѯָ���û�����Ƶ������ID

// ����״̬��־���壨API��BRAC_QueryRoomState ���������
#define BRAC_ROOMSTATE_ROOMNAME				1	///< �������ƣ�����Ϊ�ַ���TCHAR���ͣ�
#define BRAC_ROOMSTATE_ONLINEUSERS			2	///< ���������û���������ΪDWORD�ͣ��������Լ���

// ��Ƶ�����¼����Ͷ��壨API��BRAC_VideoCallControl ���������VideoCallEvent�ص�������
#define BRAC_VIDEOCALL_EVENT_REQUEST		1	///< ��������
#define BRAC_VIDEOCALL_EVENT_REPLY			2	///< ��������ظ�
#define BRAC_VIDEOCALL_EVENT_START			3	///< ��Ƶ���лỰ��ʼ�¼�
#define BRAC_VIDEOCALL_EVENT_FINISH			4	///< �Ҷϣ����������лỰ

// ��Ƶ���б�־���壨API��BRAC_VideoCallControl ���������
#define BRAC_VIDEOCALL_FLAGS_AUDIO		0x0001	///< ����ͨ��
#define BRAC_VIDEOCALL_FLAGS_VIDEO		0x0002	///< ��Ƶͨ��
#define BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	0x0010	///< ��ֹԴ�����жˣ���Ƶ
#define BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	0x0020	///< ��ֹԴ�����жˣ���Ƶ
#define BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	0x0040	///< ��ֹĿ�꣨�����жˣ���Ƶ
#define BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	0x0080	///< ��ֹĿ�꣨�����жˣ���Ƶ
#define BRAC_VIDEOCALL_FLAGS_ASSISTREQ	0x0100	///< ����Ŀ���û�Զ��Э��
#define BRAC_VIDEOCALL_FLAGS_CONTROLREQ	0x0200	///< �������Ŀ���û�

// Զ����Ƶ����������־����
#define BRAC_ROTATION_FLAGS_MIRRORED	0x1000	///< ͼ����Ҫ����ת
#define BRAC_ROTATION_FLAGS_ROTATION90	0x2000	///< ˳ʱ����ת90��
#define BRAC_ROTATION_FLAGS_ROTATION180	0x4000	///< ˳ʱ����ת180��
#define BRAC_ROTATION_FLAGS_ROTATION270	0x8000	///< ˳ʱ����ת270��

// �û���Ϣ�������Ͷ��壨API��BRAC_UserInfoControl ���������
#define BRAC_USERINFO_CTRLCODE_ROTATION		8	///< ��ָ�����û���Ƶ����ʾʱ��ת��wParamΪ��ת�ǶȲ���
#define BRAC_USERINFO_CTRLCODE_DEBUGLOG		9	///< ��������û��ĵ�����־��wParamΪ������־���ͣ�lParamΪ�Ƿ���
#define BRAC_USERINFO_CTRLCODE_LVORIENTFIX	10	///< ������Ƶ�ɼ�����������wParamΪ���������lParamΪ�����Ƕ�

// ���ݼӣ��⣩�ܱ�־���壨DataEncDec�ص�������
#define BRAC_DATAENCDEC_FLAGS_ENCMODE	0x01	///< ����ģʽ
#define BRAC_DATAENCDEC_FLAGS_DECMODE	0x02	///< ����ģʽ
#define BRAC_DATAENCDEC_FLAGS_AUDIO		0x10	///< ��Ƶ��������
#define BRAC_DATAENCDEC_FLAGS_VIDEO		0x20	///< ��Ƶ��������
#define BRAC_DATAENCDEC_FLAGS_BUFFER	0x40	///< ͸��ͨ������
#define BRAC_DATAENCDEC_FLAGS_TXTMSG	0x80	///< ������������

// �ص��������Ͷ��壨API��BRAC_SetCallBack ���������
#define BRAC_CBTYPE_NOTIFYMESSAGE			1	///< �첽��Ϣ֪ͨ�ص�
#define BRAC_CBTYPE_VIDEODATA				2	///< ��Ƶ���ݻص�
#define BRAC_CBTYPE_VIDEODATAEX				3	///< ��Ƶ������չ�ص�
#define BRAC_CBTYPE_AUDIODATA				4	///< ��Ƶ���ݻص�
#define BRAC_CBTYPE_AUDIODATAEX				5	///< ��Ƶ������չ�ص�
#define BRAC_CBTYPE_TEXTMESSAGE				6	///< ������Ϣ�ص�
#define BRAC_CBTYPE_TRANSBUFFER				7	///< ͸��ͨ�����ݻص�
#define BRAC_CBTYPE_TRANSBUFFEREX			8	///< ͸��ͨ��������չ�ص�
#define BRAC_CBTYPE_TRANSFILE				9	///< �ļ�����ص�
#define BRAC_CBTYPE_VOLUMECHANGE			10	///< �����仯�ص�
#define BRAC_CBTYPE_SDKFILTERDATA			11	///< SDK Filterͨ�����ݻص�
#define BRAC_CBTYPE_STREAMRECORD			12	///< ¼������������֪ͨ�ص�
#define BRAC_CBTYPE_STREAMRECORDEX			13	///< ¼������������֪ͨ��չ�ص�
#define BRAC_CBTYPE_VIDEOCALLEVENT			14	///< ��Ƶͨ����Ϣ֪ͨ�ص�
#define BRAC_CBTYPE_DATAENCDEC				15	///< ���ݼ��ܡ����ܻص�
#define BRAC_CBTYPE_SCREENEVENT				16	///< ��Ļ�¼��ص�
#define BRAC_CBTYPE_NETWORKDATASEND			17	///< �������ݻص�
#define BRAC_CBTYPE_OBJECTEVENT				18	///< ҵ������¼�֪ͨ
#define BRAC_CBTYPE_VIDEODATAEX2			19	///< ��Ƶ������չ�ص���֧�ֶ�·����
#define BRAC_CBTYPE_AUDIODATAEX2			20	///< ��Ƶ������չ�ص���֧�ֶ�·����
#define BRAC_CBTYPE_STREAMRECORDEX2			21	///< ¼������������֪ͨ��չ�ص���֧�ֳ�����룩
#define BRAC_CBTYPE_TRANSFILEEX				22	///< �ļ�������չ�ص���֧�ֳ�����룩
#define BRAC_CBTYPE_CORESDKEVENT			23	///< Core SDK�¼��ص���Json��ʽ��
#define BRAC_CBTYPE_CORESDKDATA				24	///< Core SDK���ݻص�



// ��Ƶ�ü�ģʽ����
#define ANYCHAT_VIDEOCLIPMODE_AUTO			0	///< Ĭ��ģʽ�������������вü���Ȼ�����������죬���汣�ֱ����������ü�����ϴ�
#define ANYCHAT_VIDEOCLIPMODE_OVERLAP		1	///< �ص�ģʽ��ֻȡ�����Ч���֣��Ա�Ե���вü�
#define ANYCHAT_VIDEOCLIPMODE_SHRINK		2	///< ��Сģʽ����С�����ʵı����������вü�
#define ANYCHAT_VIDEOCLIPMODE_STRETCH		3	///< ƽ��ģʽ�������вü��������ܵ��»��治�ɱ���
#define ANYCHAT_VIDEOCLIPMODE_DYNAMIC		4	///< ��̬ģʽ�����ϲ�Ӧ�ø��ݷֱ�����������ʾ���棬���ֻ��治����


// ��������Ϣ��ѯ�������壨API��BRAC_QueryInfoFromServer ���������
#define ANYCHAT_SERVERQUERY_USERIDBYNAME	1	///< �����û��ǳƲ�ѯ�û�ID
#define ANYCHAT_SERVERQUERY_USERIDBYSTRID	2	///< �����ַ���ID��ѯ�û�ID
#define ANYCHAT_SERVERQUERY_STRIDBYUSERID	3	///< �����û�ID��ѯ�ַ���ID

// ý�岥���¼����Ͷ���
#define ANYCHAT_STREAMPLAY_EVENT_START		3	///< ���ſ�ʼ�¼�
#define ANYCHAT_STREAMPLAY_EVENT_FINISH		4	///< ���Ž����¼�

// ý�岥�ű�־���壨API��BRAC_StreamPlayInit ���������
#define ANYCHAT_STREAMPLAY_FLAGS_REPLACEAUDIOINPUT	0x00000001	///< ������Ƶ�����汾����Ƶ���루Mic��
#define ANYCHAT_STREAMPLAY_FLAGS_REPLACEVIDEOINPUT	0x00000002	///< ������Ƶ�����汾����Ƶ���루Camera��
#define ANYCHAT_STREAMPLAY_FLAGS_CALLBACKDATA		0x00000010	///< �ص����ݸ��ϲ�

// ý�岥����Ϣ���Ͷ��壨API��BRAC_StreamPlayGetInfo ���������
#define ANYCHAT_STREAMPLAY_INFO_JSONVALUE	1	///< �������в�����Ϣ��Json�ַ���

// ý�岥�ſ������Ͷ��壨API��BRAC_StreamPlayControl ���������
#define ANYCHAT_STREAMPLAY_CTRL_START		1	///< ��ʼ����
#define ANYCHAT_STREAMPLAY_CTRL_PAUSE		2	///< ��ͣ����
#define ANYCHAT_STREAMPLAY_CTRL_STOP		3	///< ֹͣ����
#define ANYCHAT_STREAMPLAY_CTRL_SEEK		4	///< λ���϶�
#define ANYCHAT_STREAMPLAY_CTRL_SPEEDCTRL	5	///< �ٶȵ���
#define ANYCHAT_STREAMPLAY_CTRL_OPENLOOP	6	///< ��ѭ������
#define ANYCHAT_STREAMPLAY_CTRL_CLOSELOOP	7	///< �ر�ѭ������


// CoreSDK�¼����Ͷ��壨�ص�������BRAC_CoreSDKEvent_CallBack������
#define ANYCHAT_CORESDKEVENT_CAMERASTATE	10	///< ����ͷ״̬�¼�
#define ANYCHAT_CORESDKEVENT_MICSTATE		11	///< Mic״̬�¼�
#define ANYCHAT_CORESDKEVENT_STREAMPLAY		30	///< ý�岥���¼�

// CoreSDK�ص��������Ͷ��壨�ص�������BRAC_CoreSDKData_CallBack������
#define ANYCHAT_CORESDKDATA_AUDIO			1	///< ��Ƶ����
#define ANYCHAT_CORESDKDATA_VIDEO			2	///< ��Ƶ����
#define ANYCHAT_CORESDKDATA_MESSAGE			3	///< ��������
#define ANYCHAT_CORESDKDATA_BUFFER			4	///< ����������


#endif //_ANYCHAT_DEFINE_H__INCLUDE_
