using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using ANYCHATAPI;

namespace AnyChatCSharpDemo
{
    public delegate void TextReceivedHandler(int fromUID, int toUID, string Text, bool isserect);
    public delegate void TransBufferReceivedHandler(int userId, IntPtr buf, int len, int userValue);
    public delegate void TransFileReceivedHandler(int userId, string fileName,string filePath, int fileLength, int wParam, int lParam,int taskId, int userValue);
    

    public class SystemSetting
    {
        /// <summary>
        /// 初始化AnyChat sdk
        /// 注册 callback
        /// </summary>
        public static void Init(IntPtr hWnd)
        {
            AnyChatCoreSDK.ActiveCallLog(true);
            ulong dwFuncMode = AnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP
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
            AnyChatCoreSDK.InitSDK(hWnd, dwFuncMode);

            ///注册回调
            ///视频
            AnyChatCoreSDK.SetVideoDataCallBack(AnyChatCoreSDK.PixelFormat.BRAC_PIX_FMT_RGB24,
                video_Callback, hWnd.ToInt32());
            //声音
            AnyChatCoreSDK.SetAudioDataCallBack(audio_Callback, hWnd.ToInt32());
            //文字
            AnyChatCoreSDK.SetTextMessageCallBack(text_Callback, hWnd.ToInt32());
            //透明通道
            AnyChatCoreSDK.SetTransBufferCallBack(transBuff_Callback, hWnd.ToInt32());
            //p2p文件传输
            AnyChatCoreSDK.SetTransFileCallBack(transFile_callback, hWnd.ToInt32());
            ///与服务器端数据回调
            AnyChatCoreSDK.SetSDKFilterDataCallBack(filterData_callback, hWnd.ToInt32());
            ///提供服务器端验证
            AnyChatCoreSDK.SetServerAuthPass(new StringBuilder(""));

        }


        //退出释放资源
        public static void Release(int myroomID)
        {
            AnyChatCoreSDK.LeaveRoom(myroomID);
            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
        }

        static AnyChatCoreSDK.SDKFilterDataCallBack filterData_callback =
            new AnyChatCoreSDK.SDKFilterDataCallBack(SDKFilter_DataCallBack);

        static AnyChatCoreSDK.TransBufferCallBack transBuff_Callback =
            new AnyChatCoreSDK.TransBufferCallBack(TransBuffer_CallBack);

        static AnyChatCoreSDK.VideoData_CallBack video_Callback = new
            AnyChatCoreSDK.VideoData_CallBack(VideoData_CallBack);

        static AnyChatCoreSDK.AudioData_CallBack audio_Callback = new
            AnyChatCoreSDK.AudioData_CallBack(AudioData_CallBack);

        static AnyChatCoreSDK.TextMessage_CallBack text_Callback = new
            AnyChatCoreSDK.TextMessage_CallBack(TextMessage_CallBack);

        static AnyChatCoreSDK.TransFileCallBack transFile_callback = new
            AnyChatCoreSDK.TransFileCallBack(TransFile_CallBack);

        /// <summary>
        /// 服务器端消息回调
        /// </summary>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="userValue"></param>
        private static void SDKFilter_DataCallBack(IntPtr buf, int len, int userValue)
        {


        }

        public static TransFileReceivedHandler TransFile_OnReceive = null;
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
            if (TransFile_OnReceive != null)
                TransFile_OnReceive(userId, fileName,filePath, fileLength,wParam, lParam,taskId, userValue);
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
        private static void TextMessage_CallBack(int fromuserId, int touserId, bool isserect,
            string message, int len, int userValue)
        {
            if (Text_OnReceive != null)
                Text_OnReceive(fromuserId, touserId, message, isserect);
        }

        /// <summary>
        /// 音频回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="format"></param>
        /// <param name="userValue"></param>
        private static void AudioData_CallBack(int userId, IntPtr buf, int len,
            AnyChatCoreSDK.WaveFormat format, int userValue)
        {

        }

        /// <summary>
        /// 视频回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="bitMap"></param>
        /// <param name="userValue"></param>
        private static void VideoData_CallBack(int userId, IntPtr buf, int len,
            AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int userValue)
        {

        }
    }
}
