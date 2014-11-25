package com.example.funcActivity;

import java.io.File;
import java.util.ArrayList;

import android.util.Log;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatOutParam;
import com.bairuitech.anychat.AnyChatTransDataEvent;
import com.example.common.CustomApplication;
import com.example.common.ScreenInfo;
import com.example.anychatfeatures.MessageListView;
import com.example.anychatfeatures.R;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

public class FileTransfer extends Activity implements AnyChatBaseEvent,
		AnyChatTransDataEvent {

	private static final int REQUEST_EX = 1;
	private static final String SAVE_PATH = "/mnt/sdcard/AnyChat/FileRec/";

	private int userID;
	private Button mBtnOpen;
	private Button mBtnSend;
	private TextView mTVFileFathMsg;
	private ProgressBar mSendFileProgressBar;
	private MessageListView mMessageListView;
	private LinearLayout mFullLayout;
	private LinearLayout mMainLayout;
	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private int mTastID = 0;

	private ArrayList<String> mMessageList = new ArrayList<String>();

	AnyChatCoreSDK anyChatSDK;
	AnyChatOutParam mAnyChatOutParam;
	
	CustomApplication mCustomApplication;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		
		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));
		mCustomApplication = (CustomApplication) getApplication();
		
		initSDK();
		initLayout();
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgBtnReturn.setOnClickListener(onClickListener);
		mTitleName.setText("与 \"" + anyChatSDK.GetUserName(userID) + "\" 传输文件中");
	}

	private void initSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetTransDataEvent(this);
		// 设置默认文件存储目录
		anyChatSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_TMPDIR,
				SAVE_PATH);

		mAnyChatOutParam = new AnyChatOutParam();
	}

	private void initLayout() {
		mFullLayout = new LinearLayout(this);
		mFullLayout.setBackgroundResource(R.drawable.chat_bg);
		mFullLayout.setOrientation(LinearLayout.VERTICAL);

		mMainLayout = new LinearLayout(this);
		mMainLayout.setBackgroundColor(Color.TRANSPARENT);
		mMainLayout.setOrientation(LinearLayout.VERTICAL);

		TextView tvMessage = new TextView(this);
		tvMessage.setTextColor(Color.WHITE);
		tvMessage.setPadding(0, 2, 0, 2);
		tvMessage.setTextSize(18);
		tvMessage.setText("传输记录");
		tvMessage.setBackgroundColor(Color.GRAY);
		mMainLayout.addView(tvMessage, new LayoutParams(
				LayoutParams.FILL_PARENT,
				android.support.v4.view.ViewPager.LayoutParams.WRAP_CONTENT));

		mMessageListView = new MessageListView(this);
		mMessageListView.SetFileList(mMessageList);

		LinearLayout.LayoutParams messLayoutParams = new LinearLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		messLayoutParams.weight = 1;
		mMainLayout.addView(mMessageListView, messLayoutParams);

		LinearLayout bottonLayout = new LinearLayout(this);
		bottonLayout.setOrientation(LinearLayout.HORIZONTAL);
		bottonLayout.setPadding(30, 20, 30, 20);
		bottonLayout.setBackgroundDrawable(getResources().getDrawable(R.drawable.et_wideborder));
		bottonLayout.setBackgroundColor(Color.parseColor("#FFFFE0"));
		
		LinearLayout ProgressBarLayout = new LinearLayout(this);
		ProgressBarLayout.setVerticalGravity(Gravity.TOP);
		ProgressBarLayout.setPadding(ScreenInfo.WIDTH/2 - ScreenInfo.WIDTH * 1 / 5, 0, 0, 0);
		LinearLayout pathLayout = new LinearLayout(this);
		pathLayout.setPadding(30, 10, 30, 10);

		mBtnOpen = new Button(this);
		mBtnOpen.setText("打开");
		mBtnOpen.setTextSize(20);
		mBtnOpen.setOnClickListener(onClickListener);

		mTVFileFathMsg = new TextView(this);
		mTVFileFathMsg.setBackgroundDrawable(getResources().getDrawable(
				R.drawable.et_border));
		mTVFileFathMsg.setBackgroundColor(Color.parseColor("#F5F5DC"));
		mTVFileFathMsg.setTextSize(20);
		
		mBtnSend = new Button(this);
		mBtnSend.setText("发送");
		mBtnSend.setTextSize(20);
		mBtnSend.setOnClickListener(onClickListener);

		mSendFileProgressBar = new ProgressBar(this, null, android.R.attr.progressBarStyleHorizontal);
		mSendFileProgressBar.setProgress(0);
		mSendFileProgressBar.setVisibility(View.GONE);
		
		pathLayout.setOrientation(LinearLayout.VERTICAL);
		pathLayout.addView(mTVFileFathMsg,  new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		pathLayout.setVerticalGravity(Gravity.CENTER);
		
		bottonLayout.addView(mBtnOpen, new LayoutParams(
				ScreenInfo.WIDTH * 1 / 5, LayoutParams.FILL_PARENT));
		bottonLayout.addView(pathLayout, new LayoutParams(
				ScreenInfo.WIDTH * 3 / 5, LayoutParams.FILL_PARENT));
		bottonLayout.addView(mBtnSend, new LayoutParams(
				ScreenInfo.WIDTH * 1 / 5, LayoutParams.FILL_PARENT));

		ProgressBarLayout.addView(mSendFileProgressBar, new LayoutParams(
				ScreenInfo.WIDTH * 2 / 5, 50));
		
		mMainLayout.addView(ProgressBarLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, ScreenInfo.HEIGHT * 2 / 10));
		mMainLayout.addView(bottonLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, ScreenInfo.HEIGHT / 10));

		mFullLayout.addView(mMainLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		this.setContentView(mFullLayout);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			if (v == mBtnOpen) {
				Intent intent = new Intent();
				intent.setDataAndType(Uri.fromFile(new File("/mnt/sdcard")), "*/*");
				intent.setClass(FileTransfer.this, FileExplorer.class);

				startActivityForResult(intent, REQUEST_EX);
			}else if (v == mBtnSend) {
				String strFilePath = mTVFileFathMsg.getText().toString().trim();
				anyChatSDK.TransFile(userID, strFilePath, 0, 0, 0, mAnyChatOutParam);
				mTVFileFathMsg.setText("");
				
				mTastID = mAnyChatOutParam.GetIntValue();
				handler.postDelayed(runnable, 500); //每隔1s执行 
			}else if (v == mImgBtnReturn) {
				destroyCurActivity();
			}

		}
	};

	protected void onActivityResult(int requestCode, int resultCode,
			Intent intent) {
		if (resultCode == RESULT_OK) {
			if (requestCode == REQUEST_EX) {
				String strDir = intent.getStringExtra("filePath");
				mTVFileFathMsg.setText(strDir);
			}
		}
	}

	Handler handler = new Handler();
	Runnable runnable = new Runnable() {

		@Override
		public void run() {
			try {
				int returnFlag = anyChatSDK.QueryTransTaskInfo(-1,
								mTastID,
								AnyChatDefine.BRAC_TRANSTASK_PROGRESS,
								mAnyChatOutParam);
				
				if (returnFlag == 0){
					mSendFileProgressBar.setVisibility(View.VISIBLE);
					mSendFileProgressBar.setProgress(mAnyChatOutParam.GetIntValue());
				}
				else {
					handler.removeCallbacks(runnable);
					return;
				}

				if (mAnyChatOutParam.GetIntValue() == 100) {
					mSendFileProgressBar.setVisibility(View.GONE);
					mSendFileProgressBar.setProgress(0);
					handler.removeCallbacks(runnable);
					return;
				} 

				handler.postDelayed(runnable, 500);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};
	
	private void destroyCurActivity() {
		onPause();
		onDestroy();
		finish();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetTransDataEvent(this);
	}

	@Override
	public void OnAnyChatTransFile(int dwUserid, String FileName,
			String TempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		Log.d("helloanychat", "OnAnyChatTransFile:" + dwUserid + "=" + FileName
				+ "=" + TempFilePath + "=" + dwFileLength + "=" + dwTaskId);

		mMessageList.add("收到" + anyChatSDK.GetUserName(dwUserid) + "的"
				+ SAVE_PATH + FileName);
		mMessageListView.SetFileList(mMessageList);
		mMessageListView
				.setSelection(mMessageListView.getAdapter().getCount() + 1);
	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserid, byte[] lpBuf, int dwLen) {
		
	}

	@Override
	public void OnAnyChatTransBufferEx(int dwUserid, byte[] lpBuf, int dwLen,
			int wparam, int lparam, int taskid) {
		
	}

	@Override
	public void OnAnyChatSDKFilterData(byte[] lpBuf, int dwLen) {
		
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

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
		
		// 销毁当前界面
		destroyCurActivity();
	}

}
