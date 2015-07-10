package com.bairuitech.callservice;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.view.Window;
import android.widget.Button;
import android.widget.FrameLayout;

import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.anychat.AnyChatUserInfoEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.bussinesscenter.BussinessCenter;
import com.example.anychatqueue.MainActivity;
import com.example.anychatqueue.R;
import com.example.common.BaseConst;
import com.example.common.BaseMethod;
import com.example.common.DialogFactory;
import com.example.common.ConfigEntity;
import com.example.common.ConfigService;



public class VideoActivity extends Activity implements AnyChatBaseEvent,
		OnClickListener, OnTouchListener,AnyChatObjectEvent, AnyChatVideoCallEvent, AnyChatUserInfoEvent {
	private SurfaceView mSurfaceSelf;
	private SurfaceView mSurfaceRemote;
	private ProgressBar mProgressSelf;
	private ProgressBar mProgressRemote;
	
	private TextView mTxtTime;
	private Button mBtnEndSession;
	private Dialog dialog;
	private ImageButton mImgBtnReturn;	// 标题返回
	private TextView mTitleName;		// 标题名字

	private AnyChatCoreSDK anychat;
	private Handler mHandler;
	private Timer mTimerCheckAv;
	private Timer mTimerShowVideoTime;
	private TimerTask mTimerTask;
	private ConfigEntity configEntity;

	boolean bSelfVideoOpened = false;
	boolean bOtherVideoOpened = false;
	boolean bVideoViewLoaded = false;
	public static final int MSG_CHECKAV = 1;
	public static final int MSG_TIMEUPDATE = 2;
	public static final int PROGRESSBAR_HEIGHT = 5;
	
	
	
	int dwTargetUserId;
	int videoIndex = 0;
	int videocallSeconds = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		//去掉标题栏；
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		super.onCreate(savedInstanceState);
//		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		
		
		initSdk();
		
		//得到对方的Id;
		dwTargetUserId = BussinessCenter.sessionItem
				.getPeerUserItem(BussinessCenter.selfUserId);
		
		initView();
		anychat.EnterRoom(BussinessCenter.sessionItem.roomId, "");
		mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_CHECKAV:
					//
					CheckVideoStatus();
					//
					updateVolume();
					break;
				case MSG_TIMEUPDATE:
					mTxtTime.setText(BaseMethod
							.getTimeShowString(videocallSeconds++));
					break;
				}

			}
		};
		
		initTimerCheckAv();
		initTimerShowTime();

	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
	}

	
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		if (anychat == null){
			anychat = new AnyChatCoreSDK();
		}
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetObjectEvent(this);
		super.onRestart();
		// 如果是采用Java视频显示，则需要绑定用户
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			videoIndex = anychat.mVideoHelper.bindVideo(mSurfaceRemote
					.getHolder());
			anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
		}

	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		BussinessCenter.mContext = this;
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
	

	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		
		anychat.UserCameraControl(-1, 0);
		anychat.UserSpeakControl(-1, 0);
		anychat.UserSpeakControl(dwTargetUserId, 0);
		anychat.UserCameraControl(dwTargetUserId, 0);
		mTimerCheckAv.cancel();
		mTimerShowVideoTime.cancel();
		if (dialog != null && dialog.isShowing())
			dialog.dismiss();
		anychat.LeaveRoom(-1);
		super.onDestroy();

	}

	private void initSdk() {
		if (anychat == null)
			anychat = new AnyChatCoreSDK();
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.mSensorHelper.InitSensor(this);
		// 
		AnyChatCoreSDK.mCameraHelper.SetContext(this);

	}
 
	
	private void initTimerShowTime() {
		if (mTimerShowVideoTime == null)
			mTimerShowVideoTime = new Timer();
		mTimerTask = new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				mHandler.sendEmptyMessage(MSG_TIMEUPDATE);
			}
		};
		mTimerShowVideoTime.schedule(mTimerTask, 100, 1000);
	}

	private void initTimerCheckAv() {
		if (mTimerCheckAv == null)
			mTimerCheckAv = new Timer();
		mTimerTask = new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				mHandler.sendEmptyMessage(MSG_CHECKAV);
			}
		};
		mTimerCheckAv.schedule(mTimerTask, 1000, 100);
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_ENDCALL,
					dwTargetUserId, this);
			dialog.show();
		}

		return super.onKeyDown(keyCode, event);
	}

	private void initView() {
		this.setContentView(R.layout.video_activity);
		mSurfaceSelf = (SurfaceView) findViewById(R.id.surface_local);
		mSurfaceRemote = (SurfaceView) findViewById(R.id.surface_remote);
		mProgressSelf = (ProgressBar) findViewById(R.id.progress_local);
		mProgressRemote = (ProgressBar) findViewById(R.id.progress_remote);

		mTxtTime = (TextView) findViewById(R.id.txt_time);
		mBtnEndSession = (Button) findViewById(R.id.btn_endsession);
		mBtnEndSession.setOnClickListener(this);
		
	
		
		/*mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		
		mImgBtnReturn.setOnClickListener(this);
		
		
		String name1 = anychat.GetUserName(dwTargetUserId);
		mTitleName.setText("正在与 "+name1+" 通话中");	
		System.out.println("对方的用户名字是:"+name1);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setOnClickListener(this);*/
		
		
		
		
		
		mSurfaceRemote.setTag(dwTargetUserId);
		configEntity = ConfigService.LoadConfig(this);
		
		if (configEntity.videoOverlay != 0) {
			mSurfaceSelf.getHolder().setType(
					SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		}
		
		mSurfaceSelf.setZOrderOnTop(true);
		// 视频如果是采用java采集
		if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			mSurfaceSelf.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
			Log.i("ANYCHAT", "VIDEOCAPTRUE---" + "JAVA");
		}

		// 视频显示如果是采用java采集，SurfacecallBack
		if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			videoIndex = anychat.mVideoHelper.bindVideo(mSurfaceRemote.getHolder());
			anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
			Log.i("ANYCHAT", "VIDEOSHOW---" + "JAVA");
		}

		final View layoutLocal = (View) findViewById(R.id.frame_local_area);
		// 默认设置前置摄像头
		layoutLocal.getViewTreeObserver().addOnGlobalLayoutListener(
				new OnGlobalLayoutListener() {

					@Override
					public void onGlobalLayout() {
						// TODO Auto-generated method stub
						if (!bVideoViewLoaded) {
							bVideoViewLoaded = true;
						}
					}
				});
		// 如果默认有多个摄像头默认设置为前置摄像头；
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if (AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				// 
				AnyChatCoreSDK.mCameraHelper.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		} else {
			String[] strVideoCaptures = anychat.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				//
				for (int i = 0; i < strVideoCaptures.length; i++) {
					String strDevices = strVideoCaptures[i];
					if (strDevices.indexOf("Front") >= 0) {
						anychat.SelectVideoCapture(strDevices);
						break;
					}
				}
			}
		}
		
		//设置旋转屏时的操作；
		if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
			adjustLocalVideo(true);
		} else if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
			adjustLocalVideo(false);
		}

	}

	/***
	 * @param 
	 * 
	 * 
	 *            
	 * 
	 */
	public void adjustLocalVideo(boolean bLandScape) {
		float width;
		float height = 0;
		DisplayMetrics dMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dMetrics);
		width = (float) dMetrics.widthPixels / 4;
		LinearLayout layoutLocal = (LinearLayout) this
				.findViewById(R.id.frame_local_area);
		FrameLayout.LayoutParams layoutParams = (android.widget.FrameLayout.LayoutParams) layoutLocal
				.getLayoutParams();
		if (bLandScape) {

			if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL) != 0)
				height = width * AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						/ AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						+ PROGRESSBAR_HEIGHT;
			else
				height = (float) 3 / 4 * width + PROGRESSBAR_HEIGHT;
		} else {

			if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL) != 0)
				height = width * AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						/ AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						+ PROGRESSBAR_HEIGHT;
			else
				height = (float) 4 / 3 * width + PROGRESSBAR_HEIGHT;
		}
		layoutParams.width = (int) width;
		layoutParams.height = (int) height;
		layoutLocal.setLayoutParams(layoutParams);
	}
	
	//本地摄像头设置旋转
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
			adjustLocalVideo(true);
			AnyChatCoreSDK.mCameraHelper.setCameraDisplayOrientation();
		} else {
			adjustLocalVideo(false);
			AnyChatCoreSDK.mCameraHelper.setCameraDisplayOrientation();
		}

	}

	// 判断视频是否已打开
	private void CheckVideoStatus() {
		if (!bOtherVideoOpened) {
			if (anychat.GetCameraState(dwTargetUserId) == 2
					&& anychat.GetUserVideoWidth(dwTargetUserId) != 0) {
				SurfaceHolder holder = mSurfaceRemote.getHolder();
				// 如果是采用内核视频显示（非Java驱动），则需要设置Surface的参数
				if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(-1), anychat.GetUserVideoHeight(-1));
				}
				Surface s = holder.getSurface();
				if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
				} else
					anychat.SetVideoPos(dwTargetUserId, s, 0, 0, 0, 0);
				bOtherVideoOpened = true;
			}
		}
		if (!bSelfVideoOpened) {
			if (anychat.GetCameraState(-1) == 2 && anychat.GetUserVideoWidth(-1) != 0) {
				SurfaceHolder holder = mSurfaceSelf.getHolder();
				if (AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(-1), anychat.GetUserVideoHeight(-1));
				}
				Surface s = holder.getSurface();
				anychat.SetVideoPos(-1, s, 0, 0, 0, 0);
				bSelfVideoOpened = true;
			}
		}
	}
		
	private void updateVolume() {
		mProgressSelf.setProgress(anychat.GetUserSpeakVolume(-1));//自己的音频设置；
		mProgressRemote.setProgress(anychat.GetUserSpeakVolume(dwTargetUserId));//得到对方的音频设置
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub
		if (dialog != null
				&& dialog.isShowing()
				&& DialogFactory.getCurrentDialogId() == DialogFactory.DIALOGID_RESUME) {
			dialog.dismiss();
		}
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {
			
			BussinessCenter.selfUserId = dwUserId;
			BussinessCenter.selfUserName = anychat.GetUserName(dwUserId);
			
		}
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {
			//
			anychat.UserCameraControl(-1, 1);
			anychat.UserSpeakControl(-1, 1);
			bSelfVideoOpened = false;
		}
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub
		anychat.UserCameraControl(dwTargetUserId, 1);
		anychat.UserSpeakControl(dwTargetUserId, 1);
		bOtherVideoOpened = false;
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub
		anychat.UserCameraControl(dwTargetUserId, 1);
		anychat.UserSpeakControl(dwTargetUserId, 1);
		bOtherVideoOpened = false;

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub

		anychat.UserCameraControl(-1, 0);
		anychat.UserSpeakControl(-1, 0);

		anychat.UserSpeakControl(dwTargetUserId, 0);
		anychat.UserCameraControl(dwTargetUserId, 0);
		
		if (dwErrorCode == 0) {
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			BaseMethod.showToast(this.getString(R.string.session_end), this);
			dialog = DialogFactory.getDialog(DialogFactory.DIALOG_NETCLOSE,
					DialogFactory.DIALOG_NETCLOSE, this);
			dialog.show();
		} else {
			BaseMethod.showToast(this.getString(R.string.str_serverlink_close),
					this);
		
			Intent intent = new Intent();
			intent.putExtra("INTENT", BaseConst.AGAIGN_LOGIN);
			intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			intent.setClass(this, MainActivity.class);
			this.startActivity(intent);
			this.finish();
		}
		Log.i("ANYCHAT", "OnAnyChatLinkCloseMessage:" + dwErrorCode);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if (v == mBtnEndSession /*|| v == mImgBtnReturn*/) {
			
			AlertDialog.Builder builder = new AlertDialog.Builder(this);
			builder.setMessage("是否确定要退出通话")
			.setPositiveButton("sure", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface dialog, int which) {
					// TODO Auto-generated method stub
					configEntity = ConfigService.LoadConfig(VideoActivity.this);
					//对方的userId
					BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, dwTargetUserId, 0,
							0, BussinessCenter.selfUserId, "");
					
				}
			}).setNegativeButton("cancel", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface dialog, int which) {
					// TODO Auto-generated method stub
					
				}
			}).create().show();
		}
		
		
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub
		switch (dwEventType) {
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:
			
			Log.e("videoactivity", "进入视频界面回调");
			BaseMethod.showToast("通话结束...", VideoActivity.this);
			this.finish();
			break;

		default:
			break;
		}

		
	}

	@Override
	public void OnAnyChatUserInfoUpdate(int dwUserId, int dwType) {
		// TODO Auto-generated method stub
//		if (dwUserId == 0 && dwType == 0) {
//			BussinessCenter.getBussinessCenter().getOnlineFriendDatas();
//		}
	}

	@Override
	public void OnAnyChatFriendStatus(int dwUserId, int dwStatus) {
		// TODO Auto-generated method stub
//		BussinessCenter.getBussinessCenter().onUserOnlineStatusNotify(dwUserId, dwStatus);
	}
	

	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		// TODO Auto-generated method stub
		
	}
}
