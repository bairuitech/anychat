package com.bairuitech.main;





import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;

import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.common.ScreenInfo;
import com.bairuitech.common.ValueUtils;
import com.example.anychatqueue.R;


import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.View.OnClickListener;

import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class LoginAty extends Activity implements AnyChatBaseEvent,AnyChatObjectEvent {
	private String mStrIP = "www.anychat.cn";
	private String mStrName = "name";
	private int mSPort = 8906;
	
	private final int SHOWLOGINSTATEFLAG = 1; 		// 显示的按钮是登陆状态的标识
	private final int SHOWWAITINGSTATEFLAG = 2; 	// 显示的按钮是等待状态的标识
	private final int LOCALVIDEOAUTOROTATION = 1; 	// 本地视频自动旋转控制
	private final int ACTIVITY_ID_MAINUI = 1; 	    // MainActivity的id标致，onActivityResult返回
	private int USER_TYPE_ID; 					//0代表是进入客户界面，2代表是接入座席界面
	
	private EditText mEditIP;						// ip
	private EditText mEditPort;						// 端口
	private EditText mEditName;						// 用户名
	private TextView mBottomConnMsg;				// 连接服务器状态
	private TextView mBottomBuildMsg;				// 版本编译信息
	private Button mBtnStart;						// 开始登录
	private Button mBtnWaiting;						//登陆等待状态
	private LinearLayout mWaitingLayout;			// 登录加载层
	private LinearLayout mProgressLayout;			// 加载动画层
	private CustomApplication mCustomApplication;	//存储全局变量
	private Toast mToast;				
	private RadioGroup rg;
	
	public AnyChatCoreSDK anyChatSDK;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);

		setDisPlayMetrics();
		mCustomApplication = (CustomApplication) getApplication();

		InitSDK();
		InitLayout();
		// 读取登陆配置表
		readLoginDate();
		// 初始化登陆配置数据
		initLoginConfig();
		initWaitingTips();
		// 注册广播
		registerBoradcastReceiver();
	}

	// 初始化SDK
	private void InitSDK() {
		if (anyChatSDK == null) {
			anyChatSDK = AnyChatCoreSDK.getInstance(LoginAty.this);
		}
			anyChatSDK.SetBaseEvent(this);//基本事件
			anyChatSDK.SetObjectEvent(this);//营业厅排队事件
			anyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);//初始化sdk

			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
					LOCALVIDEOAUTOROTATION);	
	}

	
	// 初始化布局层
	private void InitLayout() {
		mEditIP = (EditText) this.findViewById(R.id.mainUIEditIP);
		mEditPort = (EditText) this.findViewById(R.id.mainUIEditPort);
		mEditName = (EditText) this.findViewById(R.id.main_et_name);
		mBottomConnMsg = (TextView) this.findViewById(R.id.mainUIbottomConnMsg);
		mBottomBuildMsg = (TextView) this
				.findViewById(R.id.mainUIbottomBuildMsg);
		mBtnStart = (Button) this.findViewById(R.id.mainUIStartBtn);
		mBtnWaiting = (Button) this.findViewById(R.id.mainUIWaitingBtn);
		mWaitingLayout = (LinearLayout) this.findViewById(R.id.waitingLayout);

		mBottomConnMsg.setText("No content to the server");
		
		// 初始化bottom_tips信息
		mBottomBuildMsg.setText(" V" + anyChatSDK.GetSDKMainVersion() + "."
				+ anyChatSDK.GetSDKSubVersion() + "  Build time: "
				+ anyChatSDK.GetSDKBuildTime());
		
		mBottomBuildMsg.setGravity(Gravity.CENTER_HORIZONTAL);
		mBtnStart.setOnClickListener(OnClickListener);
		rg = (RadioGroup) findViewById(R.id.id_rg_btn);
		rg.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				USER_TYPE_ID = checkedId == R.id.customer ? 0 : 2;
			}
		});
	}

	OnClickListener OnClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			// 登录
			case R.id.mainUIStartBtn:
				if (checkInputData()) {
					setBtnVisible(SHOWWAITINGSTATEFLAG);
					mStrName = mEditName.getText().toString().trim();
					mStrIP = mEditIP.getText().toString().trim();
					mSPort = Integer.parseInt(mEditPort.getText().toString()
							.trim());

					//连接服务器
					anyChatSDK.Connect(mStrIP, mSPort);
				}
				break;
			default:
				break;
			}
		}
	};

	// 设置默认数据
	private void initLoginConfig() {
		mEditIP.setText(mStrIP);
		mEditName.setText(mStrName);
		mEditPort.setText(String.valueOf(mSPort));
	}

	// 读取登陆数据
	private void readLoginDate() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		mStrIP = preferences.getString("UserIP", "www.anychat.cn");
		mStrName = preferences.getString("UserName", "name");
		mSPort = preferences.getInt("UserPort", 8906);
	}

	// 保存登陆相关数据
	private void saveLoginData() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		Editor preferencesEditor = preferences.edit();
		preferencesEditor.putString("UserIP", mStrIP);
		preferencesEditor.putString("UserName", mStrName);
		preferencesEditor.putInt("UserPort", mSPort);
		preferencesEditor.commit();
	}

	// 判断ip、端口和姓名是否是空
	private boolean checkInputData() {
		String ip = mEditIP.getText().toString().trim();
		String port = mEditPort.getText().toString().trim();
		String name = mEditName.getText().toString().trim();

		if (ValueUtils.isStrEmpty(ip)) {
			mBottomConnMsg.setText("请输入IP");
			return false;
		} else if (ValueUtils.isStrEmpty(port)) {
			mBottomConnMsg.setText("请输入端口号");
			return false;
		} else if (ValueUtils.isStrEmpty(name)) {
			mBottomConnMsg.setText("请输入姓名");
			return false;
		} else {
			return true;
		}
	}

	// 控制登陆，等待和登出按钮状态
	private void setBtnVisible(int index) {
		if (index == SHOWLOGINSTATEFLAG) {
			mBtnStart.setVisibility(View.VISIBLE);
			mBtnWaiting.setVisibility(View.GONE);

			mProgressLayout.setVisibility(View.GONE);
		} else if (index == SHOWWAITINGSTATEFLAG) {
			mBtnStart.setVisibility(View.GONE);
			mBtnWaiting.setVisibility(View.VISIBLE);

			mProgressLayout.setVisibility(View.VISIBLE);
		}
	}

	// init登陆等待状态UI
	private void initWaitingTips() {
		if (mProgressLayout == null) {
			mProgressLayout = new LinearLayout(this);
			mProgressLayout.setOrientation(LinearLayout.HORIZONTAL);
			mProgressLayout.setGravity(Gravity.CENTER_VERTICAL);
			mProgressLayout.setPadding(1, 1, 1, 1);
			LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
					LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
			params.setMargins(5, 5, 5, 5);
			ProgressBar progressBar = new ProgressBar(this, null,
					android.R.attr.progressBarStyleLarge);
			mProgressLayout.addView(progressBar, params);
			mProgressLayout.setVisibility(View.GONE);
			mWaitingLayout.addView(mProgressLayout, new LayoutParams(params));
		}
	}

	// 对键盘显示进行控制
	private void hideKeyboard() {
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		if (imm.isActive()) {
			imm.hideSoftInputFromWindow(getCurrentFocus()
					.getApplicationWindowToken(),
					InputMethodManager.HIDE_NOT_ALWAYS);
		}
	}

	private void setDisPlayMetrics() {
		DisplayMetrics dMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dMetrics);
		ScreenInfo.WIDTH = dMetrics.widthPixels;
		ScreenInfo.HEIGHT = dMetrics.heightPixels;
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	
	protected void onDestroy() {
		super.onDestroy();
		anyChatSDK.LeaveRoom(-1);
		anyChatSDK.Logout();
		anyChatSDK.Release();
		unregisterReceiver(mBroadcastReceiver);
	}

	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		anyChatSDK.SetObjectEvent(this);
		mToast = null;
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		if (!bSuccess) {
			setBtnVisible(SHOWLOGINSTATEFLAG);
			mBottomConnMsg.setText("连接服务器失败，自动重连，请稍后...");
			setBtnVisible(SHOWWAITINGSTATEFLAG);
		}
		anyChatSDK.Login(mStrName, "");
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// 连接成功
		
		if (dwErrorCode == 0) {
			saveLoginData();
			hideKeyboard();
			
			//保存用户id和用户角色信息
			mCustomApplication.setSelfUserName(mEditName.getText()
					.toString());
			mCustomApplication.setUserID(dwUserId);
			mCustomApplication.setUserType(USER_TYPE_ID);
			mBottomConnMsg.setText("Connect to the server success.");
			//初始化业务对象属性身份
			InitClientObjectInfo(dwUserId);	
			
			Intent intent = new Intent(LoginAty.this,FuncMenuAty.class);
			startActivity(intent);	
			
			setBtnVisible(SHOWLOGINSTATEFLAG);
		} else {
			
			setBtnVisible(SHOWLOGINSTATEFLAG);
			mBottomConnMsg.setText("登录失败，errorCode：" + dwErrorCode);
		}
	}


	//初始化服务对象事件；触发回调OnAnyChatObjectEvent函数
	private void InitClientObjectInfo(int dwUserId) {
		//业务对象身份初始化；0代表普通客户，2是代表座席 (USER_TYPE_ID)
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_OBJECT_INITFLAGS, USER_TYPE_ID);
		//业务对象优先级设定；
		int dwPriority = 10;
		AnyChatCoreSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER,dwUserId,AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		//业务对象属性设定,必须是-1；
		int dwAttribute = -1;
		AnyChatCoreSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER, dwUserId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwAttribute);
		// 向服务器发送数据同步请求指令
		AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, AnyChatObjectDefine.ANYCHAT_INVALID_OBJECT_ID, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_SYNCDATA, dwUserId, 0, 0, 0, "");	
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

	// 网络端口
	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		setBtnVisible(SHOWLOGINSTATEFLAG);
		anyChatSDK.LeaveRoom(-1);
		anyChatSDK.Logout();
		mBottomConnMsg.setText("连接关闭，errorCode：" + dwErrorCode);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK && requestCode == ACTIVITY_ID_MAINUI) {
			anyChatSDK.LeaveRoom(-1);
			anyChatSDK.Logout();
			setBtnVisible(SHOWLOGINSTATEFLAG);
			mBottomConnMsg.setText("No content to the server");
		}
	}
	
	// 广播
	private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.equals("NetworkDiscon")) {
				anyChatSDK.LeaveRoom(-1);
				anyChatSDK.Logout();
				setBtnVisible(SHOWLOGINSTATEFLAG);
				mBottomConnMsg.setText("No content to the server");
				if (mToast == null) {
					mToast = Toast.makeText(LoginAty.this, "网络已断开!",
							Toast.LENGTH_SHORT);
					mToast.show();
				}
			}
		}
	};

	public void registerBoradcastReceiver() {
		IntentFilter myIntentFilter = new IntentFilter();
		myIntentFilter.addAction("NetworkDiscon");
		// 注册广播
		registerReceiver(mBroadcastReceiver, myIntentFilter);
	}

	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {

	}



	
}
