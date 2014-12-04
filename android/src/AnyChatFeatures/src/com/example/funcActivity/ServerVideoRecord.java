package com.example.funcActivity;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatRecordEvent;
import com.example.anychatfeatures.R;
import com.example.common.BaseMethod;
import com.example.common.DialogFactory;
import com.example.common.RecordListMenu;

public class ServerVideoRecord extends Activity implements AnyChatBaseEvent,
		AnyChatRecordEvent{

	// handle send msg
	private final int MSG_VIDEOGESPREK = 1;		// 视频对话时间刷新消息
	private final int MSG_SERVERRECORD = 2; 	// 服务器录制时间刷新消息
	private final int UPDATEVIDEOBITDELAYMILLIS = 200; //监听音频视频的码率的间隔刷新时间（毫秒）

	int mUserID;
	private boolean bSelfVideoOpened = false; 	// 本地视频是否已打开
	private boolean bOtherVideoOpened = false;  // 对方视频是否已打开
	private int mVideogesprekSec = 0; 			// 音视频对话的时间
	private int mdwFlags = 0;
	private int mCurRecordUserID =-1;
	private int mServerRecordTimeSec = 0;	 	// 服务器录制的时间
	private int mServerRecordState; 			// 1表示服务器录制打开着，0表示服务器录制关闭着
	private Boolean mFirstGetVideoBitrate = false; //"第一次"获得视频码率的标致
	private Boolean mFirstGetAudioBitrate = false; //"第一次"获得音频码率的标致

	private SurfaceView mOtherView;
	private SurfaceView mMyView;
	private ImageButton mImgBtnReturn; 			// 返回
	private TextView mTitleName; 				// 标题
	private ImageButton mImgSwitchVideo; 		// 切换设备前后摄像头
	private Button mEndCallBtn;
	private Dialog mDialog;
	private TextView mVideogesprekTimeTV; 		// 视频对话时间
	private Timer mVideogesprekTimer;
	private TimerTask mTimerTask;
	private Handler mHandler;
	private ImageButton mIBServerRecording; 	// 服务器录制
	private TextView mServerRecordTimeTV; 		// 显示服务器视频录制时间
	private Timer mServerRecordTimer;

	public AnyChatCoreSDK anyChatSDK;
	private RecordListMenu mMenuWindow;			// 菜单窗体
	// 服务器录制开关图片
	private int[] mArrServerRecordingImg = { R.drawable.server_recording_off,
			R.drawable.server_recording_on };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.servervideorecord_frame);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
				R.layout.titlebar);

		Intent intent = getIntent();
		mUserID = Integer.parseInt(intent.getStringExtra("UserID"));

		InitSDK();
		InitLayout();
		updateTime();

		// 如果视频流过来了，则把背景设置成透明的
		handler.postDelayed(runnable, UPDATEVIDEOBITDELAYMILLIS);
	}

	private void InitSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetRecordSnapShotEvent(this);
		anyChatSDK.mSensorHelper.InitSensor(this);
		AnyChatCoreSDK.mCameraHelper.SetContext(this);

		// 设置录像格式（0表示mp4）
		AnyChatCoreSDK
				.SetSDKOptionInt(AnyChatDefine.BRAC_SO_RECORD_FILETYPE, 0);
	}

	private void InitLayout() {
		mMyView = (SurfaceView) findViewById(R.id.serverVecordSurface_local);
		mOtherView = (SurfaceView) findViewById(R.id.serverVecordSurface_remote);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgSwitchVideo = (ImageButton) findViewById(R.id.ImgSwichVideo);
		mEndCallBtn = (Button) findViewById(R.id.serverRecordEndCall);
		mIBServerRecording = (ImageButton) findViewById(R.id.btn_serverRecording);
		mVideogesprekTimeTV = (TextView) findViewById(R.id.serverRecordVideogesprekTime);
		mServerRecordTimeTV = (TextView) findViewById(R.id.serverVideoRecordTime);
		
		mServerRecordState = 0;
		mTitleName.setText("与 \"" + anyChatSDK.GetUserName(mUserID) + "\" 对话中");
		mImgSwitchVideo.setVisibility(View.VISIBLE);

		mImgBtnReturn.setOnClickListener(onClickListener);
		mImgSwitchVideo.setOnClickListener(onClickListener);
		mEndCallBtn.setOnClickListener(onClickListener);
		mIBServerRecording.setOnClickListener(onClickListener);
		// 如果是采用Java视频采集，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			mMyView.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
		}

		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anyChatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anyChatSDK.mVideoHelper.SetVideoUser(index, mUserID);
		}

		mMyView.setZOrderOnTop(true);

		anyChatSDK.UserCameraControl(mUserID, 1);
		anyChatSDK.UserSpeakControl(mUserID, 1);

		// 判断是否显示本地摄像头切换图标
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if (AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				// 默认打开前置摄像头
				AnyChatCoreSDK.mCameraHelper
						.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		} else {
			String[] strVideoCaptures = anyChatSDK.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				// 默认打开前置摄像头
				for (int i = 0; i < strVideoCaptures.length; i++) {
					String strDevices = strVideoCaptures[i];
					if (strDevices.indexOf("Front") >= 0) {
						anyChatSDK.SelectVideoCapture(strDevices);
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

		anyChatSDK.UserCameraControl(-1, 1);// -1表示对本地视频进行控制，打开本地视频
		anyChatSDK.UserSpeakControl(-1, 1);// -1表示对本地音频进行控制，打开本地音频
	}

	Handler handler = new Handler();
	Runnable runnable = new Runnable() {
		@Override
		public void run() {
			try {
				int videoBitrate = anyChatSDK.QueryUserStateInt(mUserID,
						AnyChatDefine.BRAC_USERSTATE_VIDEOBITRATE);
				int audioBitrate = anyChatSDK.QueryUserStateInt(mUserID,
						AnyChatDefine.BRAC_USERSTATE_AUDIOBITRATE);
				if (videoBitrate > 0)
				{
					//handler.removeCallbacks(runnable);
					mFirstGetVideoBitrate = true;
					mOtherView.setBackgroundColor(Color.TRANSPARENT);
				}
				
				if(audioBitrate > 0){
					mFirstGetAudioBitrate = true;
				}
				
				if (mFirstGetVideoBitrate)
				{
					if (videoBitrate <= 0){						
						Toast.makeText(ServerVideoRecord.this, "视频中断了!", Toast.LENGTH_SHORT).show();
						// 重置下，如果对方退出了，有进去了的情况
						mFirstGetVideoBitrate = false;
					}
				}
				
				if (mFirstGetAudioBitrate){
					if (audioBitrate <= 0){
						Toast.makeText(ServerVideoRecord.this, "音频中断了", Toast.LENGTH_SHORT).show();
						// 重置下，如果对方退出了，有进去了的情况
						mFirstGetAudioBitrate = false;
					}
				}

				handler.postDelayed(runnable, UPDATEVIDEOBITDELAYMILLIS);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};

	private void updateTime() {
		mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				// 刷新视频对话时间
				case MSG_VIDEOGESPREK:
					mVideogesprekTimeTV.setText(BaseMethod
							.getTimeShowStr(mVideogesprekSec++));
					break;
				// 刷新服务器录制时间
				case MSG_SERVERRECORD:
					mServerRecordTimeTV
							.setText(BaseMethod.getTimeShowStr(mServerRecordTimeSec++));
					break;
				default:
					break;
				}
			}

		};

		initVideogesprekTimer();
	}

	// 初始化视频对话定时器
	private void initVideogesprekTimer() {
		if (mVideogesprekTimer == null)
			mVideogesprekTimer = new Timer();

		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_VIDEOGESPREK);
			}
		};

		mVideogesprekTimer.schedule(mTimerTask, 1000, 1000);
	}

	// 初始化服务器录制定时器
	private void initServerRecordTimer() {
		if (mServerRecordTimer == null) {
			mServerRecordTimer = new Timer();
		}

		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_SERVERRECORD);
			}
		};

		mServerRecordTimer.schedule(mTimerTask, 10, 1000);
		mServerRecordTimeTV.setVisibility(View.VISIBLE);
	}

	// 点击事件
	private OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View view) {
			switch (view.getId()) {
			// 返回
			case (R.id.returnImgBtn): {
				destroyCurActivity();
				break;
			}
			// 摄像头切换
			case (R.id.ImgSwichVideo): {
				// 如果是采用Java视频采集，则在Java层进行摄像头切换
				if (AnyChatCoreSDK
						.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
					AnyChatCoreSDK.mCameraHelper.SwitchCamera();
					return;
				}

				String strVideoCaptures[] = anyChatSDK.EnumVideoCapture();
				String temp = anyChatSDK.GetCurVideoCapture();
				for (int i = 0; i < strVideoCaptures.length; i++) {
					if (!temp.equals(strVideoCaptures[i])) {
						anyChatSDK.UserCameraControl(-1, 0);
						bSelfVideoOpened = false;
						anyChatSDK.SelectVideoCapture(strVideoCaptures[i]);
						anyChatSDK.UserCameraControl(-1, 1);
						break;
					}
				}
			}
				break;
			// End Call
			case (R.id.serverRecordEndCall): {
				showEndVideoDialog();
				break;
			}
			// 服务器录制开关
			case R.id.btn_serverRecording:
				if (mServerRecordState == 1){
					mServerRecordState = 0;
					anyChatSDK.StreamRecordCtrlEx(mCurRecordUserID, 0, mdwFlags, 0,
							"关闭服务器视频录制");
					
					mIBServerRecording.setImageResource(mArrServerRecordingImg[mServerRecordState]);
					mServerRecordTimeTV.setVisibility(View.GONE);
					mServerRecordTimer.cancel();
					mServerRecordTimer = null;
				}else {
					if (mMenuWindow != null && mMenuWindow.isShowing())
						break;
					
					mMenuWindow = new RecordListMenu(ServerVideoRecord.this,
							itemsClickListener);
					mMenuWindow.showAtLocation(ServerVideoRecord.this
							.findViewById(R.id.servervideorecord_main),
							Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL, 0, 0);
				}

				break;
			default:
				break;
			}
		}
	};

	private OnClickListener itemsClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			mMenuWindow.dismiss();
			mMenuWindow = null;
			Boolean bCanRecord = false;
			switch (v.getId()) {
			// 给自己录像
			case R.id.btn_recordself:
				mdwFlags = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
						+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO
						+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_LOCALCB
						+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER;
				mCurRecordUserID = -1;
				bCanRecord = true;
				break;
			// 给别人录制
			case R.id.btn_recordremote:
				mdwFlags = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
						+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO
						+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_LOCALCB
						+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER;
				
				mCurRecordUserID = mUserID;
				bCanRecord = true;
				break;
			// 混合录制
			case R.id.btn_hybridrecord:
				mdwFlags = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
					+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO
					+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXAUDIO
					+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXVIDEO
					+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_STEREO
					+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_ABREAST
					+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER;
				mCurRecordUserID = -1;
				bCanRecord = true;
				break;
			default:
				break;
			}
			
			if (bCanRecord){
				anyChatSDK.StreamRecordCtrlEx(mCurRecordUserID, 1, mdwFlags, 0, "开始录制");
				mServerRecordState = 1;
				mServerRecordTimeSec = 0;
				mServerRecordTimeTV.setText("00:00:00");
				mServerRecordTimeTV.setVisibility(View.VISIBLE);
				initServerRecordTimer();
				mIBServerRecording.setImageResource(mArrServerRecordingImg[mServerRecordState]);
			}
		}
	};
	
	// 关闭视频确认框
	private void showEndVideoDialog() {
		mDialog = DialogFactory.getDialog(DialogFactory.DIALOGID_EXIT, mUserID,
				this);
		mDialog.show();
	}

	private void refreshAV() {
		anyChatSDK.UserCameraControl(mUserID, 1);
		anyChatSDK.UserSpeakControl(mUserID, 1);
		anyChatSDK.UserCameraControl(-1, 1);
		anyChatSDK.UserSpeakControl(-1, 1);
		bOtherVideoOpened = false;
		bSelfVideoOpened = false;

		mServerRecordState = 0;
		mServerRecordTimeTV.setVisibility(View.GONE);
		if (mMenuWindow != null && mMenuWindow.isShowing()) {
			mMenuWindow.dismiss();
			mMenuWindow = null;
		}
		
		if (mServerRecordTimer != null){
			mServerRecordTimer.cancel();
			mServerRecordTimer = null;
		}
		anyChatSDK.StreamRecordCtrlEx(mCurRecordUserID, 0, mdwFlags, 0, "关闭视频录制");
		mIBServerRecording
				.setImageResource(mArrServerRecordingImg[mServerRecordState]);
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();

		if (mServerRecordTimer != null)
			mServerRecordTimer.cancel();
	}

	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetRecordSnapShotEvent(this);

		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anyChatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anyChatSDK.mVideoHelper.SetVideoUser(index, mUserID);
		}

		refreshAV();
	}

	protected void onResume() {
		super.onResume();
	}

	protected void onPause() {
		super.onPause();
	}

	protected void onDestroy() {
		super.onDestroy();

		anyChatSDK.UserCameraControl(mUserID, 0);
		anyChatSDK.UserSpeakControl(mUserID, 0);
		anyChatSDK.UserCameraControl(-1, 0);
		anyChatSDK.UserSpeakControl(-1, 0);

		mServerRecordState = 0;
		mServerRecordTimeTV.setVisibility(View.GONE);
		anyChatSDK.StreamRecordCtrlEx(mCurRecordUserID, 0, mdwFlags, 0, "关闭视频录制");
		mIBServerRecording
				.setImageResource(mArrServerRecordingImg[mServerRecordState]);
		if (mServerRecordTimer != null){
			mServerRecordTimer.cancel();
			mServerRecordTimer = null;
		}
		
		if (mMenuWindow != null && mMenuWindow.isShowing()) {
			mMenuWindow.dismiss();
			mMenuWindow = null;
		}
		
		anyChatSDK.mSensorHelper.DestroySensor();

		finish();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			showEndVideoDialog();
		}

		return super.onKeyDown(keyCode, event);
	}

	public void adjustLocalVideo(boolean bLandScape) {
		float width;
		float height = 0;
		DisplayMetrics dMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dMetrics);
		width = (float) dMetrics.widthPixels / 4;
		LinearLayout layoutLocal = (LinearLayout) this
				.findViewById(R.id.serverVecordFrame_local_area);
		FrameLayout.LayoutParams layoutParams = (android.widget.FrameLayout.LayoutParams) layoutLocal
				.getLayoutParams();
		if (bLandScape) {

			if (AnyChatCoreSDK
					.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL) != 0) {
				height = width
						* AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						/ AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						+ 5;
			} else {
				height = (float) 3 / 4 * width + 5;
			}
		} else {

			if (AnyChatCoreSDK
					.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL) != 0) {
				height = width
						* AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL)
						/ AnyChatCoreSDK
								.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL)
						+ 5;
			} else {
				height = (float) 4 / 3 * width + 5;
			}
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
	public void OnAnyChatRecordEvent(int dwUserId, String lpFileName,
			int dwElapse, int dwFlags, int dwParam, String lpUserStr) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatSnapShotEvent(int dwUserId, String lpFileName,
			int dwFlags, int dwParam, String lpUserStr) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		if (!bEnter) {
			if (dwUserId == mUserID) {
				mUserID = 0;
				anyChatSDK.UserCameraControl(dwUserId, 0);
				anyChatSDK.UserSpeakControl(dwUserId, 0);
				bOtherVideoOpened = false;
			}

		} else {
			if (mUserID != 0)
				return;

			int index = anyChatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anyChatSDK.mVideoHelper.SetVideoUser(index, dwUserId);

			anyChatSDK.UserCameraControl(dwUserId, 1);
			anyChatSDK.UserSpeakControl(dwUserId, 1);
			mUserID = dwUserId;
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 网络连接断开之后，上层需要主动关闭已经打开的音视频设备
		if (bOtherVideoOpened) {
			anyChatSDK.UserCameraControl(mUserID, 0);
			anyChatSDK.UserSpeakControl(mUserID, 0);
			bOtherVideoOpened = false;
		}
		if (bSelfVideoOpened) {
			anyChatSDK.UserCameraControl(-1, 0);
			anyChatSDK.UserSpeakControl(-1, 0);
			bSelfVideoOpened = false;
		}

		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);

		// 销毁当前界面
		destroyCurActivity();
	}
}
