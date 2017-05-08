package com.example.funcActivity;

import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatRecordEvent;
import com.example.anychatselfrecord.R;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class CSingleVideo extends Activity implements AnyChatBaseEvent,
		AnyChatRecordEvent {
	private final String mStrBasePath = "/AnyChat";
	private static final int ACTIVITY_ID_PREVIEWPHOTO = 1;
	private static final int ACTIVITY_ID_PREVIEWVIDEO = 2;
	private final int MSG_VIDEORECORD = 1; // 录制时间刷新消息

	private AnyChatCoreSDK mAnyChatSDK;

	// 拍照底条层
	private LinearLayout mTakePhotoBarLay;
	// 拍照按钮
	private Button mTakephotoBtn;
	// 录像底层条
	private LinearLayout mVideoRecordingLay;
	// 录像按钮
	private Button mVideoRecordingBtn;
	private CustomApplication mCustomApplication;
	private SurfaceView mMyView;
	private TextView mVideoRecordTimeTV;
	private ImageView mGuideProcess;
	private TextView mGuideMsg;

	private boolean mStartRecordFlag = false;
	private int mVideoRecordTimeSec = 0; // 录制时间
	int mdwFlags;
	private TimerTask mTimerTask;
	private Timer mVideoRecordTimer;
	private Handler mHandler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.video_frame);
		mCustomApplication = (CustomApplication) getApplication();

		InitSDK();
		InitLayout();

		updateBottomMsgBar();
		updateTime();
		BaseMethod.addActivityToList(this);
		registerBoradcastReceiver();
	}

	private void InitSDK() {
		if (mAnyChatSDK == null) {
			mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
		}
		
		mAnyChatSDK.SetBaseEvent(this);
		mAnyChatSDK.SetRecordSnapShotEvent(this);
		mAnyChatSDK.mSensorHelper.InitSensor(getApplicationContext());
		mAnyChatSDK.mCameraHelper.SetContext(getApplicationContext());

		// 拍照存储路径
		mAnyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_SNAPSHOT_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Photo");
		
		// 设置录像存储路径
		mAnyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_RECORD_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Recording/");

		mdwFlags = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
				+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO;
	}

	private void InitLayout() {
		// 拍照
		mTakePhotoBarLay = (LinearLayout) findViewById(R.id.takephoto_bar);
		mTakephotoBtn = (Button) findViewById(R.id.takephotoBtn);
		mMyView = (SurfaceView) findViewById(R.id.surface_local);
		mGuideProcess = (ImageView) findViewById(R.id.guideProcess);
		mGuideMsg = (TextView) findViewById(R.id.guideMsg);
		mGuideMsg.setBackgroundColor(0x40EBEBEB);
		mTakephotoBtn.setOnClickListener(onClickListener);
		// 录像
		mVideoRecordingLay = (LinearLayout) findViewById(R.id.videoRecording_bar);
		mVideoRecordingBtn = (Button) findViewById(R.id.VideorecordingBtn);
		mVideoRecordTimeTV = (TextView) findViewById(R.id.videoRecordTime);
		mVideoRecordTimeTV.setVisibility(View.GONE);
		mVideoRecordingBtn.setOnClickListener(onClickListener);
		// 如果是采用Java视频采集，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			mMyView.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
		}

		// 判断是否显示本地摄像头切换图标
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if (AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				// 默认打开前置摄像头
				AnyChatCoreSDK.mCameraHelper
						.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		} else {
			String[] strVideoCaptures = mAnyChatSDK.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				// 默认打开前置摄像头
				for (int i = 0; i < strVideoCaptures.length; i++) {
					String strDevices = strVideoCaptures[i];
					if (strDevices.indexOf("Front") >= 0) {
						mAnyChatSDK.SelectVideoCapture(strDevices);
						break;
					}
				}
			}
		}

		mAnyChatSDK.UserCameraControl(-1, 1);// -1表示对本地视频进行控制，打开本地视频
		mAnyChatSDK.UserSpeakControl(-1, 1);// -1表示对本地音频进行控制，打开本地音频
	}

	private void refreshAV() {
		mAnyChatSDK.UserCameraControl(-1, 1);
		mAnyChatSDK.UserSpeakControl(-1, 1);

		if (mVideoRecordTimer != null) {
			mVideoRecordTimer.cancel();
			mVideoRecordTimer = null;
		}
		mStartRecordFlag = false;
		mVideoRecordTimeSec = 0;
		mAnyChatSDK.StreamRecordCtrlEx(-1, 0, mdwFlags, 0, "关闭视频录制");
		mVideoRecordTimeTV.setVisibility(View.GONE);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.takephotoBtn:
				mAnyChatSDK.SnapShot(-1,
						AnyChatDefine.ANYCHAT_RECORD_FLAGS_SNAPSHOT, 0);
				BaseMethod.playSound(CSingleVideo.this,
						BaseMethod.PHOTOSSOUNDID);
				break;
			case R.id.VideorecordingBtn:
				if (!mStartRecordFlag) {
					mStartRecordFlag = true;
					mAnyChatSDK.StreamRecordCtrlEx(-1, 1, mdwFlags, 0, "开始录制");
					mVideoRecordTimeTV.setText("00:00:00");
					mVideoRecordTimeTV.setVisibility(View.VISIBLE);
					mVideoRecordingBtn.setText("录制中");
					initVideoRecordTimer();
				} else {

					if (mVideoRecordTimer != null) {
						mVideoRecordTimer.cancel();
						mVideoRecordTimer = null;
					}

					mStartRecordFlag = false;
					mVideoRecordTimeTV.setVisibility(View.GONE);
					mAnyChatSDK.StreamRecordCtrlEx(-1, 0, mdwFlags, 0, "结束录制");
					mVideoRecordingBtn.setText("录制");
					mVideoRecordTimeSec = 0;
				}

				break;
			default:
				break;
			}
		}
	};

	private void updateBottomMsgBar() {
		if (mCustomApplication.getCurProcessIndex() == CustomApplication.TAKEPHOTO_PROCESS) {
			mTakePhotoBarLay.setVisibility(View.VISIBLE);
			mVideoRecordingLay.setVisibility(View.GONE);
			mGuideProcess.setBackgroundResource(R.drawable.guideprocess_1);
			mGuideMsg.setText(R.string.takePhotoMsg);
		} else if (mCustomApplication.getCurProcessIndex() == CustomApplication.VIDEORECORDING_PROCESS) {
			mTakePhotoBarLay.setVisibility(View.GONE);
			mVideoRecordingLay.setVisibility(View.VISIBLE);
			mGuideProcess.setBackgroundResource(R.drawable.guideprocess_2);
			mGuideMsg.setText(R.string.videoRecordMsg);
		}
	}

	private void updateTime() {
		mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_VIDEORECORD:
					mVideoRecordTimeTV.setText(BaseMethod
							.getTimeShowStr(mVideoRecordTimeSec++));
					break;
				default:
					break;
				}
			}

		};
	}

	// 初始化本地录制定时器
	private void initVideoRecordTimer() {
		if (mVideoRecordTimer == null) {
			mVideoRecordTimer = new Timer();
		}

		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_VIDEORECORD);
			}
		};

		mVideoRecordTimer.schedule(mTimerTask, 10, 1000);
		mVideoRecordTimeTV.setVisibility(View.VISIBLE);
	}

	// 广播
	private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.equals("NetworkDiscon")) {
				destroyCurActivity();
			}
		}
	};

	public void registerBoradcastReceiver() {
		IntentFilter myIntentFilter = new IntentFilter();
		myIntentFilter.addAction("NetworkDiscon");
		// 注册广播
		registerReceiver(mBroadcastReceiver, myIntentFilter);
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
		finish();
		BaseMethod.removeActivityFromList(this);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		if (mVideoRecordTimer != null) {
			mVideoRecordTimer.cancel();
			mVideoRecordTimer = null;
		}
		if(mAnyChatSDK != null){
			mAnyChatSDK.removeEvent(this);
		}
		unregisterReceiver(mBroadcastReceiver);
	}
	
	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
		mAnyChatSDK.SetRecordSnapShotEvent(this);

		refreshAV();
		updateBottomMsgBar();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			BaseMethod.exitVideoDialog(this);
		}

		return super.onKeyDown(keyCode, event);
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
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 销毁当前界面
		destroyCurActivity();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
	}

	@Override
	public void OnAnyChatRecordEvent(int dwUserId, int dwErrorCode, String lpFileName,
			int dwElapse, int dwFlags, int dwParam, String lpUserStr) {
		Log.d("AnyChatx", "录像文件文件路径：" + lpFileName);
		mCustomApplication.setVideoRecordingPath(lpFileName);

		Intent intent = new Intent();
		intent.setClass(CSingleVideo.this, CVideoRecordPreview.class);
		startActivityForResult(intent, ACTIVITY_ID_PREVIEWVIDEO);
		overridePendingTransition(R.anim.push_left_in, R.anim.push_left_out);
	}

	@Override
	public void OnAnyChatSnapShotEvent(int dwUserId, int dwErrorCode, String lpFileName,
			int dwFlags, int dwParam, String lpUserStr) {
		Log.d("AnyChatx", "拍照图片路径：" + lpFileName);

		mCustomApplication.setTakePhotoPath(lpFileName);

		Intent intent = new Intent();
		intent.setClass(CSingleVideo.this, CTakePhotoPreview.class);
		startActivityForResult(intent, ACTIVITY_ID_PREVIEWPHOTO);
		overridePendingTransition(R.anim.push_left_in, R.anim.push_left_out);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		if (resultCode == RESULT_OK && requestCode == ACTIVITY_ID_PREVIEWPHOTO) {

		}
	}
}
