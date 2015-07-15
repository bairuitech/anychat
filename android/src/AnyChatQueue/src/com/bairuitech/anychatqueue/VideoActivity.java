package com.bairuitech.anychatqueue;

import java.util.Timer;
import java.util.TimerTask;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Dialog;
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

import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.bussinesscenter.BussinessCenter;
import com.bairuitech.common.BaseConst;
import com.bairuitech.common.BaseMethod;
import com.bairuitech.common.ConfigEntity;
import com.bairuitech.common.ConfigService;
import com.bairuitech.common.DialogFactory;
import com.bairuitech.main.MainActivity;
import com.example.anychatqueue.R;



@SuppressLint("HandlerLeak") public class VideoActivity extends Activity implements AnyChatBaseEvent,
		OnClickListener, OnTouchListener,AnyChatObjectEvent, AnyChatVideoCallEvent {
	private SurfaceView mSurfaceSelf;
	private SurfaceView mSurfaceRemote;
	private ProgressBar mProgressSelf;
	private ProgressBar mProgressRemote;
	
	
	private TextView mTxtTime;
	private Button mBtnEndSession;
	private Dialog dialog;

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

		//去掉标题栏；
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		super.onCreate(savedInstanceState);
		
		initSdk();
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
					//实时视频刷新
					CheckVideoStatus();
					//实时音频数据
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
		super.onPause();
	}

	@Override
	protected void onRestart() {
		if (anychat == null){
			anychat = new AnyChatCoreSDK();
		}
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetObjectEvent(this);
		super.onRestart();
		
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			videoIndex = anychat.mVideoHelper.bindVideo(mSurfaceRemote
					.getHolder());
			anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
		}

	}

	@Override
	protected void onResume() {
		super.onResume();
		BussinessCenter.mContext = this;
	}

	@Override
	protected void onStop() {
		super.onStop();
	}

	@Override
	protected void onDestroy() {

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
				mHandler.sendEmptyMessage(MSG_CHECKAV);
			}
		};
		mTimerCheckAv.schedule(mTimerTask, 1000, 100);
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
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
						if (!bVideoViewLoaded) {
							bVideoViewLoaded = true;
						}
					}
				});
		// 
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

	private void CheckVideoStatus() {
		if (!bOtherVideoOpened) {
			
			if (anychat.GetCameraState(dwTargetUserId) == 2
					&& anychat.GetUserVideoWidth(dwTargetUserId) != 0) {
				SurfaceHolder holder = mSurfaceRemote.getHolder();
				
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
		mProgressSelf.setProgress(anychat.GetUserSpeakVolume(-1));//
		mProgressRemote.setProgress(anychat.GetUserSpeakVolume(dwTargetUserId));
	}

	public void OnAnyChatConnectMessage(boolean bSuccess) {
		
		if (dialog != null
				&& dialog.isShowing()
				&& DialogFactory.getCurrentDialogId() == DialogFactory.DIALOGID_RESUME) {
			dialog.dismiss();
		}
	}

	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {

		if (dwErrorCode == 0) {
			BussinessCenter.selfUserId = dwUserId;
			BussinessCenter.selfUserName = anychat.GetUserName(dwUserId);
		}
	}

	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {

		if (dwErrorCode == 0) {
			
			anychat.UserCameraControl(-1, 1);
			anychat.UserSpeakControl(-1, 1);
			bSelfVideoOpened = false;
		}
	}

	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {

		anychat.UserCameraControl(dwTargetUserId, 1);
		anychat.UserSpeakControl(dwTargetUserId, 1);
		bOtherVideoOpened = false;
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {

		anychat.UserCameraControl(dwTargetUserId, 1);
		anychat.UserSpeakControl(dwTargetUserId, 1);
		bOtherVideoOpened = false;

	}

	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {

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

	public void onClick(View v) {

		if (v == mBtnEndSession) {
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_ENDCALL,
					dwTargetUserId, this);
			dialog.show();
		}
		
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {

		switch (dwEventType) {
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:
			
			BaseMethod.showToast("视频通话已结束...", VideoActivity.this);	
			Log.e("videoactivity", "进入视频界面回调");
			
			Intent intent = new Intent();
			intent.putExtra("INTENT", BaseConst.APP_EXIT);
			intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			intent.setClass(this, YeWuActivity.class);
			this.startActivity(intent);
			this.finish();
			
			break;

		default:
			break;
		}

		
	}


	@Override
	public boolean onTouch(View v, MotionEvent event) {
		return false;
	}

	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		
	}
}
