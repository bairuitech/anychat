package com.bairuitech.callcenter;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.Dialog;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
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
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatUserInfoEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.bussinesscenter.BussinessCenter;
import com.bairuitech.bussinesscenter.UserItem;
import com.bairuitech.callcenter.R;
import com.bairuitech.util.ConfigEntity;
import com.bairuitech.util.ConfigHelper;
import com.bairuitech.util.DialogFactory;
import com.bairuitech.util.TimeShowHelper;

public class VideoActivity extends Activity implements AnyChatBaseEvent,
		OnClickListener, OnTouchListener, AnyChatVideoCallEvent,
		AnyChatUserInfoEvent {
	private SurfaceView mSurfaceSelf;
	private SurfaceView mSurfaceRemote;
	private ProgressBar mProgressSelf;
	private ProgressBar mProgressRemote;
	private ImageView mImgSwitch;
	private TextView mTxtTime;
	private TextView mTxtTarget;
	private Button mBtnEndSession;
	private Button mBtnSwitch;
	private View view;
	private Dialog dialog;

	private AnyChatCoreSDK anychat;
	private Handler mHandler;
	private Timer mTimerCheckAv;
	private Timer mTImerShowVidoTime;
	private TimerTask mTimerTask;
	private ConfigEntity configEntity;

	boolean bSelfVideoOpened = false;
	boolean bOtherVideoOpened = false;

	boolean isFirstLoad = true;
	public static final int MSG_CHECKAV = 1;
	public static final int MSG_TIMEUPDATE = 2;
	public static final int MSG_CHAT_GONE = 33;
	public static final int MSG_SESSIONEND = 34;
	boolean mIsFirst = true;
	float mOriginalLength = 0;
	float mCurrentLength = 0;
	float mCurrentRate = 1;

	int videoAreaWidth = 0;
	int videoAreaHeight = 0;
	int dwTargetUserId;
	int videoIndex = 0;
	boolean bNormal = true;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		initSdk();
		dwTargetUserId = BussinessCenter.sessionItem
				.getPeerUserItem(BussinessCenter.selfUserId);
		initView();
		anychat.EnterRoom(BussinessCenter.sessionItem.roomId, "");
		TimeShowHelper.initTimer();
		mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_CHECKAV:
					CheckVideoStatus();
					updateVolume();
					break;
				case MSG_TIMEUPDATE:
					TimeShowHelper.handleShowTime();
					mTxtTime.setText(TimeShowHelper.getTimeShowString());
					break;
				}

			}
		};
		initTimerCheckAv();
		initTimerShowTime();
		Log.i("ANYCHAT", "VIDEO" + "onCreate");

	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
		anychat.UserCameraControl(-1, 1);
		anychat.UserSpeakControl(-1, 1);
		anychat.UserSpeakControl(dwTargetUserId, 1);
		anychat.UserCameraControl(dwTargetUserId, 1);
		// 如果是采用Java视频显示，则需要绑定用户
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			videoIndex = anychat.mVideoHelper.bindVideo(mSurfaceRemote.getHolder());
			anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
		}

		Log.i("ANYCHAT", "VIDEO" + "onRestart");
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		BussinessCenter.mContext = this;
		Log.i("ANYCHAT", "VIDEO" + "onResume");
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
		anychat.UserCameraControl(-1, 0);
		anychat.UserSpeakControl(-1, 0);
		anychat.UserSpeakControl(dwTargetUserId, 0);
		anychat.UserCameraControl(dwTargetUserId, 0);
		Log.i("ANYCHAT", "VideoActivity" + "onStop");

	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		mTimerCheckAv.cancel();
		mTImerShowVidoTime.cancel();
		if (dialog != null && dialog.isShowing())
			dialog.dismiss();

	}

	private void initSdk() {
		if (anychat == null)
			anychat = new AnyChatCoreSDK();
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetUserInfoEvent(this);
		anychat.mSensorHelper.InitSensor(this);
	}

	private void initTimerShowTime() {
		if (mTImerShowVidoTime == null)
			mTImerShowVidoTime = new Timer();
		mTimerTask = new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				mHandler.sendEmptyMessage(MSG_TIMEUPDATE);
			}
		};
		mTImerShowVidoTime.schedule(mTimerTask, 100, 1000);
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
		mImgSwitch = (ImageView) findViewById(R.id.img_switch);
		mTxtTime = (TextView) findViewById(R.id.txt_time);
		mTxtTarget = (TextView) findViewById(R.id.txt_target);
		mBtnEndSession = (Button) findViewById(R.id.btn_endsession);
		mBtnSwitch = (Button) findViewById(R.id.btn_swtich);
		mBtnSwitch.setOnClickListener(this);
		mBtnEndSession.setOnClickListener(this);
		mImgSwitch.setOnClickListener(this);
		UserItem item = BussinessCenter.getBussinessCenter()
				.getUserItemByUserId(dwTargetUserId);
		if (item != null)
			mTxtTarget.setText("正在与" + item.getUserName() + "通话中");
		mSurfaceRemote.setTag(dwTargetUserId);
		configEntity = ConfigHelper.getConfigHelper().LoadConfig(this);
		if (configEntity.videoOverlay != 0) {
			mSurfaceSelf.getHolder().setType(
					SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		}
		mSurfaceSelf.setZOrderOnTop(true);
		// 如果是采用Java视频采集，则�?��设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			mSurfaceSelf.getHolder().addCallback(AnyChatCoreSDK.mCameraHelper);
			Log.i("ANYCHAT", "VIDEOCAPTRUE---" + "JAVA");
		}

		// 如果是采用Java视频显示，则�?��设置Surface的CallBack
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
			videoIndex = anychat.mVideoHelper.bindVideo(mSurfaceRemote
					.getHolder());
			anychat.mVideoHelper.SetVideoUser(videoIndex, dwTargetUserId);
			Log.i("ANYCHAT", "VIDEOSHOW---" + "JAVA");
		}

		view = (View) findViewById(R.id.video_area);
		// 得到xml布局中视频区域的大小
		view.getViewTreeObserver().addOnGlobalLayoutListener(
				new OnGlobalLayoutListener() {

					@Override
					public void onGlobalLayout() {
						// TODO Auto-generated method stub
						if (isFirstLoad) {
							isFirstLoad = false;
							Log.i("wdith", view.getWidth() + "");
							Log.i("height", view.getHeight() + "");
							videoAreaWidth = view.getWidth();
							videoAreaHeight = view.getHeight();
							adjuestVideoNormalSize(videoAreaWidth - 20,
									videoAreaHeight - 5);
						}
					}
				});
		view.setOnTouchListener(this);
		// 判断是否显示本地摄像头切换图标
		if (AnyChatCoreSDK
				.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
			if (AnyChatCoreSDK.mCameraHelper.GetCameraNumber() > 1) {
				mImgSwitch.setVisibility(View.VISIBLE);
				// 默认打开前置摄像头
				AnyChatCoreSDK.mCameraHelper
						.SelectVideoCapture(AnyChatCoreSDK.mCameraHelper.CAMERA_FACING_FRONT);
			}
		} else {
			String[] strVideoCaptures = anychat.EnumVideoCapture();
			if (strVideoCaptures != null && strVideoCaptures.length > 1) {
				mImgSwitch.setVisibility(View.VISIBLE);
				// 默认打开前置摄像头
				for (int i = 0; i < strVideoCaptures.length; i++) {
					String strDevices = strVideoCaptures[i];
					if (strDevices.indexOf("Front") >= 0) {
						anychat.SelectVideoCapture(strDevices);
						break;
					}
				}
			}
		}

	}

	/***
	 * 调整视频的位置和大小，让本地视频叠在远程视频右上方
	 * 
	 * @param width
	 * @param height
	 */
	public void adjuestVideoSpecialSize(int width, int height) {

		int dwRemoteVideoHeight = 0;
		int dwRemoteVideoWidth = 0;
		int dwLocalVideoWidth = 0;
		int dwLocalVideoHeight = 0;
		if (3 * width > 4 * height) {

			dwRemoteVideoHeight = height - 10;
			dwRemoteVideoWidth = (int) (4.0 / 3.0 * dwRemoteVideoHeight);
		} else {
			dwRemoteVideoWidth = width - 20;
			dwRemoteVideoHeight = (int) (3.0 / 4.0 * dwRemoteVideoWidth);
		}
		dwLocalVideoWidth = (int) (1.0 / 4 * dwRemoteVideoWidth);
		dwLocalVideoHeight = (int) (1.0 / 4 * dwRemoteVideoHeight);
		LinearLayout.LayoutParams layoutVideoArea = (LayoutParams) view
				.getLayoutParams();
		// 视频区域参数
		layoutVideoArea.width = dwRemoteVideoWidth;
		layoutVideoArea.height = dwRemoteVideoHeight;
		view.setLayoutParams(layoutVideoArea);
		// 设置远程视频位置
		RelativeLayout.LayoutParams layoutParamOther = (android.widget.RelativeLayout.LayoutParams) mSurfaceRemote
				.getLayoutParams();
		layoutParamOther.width = dwRemoteVideoWidth;
		layoutParamOther.height = dwRemoteVideoHeight;
		mSurfaceRemote.setLayoutParams(layoutParamOther);
		// 设置本地视频位置
		RelativeLayout.LayoutParams layoutPramSelf = (android.widget.RelativeLayout.LayoutParams) mSurfaceSelf
				.getLayoutParams();
		layoutPramSelf.width = dwLocalVideoWidth;
		layoutPramSelf.height = dwLocalVideoHeight;
		layoutPramSelf.rightMargin = 0;
		layoutPramSelf.leftMargin = 5;
		layoutPramSelf.addRule(RelativeLayout.CENTER_VERTICAL, 0);
		mSurfaceSelf.setLayoutParams(layoutPramSelf);
	}

	/***
	 * 调整视频的位置和大小，使本地和远程左右居中显示。
	 * 
	 * @param width
	 * @param height
	 */
	public void adjuestVideoNormalSize(int width, int height) {
		int dwRemoteVideoHeight = 0;
		int dwRemoteVideoWidth = 0;
		int dwLocalVideoWidth = 0;
		int dwLocalVideoHeight = 0;
		if (3.0 / 2 * width > 4 * height) {
			dwRemoteVideoHeight = height;
			dwRemoteVideoWidth = (int) (4.0 / 3.0 * dwRemoteVideoHeight);
		} else {
			dwRemoteVideoWidth = (int) (width / 2.0);
			dwRemoteVideoHeight = (int) (3.0 / 4.0 * dwRemoteVideoWidth);
		}

		dwLocalVideoWidth = dwRemoteVideoWidth;
		dwLocalVideoHeight = dwRemoteVideoHeight;
		LinearLayout.LayoutParams layoutVideoArea = (LayoutParams) view
				.getLayoutParams();
		// 视频区域参数
		layoutVideoArea.width = width;
		layoutVideoArea.height = height;
		view.setLayoutParams(layoutVideoArea);
		// 设置远程视频位置
		RelativeLayout.LayoutParams layoutParamOther = (android.widget.RelativeLayout.LayoutParams) mSurfaceRemote
				.getLayoutParams();
		layoutParamOther.width = dwRemoteVideoWidth;
		layoutParamOther.height = dwRemoteVideoHeight;
		layoutParamOther.leftMargin = 5;
		mSurfaceRemote.setLayoutParams(layoutParamOther);

		// 设置远程程音量条的位置
		RelativeLayout.LayoutParams layoutParamsRProBar = (android.widget.RelativeLayout.LayoutParams) mProgressRemote
				.getLayoutParams();
		layoutParamsRProBar.width = dwLocalVideoWidth;
		layoutParamsRProBar.leftMargin = 5;
		mProgressRemote.setLayoutParams(layoutParamsRProBar);

		// 设置本地视频位置
		RelativeLayout.LayoutParams layoutPramSelf = (android.widget.RelativeLayout.LayoutParams) mSurfaceSelf
				.getLayoutParams();
		layoutPramSelf.width = dwLocalVideoWidth;
		layoutPramSelf.height = dwLocalVideoHeight;
		layoutPramSelf.leftMargin = 5;
		layoutPramSelf.rightMargin = 5;
		layoutPramSelf.addRule(RelativeLayout.CENTER_VERTICAL);
		mSurfaceSelf.setLayoutParams(layoutPramSelf);

		// 设置本地音量条的位置
		RelativeLayout.LayoutParams layoutParamsLProBar = (android.widget.RelativeLayout.LayoutParams) mProgressSelf
				.getLayoutParams();
		layoutParamsLProBar.width = dwLocalVideoWidth;
		layoutParamsLProBar.leftMargin = 5;
		layoutParamsLProBar.rightMargin = 5;
		mProgressSelf.setLayoutParams(layoutParamsLProBar);
	}

	// 判断视频是否已打开
	private void CheckVideoStatus() {
		if (!bOtherVideoOpened) {
			if (anychat.GetCameraState(dwTargetUserId) == 2
					&& anychat.GetUserVideoWidth(dwTargetUserId) != 0) {
				SurfaceHolder holder = mSurfaceRemote.getHolder();
				// 如果是采用内核视频显示（非Java驱动），则需要设置Surface的参数
				if (AnyChatCoreSDK
						.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(-1),
							anychat.GetUserVideoHeight(-1));
				}
				Surface s = holder.getSurface();
				if (AnyChatCoreSDK
						.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) == AnyChatDefine.VIDEOSHOW_DRIVER_JAVA)
					anychat.mVideoHelper.SetVideoUser(videoIndex,
							dwTargetUserId);
				else
					anychat.SetVideoPos(dwTargetUserId, s, 0, 0, 0, 0);
				bOtherVideoOpened = true;
			}
		}
		if (!bSelfVideoOpened) {
			if (anychat.GetCameraState(-1) == 2
					&& anychat.GetUserVideoWidth(-1) != 0) {
				SurfaceHolder holder = mSurfaceSelf.getHolder();
				if (AnyChatCoreSDK
						.GetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL) != AnyChatDefine.VIDEOSHOW_DRIVER_JAVA) {
					holder.setFormat(PixelFormat.RGB_565);
					holder.setFixedSize(anychat.GetUserVideoWidth(-1),
							anychat.GetUserVideoHeight(-1));
				}
				Surface s = holder.getSurface();
				anychat.SetVideoPos(-1, s, 0, 0, 0, 0);
				bSelfVideoOpened = true;
			}
		}

	}

	private void updateVolume() {
		mProgressSelf.setProgress(anychat.GetUserSpeakVolume(-1));
		mProgressRemote.setProgress(anychat.GetUserSpeakVolume(dwTargetUserId));
		Log.i("ANYCHAT",
				"SELEF_VOLUME:" + anychat.GetUserSpeakVolume(dwTargetUserId));
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

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {
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
		if (dwErrorCode == 0) {
			if (dialog == null || (dialog != null && !dialog.isShowing())) {
				dialog = DialogFactory.getDialog(DialogFactory.DIALOG_NETCLOSE,
						DialogFactory.DIALOG_NETCLOSE, this);
				dialog.show();
			}
		}
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if (v == mBtnEndSession) {
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_ENDCALL,
					dwTargetUserId, this);
			dialog.show();
		}
		if (v == mImgSwitch) {
			// 如果是采用Java视频采集，则在Java层进行摄像头切换
			if (AnyChatCoreSDK
					.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER) == AnyChatDefine.VIDEOCAP_DRIVER_JAVA) {
				AnyChatCoreSDK.mCameraHelper.SwitchCamera();
				return;
			}

			String strVideoCaptures[] = anychat.EnumVideoCapture();
			;
			String temp = anychat.GetCurVideoCapture();
			for (int i = 0; i < strVideoCaptures.length; i++) {
				if (!temp.equals(strVideoCaptures[i])) {
					anychat.UserCameraControl(-1, 0);
					anychat.SelectVideoCapture(strVideoCaptures[i]);
					anychat.UserCameraControl(-1, 1);
					bSelfVideoOpened = false;
					break;
				}
			}

		}
		if (v == mBtnSwitch) {
			if (bNormal) {
				adjuestVideoSpecialSize(videoAreaWidth, videoAreaHeight);
				bNormal = false;
			} else {
				adjuestVideoNormalSize(videoAreaWidth, videoAreaHeight);
				bNormal = true;
			}
		}
	}

	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
		Log.i("ANYCHAT", "VIDEO-TOUCH");
		float dwFirstPOS = 0;
		float dweEndPOS = 0;
		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			dwFirstPOS = event.getX();
			break;
		case MotionEvent.ACTION_MOVE:
			if (event.getPointerCount() == 2) {
				if (mIsFirst) {
					mOriginalLength = (float) Math.sqrt(Math.pow(event.getX(0)
							- event.getX(1), 2)
							+ Math.pow(event.getY(0) - event.getY(1), 2));
					mIsFirst = false;
				} else {
					mCurrentLength = (float) Math.sqrt(Math.pow(event.getX(0)
							- event.getX(1), 2)
							+ Math.pow(event.getY(0) - event.getY(1), 2));
					mCurrentRate = (mCurrentLength / mOriginalLength);
				}
				Log.i("ANYCHAT", "getPointerCount");
			}
			Log.i("ANYCHAT", "ACTION_MOVE");
			break;
		case MotionEvent.ACTION_UP:
			if (mCurrentRate > 1) {
				adjuestVideoSpecialSize(videoAreaWidth, videoAreaHeight);
				Log.i("ANYCHAT", "SCALE");
			} else if (mCurrentRate < 1) {
				adjuestVideoNormalSize(videoAreaWidth, videoAreaHeight);
				Log.i("ANYCHAT", "SOUXIAO");
			} else {
				dweEndPOS = event.getX();
				float dis = dweEndPOS - dwFirstPOS;
				if (dis > 10) {
					adjuestVideoSpecialSize(videoAreaWidth, videoAreaHeight);
				} else if (dis < -10) {
					adjuestVideoNormalSize(videoAreaWidth, videoAreaHeight);
				}

				dweEndPOS = 0;
				Log.i("ANYCHAT", "DIS" + dis);
			}

			mCurrentRate = 1;
			Log.i("ANYCHAT", "ACTION_UP");
			mIsFirst = true;
			break;
		}
		return true;
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub
		if (dwEventType == AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH) {
			anychat.UserCameraControl(-1, 0);
			anychat.UserSpeakControl(-1, 0);
			anychat.UserSpeakControl(dwTargetUserId, 0);
			anychat.UserCameraControl(dwTargetUserId, 0);
			anychat.LeaveRoom(-1);
			this.finish();
		}
	}

	@Override
	public void OnAnyChatUserInfoUpdate(int dwUserId, int dwType) {
		// TODO Auto-generated method stub
		if (dwUserId == 0 && dwType == 0) {
			BussinessCenter.getBussinessCenter().getOnlineFriendDatas();
		}
	}

	@Override
	public void OnAnyChatFriendStatus(int dwUserId, int dwStatus) {
		// TODO Auto-generated method stub
		BussinessCenter.getBussinessCenter().onUserOnlineStatusNotify(dwUserId,
				dwStatus);
	}

}
