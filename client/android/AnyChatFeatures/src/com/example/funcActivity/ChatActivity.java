package com.example.funcActivity;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.ViewGroup.LayoutParams;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

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

	private int userID;
	private Button mSendBtn;
	private EditText mMessagEditText;
	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private MessageListView mMessageListView;
	private LinearLayout mFullLayout;
	private LinearLayout mMainLayout;

	private ArrayList<String> mMessageList = new ArrayList<String>();

	private AnyChatCoreSDK anyChatSDK;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		Intent intent = getIntent();
		userID = Integer.parseInt(intent.getStringExtra("UserID"));

		InitSDK();
		InitLayout();
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mImgBtnReturn.setOnClickListener(onClickListener);
		mTitleName.setText("与" + anyChatSDK.GetUserName(userID) + "聊天中");
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
		mMessagEditText = new EditText(this);
		mSendBtn = new Button(this);
		mSendBtn.setText("发送");
		mSendBtn.setTextSize(22);
		mSendBtn.setOnClickListener(onClickListener);

		sendLayout.addView(mMessagEditText, new LayoutParams(
				ScreenInfo.WIDTH * 4 / 5 - 60, LayoutParams.FILL_PARENT));
		sendLayout.addView(mSendBtn, new LayoutParams(ScreenInfo.WIDTH / 5,
				LayoutParams.FILL_PARENT));
		mMainLayout.addView(sendLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, ScreenInfo.HEIGHT / 10));

		mFullLayout.addView(mMainLayout, new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		this.setContentView(mFullLayout);
	}

	OnClickListener onClickListener = new OnClickListener() {
		public void onClick(View v) {
			if (v == mSendBtn) {
				sendMessage();
			}else if (v == mImgBtnReturn) {
				destroyCurActivity();
			}
		}
	};

	private void sendMessage() {
		String strSendMsg = mMessagEditText.getText().toString().trim();
		if (ValueUtils.isStrEmpty(strSendMsg))
			return;

		anyChatSDK.SendTextMessage(userID, 1, strSendMsg);
		mMessageList.add("我说: " + strSendMsg);
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
		finish();
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
	}
	
	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		mMessageList
				.add(anyChatSDK.GetUserName(dwFromUserid) + "说: " + message);
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

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 销毁当前界面
		destroyCurActivity();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
	}

}
