package com.example.anychatfeatures;

import com.example.anychatfeatures.R;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.common.CustomApplication;
import com.example.common.ScreenInfo;
import com.example.common.ValueUtils;

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
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements AnyChatBaseEvent {
	private String mStrIP = "demo.anychat.cn";
	private String mStrName = "name";
	private int mSPort = 8906;

	private final int SHOWLOGINSTATEFLAG = 1; // 显示的按钮是登陆状态的标识
	private final int SHOWWAITINGSTATEFLAG = 2; // 显示的按钮是等待状态的标识
	private final int LOCALVIDEOAUTOROTATION = 1; // 本地视频自动旋转控制
	private final int ACTIVITY_ID_MAINUI = 1;
	
	private EditText mEditIP;
	private EditText mEditPort;
	private EditText mEditName;
	private TextView mBottomConnMsg;
	private TextView mBottomBuildMsg;
	private Button mBtnStart;
	private Button mBtnLogout;
	private Button mBtnWaiting;
	private LinearLayout mWaitingLayout;
	private LinearLayout mProgressLayout;
	private CustomApplication mCustomApplication;
	private Toast mToast;

	public AnyChatCoreSDK anyChatSDK;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setDisPlayMetrics();

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);

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

	private void InitSDK() {
		if (anyChatSDK == null) {
			anyChatSDK = AnyChatCoreSDK.getInstance(this);
			anyChatSDK.SetBaseEvent(this);
			anyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);

			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
					LOCALVIDEOAUTOROTATION);
		}
	}

	private void InitLayout() {
		mEditIP = (EditText) this.findViewById(R.id.mainUIEditIP);
		mEditPort = (EditText) this.findViewById(R.id.mainUIEditPort);
		mEditName = (EditText) this.findViewById(R.id.main_et_name);
		mBottomConnMsg = (TextView) this.findViewById(R.id.mainUIbottomConnMsg);
		mBottomBuildMsg = (TextView) this
				.findViewById(R.id.mainUIbottomBuildMsg);
		mBtnStart = (Button) this.findViewById(R.id.mainUIStartBtn);
		mBtnLogout = (Button) this.findViewById(R.id.mainUILogoutBtn);
		mBtnWaiting = (Button) this.findViewById(R.id.mainUIWaitingBtn);
		mWaitingLayout = (LinearLayout) this.findViewById(R.id.waitingLayout);

		mBottomConnMsg.setText("No content to the server");
		// 初始化bottom_tips信息
		mBottomBuildMsg.setText(" V" + anyChatSDK.GetSDKMainVersion() + "."
				+ anyChatSDK.GetSDKSubVersion() + "  Build time: "
				+ anyChatSDK.GetSDKBuildTime());
		mBottomBuildMsg.setGravity(Gravity.CENTER_HORIZONTAL);
		mBtnStart.setOnClickListener(OnClickListener);
		mBtnLogout.setOnClickListener(OnClickListener);//现在无用
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

					anyChatSDK.Connect(mStrIP, mSPort);
					anyChatSDK.Login(mStrName, "");
				}
				break;
			//现在无用
			case R.id.mainUILogoutBtn:
				setBtnVisible(SHOWLOGINSTATEFLAG);

				anyChatSDK.Logout();
				mBottomConnMsg.setText("No connnect to the server");
				break;
			default:
				break;
			}
		}
	};

	private void initLoginConfig() {
		mEditIP.setText(mStrIP);
		mEditName.setText(mStrName);
		mEditPort.setText(String.valueOf(mSPort));
	}

	// 读取登陆数据
	private void readLoginDate() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		mStrIP = preferences.getString("UserIP", "demo.anychat.cn");
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
			mBtnLogout.setVisibility(View.GONE);
			mBtnWaiting.setVisibility(View.GONE);

			mProgressLayout.setVisibility(View.GONE);
		} else if (index == SHOWWAITINGSTATEFLAG) {
			mBtnStart.setVisibility(View.GONE);
			mBtnLogout.setVisibility(View.GONE);
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
		
		anyChatSDK.Logout();
		anyChatSDK.Release();
	}

	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		anyChatSDK.SetBaseEvent(this);
		mToast = null;
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		if (!bSuccess) {
			setBtnVisible(SHOWLOGINSTATEFLAG);
			mBottomConnMsg.setText("连接服务器失败，自动重连，请稍后...");
			setBtnVisible(SHOWWAITINGSTATEFLAG);
		}
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		if (dwErrorCode == 0) {
			saveLoginData();
			hideKeyboard();

			mCustomApplication.setUserID(dwUserId);
			mBottomConnMsg.setText("Connect to the server success.");

			Intent intent = new Intent(this, FuncMenu.class);
			startActivityForResult(intent, ACTIVITY_ID_MAINUI);
		} else {
			setBtnVisible(SHOWLOGINSTATEFLAG);
			mBottomConnMsg.setText("登录失败，errorCode：" + dwErrorCode);
		}
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
		setBtnVisible(SHOWLOGINSTATEFLAG);
		mBottomConnMsg.setText("连接关闭，errorCode：" + dwErrorCode);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK && requestCode == ACTIVITY_ID_MAINUI) {
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
				anyChatSDK.Logout();
				setBtnVisible(SHOWLOGINSTATEFLAG);
				mBottomConnMsg.setText("No content to the server");

				if (mToast == null) {
					mToast = Toast.makeText(MainActivity.this, "网络断开",
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
}
