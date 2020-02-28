package com.example.anychatfeatures;

import com.example.anychatfeatures.R;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.example.common.CustomApplication;
import com.example.common.DialogFactory;
import com.example.common.DragListView;
import com.example.funcActivity.AlphaChannel;
import com.example.funcActivity.CallingCenter;
import com.example.funcActivity.ChatActivity;
import com.example.funcActivity.FileTransfer;
import com.example.funcActivity.LocalVideoRecord;
import com.example.funcActivity.ServerVideoRecord;
import com.example.funcActivity.SingleSelfVideo;
import com.example.funcActivity.VideoActivity;

import android.app.Activity;
import android.app.Dialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class RolesListActivity extends Activity implements AnyChatBaseEvent,
		AnyChatVideoCallEvent {

	private int mUserselfID;		// 自己id
	private int mRoomID;			// 进入房间ID
	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private DragListView mRolesListView;	// 角色列表
	private CustomApplication mCustomApplication;
	private AnyChatCoreSDK anyChatSDK;

	private List<RoleInfo> mRolesInfoList = new ArrayList<RoleInfo>();
	private RoleListAdapter mAdapter;
	// 呼叫中心用到的对话框
	private Dialog mDialog;
	private boolean mReceiverTag = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		this.setContentView(R.layout.roleslist);

		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		
		Intent intent = getIntent();
		mRoomID = intent.getIntExtra("roomID", 1);
		mCustomApplication = (CustomApplication) getApplication();
		mUserselfID = mCustomApplication.getUserID();

		initSdk();
		InitLayout();
		registerBoradcastReceiver();
	}

	private void initSdk() {
		if (anyChatSDK == null) {
			anyChatSDK = AnyChatCoreSDK.getInstance(RolesListActivity.this);
		}

		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetVideoCallEvent(this);

		anyChatSDK.EnterRoom(mRoomID, "");
	}

	private void InitLayout() {
		mRolesListView = (DragListView) findViewById(R.id.roleListView);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);

		mRolesListView.setDivider(null);
		mTitleName.setText(R.string.str_rolesListTitle);
		mImgBtnReturn.setOnClickListener(onClickListener);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			destroyCurActivity();
		}
	};
	
	private void destroyCurActivity() {
		//onPause();
		onDestroy();
	}

	// 更新用户列表
	private void updateListData() {
		mRolesInfoList.clear();
		int[] userID = anyChatSDK.GetOnlineUser();
		RoleInfo userselfInfo = new RoleInfo();
		mRolesInfoList.add(userselfInfo);
		userselfInfo.setUserID(String.valueOf(mUserselfID));
		userselfInfo.setRoleIconID(getRandomResID());
		if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_LOCALVIDEO) {
			userselfInfo.setName(anyChatSDK.GetUserName(mUserselfID) + "(点击录制自己)");
		}else if (mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_PHOTOGRAPH) {
			userselfInfo.setName(anyChatSDK.GetUserName(mUserselfID) + "(点击自拍)");
		}else {
			userselfInfo.setName(anyChatSDK.GetUserName(mUserselfID) + "(自己)");
		}

		for (int index = 0; index < userID.length; ++index) {
			RoleInfo info = new RoleInfo();
			info.setName(anyChatSDK.GetUserName(userID[index]));
			info.setUserID(String.valueOf(userID[index]));
			info.setRoleIconID(getRandomResID());
			mRolesInfoList.add(info);
		}

		mAdapter = new RoleListAdapter(RolesListActivity.this, mRolesInfoList);
		mRolesListView.setAdapter(mAdapter);
		mRolesListView.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				if (arg2 == 0 &&( mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_LOCALVIDEO ||
						mCustomApplication.getCurOpenFuncUI() == FuncMenu.FUNC_PHOTOGRAPH)){
					Intent intent = new Intent();
					intent.setClass(RolesListActivity.this, SingleSelfVideo.class);
					startActivity(intent);
					return;
				}else if(arg2 == 0) {
					//如果点击的不是本地录制和拍照，则点击角色列表中的自己返回，不做处理
					return;
				}
					
				onSelectItem(arg2);
			}
		});
	}
	
	private int getRandomResID()
	{
		int number = new Random().nextInt(5) + 1;
		if (number == 1) {
			return R.drawable.role_1;
		} else if (number == 2) {
			return R.drawable.role_2;
		} else if (number == 3) {
			return R.drawable.role_3;
		} else if (number == 4) {
			return R.drawable.role_4;
		} else if (number == 5) {
			return R.drawable.role_5;
		}
		
		return R.drawable.role_1;
	}
	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		anyChatSDK.LeaveRoom(-1);
		anyChatSDK.removeEvent(this);
		unRegisterReceiver();
		finish();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetVideoCallEvent(this);
		updateListData();
	}

	@Override
	protected void onResume() {
		super.onResume();
		CallingCenter.mContext = RolesListActivity.this;
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		if (dwErrorCode != 0) {
			Toast.makeText(this, "进入失败", Toast.LENGTH_LONG).show();
			destroyCurActivity();
		}
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		updateListData();
	}

	private void onSelectItem(int postion) {
		String strUserID = mRolesInfoList.get(postion).getUserID();
		if (mRoomID == FuncMenu.FUNC_VIDEOCALL) {
			mDialog = DialogFactory.getDialog(
					DialogFactory.DIALOGID_CALLRESUME,
					Integer.parseInt(strUserID), this);
			mDialog.show();
			return;
		}

		Intent intent = new Intent();
		intent.putExtra("UserID", strUserID);
		if (mRoomID == FuncMenu.FUNC_VOICEVIDEO) {
			intent.setClass(this, VideoActivity.class);
		} else if (mRoomID == FuncMenu.FUNC_TEXTCHAT) {
			intent.setClass(this, ChatActivity.class);
		} else if (mRoomID == FuncMenu.FUNC_ALPHACHANNEL) {
			intent.setClass(this, AlphaChannel.class);
		} else if (mRoomID == FuncMenu.FUNC_FILETRANSFER) {
			intent.setClass(this, FileTransfer.class);
		} else if (mRoomID == FuncMenu.FUNC_LOCALVIDEO) {
			intent.setClass(this, LocalVideoRecord.class);
		} else if (mRoomID == FuncMenu.FUNC_SERVERVIDEO) {
			intent.setClass(this, ServerVideoRecord.class);
		} else if (mRoomID == FuncMenu.FUNC_PHOTOGRAPH) {
			intent.setClass(this, VideoActivity.class);
		}

		startActivity(intent);
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		if (bEnter) {
			RoleInfo roleInfo = new RoleInfo();
			roleInfo.setUserID(String.valueOf(dwUserId));
			roleInfo.setName(anyChatSDK.GetUserName(dwUserId));
			roleInfo.setRoleIconID(getRandomResID());
			mRolesInfoList.add(roleInfo);
			mAdapter.notifyDataSetChanged();
		} else {
			for (int i = 0; i < mRolesInfoList.size(); i++) {
				if (mRolesInfoList.get(i).getUserID().equals("" + dwUserId)) {
					mRolesInfoList.remove(i);
					mAdapter.notifyDataSetChanged();
				}
			}
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		mRolesListView.setAdapter(null);
		if (dwErrorCode == 0) {
			if (mDialog != null && mDialog.isShowing()) {
				mDialog.dismiss();
			}
		}
		
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);

		// 销毁当前界面
		destroyCurActivity();
	}

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
		if (!mReceiverTag){
			IntentFilter myIntentFilter = new IntentFilter();
			myIntentFilter.addAction("NetworkDiscon");
			// 注册广播
			this.registerReceiver(mBroadcastReceiver, myIntentFilter);
			mReceiverTag = true;
		}
	}

	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		switch (dwEventType) {

		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST:
			CallingCenter.getInstance().onVideoCallRequest(dwUserId, dwFlags,
					dwParam, userStr);
			if (mDialog != null && mDialog.isShowing())
				mDialog.dismiss();
			mDialog = DialogFactory.getDialog(DialogFactory.DIALOGID_REQUEST, dwUserId, this);
			mDialog.show();
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY:
			CallingCenter.getInstance().onVideoCallReply(dwUserId, dwErrorCode,
					dwFlags, dwParam, userStr);
			if (dwErrorCode == AnyChatDefine.BRAC_ERRORCODE_SUCCESS) {
				mDialog = DialogFactory.getDialog(
						DialogFactory.DIALOGID_CALLING, dwUserId,
						RolesListActivity.this);
				mDialog.show();

			} else {
				if (mDialog != null && mDialog.isShowing()) {
					mDialog.dismiss();
					
					Toast.makeText(this, getCodeMsg(dwErrorCode), Toast.LENGTH_LONG).show();;
				}
			}
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_START:
			if (mDialog != null && mDialog.isShowing())
				mDialog.dismiss();
			
			CallingCenter.getInstance().stopSessionMusic();
			Intent intent = new Intent();
			intent.putExtra("UserID", String.valueOf(dwUserId));
			intent.setClass(this, VideoActivity.class);
			startActivity(intent);
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:

			break;
		}
	}
	
	private String getCodeMsg(int dwErrorCode) {
		String strMessage = null;
		switch (dwErrorCode) {
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_BUSY:
			strMessage = getString(R.string.str_returncode_bussiness);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE:
			strMessage = getString(R.string.str_returncode_requestrefuse);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_OFFLINE:
			strMessage = getString(R.string.str_returncode_offline);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT:
			strMessage = getString(R.string.str_returncode_requestcancel);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_TIMEOUT:
			strMessage = getString(R.string.str_returncode_timeout);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_DISCONNECT:
			strMessage = getString(R.string.str_returncode_disconnect);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SUCCESS:
			break;
		default:
			break;
		}
		
		return strMessage;
	}

	private void unRegisterReceiver(){
		if (mReceiverTag) {
			mReceiverTag = false;
			if(mBroadcastReceiver!=null){
				this.unregisterReceiver(mBroadcastReceiver);
			}
		}

	}

}
