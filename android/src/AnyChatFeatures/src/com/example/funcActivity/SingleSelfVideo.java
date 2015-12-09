package com.example.funcActivity;

import java.io.File;
import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatRecordEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.example.anychatfeatures.FuncMenu;
import com.example.anychatfeatures.R;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class SingleSelfVideo extends Activity implements AnyChatBaseEvent,
		AnyChatRecordEvent, AnyChatVideoCallEvent {
	// handle send msg
	private final int MSG_LOCALRECORD = 1; 	// 本地录制时间刷新消息
	private final int MSG_PREVIEWVIDEO = 2; // 视频录制预览倒计时时间刷新消息
	
	public AnyChatCoreSDK anyChatSDK;

	private int mRecordState; 				// 1表示本地录制打开着，0表示本地录制关闭着
	private SurfaceView mMyView;
	private ImageButton mImageBtnReturn;
	private TextView mTitleName;
	private ImageButton mImgSwitchVideo;
	private CustomApplication mCustomApplication;
	private int mRecordTimeSec;
	private ImageView mRecordIV;
	private TextView mVideRecordTimeTV;
	private Timer mVideoRecordTimer;
	private TimerTask mTimerTask;
	private Handler mHandler;
	private ImageView mTakePhotoBtn; 	   // 自拍
	
	
	private Timer mPreviewPicTimer = null;
	private int mPreviewPicSec = 0; 	   // 预览图片或录像的剩余时间
	private final String mStrBasePath = "/AnyChat";
	private TextView mPreviewFilePath;     // 录的视频或拍照的图片存储路径
	private ImageView mPreviewPicIV;
	private String mPreviewPicPathStr = ""; // 拍照图片或录制自己的视频存储路径
	// 存储本地录制开关图片
	private int[] mArrLocalRecordingImg = { R.drawable.singlevideorecordoff,
			R.drawable.singlevideorecordon };
	private int mdwFlags = AnyChatDefine.BRAC_RECORD_FLAGS_AUDIO
			+ AnyChatDefine.BRAC_RECORD_FLAGS_VIDEO
			+ AnyChatDefine.ANYCHAT_RECORD_FLAGS_LOCALCB;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.singlevideo_session);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
				R.layout.titlebar);

		mCustomApplication = (CustomApplication) getApplication();
		InitSDK();
		InitLayout();
		updateTime();
	}

	private void InitSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetRecordSnapShotEvent(this);
		anyChatSDK.mSensorHelper.InitSensor(this);
		AnyChatCoreSDK.mCameraHelper.SetContext(this);

		// 设置录像存储路径
		anyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_RECORD_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Recording/");
		// 设置录像格式（0表示mp4）
		AnyChatCoreSDK
				.SetSDKOptionInt(AnyChatDefine.BRAC_SO_RECORD_FILETYPE, 0);

		// 拍照存储路径
		anyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_SNAPSHOT_TMPDIR,
				Environment.getExternalStorageDirectory() + mStrBasePath
						+ "/Photo");
	}

	private void InitLayout() {
		mMyView = (SurfaceView) findViewById(R.id.singleVideoSurface);
		mImageBtnReturn = (ImageButton) findViewById(R.id.returnImgBtn);
		mTitleName = (TextView)findViewById(R.id.titleName);
		mImgSwitchVideo = (ImageButton) findViewById(R.id.ImgSwichVideo);
		mPreviewPicIV = (ImageView) findViewById(R.id.singleVideoPreviewImg);
		mVideRecordTimeTV = (TextView) findViewById(R.id.SingleVideoRecordTime);
		mTakePhotoBtn = (ImageView)findViewById(R.id.singleVideo_TakePhoto);
		mPreviewFilePath = (TextView) findViewById(R.id.singleVideoPreviewImgPath);
		mRecordIV = (ImageView) findViewById(R.id.singleVideo_Recording);

		mRecordState = 0;
		mRecordTimeSec = 0;

		if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_LOCALVIDEO) {
			mTitleName.setText("录像");
			mTakePhotoBtn.setVisibility(View.GONE);
		} else {
			mTitleName.setText("拍照");
			mRecordIV.setVisibility(View.GONE);
		}

		mImgSwitchVideo.setVisibility(View.VISIBLE);

		mImageBtnReturn.setOnClickListener(onClickListener);
		mImgSwitchVideo.setOnClickListener(onClickListener);
		mRecordIV.setOnClickListener(onClickListener);
		mTakePhotoBtn.setOnClickListener(onClickListener);
		mPreviewPicIV.setOnClickListener(onClickListener);

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

		anyChatSDK.UserCameraControl(-1, 1);// -1表示对本地视频进行控制，打开本地视频
		anyChatSDK.UserSpeakControl(-1, 1);// -1表示对本地音频进行控制，打开本地音频

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
		anyChatSDK.UserCameraControl(-1, 0);
		anyChatSDK.UserSpeakControl(-1, 0);
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);

		// 销毁当前界面
		destroyCurActivity();
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatRecordEvent(int dwUserId, int dwErrorCode, String lpFileName,
			int dwElapse, int dwFlags, int dwParam, String lpUserStr) {
		Log.d("AnyChatx", "录像文件文件路径：" + lpFileName);
		mPreviewPicPathStr = lpFileName;
		File file = new File(lpFileName);
		if (file.exists()) {
			mPreviewPicIV.setImageBitmap(BaseMethod.getVideoThumbnail(
					lpFileName, 300, 400,
					MediaStore.Images.Thumbnails.MICRO_KIND));
			mPreviewFilePath.setText(lpFileName);
			if (mPreviewPicTimer != null) {
				mPreviewPicTimer.cancel();
				mPreviewPicTimer = null;
			}

			initPreviewVideoTimer();
			mPreviewPicSec = 10;
		}
	}

	@Override
	public void OnAnyChatSnapShotEvent(int dwUserId, int dwErrorCode, String lpFileName,
			int dwFlags, int dwParam, String lpUserStr) {
		mPreviewPicPathStr = lpFileName;
		File file = new File(lpFileName);
		if (file.exists()) {
			mPreviewPicIV.setImageBitmap(BaseMethod.getImageThumbnail(lpFileName, 300, 400));
			mPreviewFilePath.setText(lpFileName);
			if (mPreviewPicTimer != null) {
				mPreviewPicTimer.cancel();
				mPreviewPicTimer = null;
			}
			
			initPreviewVideoTimer();
			mPreviewPicSec = 10;
		}
	}

	private void refreshAV() {
		anyChatSDK.UserCameraControl(-1, 1);
		anyChatSDK.UserSpeakControl(-1, 1);

		mVideRecordTimeTV.setVisibility(View.GONE);

		if (mVideoRecordTimer != null) {
			mVideoRecordTimer.cancel();
			mVideoRecordTimer = null;
		}
		
		anyChatSDK.StreamRecordCtrlEx(-1, 0, mdwFlags, 0, "关闭视频录制");
		mRecordState = 0;
		
		mRecordIV.setImageResource(mArrLocalRecordingImg[mRecordState]);
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
	}

	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetRecordSnapShotEvent(this);

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

		anyChatSDK.UserCameraControl(-1, 0);
		anyChatSDK.UserSpeakControl(-1, 0);

		anyChatSDK.StreamRecordCtrlEx(-1, 0, mdwFlags, 0, "关闭视频录制");

		if (mVideoRecordTimer != null) {
			mVideoRecordTimer.cancel();
			mVideoRecordTimer = null;
		}

		anyChatSDK.mSensorHelper.DestroySensor();

		finish();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			exitVideoDialog();
		}
		
		return super.onKeyDown(keyCode, event);
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

	// 点击事件
	private OnClickListener onClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {
			Intent intent = null;
			switch (v.getId()) {
			// 返回
			case (R.id.returnImgBtn):
				destroyCurActivity();
				break;
			case (R.id.ImgSwichVideo):
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
						anyChatSDK.SelectVideoCapture(strVideoCaptures[i]);
						anyChatSDK.UserCameraControl(-1, 1);
						break;
					}
				}
				break;
			case (R.id.singleVideo_Recording):
				if (mRecordState == 0){
					
					if(mPreviewPicIV.getVisibility() == View.VISIBLE){
						mPreviewPicSec = 0;
						mPreviewFilePath.setVisibility(View.GONE);
						mPreviewPicIV.setVisibility(View.GONE);
					}					
					
					anyChatSDK.StreamRecordCtrlEx(-1, 1, mdwFlags, 0,
							"开始录制");
					mRecordState = 1;
					mRecordTimeSec = 0;
					mVideRecordTimeTV.setText("00:00:00");
					mVideRecordTimeTV.setVisibility(View.VISIBLE);
					initLocalRecordTimer();
				}else {
					anyChatSDK.StreamRecordCtrlEx(-1, 0, mdwFlags, 0,
							"关闭录制");
					mRecordState = 0;
					mVideRecordTimeTV.setVisibility(View.GONE);
					mVideoRecordTimer.cancel();
					mVideoRecordTimer = null;
				}
				
				mRecordIV.setImageResource(mArrLocalRecordingImg[mRecordState]);
				break;
			case (R.id.singleVideo_TakePhoto):
				anyChatSDK.SnapShot(-1, AnyChatDefine.ANYCHAT_RECORD_FLAGS_SNAPSHOT, 0);
				BaseMethod.playSound(SingleSelfVideo.this, BaseMethod.PHOTOSSOUNDID);
				break;
			case (R.id.singleVideoPreviewImg):
				if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_LOCALVIDEO) {
					intent = BaseMethod.getIntent(mPreviewPicPathStr, "video/*");
				}else if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_PHOTOGRAPH) {
					intent = BaseMethod.getIntent(mPreviewPicPathStr, "image/*");
				}
			
				startActivity(intent);
				break;
			default:
				break;
			}
		}
	};

	private void updateTime() {
		mHandler = new Handler() {

			@Override
			public void handleMessage(Message msg) {
				// TODO Auto-generated method stub
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_LOCALRECORD:
					mVideRecordTimeTV.setText(BaseMethod
							.getTimeShowStr(mRecordTimeSec++));
					break;
				case MSG_PREVIEWVIDEO:
					if (mPreviewPicSec <= 0) {
						mPreviewPicTimer.cancel();
						mPreviewPicTimer = null;
						mPreviewPicIV.setVisibility(View.GONE);
						mPreviewFilePath.setVisibility(View.GONE);
					} else {
						mPreviewPicSec -= 1;
					}

					break;
				default:
					break;
				}
			}
		};
	}

	// 初始化本地录制定时器
	private void initLocalRecordTimer() {
		if (mVideoRecordTimer == null) {
			mVideoRecordTimer = new Timer();
		}

		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_LOCALRECORD);
			}
		};

		mVideoRecordTimer.schedule(mTimerTask, 10, 1000);
		mVideRecordTimeTV.setVisibility(View.VISIBLE);
	}

	// 初始化录制视频或拍照预览定时器
	private void initPreviewVideoTimer() {
		if (mPreviewPicTimer == null) {
			mPreviewPicTimer = new Timer();
		}

		mTimerTask = new TimerTask() {
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_PREVIEWVIDEO);
			}
		};

		mPreviewPicTimer.schedule(mTimerTask, 10, 1000);
		mPreviewPicIV.setVisibility(View.VISIBLE);
		mPreviewFilePath.setVisibility(View.VISIBLE);
	}

}
