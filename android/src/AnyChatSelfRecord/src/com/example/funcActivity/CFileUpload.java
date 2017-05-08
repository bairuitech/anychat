package com.example.funcActivity;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatOutParam;
import com.bairuitech.anychat.AnyChatTransDataEvent;
import com.example.anychatselfrecord.R;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;

public class CFileUpload extends Activity implements AnyChatBaseEvent,
		AnyChatTransDataEvent {
	private final int UPLOATFILEUPDATETime = 500;
	private final int ACTIVITY_ID_CHECKSTAGE = 7;

	AnyChatCoreSDK mAnyChatSDK;
	CustomApplication mCustomApplication;
	AnyChatOutParam mPicUploadOutParam;
	AnyChatOutParam mVideoUploadOutParam;

	Button mConfirmUploadBtn;
	private int mPicTastID = 0; // 当前上传图片任务ID
	private int mVideoTastID = 0; // 当前上传视频任务ID
	private ProgressBar mPicProgressBar;
	private ProgressBar mVideoProgressBar;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.file_upload);
		mCustomApplication = (CustomApplication) getApplication();
		mPicUploadOutParam = new AnyChatOutParam();
		mVideoUploadOutParam = new AnyChatOutParam();

		InitSDK();
		InitLayout();
		BaseMethod.addActivityToList(this);
		registerBoradcastReceiver();
	}

	private void InitSDK() {
		if (mAnyChatSDK == null) {
			mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
		}

		mAnyChatSDK.SetBaseEvent(this);
		mAnyChatSDK.SetTransDataEvent(this);
	}

	private void InitLayout() {
		mConfirmUploadBtn = (Button) findViewById(R.id.fileUploadBtn);
		mPicProgressBar = (ProgressBar) findViewById(R.id.picProgress);
		mVideoProgressBar = (ProgressBar) findViewById(R.id.videoProgress);

		mConfirmUploadBtn.setOnClickListener(onClickListener);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			mAnyChatSDK.TransFile(0, mCustomApplication.getTakePhotoPath(), 0,
					0, 0, mPicUploadOutParam);
			mPicTastID = mPicUploadOutParam.GetIntValue();
			mAnyChatSDK.TransFile(0,
					mCustomApplication.getVideoRecordingPath(), 0, 0, 0,
					mVideoUploadOutParam);
			mVideoTastID = mVideoUploadOutParam.GetIntValue();

			handler.postDelayed(runnable, UPLOATFILEUPDATETime); // 每隔500ms执行
		}
	};

	Handler handler = new Handler();
	Runnable runnable = new Runnable() {

		@Override
		public void run() {
			try {
				int uploadPicFlag = mAnyChatSDK.QueryTransTaskInfo(-1,
						mPicTastID, AnyChatDefine.BRAC_TRANSTASK_PROGRESS,
						mPicUploadOutParam);
				int uploadVideoFlag = mAnyChatSDK.QueryTransTaskInfo(-1,
						mVideoTastID, AnyChatDefine.BRAC_TRANSTASK_PROGRESS,
						mVideoUploadOutParam);

				if (uploadPicFlag == 0) {
					mPicProgressBar.setProgress(mPicUploadOutParam
							.GetIntValue());
				}

				if (uploadVideoFlag == 0) {
					mVideoProgressBar.setProgress(mVideoUploadOutParam
							.GetIntValue());
				}

				if (mPicUploadOutParam.GetIntValue() == 100
						&& mVideoUploadOutParam.GetIntValue() == 100) {

					handler.removeCallbacks(runnable);

					Intent intent = new Intent();
					intent.setClass(CFileUpload.this, CCheckStage.class);
					startActivityForResult(intent, ACTIVITY_ID_CHECKSTAGE);
					destroyCurActivity();
					overridePendingTransition(R.anim.push_left_in,
							R.anim.push_left_out);

					BaseMethod.removeActivityFromList(CFileUpload.this);
					return;
				}

				handler.postDelayed(runnable, 500);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};

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
		super.onDestroy();
		if (mAnyChatSDK != null) {
			mAnyChatSDK.removeEvent(this);
		}
		if (mBroadcastReceiver != null) {
			unregisterReceiver(mBroadcastReceiver);
			unregisterReceiver = null;
		}
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
		mAnyChatSDK.SetTransDataEvent(this);
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
	public void OnAnyChatTransFile(int dwUserid, String FileName,
			String TempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserid, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatTransBufferEx(int dwUserid, byte[] lpBuf, int dwLen,
			int wparam, int lparam, int taskid) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatSDKFilterData(byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub

	}
}
