package com.example.helloanychat;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatStateChgEvent;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.Toast;

public class VideoActivity extends Activity implements AnyChatBaseEvent,
		AnyChatStateChgEvent {

	int userID;
	boolean bOnPaused = false;
	private boolean bSelfVideoOpened = false; // 本地视频是否已打开
	private boolean bOtherVideoOpened = false; // 对方视频是否已打开

	private SurfaceView mOtherView;
	private SurfaceView mMyView;
	private ImageButton mImgSwitchVideo;
	private Button mEndCallBtn;
	private ImageButton mBtnCameraCtrl; // 控制视频的按钮
	private ImageButton mBtnSpeakCtrl; // 控制音频的按钮

	public AnyChatCoreSDK anychatSDK;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));

		InitSDK();
		InitLayout();

		// 如果视频流过来了，则把背景设置成透明的
		handler.postDelayed(runnable, 200);
	}

	private void InitSDK() {
		anychatSDK = new AnyChatCoreSDK();
		anychatSDK.SetBaseEvent(this);
		anychatSDK.SetStateChgEvent(this);
		anychatSDK.mSensorHelper.InitSensor(this);
		AnyChatCoreSDK.mCameraHelper.SetContext(this);
	}

	private void InitLayout() {
		this.setContentView(R.layout.video_frame);
		this.setTitle("与 \"" + anychatSDK.GetUserName(userID) + "\" 对话中");
		mMyView = (SurfaceView) findViewById(R.id.surface_local);
		mOtherView = (SurfaceView) findViewById(R.id.surface_remote);
		mImgSwitchVideo = (ImageButton) findViewById(R.id.ImgSwichVideo);
		mEndCallBtn = (Button) findViewById(R.id.endCall);
		mBtnSpeakCtrl = (ImageButton) findViewById(R.id.btn_speakControl);
		mBtnCameraCtrl = (ImageButton) findViewById(R.id.btn_cameraControl);
		mBtnSpeakCtrl.setOnClickListener(onClickListener);
		mBtnCameraCtrl.setOnClickListener(onClickListener);
		mImgSwitchVideo.setOnClickListener(onClickListener);
		mEndCallBtn.setOnClickListener(onClickListener);
		// 如果是采用Java视频采集，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			mMyView.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
		}

		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anychatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anychatSDK.mVideoHelper.SetVideoUser(index, userID);
		}

		mMyView.setZOrderOnTop(true);

		anychatSDK.UserCameraControl(userID, 1);
		anychatSDK.UserSpeakControl(userID, 1);

		// 判断是否显示本地摄像头切换图标
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if (AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				// 默认打开前置摄像头
				AnyChatCoreSDK.mCameraHelper
						.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		} else {
			String[] strVideoCaptures = anychatSDK.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				// 默认打开前置摄像头
				for (int i = 0; i < strVideoCaptures.length; i++) {
					String strDevices = strVideoCaptures[i];
					if (strDevices.indexOf("Front") >= 0) {
						anychatSDK.SelectVideoCapture(strDevices);
						break;
					}
				}
			}
		}

		// 根据屏幕方向改变本地surfaceview的宽高比
		if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
			adjustLocalVideo(true);
		} else if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
			adjustLocalVideo(false);
		}

		anychatSDK.UserCameraControl(-1, 1);// -1表示对本地视频进行控制，打开本地视频
		anychatSDK.UserSpeakControl(-1, 1);// -1表示对本地音频进行控制，打开本地音频

	}

	Handler handler = new Handler();
	Runnable runnable = new Runnable() {

		@Override
		public void run() {
			try {
				int videoBitrate = anychatSDK.QueryUserStateInt(userID,
						AnyChatDefine.BRAC_USERSTATE_VIDEOBITRATE);
				if (videoBitrate > 0) {
					handler.removeCallbacks(runnable);
					mOtherView.setBackgroundColor(Color.TRANSPARENT);
				}

				handler.postDelayed(runnable, 200);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};

	private OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View view) {
			switch (view.getId()) {
			case (R.id.ImgSwichVideo): {

				// 如果是采用Java视频采集，则在Java层进行摄像头切换
				if (AnyChatCoreSDK
						.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
					AnyChatCoreSDK.mCameraHelper.SwitchCamera();
					return;
				}

				String strVideoCaptures[] = anychatSDK.EnumVideoCapture();
				String temp = anychatSDK.GetCurVideoCapture();
				for (int i = 0; i < strVideoCaptures.length; i++) {
					if (!temp.equals(strVideoCaptures[i])) {
						anychatSDK.UserCameraControl(-1, 0);
						bSelfVideoOpened = false;
						anychatSDK.SelectVideoCapture(strVideoCaptures[i]);
						anychatSDK.UserCameraControl(-1, 1);
						break;
					}
				}
			}
				break;
			case (R.id.endCall): {
				exitVideoDialog();
			}
			case R.id.btn_speakControl:
				if ((anychatSDK.GetSpeakState(-1) == 1)) {
					mBtnSpeakCtrl.setImageResource(R.drawable.speak_off);
					anychatSDK.UserSpeakControl(-1, 0);
				} else {
					mBtnSpeakCtrl.setImageResource(R.drawable.speak_on);
					anychatSDK.UserSpeakControl(-1, 1);
				}

				break;
			case R.id.btn_cameraControl:
				if ((anychatSDK.GetCameraState(-1) == 2)) {
					mBtnCameraCtrl.setImageResource(R.drawable.camera_off);
					anychatSDK.UserCameraControl(-1, 0);
				} else {
					mBtnCameraCtrl.setImageResource(R.drawable.camera_on);
					anychatSDK.UserCameraControl(-1, 1);
				}
				break;
			default:
				break;
			}
		}
	};

	private void refreshAV() {
		anychatSDK.UserCameraControl(userID, 1);
		anychatSDK.UserSpeakControl(userID, 1);
		anychatSDK.UserCameraControl(-1, 1);
		anychatSDK.UserSpeakControl(-1, 1);
		mBtnSpeakCtrl.setImageResource(R.drawable.speak_on);
		mBtnCameraCtrl.setImageResource(R.drawable.camera_on);
		bOtherVideoOpened = false;
		bSelfVideoOpened = false;
	}

	private void exitVideoDialog() {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setMessage("Are you sure to exit ?")
				.setCancelable(false)
				.setPositiveButton("Yes",
						new DialogInterface.OnClickListener() {

							@Override
							public void onClick(DialogInterface dialog,
									int which) {
								destroyCurActivity();
							}
						})
				.setNegativeButton("No", new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.cancel();
					}
				}).show();
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			exitVideoDialog();
		}

		return super.onKeyDown(keyCode, event);
	}

	protected void onRestart() {
		super.onRestart();
		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anychatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anychatSDK.mVideoHelper.SetVideoUser(index, userID);
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
		anychatSDK.UserCameraControl(userID, 0);
		anychatSDK.UserSpeakControl(userID, 0);
		anychatSDK.UserCameraControl(-1, 0);
		anychatSDK.UserSpeakControl(-1, 0);
	}

	protected void onDestroy() {
		super.onDestroy();

		anychatSDK.mSensorHelper.DestroySensor();
		finish();
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

			if (AnyChatCoreSDK
					.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL) != 0)
				height = width
						* AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						/ AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						+ 5;
			else
				height = (float) 3 / 4 * width + 5;
		} else {

			if (AnyChatCoreSDK
					.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL) != 0)
				height = width
						* AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						/ AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						+ 5;
			else
				height = (float) 4 / 3 * width + 5;
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

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {

	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {

	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		if (!bEnter) {
			if (dwUserId == userID) {
				userID = 0;
				anychatSDK.UserCameraControl(dwUserId, 0);
				anychatSDK.UserSpeakControl(dwUserId, 0);
				bOtherVideoOpened = false;
			}

		} else {
			if (userID != 0)
				return;

			int index = anychatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anychatSDK.mVideoHelper.SetVideoUser(index, dwUserId);

			anychatSDK.UserCameraControl(dwUserId, 1);
			anychatSDK.UserSpeakControl(dwUserId, 1);
			userID = dwUserId;
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 网络连接断开之后，上层需要主动关闭已经打开的音视频设备
		if (bOtherVideoOpened) {
			anychatSDK.UserCameraControl(userID, 0);
			anychatSDK.UserSpeakControl(userID, 0);
			bOtherVideoOpened = false;
		}
		if (bSelfVideoOpened) {
			anychatSDK.UserCameraControl(-1, 0);
			anychatSDK.UserSpeakControl(-1, 0);
			bSelfVideoOpened = false;
		}

		// 销毁当前界面
		destroyCurActivity();
		Intent mIntent = new Intent("VideoActivity");
		// 发送广播
		sendBroadcast(mIntent);
	}

	@Override
	public void OnAnyChatMicStateChgMessage(int dwUserId, boolean bOpenMic) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatCameraStateChgMessage(int dwUserId, int dwState) {
		String strNameStr = anychatSDK.GetUserName(dwUserId);
		if (dwState == 1 && dwUserId == userID) {
			Toast.makeText(this, "\" "+strNameStr+"\" 已离开", Toast.LENGTH_LONG).show();
		}
	}

	@Override
	public void OnAnyChatChatModeChgMessage(int dwUserId, boolean bPublicChat) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatActiveStateChgMessage(int dwUserId, int dwState) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatP2PConnectStateMessage(int dwUserId, int dwState) {
		if(dwState == 0 && dwUserId == userID)
			Toast.makeText(this, "\" " + anychatSDK.GetUserName(dwUserId) + "\" 已离开", Toast.LENGTH_LONG).show();
	}
}
