package com.example.anychatfeatures;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.*;
import android.widget.AdapterView.OnItemClickListener;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.common.CustomApplication;
import com.example.common.TraceSelectDialog;
import com.example.config.ConfigEntity;
import com.example.config.ConfigService;
import com.example.funcActivity.ReceiverTrace;
import com.example.funcActivity.SenderTrace;
import com.example.funcActivity.VideoConfig;

import java.util.ArrayList;
import java.util.HashMap;

public class FuncMenu extends Activity implements AnyChatBaseEvent {
	public static final int FUNC_VOICEVIDEO = 1;		// 音视频交互
	public static final int FUNC_TEXTCHAT = 2;			// 文字聊天
	public static final int FUNC_ALPHACHANNEL = 3;		// 透明通道
	public static final int FUNC_FILETRANSFER = 4;		// 文件传输
	public static final int FUNC_LOCALVIDEO = 5;		// 本地录像
	public static final int FUNC_SERVERVIDEO = 6;		// 服务器录像
	public static final int FUNC_PHOTOGRAPH = 7;		// 视频抓拍
	public static final int FUNC_VIDEOCALL = 8;			// 呼叫中心
	public static final int FUNC_UDPTRACE = 9;			// 网络检测
	public static final int FUNC_CONFIG = 10;  			// 设置

	// 视频配置界面标识
	public static final int ACTIVITY_ID_VIDEOCONFIG = 1;

    private ImageButton btnBack;  //返回按钮
    private TextView titleName;   //标题名称
    private ImageButton btnSet;   //设置按钮
	private GridView mMenuGridView;
	private CustomApplication mCustomApplication;
	private ArrayList<HashMap<String, Object>> mArrItem;// 存储功能菜单图标和描述
	private TraceSelectDialog mTraceSelectDialog;		// 网络检测二次选择确认框
	
	AnyChatCoreSDK anyChatSDK;
	private boolean mReceiverTag = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.funcmenu_new);
		ApplyVideoConfig();
		
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		
		InitLayout();
		registerBoradcastReceiver();
	}

	private void InitLayout() {
		this.setTitle("AnyChat功能菜单");
		mCustomApplication = (CustomApplication) getApplication();
		mMenuGridView = (GridView) this.findViewById(R.id.funcmenuGridView);
		btnBack = (ImageButton) this.findViewById(R.id.btnBack);
		titleName = (TextView) this.findViewById(R.id.titleName);
		btnSet = (ImageButton) this.findViewById(R.id.btnSet);

		// 功能菜单名字数组
		String[] arrFuncNames = { getString(R.string.voiceVideoInteraction),
				getString(R.string.textChat), getString(R.string.alphaChannel),
				getString(R.string.fileTransfer), getString(R.string.lovalVideoRecord),
				getString(R.string.serverVideoRecord), getString(R.string.photograph), 
				getString(R.string.videoCall), getString(R.string.udpTrace)};

		// 功能菜单图标
		int[] arrFuncIcons = { R.drawable.menu_av_interaction, R.drawable.menu_text_chat,
				R.drawable.menu_transparent_channel, R.drawable.menu_file_transfer,
				R.drawable.menu_local_record, R.drawable.menu_server_record,
				R.drawable.menu_video_capture, R.drawable.menu_call_center,
				R.drawable.menu_network_assessment};

		mArrItem = new ArrayList<HashMap<String, Object>>();
		for (int index = 0; index < arrFuncNames.length; ++index) {
			HashMap<String, Object> itemMap = new HashMap<String, Object>();
			itemMap.put("ItemImage", arrFuncIcons[index]);
			itemMap.put("ItemText", arrFuncNames[index]);
			mArrItem.add(itemMap);
		}

		SimpleAdapter sMenuItemAdapter = new SimpleAdapter(this, mArrItem,
				R.layout.funcmenu_cell,
				new String[] { "ItemImage", "ItemText" }, new int[] {
						R.id.funcItemImage, R.id.funcItemText });

		mMenuGridView.setAdapter(sMenuItemAdapter);
		mMenuGridView.setOnItemClickListener(onListClickListener);
		titleName.setText("功能列表");
		btnBack.setOnClickListener(onClickListener);
		btnSet.setOnClickListener(onClickListener);
	}

	OnItemClickListener onListClickListener = new OnItemClickListener() {

		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			//网络检测二次选择确认框
			if (arg2 + 1 == FUNC_UDPTRACE) {
				if (mTraceSelectDialog != null && mTraceSelectDialog.isShowing()) {	
					return;
				}
				
				mTraceSelectDialog = new TraceSelectDialog(FuncMenu.this, onClickListener);
				mTraceSelectDialog.showAtLocation(FuncMenu.this.findViewById(R.id.funcmenuGridView),
						Gravity.CENTER|Gravity.CENTER_HORIZONTAL, 0, 0);
								
				return;
			}
			
			// 不同的功能模块进入不同的房间，从1开始，1~7房间，如语音视频聊天进入1号房间，文字聊天进入2号房间。。。
			mCustomApplication.setCurOpenFuncUI(arg2 + 1);
			openRolesListActivity(arg2 + 1);
		}
	};

	private short curSelcetTraceIndex;
	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.btnBack:
				destroyCurActivity();
				break;
				case R.id.btnSet:
					Intent intents = new Intent();
					intents.setClass(FuncMenu.this, VideoConfig.class);
					startActivityForResult(intents, ACTIVITY_ID_VIDEOCONFIG);
				break;

				// 网络检测选择二次框确定按钮
			case R.id.udpTraceConfirm:
				curSelcetTraceIndex = mTraceSelectDialog.getCurSelectTraceRole();
				int roomId = mTraceSelectDialog.getRoomId();
				if(roomId==-1){
					Toast.makeText(FuncMenu.this, "请输入房间号", Toast.LENGTH_SHORT).show();
					return;
				}
				anyChatSDK.EnterRoom(roomId, "");
				mTraceSelectDialog.dismiss();
				mTraceSelectDialog = null;
				break;
				// 网络检测选择二次框取消按钮
			case R.id.udpTraceCancel:
				//设置背景颜色变亮
//				WindowManager.LayoutParams lp = getWindow().getAttributes();
//				lp.alpha = 1f;
//				getWindow().setAttributes(lp);

				mTraceSelectDialog.dismiss();
				mTraceSelectDialog = null;
				break;
			default:
				break;
			}			
		}
	};
	
	// 打开对应功能房间的用户列表
	private void openRolesListActivity(int sEnterRoomID) {
		Intent intent = new Intent(this, RolesListActivity.class);
		intent.putExtra("roomID", sEnterRoomID);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK
				| Intent.FLAG_ACTIVITY_CLEAR_TOP);
		startActivity(intent);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		if (resultCode == RESULT_OK && requestCode == ACTIVITY_ID_VIDEOCONFIG ) {
			ApplyVideoConfig();
		}
	}

	// 根据配置文件配置视频参数
	private void ApplyVideoConfig() {
		ConfigEntity configEntity = ConfigService.LoadConfig(this);
		if (configEntity.mConfigMode == 1) // 自定义视频参数配置
		{
			// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL,
					configEntity.mVideoBitrate);
			if (configEntity.mVideoBitrate == 0) {
				// 设置本地视频编码的质量
				AnyChatCoreSDK.SetSDKOptionInt(
						AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL,
						configEntity.mVideoQuality);
			}
			// 设置本地视频编码的帧率
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL,
					configEntity.mVideoFps);
			// 设置本地视频编码的关键帧间隔
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL,
					configEntity.mVideoFps);
			// 设置本地视频采集分辨率
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL,
					configEntity.mResolutionWidth);
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL,
					configEntity.mResolutionHeight);
			// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL,
					configEntity.mVideoPreset);
		}
		// 让视频参数生效
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM,
				configEntity.mConfigMode);
		// P2P设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC,
				configEntity.mEnableP2P);
		// 本地视频Overlay模式设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY,
				configEntity.mVideoOverlay);
		// 回音消除设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL,
				configEntity.mEnableAEC);
		// 平台硬件编码设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC,
				configEntity.mUseHWCodec);
		// 视频旋转模式设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL,
				configEntity.mVideoRotateMode);
		// 本地视频采集偏色修正设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA,
				configEntity.mFixColorDeviation);
		// 视频GPU渲染设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER,
				configEntity.mVideoShowGPURender);
		// 本地视频自动旋转设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
				configEntity.mVideoAutoRotation);
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

	// 注册广播
	public void registerBoradcastReceiver() {
		if (!mReceiverTag){
			IntentFilter myIntentFilter = new IntentFilter();
			myIntentFilter.addAction("NetworkDiscon");
			// 注册广播
			this.registerReceiver(mBroadcastReceiver, myIntentFilter);
			mReceiverTag = true;
		}
	}

	private void destroyCurActivity() {
		this.setResult(RESULT_OK);
		//onPause();
		onDestroy();
		finish();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		unRegisterReceiver();
		if(anyChatSDK != null)
		anyChatSDK.removeEvent(this);
	}

	@Override
	protected void onPause() {
		super.onPause();
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
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK){
			this.setResult(RESULT_OK);			
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
		if(dwErrorCode==0) {
			Intent intent = new Intent();
			if (curSelcetTraceIndex == 0) {
				intent.setClass(FuncMenu.this, SenderTrace.class);
			} else {
				intent.setClass(FuncMenu.this, ReceiverTrace.class);
			}
//				//设置背景颜色变亮
//				WindowManager.LayoutParams lps = getWindow().getAttributes();
//				lps.alpha = 1f;
//				getWindow().setAttributes(lps);
			startActivity(intent);
		}else{
			anyChatSDK.LeaveRoom(-1);
			Toast.makeText(FuncMenu.this,"进入房间失败，请重新操作",Toast.LENGTH_SHORT).show();
		}
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub
		
	}

	// 网络断开
	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 销毁当前界面
		destroyCurActivity();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
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
