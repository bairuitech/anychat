package com.example.funcActivity;

import java.io.File;
import java.util.ArrayList;

import android.util.Log;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatOutParam;
import com.bairuitech.anychat.AnyChatTransDataEvent;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;
import com.example.common.ScreenInfo;
import com.example.anychatfeatures.MessageListView;
import com.example.anychatfeatures.R;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.DialogInterface;
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
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class FileTransfer extends Activity implements AnyChatBaseEvent,
		AnyChatTransDataEvent {

	private static final int REQUEST_EX = 1;
	private static final String SAVE_PATH = "/mnt/sdcard/AnyChat/FileRec/";

	private int mUserID;
	private Button mBtnOpen;					// 打开文件按钮
	private Button mBtnSend;					// 发送文件按钮
	private TextView mTVFileFathMsg;			// 打开文件的文件路径view
	private ProgressDialog mProgressDialog;		// 发送文件进度框
	private MessageListView mMessageListView;	// 用于显示对方发送来的文件列表
	private LinearLayout mFullLayout;
	private LinearLayout mMainLayout;
	private ImageButton btnBack;
	private TextView titleName;
	private ImageButton btnChangeCamrea;
	private int mTastID = 0;					// 当前发送文件

	private ArrayList<String> mMessageList = new ArrayList<String>();

	AnyChatCoreSDK anyChatSDK;
	AnyChatOutParam mAnyChatOutParam;
	
	CustomApplication mCustomApplication;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		
		Intent intent = getIntent();
		mUserID = Integer.parseInt(intent.getStringExtra("UserID"));
		mCustomApplication = (CustomApplication) getApplication();
		
		initSDK();
		initLayout();
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar_audio_video);
		btnBack = (ImageButton) this.findViewById(R.id.btnBack);
		titleName = (TextView) this.findViewById(R.id.titleName);
		btnBack.setOnClickListener(onClickListener);
		titleName.setText("与 \"" + anyChatSDK.GetUserName(mUserID) + "\" 传输文件中");
		btnChangeCamrea = (ImageButton) findViewById(R.id.btnChangeCamrea);
		btnChangeCamrea.setVisibility(View.INVISIBLE);
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
		mMessageListView.setOnItemClickListener(onItemClickListener);

		LinearLayout.LayoutParams messLayoutParams = new LinearLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		messLayoutParams.weight = 1;
		mMainLayout.addView(mMessageListView, messLayoutParams);

		LinearLayout bottonLayout = new LinearLayout(this);
		bottonLayout.setOrientation(LinearLayout.HORIZONTAL);
		bottonLayout.setPadding(30, 20, 30, 20);
		bottonLayout.setBackgroundDrawable(getResources().getDrawable(R.drawable.et_wideborder));
		bottonLayout.setBackgroundColor(Color.parseColor("#FFFFE0"));
		
		LinearLayout pathLayout = new LinearLayout(this);
		pathLayout.setPadding(30, 10, 30, 10);

		mBtnOpen = new Button(this);
		mBtnOpen.setBackgroundColor(Color.WHITE);
		mBtnOpen.setText("打开");
		mBtnOpen.setTextSize(19);
		mBtnOpen.setTextColor(getResources().getColor(R.color.text_blue));
		mBtnOpen.setOnClickListener(onClickListener);

		mTVFileFathMsg = new TextView(this);
		mTVFileFathMsg.setBackgroundDrawable(getResources().getDrawable(
				R.drawable.et_border));
		mTVFileFathMsg.setBackgroundColor(Color.parseColor("#F5F5DC"));
		mTVFileFathMsg.setTextSize(20);
		
		mBtnSend = new Button(this);
		mBtnSend.setBackgroundColor(Color.WHITE);
		mBtnSend.setText("发送");
		mBtnSend.setTextSize(19);
		mBtnSend.setTextColor(getResources().getColor(R.color.text_blue));
		mBtnSend.setOnClickListener(onClickListener);
		
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

		mMainLayout.addView(bottonLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, ScreenInfo.HEIGHT / 10));

		mFullLayout.addView(mMainLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		this.setContentView(mFullLayout);
	}

	// 按钮响应事件
	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			if (v == mBtnOpen) {	// 打开文件
				Intent intent = new Intent();
				intent.setDataAndType(Uri.fromFile(new File("/mnt/sdcard")), "*/*");
				intent.setClass(FileTransfer.this, FileExplorer.class);

				startActivityForResult(intent, REQUEST_EX);
			}else if (v == mBtnSend) {		// 发送文件
				String strFilePath = mTVFileFathMsg.getText().toString().trim();
				anyChatSDK.TransFile(mUserID, strFilePath, 0, 0, 0, mAnyChatOutParam);
				mTVFileFathMsg.setText("");
				
				mTastID = mAnyChatOutParam.GetIntValue();
				handler.postDelayed(runnable, 500); //每隔1s执行 
			}else if (v == btnBack) {		// 返回
				destroyCurActivity();
			}

		}
	};
	
	// 传送的文件信息条响应事件
	OnItemClickListener onItemClickListener = new OnItemClickListener() {
		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
				long id) {
			
			Intent intent = null;
			String strDotType = "";
			String strFileName = "";
			String strFile = mMessageList.get(position);
			if ((strFile != null) && (strFile.length() > 0))
			{
				int dotIndex = strFile.lastIndexOf('.');
				int nameIndex = strFile.lastIndexOf('/');
				if ((dotIndex > -1) && (dotIndex < (strFile.length() - 1))){
					strDotType = strFile.substring(dotIndex + 1);
					strFileName = strFile.substring(nameIndex + 1, dotIndex);
					java.lang.System.out.println("" + strFileName + "::" + strDotType);
				}				
				
				String strFileMes = SAVE_PATH + strFileName + "." + strDotType;
				if (strDotType.equalsIgnoreCase("html")){
					intent = BaseMethod.getIntent(strFileMes, "text/html");
				}else if (strDotType.equalsIgnoreCase("jpg") || strDotType.equalsIgnoreCase("png") || strDotType.equalsIgnoreCase("bmp")) {
					intent = BaseMethod.getIntent(strFileMes, "image/*");
				}else if (strDotType.equalsIgnoreCase("pdf")) {
					intent = BaseMethod.getIntent(strFileMes, "application/pdf");
				}else if (strDotType.equalsIgnoreCase("txt")) {
					intent = BaseMethod.getIntent(strFileMes, "text/plain");
				}else if (strDotType.equalsIgnoreCase("avi") || strDotType.equalsIgnoreCase("mp4") || strDotType.equalsIgnoreCase("wmv")
						|| strDotType.equalsIgnoreCase("3gp")  || strDotType.equalsIgnoreCase("flv")  || strDotType.equalsIgnoreCase("mov")) {
					intent = BaseMethod.getIntent(strFileMes, "video/*");
				}else if (strDotType.equalsIgnoreCase("mp3")) {
					intent = BaseMethod.getIntent(strFileMes, "audio/*");
				}else if (strDotType.equalsIgnoreCase("doc") || strDotType.equalsIgnoreCase("docx")) {
					intent = BaseMethod.getIntent(strFileMes, "application/msword");
				}else if (strDotType.equalsIgnoreCase("xls") || strDotType.equalsIgnoreCase("xlsx")) {
					intent = BaseMethod.getIntent(strFileMes, "application/vnd.ms-excel");
				}else if (strDotType.equalsIgnoreCase("ppt") || strDotType.equalsIgnoreCase("pptx")) {
					intent = BaseMethod.getIntent(strFileMes,  "application/vnd.ms-powerpoint");
				}else {
					intent = new Intent();
					File file = new File(SAVE_PATH);
					Uri uri = Uri.fromFile(file);
					intent.setData(uri);
				}
				
				if (intent != null)
					startActivity(intent);
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
					handleProgressDlg();
					mProgressDialog.setProgress(mAnyChatOutParam.GetIntValue());
				}
				else {
					handler.removeCallbacks(runnable);
					return;
				}

				if (mAnyChatOutParam.GetIntValue() == 100) {
					mProgressDialog.dismiss();
					handler.removeCallbacks(runnable);
					return;
				} 

				handler.postDelayed(runnable, 500);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};
	
	private void handleProgressDlg(){
		if (mProgressDialog == null){
			mProgressDialog = new ProgressDialog(this);
			mProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			mProgressDialog.setMax(100);
			mProgressDialog.setMessage("正在传送");
			mProgressDialog.setCanceledOnTouchOutside(false);
			mProgressDialog.setButton("取消", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface dialog, int which) {
					if (mAnyChatOutParam != null){
						anyChatSDK.CancelTransTask(-1, mAnyChatOutParam.GetIntValue());
						handler.removeCallbacks(runnable);
						mProgressDialog.cancel();
						mProgressDialog = null;
					}
				}
			});
		}
		
		mProgressDialog.show();
	}
	
	private void destroyCurActivity() {
		onPause();
		onDestroy();
		finish();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		if(anyChatSDK != null)
			anyChatSDK.removeEvent(this);
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

	// 文件传输接受
	@Override
	public void OnAnyChatTransFile(int dwUserid, String FileName,
			String TempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		Log.d("helloanychat", "OnAnyChatTransFile:" + dwUserid + "=" + FileName
				+ "=" + TempFilePath + "=" + dwFileLength + "=" + dwTaskId);

		mMessageList.add("收到" + anyChatSDK.GetUserName(dwUserid) + "的"
				+ TempFilePath);
		mMessageListView.SetFileList(mMessageList);
		mMessageListView.setSelection(mMessageListView.getAdapter().getCount() + 1);
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
		if(!bEnter){
			if (dwUserId == mUserID) {
				Toast.makeText(this,"\"" + anyChatSDK.GetUserName(mUserID)+ "\" " + "已离开房间", Toast.LENGTH_LONG).show();
				destroyCurActivity();
			}
		}
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
