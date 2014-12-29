package com.example.funcActivity;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.example.anychatselfrecord.R;
import com.example.common.BaseMethod;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class CCheckStage extends Activity implements AnyChatBaseEvent{
	private AnyChatCoreSDK mAnyChatSDK;
	private Button mReturnBtn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.check_stage);
		InitSDK();
		InitLayout();

		BaseMethod.addActivityToList(this);
	}

	private void InitSDK() {
		if (mAnyChatSDK == null) {
			mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
		}
		
		mAnyChatSDK.SetBaseEvent(this);
	}

	private void InitLayout() {
		mReturnBtn = (Button) findViewById(R.id.returnBtn);
		mReturnBtn.setOnClickListener(onClickListener);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			mAnyChatSDK.LeaveRoom(1);
			mAnyChatSDK.Logout();
			mAnyChatSDK.Release();

			BaseMethod.deleteAllActivity(CCheckStage.this);
		}
	};

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			BaseMethod.exitVideoDialog(this);
		}

		return super.onKeyDown(keyCode, event);
	}
	
	private void destroyCurActivity() {
		onDestroy();
		finish();
		BaseMethod.removeActivityFromList(this);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}
	
	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
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
	
}
