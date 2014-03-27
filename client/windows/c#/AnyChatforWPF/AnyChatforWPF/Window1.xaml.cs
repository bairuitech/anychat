using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ANYCHATAPI;
using System.IO;
using System.Threading;
using System.Windows.Interop;

namespace AnyChatforWPF
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class Window1 : Window
    {
        // 回调句柄定义
        static AnyChatCoreSDK.NotifyMessage_CallBack OnNotifyMessageCallback = new
            AnyChatCoreSDK.NotifyMessage_CallBack(NotifyMessage_CallBack);

        static AnyChatCoreSDK.VideoData_CallBack OnVideoDataCallback = new
            AnyChatCoreSDK.VideoData_CallBack(VideoData_CallBack);

        // 委托句柄定义
        public static AnyChatCoreSDK.NotifyMessage_CallBack NotifyMessageHandler = null;
        public static AnyChatCoreSDK.VideoData_CallBack VideoDataHandler = null;

        public static int g_selfUserId = -1;
        public static int g_otherUserId = -1;

        public Window1()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, RoutedEventArgs e)
        {
            // 设置回调函数
            AnyChatCoreSDK.SetNotifyMessageCallBack(OnNotifyMessageCallback, 0);
            AnyChatCoreSDK.SetVideoDataCallBack(AnyChatCoreSDK.PixelFormat.BRAC_PIX_FMT_RGB24, OnVideoDataCallback, 0);

            ulong dwFuncMode = /*AnyChatCoreSDK.BRAC_FUNC_VIDEO_CBDATA | */AnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP | AnyChatCoreSDK.BRAC_FUNC_AUDIO_AUTOPLAY | AnyChatCoreSDK.BRAC_FUNC_CHKDEPENDMODULE
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_VOLUMECALC | AnyChatCoreSDK.BRAC_FUNC_NET_SUPPORTUPNP | AnyChatCoreSDK.BRAC_FUNC_FIREWALL_OPEN
                | AnyChatCoreSDK.BRAC_FUNC_AUDIO_AUTOVOLUME | AnyChatCoreSDK.BRAC_FUNC_CONFIG_LOCALINI;

            // 初始化SDK
            AnyChatCoreSDK.InitSDK(IntPtr.Zero, dwFuncMode);
            AnyChatCoreSDK.Connect("demo.anychat.cn", 8906);
            AnyChatCoreSDK.Login("WPF", "", 0);
            AnyChatCoreSDK.EnterRoom(1, "", 0);


            NotifyMessageHandler = new AnyChatCoreSDK.NotifyMessage_CallBack(NotifyMessageCallbackDelegate);
            VideoDataHandler = new AnyChatCoreSDK.VideoData_CallBack(VideoDataCallbackDelegate);
        }
        // 关闭窗口时释放资源
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            AnyChatCoreSDK.LeaveRoom(-1);
            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
        }


        // AnyChat 内核回调，不能操作界面
        public static void NotifyMessage_CallBack(int dwNotifyMsg, int wParam, int lParam, int userValue)
        {
            if (NotifyMessageHandler != null)
                NotifyMessageHandler(dwNotifyMsg, wParam, lParam, userValue);
        }

        // 委托，可以操作界面
        public void NotifyMessageCallbackDelegate(int dwNotifyMsg, int wParam, int lParam, int userValue)
        {

            switch(dwNotifyMsg)
            {
                case AnyChatCoreSDK.WM_GV_CONNECT:
                    if(wParam != 0)
                        msglabel.Content = "连接服务器成功";
                    else
                        msglabel.Content = "连接服务器失败";
                    break;
                case AnyChatCoreSDK.WM_GV_LOGINSYSTEM:
                    if (lParam == 0)
                    {
                        g_selfUserId = wParam;
                        msglabel.Content = "登录成功";
                    }
                    else
                    {
                        msglabel.Content = "登录失败, ErrorCode:" + lParam;
                    }
                    break;
                case AnyChatCoreSDK.WM_GV_ENTERROOM:
                    if (lParam == 0)
                    {
                        msglabel.Content = "进入房间成功";
                        //获取控件的句柄
                        IntPtr mHandle = ((HwndSource)PresentationSource.FromVisual(this.localVideoImage)).Handle;
                        //获取控件的位置
                        Window window = Window.GetWindow(this.localVideoImage);
                        Point point = this.localVideoImage.TransformToAncestor(window).Transform(new Point(0, 0));
                        //显示视频
                        AnyChatCoreSDK.SetVideoPos(-1, mHandle, (int)point.X, (int)point.Y, (int)(this.localVideoImage.Width + point.X), (int)(this.localVideoImage.Height + point.Y));
                        AnyChatCoreSDK.UserSpeakControl(-1, true);
                        AnyChatCoreSDK.UserCameraControl(-1, true);
                    }
                    else
                        msglabel.Content = "进入房间失败, ErrorCode:" + lParam; 
                    break;
                case AnyChatCoreSDK.WM_GV_ONLINEUSER:
                    OpenRemoteUserVideo();
                    break;
                case AnyChatCoreSDK.WM_GV_USERATROOM:
                    if(lParam != 0)     // 其它用户进入房间
                    {
                        OpenRemoteUserVideo();
                    }
                    else                // 其它用户离开房间
                    {
                        if(wParam == g_otherUserId)
                        {
                            g_otherUserId = -1;
                            OpenRemoteUserVideo();
                        }
                    }
                    break;
                case AnyChatCoreSDK.WM_GV_LINKCLOSE:
                    msglabel.Content = "网络连接关闭, ErrorCode:" + lParam; 
                    break;
                default:
                    break;
            }
        }

        // AnyChat内核回调
        public static void VideoData_CallBack(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int userValue)
        {
            if (VideoDataHandler != null)
                VideoDataHandler(userId, buf, len, bitMap, userValue);
        }

        // 静态委托
        public void VideoDataCallbackDelegate(int userId, IntPtr buf, int len, AnyChatCoreSDK.BITMAPINFOHEADER bitMap, int userValue)
        {
            // 由于采用自动显示（在AnyChatCoreSDK.InitSDK时设置了AnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP），所以屏蔽通过回调的方式显示视频，效率更高
            // 如果希望对视频进行处理，则可以设置AnyChatCoreSDK.BRAC_FUNC_VIDEO_CBDATA，去掉AnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP，然后开放下面的代码即可
            // 有关AnyChat自动显示和回调显示的区别可参考：http://www.anychat.cn/faq/index.php?action=artikel&cat=2&id=196&artlang=zh
/*
            int stride = bitMap.biWidth * 3;
            BitmapSource bs = BitmapSource.Create(bitMap.biWidth, bitMap.biHeight, 96, 96, PixelFormats.Bgr24, null, buf, len, stride);
            // 将图像进行翻转
            TransformedBitmap RotateBitmap = new TransformedBitmap();
            RotateBitmap.BeginInit();
            RotateBitmap.Source = bs;                    
            ScaleTransform scaleTransform = new ScaleTransform();
            scaleTransform.ScaleY = -1;
            RotateBitmap.Transform = scaleTransform;
            RotateBitmap.EndInit();
            RotateBitmap.Freeze();

            //// 异步操作
            Action action = new Action(delegate()
            {
               Dispatcher.BeginInvoke(new Action(delegate()
               {
                   if (userId == g_selfUserId)
                       localVideoImage.Source = RotateBitmap;
                   else if (userId == g_otherUserId)
                       remoteVideoImage.Source = RotateBitmap;
               }), null);
            });
            action.BeginInvoke(null, null);
*/
        }

        // 打开远程用户的音频、视频
        public void OpenRemoteUserVideo()
        {
            if(g_otherUserId != -1)
                return;
            // 获取当前房间用户列表
            int usercount = 0;
            AnyChatCoreSDK.GetOnlineUser(null, ref usercount);
            if(usercount > 0)
            {
                int[] useridarray = new int[usercount];
                AnyChatCoreSDK.GetOnlineUser(useridarray, ref usercount);
                for(int i=0; i<usercount; i++)
                {
                    // 判断该用户的视频是否已打开
                    int usercamerastatus = 0;
                    if(AnyChatCoreSDK.QueryUserState(useridarray[i], AnyChatCoreSDK.BRAC_USERSTATE_CAMERA, ref usercamerastatus, sizeof(int)) != 0)
                        continue;
                    if(usercamerastatus == 2)
                    {
                        g_otherUserId = useridarray[i];
                        //获取控件的句柄
                        IntPtr mHandle = ((HwndSource)PresentationSource.FromVisual(this.remoteVideoImage)).Handle;
                        //获取控件的位置
                        Window window = Window.GetWindow(this.remoteVideoImage);
                        Point point = this.remoteVideoImage.TransformToAncestor(window).Transform(new Point(0, 0));
                        //显示视频
                        AnyChatCoreSDK.SetVideoPos(g_otherUserId, mHandle, (int)point.X, (int)point.Y, (int)(this.remoteVideoImage.Width + point.X), (int)(this.remoteVideoImage.Height + point.Y));
                        AnyChatCoreSDK.UserSpeakControl(g_otherUserId, true);
                        AnyChatCoreSDK.UserCameraControl(g_otherUserId, true);
                        break;
                    }
                }
            }
        }

       


    }
}
