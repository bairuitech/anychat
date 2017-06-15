package com.bairuitech.demo;

import java.util.Timer;
import java.util.TimerTask;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;

public class VideoActivity extends Activity implements AnyChatBaseEvent, OnClickListener {
	// private LinearLayout mainLayout;

	private SurfaceView otherView;
	ProgressBar OtherProgressBar;
	ProgressBar MyProgressBar;
	private ImageView mCameraSwitchImage; // 前后摄像头切换按钮

	private SurfaceView myView;

	public AnyChatCoreSDK anychat;
	int userID;
	boolean bOnPaused = false;

	private boolean bSelfVideoOpened = false; // 本地视频是否已打开
	private boolean bOtherVideoOpened = false; // 对方视频是否已打开
	private boolean bVideoAreaLoaded = false; // 视频区域大小是否加载

	private int dwLocalVideoWidth = 0;
	private int dwLocalVideoHeight = 0;
	private int dwRemoteVideoHeight = 0;
	private int dwRemoteVideoWidth = 0;

	private Timer mTimer = new Timer(true);
	private TimerTask mTimerTask;
	private Handler handler;

	@SuppressLint("HandlerLeak")
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));
		InitialSDK();
		InitialLayout();

		mTimerTask = new TimerTask() {
			public void run() {
				if(handler == null)
					return;
				Message mesasge = new Message();
				handler.sendMessage(mesasge);
			}
		};

		mTimer.schedule(mTimerTask, 1000, 100);

		handler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				CheckVideoStatus();
				SetVolum();
				super.handleMessage(msg);
			}
		};
	}

	private void SetVolum() {
		OtherProgressBar.setProgress(anychat.GetUserSpeakVolume(userID));
		MyProgressBar.setProgress(anychat.GetUserSpeakVolume(-1));
	}

	// 判断视频是否已打开
	private void CheckVideoStatus() {
		if(bOnPaused)
			return;
		if (!bOtherVideoOpened) {
			if (anychat.GetCameraState(userID) == 2 && anychat.GetUserVideoWidth(userID) != 0) {
				SurfaceHolder holder = otherView.getHolder();
				// 如果是采用内核视频显示（非Java驱动），则需要设置Surface的参数
				if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(userID), anychat.GetUserVideoHeight(userID));
				}
				Surface s = holder.getSurface();
				anychat.SetVideoPos(userID, s, 0, 0, 0, 0);
				bOtherVideoOpened = true;
			}
		}
		if (!bSelfVideoOpened) {
			if (anychat.GetCameraState(-1) == 2 && anychat.GetUserVideoWidth(-1) != 0) {
				SurfaceHolder holder = myView.getHolder();
				// 如果是采用内核视频显示（非Java驱动），则需要设置Surface的参数
				if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(-1), anychat.GetUserVideoHeight(-1));
				}
				Surface s = holder.getSurface();
				anychat.SetVideoPos(-1, s, 0, 0, 0, 0);
				bSelfVideoOpened = true;
			}
		}

	}

	private void InitialSDK() {
		anychat = AnyChatCoreSDK.getInstance(VideoActivity.this);
		anychat.SetBaseEvent(this);
		// 启动AnyChat传感器监听
		anychat.mSensorHelper.InitSensor(getApplicationContext());
		// 初始化Camera上下文句柄
		AnyChatCoreSDK.mCameraHelper.SetContext(getApplicationContext());
	}

	private void adjuestVideoSize(int width, int height) {

		if (3 * width > 4 * height) {

			dwRemoteVideoHeight = height;
			dwRemoteVideoWidth = (int) (4.0 / 3.0 * dwRemoteVideoHeight);
		} else {
			dwRemoteVideoWidth = width;
			dwRemoteVideoHeight = (int) (3.0 / 4.0 * dwRemoteVideoWidth);
		}
		dwLocalVideoWidth = dwRemoteVideoWidth;
		dwLocalVideoHeight = dwRemoteVideoHeight;
		FrameLayout.LayoutParams layoutParamSelf=new FrameLayout.LayoutParams(dwLocalVideoWidth, dwLocalVideoHeight);
		myView.setLayoutParams(layoutParamSelf);
		LinearLayout.LayoutParams layoutPramOther=new LinearLayout.LayoutParams(dwLocalVideoWidth, dwLocalVideoHeight);
		otherView.setLayoutParams(layoutPramOther);
	}

	private void InitialLayout() {
		this.setContentView(R.layout.video_room);
		this.setTitle("与" + anychat.GetUserName(userID) + "视频通话");
		myView = (SurfaceView) findViewById(R.id.surface_local);
		otherView = (SurfaceView) findViewById(R.id.surface_remote);
		
		// 如果是采用Java视频采集，则需要设置Surface的CallBack
		if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			myView.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);			
		}
		
		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anychat.mVideoHelper.bindVideo(otherView.getHolder());
			anychat.mVideoHelper.SetVideoUser(index, userID);
		}
		
		otherView.getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() {
			
			@Override
			public void onGlobalLayout() {
				// TODO Auto-generated method stub
				if(!bVideoAreaLoaded)
				{
					adjuestVideoSize(otherView.getWidth(), otherView.getHeight());
					bVideoAreaLoaded=true;
				}
			}
		});
		mCameraSwitchImage = (ImageView) findViewById(R.id.image_switch_camera);
		mCameraSwitchImage.setOnClickListener(this);
		MyProgressBar = (ProgressBar) findViewById(R.id.progress_local);
		OtherProgressBar = (ProgressBar) findViewById(R.id.progress_remote);
		SurfaceHolder holder = otherView.getHolder();
		holder.setKeepScreenOn(true);
		anychat.UserCameraControl(userID, 1);
		anychat.UserSpeakControl(userID, 1);
		myView.setOnClickListener(this);
		ConfigEntity configEntity = ConfigService.LoadConfig(this);		
		if (configEntity.videoOverlay != 0) {
			myView.getHolder().setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		}
		// 判断是否显示本地摄像头切换图标
		if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if(AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				mCameraSwitchImage.setVisibility(View.VISIBLE);
				// 默认打开前置摄像头
				AnyChatCoreSDK.mCameraHelper.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		}else {
			String[] strVideoCaptures = anychat.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				mCameraSwitchImage.setVisibility(View.VISIBLE);
				// 默认打开前置摄像头
				for(int i=0;i<strVideoCaptures.length;i++)
				{
					String strDevices=strVideoCaptures[i];
					if(strDevices.indexOf("Front")>=0) {
						anychat.SelectVideoCapture(strDevices);
						break;
					}
				}
			}
		}
		// 打开本地音频、视频设备	
		anychat.UserCameraControl(-1, 1);
		anychat.UserSpeakControl(-1, 1);		
	}

	OnClickListener listener = new OnClickListener() {
		public void onClick(View v) {

		}
	};

	private void refreshAV() {
		anychat.UserCameraControl(userID, 1);
		anychat.UserSpeakControl(userID, 1);
		anychat.UserCameraControl(-1, 1);
		anychat.UserSpeakControl(-1, 1);
		bOtherVideoOpened = false;
		bSelfVideoOpened = false;
	}

	protected void onRestart() {
		super.onRestart();
		
		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anychat.mVideoHelper.bindVideo(otherView.getHolder());
			anychat.mVideoHelper.SetVideoUser(index, userID);
		}
		
		refreshAV();
		bOnPaused = false;
	}

	protected void onResume() {
		super.onResume();
	}

	protected void onPause() {
		super.onPause();
		bOnPaused = true;
		anychat.UserCameraControl(userID, 0);
		anychat.UserSpeakControl(userID, 0);
		anychat.UserCameraControl(-1, 0);
		anychat.UserSpeakControl(-1, 0);
	}

	protected void onDestroy() {
		super.onDestroy();
		mTimer.cancel();
		anychat.removeEvent(this);
		anychat.mSensorHelper.DestroySensor();
		finish();
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
		Log.e("********VideoActivity*********", "OnAnyChatEnterRoomMessage");

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 网络连接断开之后，上层需要主动关闭已经打开的音视频设备
		if(bOtherVideoOpened)
		{
			anychat.UserCameraControl(userID, 0);
			anychat.UserSpeakControl(userID, 0);
			bOtherVideoOpened = false;
		}
		if(bSelfVideoOpened)
		{
			anychat.UserCameraControl(-1, 0);
			anychat.UserSpeakControl(-1, 0);
			bSelfVideoOpened = false;
		}
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub
		Log.e("********VideoActivity*********", "OnAnyChatOnlineUserMessage   "
				+ dwUserNum);
		refreshAV();
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub
		Log.e("********VideoActivity*********", "OnAnyChatUserAtRoomMessage"
				+ dwUserId);
		if (dwUserId == userID) {
			if (!bEnter) {
				anychat.UserCameraControl(dwUserId, 0);
				anychat.UserSpeakControl(dwUserId, 0);
				bOtherVideoOpened = false;
			} else {
				anychat.UserCameraControl(dwUserId, 1);
				anychat.UserSpeakControl(dwUserId, 1);
			}
		}

	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if (v == mCameraSwitchImage) {
			
			// 如果是采用Java视频采集，则在Java层进行摄像头切换
			if(AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
				AnyChatCoreSDK.mCameraHelper.SwitchCamera();
				return;
			}

			String strVideoCaptures[] = anychat.EnumVideoCapture();
			;
			String temp = anychat.GetCurVideoCapture();
			for (int i = 0; i < strVideoCaptures.length; i++) {
				if (!temp.equals(strVideoCaptures[i])) {
					anychat.UserCameraControl(-1, 0);
					bSelfVideoOpened = false;
					anychat.SelectVideoCapture(strVideoCaptures[i]);
					anychat.UserCameraControl(-1, 1);
					break;
				}
			}

		}
	}
}
