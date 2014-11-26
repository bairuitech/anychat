package com.example.funcActivity;

import java.io.File;
import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatRecordEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;
import com.example.common.DialogFactory;
import com.example.anychatfeatures.FuncMenu;
import com.example.anychatfeatures.R;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.media.ThumbnailUtils;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class VideoActivity extends Activity implements AnyChatBaseEvent,
		AnyChatRecordEvent, AnyChatVideoCallEvent {

	int userID;
	boolean bOnPaused = false;
	private boolean bSelfVideoOpened = false; // 本地视频是否已打开
	private boolean bOtherVideoOpened = false; // 对方视频是否已打开
	private int dwFlags = 0;
	private static final int MSG_VIDEOGESPREK = 1;
	private static final int MSG_VIDEORECORD = 2;
	private static final int MSG_PREVIEWPIC = 3;
	private static final int MSG_PREVIEWVIDEO = 4;
	private int mVideogesprekSec = 0;
	private int mVideoRecordTimeSec = 0;
	private int mPreviewPicSec = 0;
	private int mPreviewVideoSec = 0;
	private int[] mArrLocalRecordingImg = { R.drawable.local_recording_off,
			R.drawable.local_recording_on };
	private int[] mArrServerRecordingImg = { R.drawable.server_recording_off,
			R.drawable.server_recording_on };
	private int mLocalRecordState; // 1表示本地录制打开着，0表示本地录制关闭着
	private int mServerRecordState; // 1表示服务器录制打开着，0表示服务器录制关闭着
	private String mPreviewPicPathStr = "";
	private String mPreviewVideoPathStr = "";

	private SurfaceView mOtherView;
	private SurfaceView mMyView;
	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private ImageButton mImgSwitchVideo;
	private Button mEndCallBtn;
	private ImageButton mBtnCameraCtrl; // 控制视频的按钮
	private ImageButton mBtnSpeakCtrl; // 控制音频的按钮
	private ImageButton mIBLocalRecording; // 混合录制
	private ImageButton mIBServerRecording; // 服务器录制
	private ImageView mPreviewPicIV;
	private ImageView mPreviewVideIV;
	private ImageButton mIBTakePhotoSelf;
	private ImageButton mIBTakePhotoOther;
	private CustomApplication mCustomApplication;
	private Dialog mDialog;
	private TextView mVideogesprekTimeTV;  // 视频对话时间
	private TextView mVideoRecordTimeTV;   // 视频录制时间
	private Timer mVideogesprekTimer;
	private Timer mVideoRecordTimer;
	private Timer mPreviewPicTimer = null;
	private Timer mPreviewVideoTimer = null;
	private TimerTask mTimerTask;
	private Handler mHandler;
	
	private final String mStrBasePath = "/AnyChat";

	public AnyChatCoreSDK anyChatSDK;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.video_frame);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
				R.layout.titlebar);

		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));

		InitSDK();
		InitLayout();
		updateTime();
		
		//如果视频流过来了，则把背景设置成透明的
		handler.postDelayed(runnable, 200);
	}

	private void InitSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetVideoCallEvent(this);
		anyChatSDK.SetRecordSnapShotEvent(this);
		anyChatSDK.mSensorHelper.InitSensor(this);
		AnyChatCoreSDK.mCameraHelper.SetContext(this);

		anyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_RECORD_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Recording");
		// 设置录像格式（0表示mp4）
		AnyChatCoreSDK
				.SetSDKOptionInt(AnyChatDefine.BRAC_SO_RECORD_FILETYPE, 0);

		// 拍照存储路径
		anyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_SNAPSHOT_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Photo");
	}

	private void InitLayout() {
		mMyView = (SurfaceView) findViewById(R.id.surface_local);
		mOtherView = (SurfaceView) findViewById(R.id.surface_remote);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgSwitchVideo = (ImageButton) findViewById(R.id.ImgSwichVideo);
		mEndCallBtn = (Button) findViewById(R.id.endCall);
		mBtnSpeakCtrl = (ImageButton) findViewById(R.id.btn_speakControl);
		mBtnCameraCtrl = (ImageButton) findViewById(R.id.btn_cameraControl);
		mIBLocalRecording = (ImageButton) findViewById(R.id.btn_LocalRecording);
		mIBServerRecording = (ImageButton) findViewById(R.id.btn_ServerRecording);
		mVideogesprekTimeTV = (TextView) findViewById(R.id.videogesprekTime);
		mVideoRecordTimeTV = (TextView) findViewById(R.id.videoRecordTime);
		mPreviewPicIV = (ImageView) findViewById(R.id.previewPhoto);
		mPreviewVideIV = (ImageView) findViewById(R.id.previewVideo);
		mLocalRecordState = 0;
		mServerRecordState = 0;
		mIBTakePhotoSelf = (ImageButton) findViewById(R.id.btn_TakePhotoSelf);
		mIBTakePhotoOther = (ImageButton) findViewById(R.id.btn_TakePhotoOther);

		mTitleName.setText("与 \"" + anyChatSDK.GetUserName(userID) + "\" 对话中");
		mImgSwitchVideo.setVisibility(View.VISIBLE);

		mCustomApplication = (CustomApplication) getApplication();
		if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VOICEVIDEO) {
			mIBLocalRecording.setVisibility(View.GONE);
			mIBServerRecording.setVisibility(View.GONE);

			mIBTakePhotoSelf.setVisibility(View.GONE);
			mIBTakePhotoOther.setVisibility(View.GONE);
		} else if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VIDEO) {
			mBtnSpeakCtrl.setVisibility(View.GONE);
			mBtnCameraCtrl.setVisibility(View.GONE);

			mIBTakePhotoSelf.setVisibility(View.GONE);
			mIBTakePhotoOther.setVisibility(View.GONE);
		} else if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_PHOTOGRAPH) {
			mBtnSpeakCtrl.setVisibility(View.GONE);
			mBtnCameraCtrl.setVisibility(View.GONE);

			mIBLocalRecording.setVisibility(View.GONE);
			mIBServerRecording.setVisibility(View.GONE);
		} else if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VIDEOCALL) {
			mIBLocalRecording.setVisibility(View.GONE);
			mIBServerRecording.setVisibility(View.GONE);

			mIBTakePhotoSelf.setVisibility(View.GONE);
			mIBTakePhotoOther.setVisibility(View.GONE);
		}

		mImgBtnReturn.setOnClickListener(onClickListener);
		mBtnSpeakCtrl.setOnClickListener(onClickListener);
		mBtnCameraCtrl.setOnClickListener(onClickListener);
		mImgSwitchVideo.setOnClickListener(onClickListener);
		mEndCallBtn.setOnClickListener(onClickListener);
		mIBLocalRecording.setOnClickListener(onClickListener);
		mIBServerRecording.setOnClickListener(onClickListener);
		mIBTakePhotoSelf.setOnClickListener(onClickListener);
		mIBTakePhotoOther.setOnClickListener(onClickListener);
		mPreviewPicIV.setOnClickListener(onClickListener);
		mPreviewVideIV.setOnClickListener(onClickListener);
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
			anyChatSDK.mVideoHelper.SetVideoUser(index, userID);
		}

		mMyView.setZOrderOnTop(true);

		anyChatSDK.UserCameraControl(userID, 1);
		anyChatSDK.UserSpeakControl(userID, 1);

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
				int videoBitrate = anyChatSDK.QueryUserStateInt(userID, AnyChatDefine.BRAC_USERSTATE_VIDEOBITRATE);
				if (videoBitrate > 0)
				{
					handler.removeCallbacks(runnable);
					mOtherView.setBackgroundColor(Color.TRANSPARENT);
				}
				
				handler.postDelayed(runnable, 200);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};
	
	private void updateTime() {
		mHandler = new Handler(){
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_VIDEOGESPREK:
					mVideogesprekTimeTV.setText(BaseMethod.getTimeShowStr(mVideogesprekSec++));
					break;
				case MSG_VIDEORECORD:
					mVideoRecordTimeTV.setText(BaseMethod.getTimeShowStr(mVideoRecordTimeSec++));
					break;
				case MSG_PREVIEWPIC:
					if (mPreviewPicSec <= 0){
						mPreviewPicTimer.cancel();
						mPreviewPicTimer = null;
						mPreviewPicIV.setVisibility(View.GONE);
					}
					else {
						mPreviewPicSec -= 1;
					}
					break;
				case MSG_PREVIEWVIDEO:
					if (mPreviewVideoSec <= 0){
						mPreviewVideoTimer.cancel();
						mPreviewVideoTimer = null;
						mPreviewVideIV.setVisibility(View.GONE);
					}else {
						mPreviewVideoSec -= 1;
					}
				default:
					break;
				}
			}
			
		};
		
		initVideogesprekTimer();
	}
	
	private void initVideogesprekTimer()
	{
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
	
	private void initVideoRecordTimer() {
		if (mVideoRecordTimer == null){
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
	
	private void initPreviewPicTimer() {
		if (mPreviewPicTimer == null){
			mPreviewPicTimer = new Timer();
		}
		
		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_PREVIEWPIC);				
			}
		};
		
		mPreviewPicTimer.schedule(mTimerTask, 10, 1000);
		mPreviewPicIV.setVisibility(View.VISIBLE);
	}
	
	private void initPreviewVideoTimer(){
		if(mPreviewVideoTimer == null){
			mPreviewVideoTimer = new Timer();
		}
		
		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_PREVIEWVIDEO);				
			}
		};
		
		mPreviewVideoTimer.schedule(mTimerTask, 10, 1000);
		mPreviewVideIV.setVisibility(View.VISIBLE);
	}

	private OnClickListener onClickListener = new OnClickListener() {
		int dwFlagsBase = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
				+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO
				+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXAUDIO
				+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXVIDEO
				+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_STEREO
				+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_LOCALCB
				+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_ABREAST;

		@Override
		public void onClick(View view) {
			Intent intent;
			switch (view.getId()) {
			case (R.id.returnImgBtn): {
				if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VIDEOCALL) {
					CallingCenter.getInstance().VideoCallControl(
							AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userID,
							0, 0, -1, "");
				}

				destroyCurActivity();
				break;
			}
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
			case (R.id.endCall): {
				if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VIDEOCALL) {
					showEndVideoCallDialog();
				}else {
					showEndVideoDialog();
				}
	
				break;
			}
			case R.id.btn_speakControl:
				if ((anyChatSDK.GetSpeakState(-1) == 1)) {
					mBtnSpeakCtrl.setImageResource(R.drawable.speak_off);
					anyChatSDK.UserSpeakControl(-1, 0);
				} else {
					mBtnSpeakCtrl.setImageResource(R.drawable.speak_on);
					anyChatSDK.UserSpeakControl(-1, 1);
				}

				break;
			case R.id.btn_cameraControl:
				if ((anyChatSDK.GetCameraState(-1) == 2)) {
					mBtnCameraCtrl.setImageResource(R.drawable.camera_off);
					anyChatSDK.UserCameraControl(-1, 0);
				} else {
					mBtnCameraCtrl.setImageResource(R.drawable.camera_on);
					anyChatSDK.UserCameraControl(-1, 1);
				}
				break;
			case R.id.btn_LocalRecording:
				if (mServerRecordState == 1) {
					mServerRecordState = 0;
					dwFlags = dwFlagsBase
							+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER;
					anyChatSDK.StreamRecordCtrlEx(-1, 0, dwFlags, 0, "打开视频录制");
					mIBServerRecording.setImageResource(mArrServerRecordingImg[mServerRecordState]);
					
					mVideoRecordTimeTV.setVisibility(View.GONE);
					mVideoRecordTimer.cancel();
					mVideoRecordTimer = null;
				}

				dwFlags = dwFlagsBase;
				if (mLocalRecordState == 1) {
					mLocalRecordState = 0;
					anyChatSDK.StreamRecordCtrlEx(-1, 0, dwFlags, 0, "关闭本地视频录制");
					
					mVideoRecordTimeTV.setVisibility(View.GONE);
					mVideoRecordTimer.cancel();
					mVideoRecordTimer = null;
					
				} else {
					mLocalRecordState = 1;
					anyChatSDK.StreamRecordCtrlEx(-1, 1, dwFlags, 0, "打开本地视频录制");
					
					mVideoRecordTimeSec = 0;
					mVideoRecordTimeTV.setText("00:00:00");
					mVideoRecordTimeTV.setVisibility(View.VISIBLE);
					initVideoRecordTimer();
				}

				mIBLocalRecording.setImageResource(mArrLocalRecordingImg[mLocalRecordState]);
						
				break;
			case R.id.btn_ServerRecording:
				dwFlags = dwFlagsBase;
				if (mLocalRecordState == 1) {
					mLocalRecordState = 0;
					anyChatSDK
							.StreamRecordCtrlEx(-1, 0, dwFlags, 0, "关闭本地视频录制");
					mIBLocalRecording
							.setImageResource(mArrLocalRecordingImg[mLocalRecordState]);
					
					mVideoRecordTimeTV.setVisibility(View.GONE);
					mVideoRecordTimer.cancel();
					mVideoRecordTimer = null;
				}

				dwFlags = dwFlagsBase
						+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER;
				if (mServerRecordState == 1) {
					mServerRecordState = 0;
					anyChatSDK.StreamRecordCtrlEx(-1, 0, dwFlags, 0,
							"关闭服务器视频录制");
					
					mVideoRecordTimeTV.setVisibility(View.GONE);
					mVideoRecordTimer.cancel();
					mVideoRecordTimer = null;
				} else {
					mServerRecordState = 1;
					anyChatSDK.StreamRecordCtrlEx(-1, 1, dwFlags, 0,
							"打开服务器视频录制");
					
					initVideoRecordTimer();
					mVideoRecordTimeSec = 0;
					mVideoRecordTimeTV.setText("00:00:00");
					mVideoRecordTimeTV.setVisibility(View.VISIBLE);
				}

				mIBServerRecording.setImageResource(mArrServerRecordingImg[mServerRecordState]);
				
				break;
			case R.id.btn_TakePhotoSelf:
				anyChatSDK.SnapShot(-1, AnyChatDefine.ANYCHAT_RECORD_FLAGS_SNAPSHOT, 0);
				break;
			case R.id.btn_TakePhotoOther:
				anyChatSDK.SnapShot(userID, AnyChatDefine.ANYCHAT_RECORD_FLAGS_SNAPSHOT, 0);
				break;
			case R.id.previewPhoto:
			    intent = BaseMethod.getIntent(mPreviewPicPathStr, "image/*");
				startActivity(intent);
				break;
			case R.id.previewVideo:
				intent = BaseMethod.getIntent(mPreviewVideoPathStr, "video/*");
				startActivity(intent);
				break;
			default:
				break;
			}
		}
	};

	private void showEndVideoCallDialog() {
		mDialog = DialogFactory.getDialog(DialogFactory.DIALOGID_ENDCALL,
				userID, this);
		mDialog.show();
	}

	private void showEndVideoDialog() {
		mDialog = DialogFactory.getDialog(DialogFactory.DIALOGID_EXIT, userID, this);
		mDialog.show();
	}

	private void refreshAV() {
		anyChatSDK.UserCameraControl(userID, 1);
		anyChatSDK.UserSpeakControl(userID, 1);
		anyChatSDK.UserCameraControl(-1, 1);
		anyChatSDK.UserSpeakControl(-1, 1);
		mBtnSpeakCtrl.setImageResource(R.drawable.speak_on);
		mBtnCameraCtrl.setImageResource(R.drawable.camera_on);
		bOtherVideoOpened = false;
		bSelfVideoOpened = false;

		mLocalRecordState = 0;
		mServerRecordState = 0;
		anyChatSDK.StreamRecordCtrlEx(-1, 0, dwFlags, 0, "关闭视频录制");
		mIBLocalRecording
				.setImageResource(mArrLocalRecordingImg[mLocalRecordState]);
		mIBServerRecording
				.setImageResource(mArrServerRecordingImg[mServerRecordState]);
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
		
		if (mVideoRecordTimer != null)
			mVideoRecordTimer.cancel();
	}

	protected void onRestart() {
		super.onRestart();

		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetVideoCallEvent(this);
		// 如果是采用Java视频显示，则需要设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			int index = anyChatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anyChatSDK.mVideoHelper.SetVideoUser(index, userID);
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
		anyChatSDK.UserCameraControl(userID, 0);
		anyChatSDK.UserSpeakControl(userID, 0);
		anyChatSDK.UserCameraControl(-1, 0);
		anyChatSDK.UserSpeakControl(-1, 0);

		mLocalRecordState = 0;
		mServerRecordState = 0;
		anyChatSDK.StreamRecordCtrlEx(-1, 0, dwFlags, 0, "关闭视频录制");
		mIBLocalRecording
				.setImageResource(mArrLocalRecordingImg[mLocalRecordState]);
		mIBServerRecording
				.setImageResource(mArrServerRecordingImg[mServerRecordState]);
	}

	protected void onDestroy() {
		super.onDestroy();

		anyChatSDK.mSensorHelper.DestroySensor();
		finish();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK){
			if(mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_VIDEOCALL) {
			showEndVideoCallDialog();
			}else{
				showEndVideoDialog();
			}
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
				anyChatSDK.UserCameraControl(dwUserId, 0);
				anyChatSDK.UserSpeakControl(dwUserId, 0);
				bOtherVideoOpened = false;
			}

		} else {
			if (userID != 0)
				return;

			int index = anyChatSDK.mVideoHelper.bindVideo(mOtherView
					.getHolder());
			anyChatSDK.mVideoHelper.SetVideoUser(index, dwUserId);

			anyChatSDK.UserCameraControl(dwUserId, 1);
			anyChatSDK.UserSpeakControl(dwUserId, 1);
			userID = dwUserId;
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 网络连接断开之后，上层需要主动关闭已经打开的音视频设备
		if (bOtherVideoOpened) {
			anyChatSDK.UserCameraControl(userID, 0);
			anyChatSDK.UserSpeakControl(userID, 0);
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

	@Override
	public void OnAnyChatRecordEvent(int dwUserId, String lpFileName,
			int dwElapse, int dwFlags, int dwParam, String lpUserStr) {
		Log.d("helloanychat", "录像文件文件路径：" + lpFileName);
		mPreviewVideoPathStr = lpFileName;
		
		File file = new File(lpFileName);
		if (file.exists()){
			mPreviewVideIV.setImageBitmap(getVideoThumbnail(lpFileName, 300, 400, MediaStore.Images.Thumbnails.MICRO_KIND));
			if (mPreviewVideoTimer != null){
				mPreviewVideoTimer.cancel();
				mPreviewVideoTimer = null;
			}
			
			initPreviewVideoTimer();
			mPreviewVideoSec = 3;
		}
		
	}

	@Override
	public void OnAnyChatSnapShotEvent(int dwUserId, String lpFileName,
			int dwFlags, int dwParam, String lpUserStr) {
		
		Log.d("AnyChatx", "拍照图片路径：" + lpFileName);
		mPreviewPicPathStr = lpFileName;
		
		File file = new File(lpFileName);
		if (file.exists()){
			mPreviewPicIV.setImageBitmap(getImageThumbnail(lpFileName, 300, 400));
			
			if (mPreviewPicTimer != null){
				mPreviewPicTimer.cancel();
				mPreviewPicTimer = null;
			}
			
			initPreviewPicTimer();
			mPreviewPicSec = 3;
		}		
	}
	
	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		this.finish();
	}

	private Bitmap getImageThumbnail(String imagePath, int width, int height) {  
        Bitmap bitmap = null;  
        BitmapFactory.Options options = new BitmapFactory.Options();  
        options.inJustDecodeBounds = true;  
        // 获取这个图片的宽和高，注意此处的bitmap为null  
        bitmap = BitmapFactory.decodeFile(imagePath, options);  
        options.inJustDecodeBounds = false; // 设为 false  
        // 计算缩放比  
        int h = options.outHeight;  
        int w = options.outWidth;  
        int beWidth = w / width;  
        int beHeight = h / height;  
        int be = 1;  
        if (beWidth < beHeight) {  
            be = beWidth;  
        } else {  
            be = beHeight;  
        }  
        if (be <= 0) {  
            be = 1;  
        }  
        options.inSampleSize = be;  
        // 重新读入图片，读取缩放后的bitmap，注意这次要把options.inJustDecodeBounds 设为 false  
        bitmap = BitmapFactory.decodeFile(imagePath, options);  
        // 利用ThumbnailUtils来创建缩略图，这里要指定要缩放哪个Bitmap对象  
        bitmap = ThumbnailUtils.extractThumbnail(bitmap, width, height,  
                ThumbnailUtils.OPTIONS_RECYCLE_INPUT);  
        return bitmap;  
    }  
	
	private Bitmap getVideoThumbnail(String videoPath, int width, int height,  
	            int kind) {  
	        Bitmap bitmap = null;  
	        // 获取视频的缩略图  
	        bitmap = ThumbnailUtils.createVideoThumbnail(videoPath, kind);  
	        System.out.println("w"+bitmap.getWidth());  
	        System.out.println("h"+bitmap.getHeight());  
	        bitmap = ThumbnailUtils.extractThumbnail(bitmap, width, height,  
	                ThumbnailUtils.OPTIONS_RECYCLE_INPUT);  
	        return bitmap;  
	}  
}
