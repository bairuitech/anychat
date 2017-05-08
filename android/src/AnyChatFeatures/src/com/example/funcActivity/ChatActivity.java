package com.example.funcActivity;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.ViewGroup.LayoutParams;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatTextMsgEvent;
import com.example.common.ScreenInfo;
import com.example.common.ValueUtils;
import com.example.anychatfeatures.MessageListView;
import com.example.anychatfeatures.OnDismissCallback;
import com.example.anychatfeatures.R;

public class ChatActivity extends Activity implements AnyChatBaseEvent,
		AnyChatTextMsgEvent, OnDismissCallback {

	private int mUserID;
	private TextView mSendTV;					// 发送按钮
	private EditText mMessagEditText;			// 发送输入的内容view
	private ImageButton mImgBtnReturn;			// 返回
	private TextView mTitleName;
	private MessageListView mMessageListView;	// 已发送信息列表
	private LinearLayout mFullLayout;
	private LinearLayout mMainLayout;

	private ArrayList<String> mMessageList = new ArrayList<String>(); // 存储已发送的信息

	private AnyChatCoreSDK anyChatSDK;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		Intent intent = getIntent();
		mUserID = Integer.parseInt(intent.getStringExtra("UserID"));

		InitSDK();
		InitLayout();
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgBtnReturn.setOnClickListener(onClickListener);
		mTitleName.setText("与 \"" + anyChatSDK.GetUserName(mUserID) + "\" 聊天中");
	}

	private void InitSDK() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetTextMessageEvent(this);
	}

	private void InitLayout() {
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
		tvMessage.setText("消息记录");
		tvMessage.setBackgroundColor(Color.GRAY);
		mMainLayout.addView(tvMessage, new LayoutParams(
				LayoutParams.FILL_PARENT,
				LayoutParams.WRAP_CONTENT));

		mMessageListView = new MessageListView(this);
		mMessageListView.SetFileList(mMessageList);
		
		LinearLayout.LayoutParams messLayoutParams = new LinearLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		messLayoutParams.weight = 1;
		mMainLayout.addView(mMessageListView, messLayoutParams);

		LinearLayout sendLayout = new LinearLayout(this);
		sendLayout.setOrientation(LinearLayout.HORIZONTAL);
		sendLayout.setBackgroundDrawable(getResources().getDrawable(R.drawable.et_wideborder));
		sendLayout.setBackgroundColor(Color.parseColor("#E8E8E8"));
		sendLayout.setPadding(30, 20, 30, 20);
		mMessagEditText = new EditText(this);
		mMessagEditText.setHint("请输入内容...");
		mSendTV = new TextView(this);
		mSendTV.setGravity(Gravity.CENTER);
		mSendTV.setText("发送");
		mSendTV.setTextSize(25);
		mSendTV.setOnClickListener(onClickListener);

		sendLayout.addView(mMessagEditText, new LayoutParams(
				ScreenInfo.WIDTH * 4 / 5 - 60, 100));
		sendLayout.addView(mSendTV, new LayoutParams(ScreenInfo.WIDTH / 5,
				100));
		mMainLayout.addView(sendLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, 140));

		mFullLayout.addView(mMainLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		this.setContentView(mFullLayout);
	}

	OnClickListener onClickListener = new OnClickListener() {
		public void onClick(View v) {
			if (v == mSendTV) {	
				sendMessage();//发送信息
			}else if (v == mImgBtnReturn) {	
				destroyCurActivity();
			}
		}
	};

	private void sendMessage() {
		String strSendMsg = mMessagEditText.getText().toString().trim();
		if (ValueUtils.isStrEmpty(strSendMsg))
			return;

		anyChatSDK.SendTextMessage(mUserID, 1, strSendMsg);
		mMessageList.add("我: " + strSendMsg);
		mMessageListView.SetFileList(mMessageList);
		mMessagEditText.setText("");
		mMessageListView
				.setSelection(mMessageListView.getAdapter().getCount() + 1);
	}
	
	@Override
	public void onDismiss(ListView listView, int[] reverseSortedPositions) {
		for (int position : reverseSortedPositions) {
			mMessageList.remove(position);
			mMessageListView.SetFileList(mMessageList);
		}
	}
	
	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		if(anyChatSDK != null)
			anyChatSDK.removeEvent(this);
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
	//聊天接受
	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		mMessageList
				.add(anyChatSDK.GetUserName(dwFromUserid) + ": " + message);
		// messageListView.setStackFromBottom(true);
		mMessageListView.SetFileList(mMessageList);
		mMessageListView
				.setSelection(mMessageListView.getAdapter().getCount() - 1);
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
