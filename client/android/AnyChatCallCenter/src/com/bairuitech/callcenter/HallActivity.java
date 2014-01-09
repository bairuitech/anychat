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
import com.bairuitech.callcenter.R;
import com.bairuitech.util.BaseConst;
import com.bairuitech.util.BaseMethod;
import com.bairuitech.util.ConfigEntity;
import com.bairuitech.util.ConfigService;
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
		ApplyVideoConfig();
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
			ApplyVideoConfig();
		}
	}

	// 根据配置文件配置视频参数
	private void ApplyVideoConfig()
	{
		ConfigEntity configEntity = ConfigService.LoadConfig(this);
		if(configEntity.configMode == 1)		// 自定义视频参数配置
		{
			// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL, configEntity.videoBitrate);
			if(configEntity.videoBitrate==0)
			{
				// 设置本地视频编码的质量
				AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL, configEntity.videoQuality);
			}
			// 设置本地视频编码的帧率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL, configEntity.videoFps);
			// 设置本地视频编码的关键帧间隔
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL, configEntity.videoFps*4);
			// 设置本地视频采集分辨率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL, configEntity.resolution_width);
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, configEntity.resolution_height);
			// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL, configEntity.videoPreset);
		}
		// 让视频参数生效
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM, configEntity.configMode);
		// P2P设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC, configEntity.enableP2P);
		// 本地视频Overlay模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY, configEntity.videoOverlay);
		// 回音消除设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL, configEntity.enableAEC);
		// 平台硬件编码设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC, configEntity.useHWCodec);
		// 视频旋转模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL, configEntity.videorotatemode);
		// 视频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER, configEntity.videoCapDriver);
		// 本地视频采集偏色修正设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA, configEntity.fixcolordeviation);
		// 视频显示驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL, configEntity.videoShowDriver);
		// 音频播放驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_PLAYDRVCTRL, configEntity.audioPlayDriver);
		// 音频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_RECORDDRVCTRL, configEntity.audioRecordDriver);
		// 视频GPU渲染设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER, configEntity.videoShowGPURender);
		// 本地视频自动旋转设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION, configEntity.videoAutoRotation);
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
		intent.setAction(BaseConst.ACTION_BACK_SERVICE);
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
			BussinessCenter.getBussinessCenter().onVideoCallRequest(
					dwUserId, dwFlags, dwParam, userStr);
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_REQUEST,
					dwUserId, this);
			dialog.show();
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY:
			BussinessCenter.getBussinessCenter().onVideoCallReply(
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
			BussinessCenter.getBussinessCenter().onVideoCallStart(
					dwUserId, dwFlags, dwParam, userStr);
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:
			BussinessCenter.getBussinessCenter().onVideoCallEnd(dwUserId,
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
