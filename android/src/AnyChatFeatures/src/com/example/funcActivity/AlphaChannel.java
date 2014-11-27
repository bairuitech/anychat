package com.example.funcActivity;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatTransDataEvent;
import com.example.common.BaseMethod;
import com.example.common.ScreenInfo;
import com.example.common.ValueUtils;
import com.example.anychatfeatures.MessageListView;
import com.example.anychatfeatures.R;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;

public class AlphaChannel extends Activity implements AnyChatBaseEvent,
		AnyChatTransDataEvent {

	private int userID;
	private Button mBtnTrans;
	private EditText mETInputMessag;
	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private MessageListView mMessageListView;
	private LinearLayout mFullLayout;
	private LinearLayout mMainLayout;

	private ArrayList<String> mMessageList = new ArrayList<String>();

	private AnyChatCoreSDK anyChatSDK;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));

		initSDK();
		initLayout();
		
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgBtnReturn.setOnClickListener(onClickListener);
		mTitleName.setText("与 \"" + anyChatSDK.GetUserName(userID) + "\" 发送指令中");
	}

	private void initSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetTransDataEvent(this);
	}

	private void initLayout() {
		mFullLayout = new LinearLayout(this);
		mFullLayout.setBackgroundResource(R.drawable.chat_bg);
		// fullLayout.setBackgroundColor(Color.WHITE);
		mFullLayout.setOrientation(LinearLayout.VERTICAL);

		mMainLayout = new LinearLayout(this);
		mMainLayout.setBackgroundColor(Color.TRANSPARENT);
		mMainLayout.setOrientation(LinearLayout.VERTICAL);

		TextView tvMessage = new TextView(this);
		tvMessage.setTextColor(Color.WHITE);
		tvMessage.setPadding(2, 2, 0, 2);
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

		LinearLayout sendLayout = new LinearLayout(this);
		sendLayout.setOrientation(LinearLayout.HORIZONTAL);
		sendLayout.setBackgroundDrawable(getResources().getDrawable(R.drawable.et_wideborder));
		sendLayout.setBackgroundColor(Color.parseColor("#FFFFE0"));
		sendLayout.setPadding(30, 20, 30, 20);
		
		mETInputMessag = new EditText(this);
		mBtnTrans = new Button(this);
		mBtnTrans.setText("传送");
		mBtnTrans.setTextSize(24);
		mBtnTrans.setOnClickListener(onClickListener);

		sendLayout.addView(mETInputMessag, new LayoutParams(
				ScreenInfo.WIDTH * 4 / 5 - 60, LayoutParams.FILL_PARENT));
		sendLayout.addView(mBtnTrans, new LayoutParams(ScreenInfo.WIDTH / 5,
				LayoutParams.FILL_PARENT));
		mMainLayout.addView(sendLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, ScreenInfo.HEIGHT / 10));

		mFullLayout.addView(mMainLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		this.setContentView(mFullLayout);
	}

	OnClickListener onClickListener = new OnClickListener() {
		public void onClick(View v) {
			if (v == mBtnTrans) {
				transMessage();
			}else if (v == mImgBtnReturn) {
				destroyCurActivity();
			}
		}
	};

	private void transMessage() {
		String strTransMsg = mETInputMessag.getText().toString().trim();
		if (ValueUtils.isStrEmpty(strTransMsg))
			return;

		byte[] strByteMsg = null;
		try {
			strByteMsg = strTransMsg.getBytes("UTF8");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		anyChatSDK.TransBuffer(userID, strByteMsg, 1000);
		mMessageList.add("我传送: " + strTransMsg);
		mMessageListView.SetFileList(mMessageList);
		mETInputMessag.setText("");
		mMessageListView
				.setSelection(mMessageListView.getAdapter().getCount() + 1);
	}
	
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		finish();
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
	}
	
	private void destroyCurActivity() {
		onPause();
		onDestroy();
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

	@Override
	public void OnAnyChatTransFile(int dwUserid, String FileName,
			String TempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		Log.d("helloanychat", "OnAnyChatTransFile");
	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserid, byte[] lpBuf, int dwLen) {
		Log.d("helloanychat", "OnAnyChatTransBuffer");
		String srtReceMsg = ""; 
		try {
		  srtReceMsg=new String(lpBuf,"UTF-8");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		mMessageList.add(anyChatSDK.GetUserName(dwUserid) + "传送: " + srtReceMsg);
		mMessageListView.SetFileList(mMessageList);
		mMessageListView
				.setSelection(mMessageListView.getAdapter().getCount() - 1);
	}

	@Override
	public void OnAnyChatTransBufferEx(int dwUserid, byte[] lpBuf, int dwLen,
			int wparam, int lparam, int taskid) {
		Log.d("helloanychat", "OnAnyChatTransBufferEx");
	}

	@Override
	public void OnAnyChatSDKFilterData(byte[] lpBuf, int dwLen) {
		Log.d("helloanychat", "OnAnyChatSDKFilterData");
	}

}
