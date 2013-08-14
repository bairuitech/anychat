package com.bairuitech.demo;

import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;

public class LiveVideoActivity extends Activity implements AnyChatBaseEvent{
	private SurfaceView videoView;
	ProgressBar volumeProgressBar;
	private ImageView mCameraSwitchImage;		// 前后摄像头切换按钮

	public AnyChatCoreSDK anychat;
	int userID = -1;
	int otherVideoIndex = -1;					// 视频显示序号（Java视频显示驱动需要）
	private ConfigEntity configEntity;
	
	private boolean bVideoOpened = false;		// 视频是否已打开
	private boolean bSuccessEnterRoom = false;	// 是否已成功进入房间
	
	private final int WORK_MODE_DOWNSTREAM = 1;	// 下载工作模式
	private final int WORK_MODE_UPSTREAM = 2;	// 上传工作模式
	private int iWorkMode;
	private boolean bOnPaused = false;
	
	private Timer  mTimer = new Timer(true); 
	private TimerTask mTimerTask;
	private Handler handler = null;

	private Button quitBtn;
	private boolean bShowQuitBtn = true;			// 是否已显示退出按钮
	private Date mLastShowQuitBtnTime = new Date();	// 开始显示退出按钮的时间

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        configEntity = ConfigService.LoadConfig(this);
        iWorkMode = getIntent().getIntExtra("mode",0);
        if(iWorkMode == WORK_MODE_UPSTREAM)		// 如果是上传模式，只打开自己的视频
        {
        	userID = -1;
        }
        
        InitialSDK();
        InitialLayout();
        
        mTimerTask = new TimerTask() 
        {
          public void run()
          {
        	  if(handler == null)
        		  return;
              Message mesasge = new Message();
              handler.sendMessage(mesasge);  
          }         
         };
         mTimer.schedule(mTimerTask, 1000,100);
         handler = new Handler()  
         {  
             @Override  
             public void handleMessage(Message msg)  
             {
            	 CheckVideoStatus();
            	 // 刷新音量条
            	 if(LiveVideoActivity.this.bSuccessEnterRoom)
            		 LiveVideoActivity.this.volumeProgressBar.setProgress(LiveVideoActivity.this.anychat.GetUserSpeakVolume(userID));
            	 // 判断是否需要隐藏退出按钮
            	 Date now = new Date();
            	 long interval = now.getTime() - LiveVideoActivity.this.mLastShowQuitBtnTime.getTime();
            	 if(LiveVideoActivity.this.bShowQuitBtn && (interval > 2000))
            	 {
            		 LiveVideoActivity.this.bShowQuitBtn = false;
            		 quitBtn.setVisibility(View.GONE);
            	 }
            	 super.handleMessage(msg);  
             }
         };
    }
    // 判断视频打开状态，如果没有打开，则找一个适合的用户
    private void CheckVideoStatus()
    {
    	if(bVideoOpened || !bSuccessEnterRoom || bOnPaused)
    		return;
    	if(iWorkMode == WORK_MODE_DOWNSTREAM)			// 打开其他人的视频
    	{
	     	int[] userarray = anychat.GetOnlineUser();
	   		for(int i=0; i<userarray.length; i++)
	   		{
	   			int uid = userarray[i];
	   			if(anychat.GetCameraState(uid) == 2 && anychat.GetUserVideoWidth(uid) != 0)
	   			{
	   				userID = uid;
	   				SurfaceHolder holder=videoView.getHolder();
	   				holder.setFormat(PixelFormat.RGB_565);
	   				holder.setFixedSize(anychat.GetUserVideoWidth(userID), anychat.GetUserVideoHeight(userID));
	   				Surface s=holder.getSurface();
	   				anychat.SetVideoPos(userID, s, 0, 0, 0, 0);
	   				anychat.UserCameraControl(userID, 1);
	   				anychat.UserSpeakControl(userID, 1);
	   				bVideoOpened = true;
	   				
	   				// 如果是采用Java视频显示，则需要将视频窗口与用户关联起来
	   				if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
	   					anychat.mVideoHelper.SetVideoUser(otherVideoIndex, userID);
	   				}
	   				break;
	   			}
	   		}   		
    	}
    	else		// 打开本地的视频，进入房间成功已经进行了打开操作，这儿只需要设置显示
    	{
    		if(anychat.GetCameraState(userID) == 2 && anychat.GetUserVideoWidth(userID) != 0)
    		{
    			SurfaceHolder holder=videoView.getHolder();
    			holder.setFormat(PixelFormat.RGB_565);
	    		holder.setFixedSize(anychat.GetUserVideoWidth(userID), anychat.GetUserVideoHeight(userID));
				Surface s=holder.getSurface();
				anychat.SetVideoPos(userID, s, 0, 0, 0, 0);  
				bVideoOpened = true;
    		}
    	}

    }
    
    private void InitialSDK()
    {
        anychat = new AnyChatCoreSDK();
        anychat.SetBaseEvent(this);
        
        // 启动AnyChat传感器监听
		anychat.mSensorHelper.InitSensor(this);
        
        int RoomID = getIntent().getIntExtra("RoomID",0);
        anychat.EnterRoom(RoomID, "");
    }
    
	private void InitialLayout()
    {
		this.setContentView(R.layout.live_video_room);
		if(iWorkMode == WORK_MODE_UPSTREAM)
			this.setTitle("本地视频上传");
		else
			this.setTitle("实时流媒体直播");
		videoView = (SurfaceView) findViewById(R.id.surface_video);
		SurfaceHolder holder=videoView.getHolder();
		holder.setKeepScreenOn(true);
		videoView.setOnClickListener(listener);
		if(iWorkMode == WORK_MODE_UPSTREAM && configEntity.videoOverlay==1)
			holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		
		if(iWorkMode == WORK_MODE_UPSTREAM) {
			// 如果是采用Java视频采集，则需要设置Surface的CallBack
			if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA)
				videoView.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
		} else {
			// 如果是采用Java视频显示，则需要设置Surface的CallBack
			if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
				otherVideoIndex = anychat.mVideoHelper.bindVideo(videoView.getHolder());
			}
		}

		mCameraSwitchImage = (ImageView) findViewById(R.id.image_switch_camera);
		mCameraSwitchImage.setOnClickListener(listener);
		quitBtn = (Button) findViewById(R.id.btn_back);
    	quitBtn.setOnClickListener(listener);
    	volumeProgressBar = (ProgressBar) findViewById(R.id.progress_volume);
    	
    	// 判断是否显示本地摄像头切换图标
    	if(iWorkMode==WORK_MODE_UPSTREAM) {
	 		if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
				if(AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1)
					mCameraSwitchImage.setVisibility(View.VISIBLE);
			}else {
				String[] strVideoCaptures = anychat.EnumVideoCapture();
				if (strVideoCaptures != null && strVideoCaptures.length > 1)
					mCameraSwitchImage.setVisibility(View.VISIBLE);
			}   		
    	}
    }
	
	OnClickListener listener = new OnClickListener()
    {       
		public void onClick(View v) 
		{
			if(v == quitBtn)
			{
				mTimer.cancel();
				if(bVideoOpened)
				{
					anychat.UserCameraControl(userID, 0);
					anychat.UserSpeakControl(userID, 0);
					bVideoOpened = false;
				}
				finish();
			}
			else if(v == videoView)
			{
				bShowQuitBtn = true;
				mLastShowQuitBtnTime = new Date();
				quitBtn.setVisibility(View.VISIBLE);
			}
			else if(v==mCameraSwitchImage)		// 前后摄像头切换事件
			{
				// 如果是采用Java视频采集，则在Java层进行摄像头切换
				if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
					AnyChatCoreSDK.mCameraHelper.SwitchCamera();
					return;
				}
				
				String strVideoCaptures[]=anychat.EnumVideoCapture();
				if(strVideoCaptures==null)
					return;
				String temp=anychat.GetCurVideoCapture();
				for(int i=0;i<strVideoCaptures.length;i++)
				{
					if(!temp.equals(strVideoCaptures[i]))
					{
						anychat.UserCameraControl(-1, 0);
						bVideoOpened=false;
						anychat.SelectVideoCapture(strVideoCaptures[i]);
						anychat.UserCameraControl(-1, 1);
						break;
					}
				}
			}
		}
    };
    
	protected void onRestart() {
    	super.onRestart();
    	anychat.UserCameraControl(userID, 1);
		anychat.UserSpeakControl(userID, 1);
		bOnPaused = false;
    }

    protected void onResume() {
    	super.onResume();

    }

    protected void onPause() {
    	super.onPause();
    	bOnPaused = true;
		if(bVideoOpened)
		{
			anychat.UserCameraControl(userID, 0);
			anychat.UserSpeakControl(userID, 0);
			bVideoOpened = false;
			
		}
    }
    
    protected void onDestroy(){
    	mTimer.cancel();
		anychat.LeaveRoom(-1);
		anychat.mSensorHelper.DestroySensor();
		super.onDestroy();
    	finish();
    }
 


	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		if(dwErrorCode == 0)
		{
			bSuccessEnterRoom = true;
			if(iWorkMode == WORK_MODE_UPSTREAM)
			{
				anychat.UserCameraControl(userID, 1);
				anychat.UserSpeakControl(userID, 1); 
			}
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 网络连接断开之后，上层需要主动关闭已经打开的音视频设备
		if(bVideoOpened)
		{
			if(iWorkMode == WORK_MODE_DOWNSTREAM)
			{
				anychat.UserCameraControl(userID, 0);
				anychat.UserSpeakControl(userID, 0);
			}
			else
			{
				anychat.UserCameraControl(-1, 0);
				anychat.UserSpeakControl(-1, 0);
			}
			bVideoOpened = false;
		}
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {

	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {

	}
}
