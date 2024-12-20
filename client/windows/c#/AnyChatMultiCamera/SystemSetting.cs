using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace ANYCHATAPI
{

    public delegate void TextReceivedHandler(int fromUID, int toUID, string Text, bool isserect);
    public delegate void TransBufferReceivedHandler(int userId, IntPtr buf, int len, int userValue);
    public delegate void TransFileReceivedHandler(int userId, string fileName,string filePath, int fileLength, int wParam, int lParam,int taskId, int userValue);
    public delegate void SetRecordReceivedHandler(int userId, string filePath, int param, bool recordType, int userValue);
    public delegate void SetVolumeChange_CallBack(AnyChatCoreSDK.AudioDevice device, int currentVolume, int userValue);


    public class SystemSetting
    {
        /// <summary>
        /// 初始化AnyChat sdk
        /// 注册 callback
        /// </summary>
        public static bool Init(IntPtr hWnd)
        {
            bool isok = false;
            AnyChatCoreSDK.ActiveCallLog(true);
            ulong dwFuncMode = AnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP//BRAC_FUNC_VIDEO_CBDATA
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_AUTOPLAY
                | AnyChatCoreSDK.BRAC_FUNC_CHKDEPENDMODULE
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_VOLUMECALC
                | AnyChatCoreSDK.BRAC_FUNC_NET_SUPPORTUPNP
                | AnyChatCoreSDK.BRAC_FUNC_FIREWALL_OPEN
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_AUTOVOLUME
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_VOLUMECALC
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_CBDATA
                | AnyChatCoreSDK.BRAC_FUNC_CONFIG_LOCALINI;

            ///初始化
            if (AnyChatCoreSDK.InitSDK(hWnd, dwFuncMode) == 0) isok = true;

            int useHWCodec = 1;
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CORESDK_USEHWCODEC, ref useHWCodec, sizeof(int));

            int overLayTimeStamp = 1;
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP, ref overLayTimeStamp, sizeof(int));

            string recordDir = "D:\\KingDom\\VideoCapture\\Bin";
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_RECORD_TMPDIR, recordDir, recordDir.ToCharArray().Length);

            ///注册回调
            ///视频
            AnyChatCoreSDK.SetVideoDataCallBack(AnyChatCoreSDK.PixelFormat.BRAC_PIX_FMT_RGB24, video_Callback, hWnd.ToInt32());
            ///视频扩展
            AnyChatCoreSDK.SetVideoDataExCallBack(AnyChatCoreSDK.PixelFormat.BRAC_PIX_FMT_RGB24, videoEx_Callback, hWnd.ToInt32());
            //声音
            AnyChatCoreSDK.SetAudioDataCallBack(audio_Callback, hWnd.ToInt32());
            //声音扩展
            AnyChatCoreSDK.SetAudioDataExCallBack(audioEx_Callback, hWnd.ToInt32());
            //文字
            AnyChatCoreSDK.SetTextMessageCallBack(text_Callback, hWnd.ToInt32());
            //透明通道
            AnyChatCoreSDK.SetTransBufferCallBack(transBuff_Callback, hWnd.ToInt32());
            //p2p文件传输
            AnyChatCoreSDK.SetTransFileCallBack(transFile_callback, hWnd.ToInt32());
            ///与服务器端数据回调
            //AnyChatCoreSDK.SetSDKFilterDataCallBack(filterData_callback, hWnd.ToInt32());
            ///提供服务器端验证
            AnyChatCoreSDK.SetServerAuthPass("");
            //保存视频
            //AnyChatCoreSDK.SetRecordCallBack(RecordCallBack_Callback, hWnd.ToInt32());
            //设置音量变化回调函数
            AnyChatCoreSDK.SetVolumeChangeCallBack(VolumeChange_callBack, hWnd.ToInt32());
            //设置视频呼叫事件回调函数
            AnyChatCoreSDK.SetVideoCallEventCallBack(VideoCallEvent_callBack, hWnd.ToInt32());

            //设置业务对象事件通知回调函数
            AnyChatCoreSDK.SetCallBack(AnyChatCoreSDK.BRAC_CBTYPE_OBJECTEVENT, Marshal.GetFunctionPointerForDelegate(ObjectEvent_callBack), hWnd);

            AnyChatCoreSDK.SetCallBack(AnyChatCoreSDK.BRAC_CBTYPE_STREAMRECORD, Marshal.GetFunctionPointerForDelegate(RecordSnapShot_callBack), hWnd);

            AnyChatCoreSDK.SetCallBack(AnyChatCoreSDK.BRAC_CBTYPE_STREAMRECORDEX, Marshal.GetFunctionPointerForDelegate(RecordSnapShotEx_callBack), hWnd);

            AnyChatCoreSDK.SetCallBack(AnyChatCoreSDK.BRAC_CBTYPE_SCREENEVENT, Marshal.GetFunctionPointerForDelegate(VideoScreenEvent_callBack), hWnd);

            //Core SDK事件回调（Json格式）
            AnyChatCoreSDK.SetCallBack(AnyChatCoreSDK.BRAC_CBTYPE_CORESDKEVENT, Marshal.GetFunctionPointerForDelegate(CoreSDKEvent_callBack), hWnd);

            return isok;
        }


        //退出释放资源
        public static void Release(int myroomID)
        {
            AnyChatCoreSDK.LeaveRoom(myroomID);
            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
        }

        static AnyChatCoreSDK.TransBufferCallBack transBuff_Callback =
            new AnyChatCoreSDK.TransBufferCallBack(TransBuffer_CallBack);

        static AnyChatCoreSDK.VideoData_CallBack video_Callback = new AnyChatCoreSDK.VideoData_CallBack(VideoData_CallBack);

        static AnyChatCoreSDK.VideoDataEx_CallBack videoEx_Callback = new AnyChatCoreSDK.VideoDataEx_CallBack(VideoDataEx_CallBack);

        static AnyChatCoreSDK.AudioData_CallBack audio_Callback = new AnyChatCoreSDK.AudioData_CallBack(AudioData_CallBack);

        static AnyChatCoreSDK.AudioDataEx_CallBack audioEx_Callback = new AnyChatCoreSDK.AudioDataEx_CallBack(AudioDataEx_CallBack);

        static AnyChatCoreSDK.TextMessage_CallBack text_Callback = new AnyChatCoreSDK.TextMessage_CallBack(TextMessage_CallBack);

        //static AnyChatCoreSDK.RecordCallBack RecordCallBack_Callback = new AnyChatCoreSDK.RecordCallBack(SetRecordCallBack_CallBack);

        static AnyChatCoreSDK.TransFileCallBack transFile_callback = new AnyChatCoreSDK.TransFileCallBack(TransFile_CallBack);

        static AnyChatCoreSDK.VolumeChangeCallBack VolumeChange_callBack = new AnyChatCoreSDK.VolumeChangeCallBack(SetVolumeChange_CallBack);

        static AnyChatCoreSDK.VideoCallEvent_CallBack VideoCallEvent_callBack = new AnyChatCoreSDK.VideoCallEvent_CallBack(VideoCallEvent_CallBack);

        static AnyChatCoreSDK.OnObjectEventNotifyCallBack ObjectEvent_callBack = new AnyChatCoreSDK.OnObjectEventNotifyCallBack(ObjectEvent_CallBack);

        static AnyChatCoreSDK.RecordSnapShot_CallBack RecordSnapShot_callBack = new AnyChatCoreSDK.RecordSnapShot_CallBack(RecordSnapShot_CallBack);

        static AnyChatCoreSDK.RecordSnapShotEx_CallBack RecordSnapShotEx_callBack = new AnyChatCoreSDK.RecordSnapShotEx_CallBack(RecordSnapShotEx_CallBack);

        static AnyChatCoreSDK.VideoScreenEvent_CallBack VideoScreenEvent_callBack = new AnyChatCoreSDK.VideoScreenEvent_CallBack(VideoScreenEvent_CallBack);

        static AnyChatCoreSDK.OnCoreSDKEventCallBack CoreSDKEvent_callBack = new AnyChatCoreSDK.OnCoreSDKEventCallBack(CoreSDKEvent_CallBack);

        public static SetRecordReceivedHandler SetRecordReceivedCallBack = null;
        /// <summary>
        /// 音视频录制回调函数
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="filePath"></param>
        /// <param name="param"></param>
        /// <param name="recordType"></param>
        /// <param name="userValue"></param>
        private static void SetRecordCallBack_CallBack(int userId, string filePath, int param, bool recordType, int userValue)
        {
            if (SetRecordReceivedCallBack != null)
                SetRecordReceivedCallBack(userId, filePath, param, recordType, userValue);
        }

        /// <summary>
        /// 服务器端消息回调
        /// </summary>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="userValue"></param>
        private static void SDKFilter_DataCallBack(byte[] buf, int len, int userValue)
        {


        }

        public static TransFileReceivedHandler TransFile_Received = null;
        /// <summary>
        /// 文件回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="fileName"></param>
        /// <param name="filePath"></param>
        /// <param name="fileLength"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <param name="taskId"></param>
        /// <param name="userValue"></param>
        private static void TransFile_CallBack(int userId, string fileName,
            string filePath, int fileLength, int wParam, int lParam,
            int taskId, int userValue)
        {
            if (TransFile_Received != null)
                TransFile_Received(userId, fileName,filePath, fileLength,wParam, lParam,taskId, userValue);
        }

        public static TransBufferReceivedHandler TransBuffer_OnReceive = null;
        /// <summary>
        /// 透明通道回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="userValue"></param>
        private static void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
            if (TransBuffer_OnReceive != null)
                TransBuffer_OnReceive(userId, buf, len, userValue);
        }

        public static SetVolumeChange_CallBack SetVolumeChange_OnReceive = null;
        /// <summary>
        /// 设置音量变化回调函数定义
        /// </summary>
        /// <param name="device">音频设备</param>
        /// <param name="currentVolume">当前音量</param>
        /// <param name="userValue">附带信息</param>
        private static void SetVolumeChange_CallBack(AnyChatCoreSDK.AudioDevice device, int currentVolume, int userValue)
        {
            if (SetVolumeChange_OnReceive != null)
                SetVolumeChange_OnReceive(device, currentVolume, userValue);
        }

        public static TextReceivedHandler Text_OnReceive = null;
        /// <summary>
        /// 消息回调
        /// </summary>
        /// <param name="fromuserId"></param>
        /// <param name="touserId"></param>
        /// <param name="isserect"></param>
        /// <param name="message"></param>
        /// <param name="len"></param>
        /// <param name="userValue"></param>
        private static void TextMessage_CallBack(int fromuserId, int touserId, bool isserect, string message, int len, int userValue)
        {
            if (Text_OnReceive != null)
                Text_OnReceive(fromuserId, touserId, message, isserect);
        }

        public delegate void AudioDataCallback(int userId, IntPtr buf, int len, AnyChatCoreSDK.WaveFormat format, int userValue);
        public static AudioDataCallback Audio_OnCallBack = null;
        /// <summary>
        /// 音频回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="format"></param>
        /// <param name="userValue"></param>
        private static void AudioData_CallBack(int userId, IntPtr buf, int len, AnyChatCoreSDK.WaveFormat format, int userValue)
        {
            if (Audio_OnCallBack != null)
                Audio_OnCallBack(userId, buf, len, format, userValue);

        }

        public delegate void AudioDataExCallback(int userId, IntPtr buf, int len, AnyChatCoreSDK.WaveFormat format, int timestamp, int userValue);
        public static AudioDataExCallback AudioEx_OnCallBack = null;
        /// <summary>
        /// 音频回调(扩展)
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="format"></param>
        /// <param name="userValue"></param>
        private static void AudioDataEx_CallBack(int userId, IntPtr buf, int len, AnyChatCoreSDK.WaveFormat format, int timestamp, int userValue)
        {
            if (AudioEx_OnCallBack != null)
                AudioEx_OnCallBack(userId, buf, len, format, timestamp, userValue);

        }
        
        public delegate void VideoDataCallback(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int userValue);
        public static VideoDataCallback Video_OnCallBack = null;
        /// <summary>
        /// 视频回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="bitMap"></param>
        /// <param name="userValue"></param>
        private static void VideoData_CallBack(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int userValue)
        {
            if (Video_OnCallBack != null)
                Video_OnCallBack(userId, buf, len, bitMap, userValue);
        }

        public delegate void VideoDataExCallback(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int timeStamp, int userValue);
        public static VideoDataExCallback VideoEx_OnCallBack = null;
        /// <summary>
        /// 视频回调(扩展)
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="bitMap"></param>
        /// <param name="userValue"></param>
        private static void VideoDataEx_CallBack(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int timeStamp, int userValue)
        {
            if (VideoEx_OnCallBack != null)
                VideoEx_OnCallBack(userId, buf, len, bitMap, timeStamp, userValue);
        }
        
        public delegate void VideoCallEventCallBack(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr);
        public static VideoCallEventCallBack VideoCallEvent_Handler;
        private static void VideoCallEvent_CallBack(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr, int lpUserValue)
        {
            if(VideoCallEvent_Handler!=null)
            {
                VideoCallEvent_Handler( dwEventType,  dwUserId,  dwErrorCode,  dwFlags,  dwParam,  lpUserStr);
            }
        }
        
        /// <summary>
        /// 业务对象事件通知回调
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwEventType"></param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        /// <param name="lpUserValue"></param>
        public delegate void AnyChatObjectEventCallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue);
        public static AnyChatObjectEventCallBack AnyChatObjectEvent_Handler;
        private static void ObjectEvent_CallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            if (AnyChatObjectEvent_Handler != null)
            {
                AnyChatObjectEvent_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam, lpUserValue);
            }
        }

        /// <summary>
        /// AnyChatCoreSDK异步事件回调
        /// </summary>
        /// <param name="dwEventType"></param>
        /// <param name="lpEventJsonStr"></param>
        /// <param name="lpUserValue"></param>
        public delegate void AnyChatCoreSDKEventCallBack(int dwEventType, string lpEventJsonStr, int lpUserValue);
        public static AnyChatCoreSDKEventCallBack AnyChatCoreSDKEvent_Handler;
        private static void CoreSDKEvent_CallBack(int dwEventType, string lpEventJsonStr, int lpUserValue)
        {
            if (AnyChatCoreSDKEvent_Handler != null)
            {
                AnyChatCoreSDKEvent_Handler(dwEventType, lpEventJsonStr, lpUserValue);
            }
        }

        /// <summary>
        /// 录像、快照任务完成回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="fileName"></param>
        /// <param name="param"></param>
        /// <param name="recordType"></param>
        /// <param name="userValue"></param>
        public delegate void AnyChatRecordSnapShotCallBack(int userId, string fileName, int param, int recordType, int userValue);
        public static AnyChatRecordSnapShotCallBack AnyChatRecordSnapShot_Handler;
        private static void RecordSnapShot_CallBack(int userId, string fileName, int param, int recordType, int userValue)
        {
            if (AnyChatRecordSnapShot_Handler != null)
            {
                AnyChatRecordSnapShot_Handler(userId, fileName, param, recordType, userValue);
            }
        }

        /// <summary>
        /// 录像、快照任务完成回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="fileName"></param>
        /// <param name="elapse"></param>
        /// <param name="flags"></param>
        /// <param name="param"></param>
        /// <param name="userStr"></param>
        /// <param name="userValue"></param>
        public delegate void AnyChatRecordSnapShotExCallBack(int userId, string fileName, int elapse, int flags, int param, string userStr, int userValue);
        public static AnyChatRecordSnapShotExCallBack AnyChatRecordSnapShotEx_Handler;
        private static void RecordSnapShotEx_CallBack(int userId, string fileName, int elapse, int flags, int param, string userStr, int userValue)
        {
            if (AnyChatRecordSnapShotEx_Handler != null)
            {
                AnyChatRecordSnapShotEx_Handler(userId, fileName, elapse, flags, param, userStr, userValue);
            }
        }

        /// <summary>
        /// 录像、快照任务完成回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="errorCode"></param>
        /// <param name="fileName"></param>
        /// <param name="elapse"></param>
        /// <param name="flags"></param>
        /// <param name="param"></param>
        /// <param name="userStr"></param>
        /// <param name="userValue"></param>
        public delegate void AnyChatRecordSnapShotEx2CallBack(int userId, int errorCode, string fileName, int elapse, int flags, int param, string userStr, int userValue);
        public static AnyChatRecordSnapShotEx2CallBack AnyChatRecordSnapShotEx2_Handler;
        private static void RecordSnapShotEx2_CallBack(int userId, int errorCode, string fileName, int elapse, int flags, int param, string userStr, int userValue)
        {
            if (AnyChatRecordSnapShotEx2_Handler != null)
            {
                AnyChatRecordSnapShotEx2_Handler(userId, errorCode, fileName, elapse, flags, param, userStr, userValue);
            }
        }

        /// <summary>
        /// 视频屏幕事件回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="type"></param>
        /// <param name="key"></param>
        /// <param name="flags"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <param name="userValue"></param>
        public delegate void AnyChatVideoScreenEventCallBack(int userId, int type, int key, int flags, int wParam, int lParam, int userValue);
        public static AnyChatVideoScreenEventCallBack AnyChatVideoScreenEvent_Handler;
        private static void VideoScreenEvent_CallBack(int userId, int type, int key, int flags, int wParam, int lParam, int userValue)
        {
            if (AnyChatVideoScreenEvent_Handler != null)
            {
                AnyChatVideoScreenEvent_Handler(userId, type, key, flags, wParam, lParam, userValue);
            }
        }




    }
}
