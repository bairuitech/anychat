package com.bairuitech.callcenter;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.GridView;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatUserInfoEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.bussinesscenter.BussinessCenter;
import com.bairuitech.bussinesscenter.SessionItem;
import com.bairuitech.bussinesscenter.UserItem;
import com.bairuitech.bussinesscenter.VideoCallContrlHandler;
import com.bairuitech.callcenter.R;
import com.bairuitech.util.BaseConst;
import com.bairuitech.util.BaseMethod;
import com.bairuitech.util.ConfigHelper;
import com.bairuitech.util.DialogFactory;

public class HallActivity extends Activity implements OnItemClickListener,
		OnClickListener, AnyChatBaseEvent, AnyChatVideoCallEvent,
		AnyChatUserInfoEvent {
	private AnyChatCoreSDK anychat;
	private Button mBtnSetting;
	private GridView mGridUsers;
	private TextView mTxtVersion;
	private Dialog dialog;
	private UserAdapter mUserAdapter;

	public static final int ACTIVITY_ID_VIDEOCONFIG = 1;
	public static final String INTENT_ACTION_SESSION_ON = "android.intent.action.hallmobileactivity.sessionon";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		initSdk();
		BussinessCenter.getBussinessCenter().getOnlineFriendDatas();
		initView();
		startBackServce();
		Log.i("HallMobileActivity+onCreate", "onCreate");

	}

	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
			/*
			 * if (dialog != null && dialog.isShowing()) dialog.dismiss();
			 */
			Log.i("ANYCHAT", "onConfigurationChanged");
		}

	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
	

	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		BussinessCenter.mContext = HallActivity.this;
		initSdk();
		if (mUserAdapter != null)
			mUserAdapter.notifyDataSetChanged();
		Log.i("ANYCHAT", "HallA" + "onResume");
		super.onResume();
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		BussinessCenter.getBussinessCenter().realseData();
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		if (resultCode == RESULT_OK) {
			ConfigHelper.getConfigHelper().ApplyVideoConfig(this);
		}
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if (v == mBtnSetting) {
			Intent intent = new Intent();
			intent.setClass(this, VideoConfigActivity.class);
			this.startActivityForResult(intent, 1000);
		}
	}

	@Override
	public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
		// TODO Auto-generated method stub
		UserItem item = BussinessCenter.getBussinessCenter()
				.getUserItemByIndex(arg2);
		if (item != null) {
			if (item.getUserId() == BussinessCenter.selfUserId) {
				BaseMethod.showToast(this.getString(R.string.str_targetwrong),
						this);
				return;
			}
			BussinessCenter.sessionItem = new SessionItem(0, item.getUserId(),
					BussinessCenter.selfUserId);
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_CALLRESUME,
					item.getUserId(), this);
			dialog.show();
		}
	}

	private void initView() {
		this.setContentView(R.layout.hall_layout);
		mBtnSetting = (Button) findViewById(R.id.btn_back);
		mGridUsers = (GridView) findViewById(R.id.grid_user);
		mBtnSetting.setText(this.getString(R.string.str_setting));
		mBtnSetting.setOnClickListener(this);
		mTxtVersion = (TextView) findViewById(R.id.txt_system_version);

		mTxtVersion.setText(BaseMethod.getVersion(this)
				+ getString(R.string.company_msg));
		mUserAdapter = new UserAdapter(this);
		mGridUsers.setAdapter(mUserAdapter);
		mGridUsers.setOnItemClickListener(this);
	}

	private void initSdk() {
		if (anychat == null) {
			anychat = new AnyChatCoreSDK();
		}
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetUserInfoEvent(this);
		Log.i("ANYCHAT", "initSdk");
	}

	protected void startBackServce() {
		Intent intent = new Intent();
		intent.setAction(BaseConst.ACTION_BACKSERVICE);
		this.startService(intent);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		// TODO Auto-generated method stub
		if (event.getAction() == KeyEvent.ACTION_DOWN
				&& event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_EXIT, null,
					this);
			dialog.show();
		}
		return super.dispatchKeyEvent(event);
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		return super.onKeyDown(keyCode, event);
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

		if(dwErrorCode==0)
		{
			BussinessCenter.selfUserId = dwUserId;
			BussinessCenter.selfUserName=anychat.GetUserName(dwUserId);
		}
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {
			Intent intent = new Intent();
			intent.setClass(this, VideoActivity.class);
			this.startActivity(intent);
		} else {
			BaseMethod.showToast(this.getString(R.string.str_enterroom_failed),
					this);
		}
		if (dialog != null)
			dialog.dismiss();
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
		// TODO Auto-generated method stub

		if (dwErrorCode == 0) {
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			dialog = DialogFactory.getDialog(DialogFactory.DIALOG_NETCLOSE,
					DialogFactory.DIALOG_NETCLOSE, this);
			dialog.show();
		} else {
			BaseMethod.showToast(this.getString(R.string.str_serverlink_close),
					this);
			Intent intent = new Intent();
			intent.putExtra("INTENT", BaseConst.AGAIGN_LOGIN);
			intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			intent.setClass(this, LoginActivity.class);
			this.startActivity(intent);
			this.finish();
		}
		Log.i("ANYCHAT", "OnAnyChatLinkCloseMessage:" + dwErrorCode);
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub
		switch (dwEventType) {

		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST:
			BussinessCenter.getBussinessCenter().VideoCall_SessionRequest(
					dwUserId, dwFlags, dwParam, userStr);
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_REQUEST,
					dwUserId, this);
			dialog.show();
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY:
			BussinessCenter.getBussinessCenter().VideoCall_SessionReply(
					dwUserId, dwErrorCode, dwFlags, dwParam, userStr);
			if (dwErrorCode == AnyChatDefine.BRAC_ERRORCODE_SUCCESS) {
				dialog = DialogFactory.getDialog(
						DialogFactory.DIALOGID_CALLING, dwUserId,
						HallActivity.this);
				dialog.show();

			} else {
				if (dialog != null && dialog.isShowing()) {
					dialog.dismiss();
				}
			}
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_START:
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			BussinessCenter.getBussinessCenter().VideoCall_SessionStart(
					dwUserId, dwFlags, dwParam, userStr);
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:
			BussinessCenter.getBussinessCenter().VideoCall_SessionEnd(dwUserId,
					dwFlags, dwParam, userStr);
			break;
		}
	}

	@Override
	public void OnAnyChatUserInfoUpdate(int dwUserId, int dwType) {
		// TODO Auto-generated method stub
		// 同步完成服务器中的所有好友数据，可以在此时获取数据
		if (dwUserId == 0 && dwType == 0) {
			BussinessCenter.getBussinessCenter().getOnlineFriendDatas();
			if (mUserAdapter != null)
				mUserAdapter.notifyDataSetChanged();
			Log.i("ANYCHAT", "OnAnyChatUserInfoUpdate");
		}
	}

	@Override
	public void OnAnyChatFriendStatus(int dwUserId, int dwStatus) {
		// TODO Auto-generated method stub
		BussinessCenter.getBussinessCenter().onUserOnlineStatusNotify(dwUserId,
				dwStatus);
		if (mUserAdapter != null)
			mUserAdapter.notifyDataSetChanged();
	}

}
