package com.example.login;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.anychatselfrecord.R;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;
import com.example.common.ScreenInfo;
import com.example.common.ValueUtils;
import com.example.funcActivity.CSingleVideo;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Gallery.LayoutParams;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

public class CLogin extends Activity implements AnyChatBaseEvent {
	private final int LOCALVIDEOAUTOROTATION = 1; 	// 本地视频自动旋转控制
	private final int SHOWLOGINSTATEFLAG = 1; 		// 显示的按钮是登陆状态的标识
	private final int SHOWWAITINGSTATEFLAG = 2; 	// 显示的按钮是等待状态的标识

	private AnyChatCoreSDK mAnyChatSDK;
	CustomApplication mCustomApplication;

	private EditText mNameEdit; // 用户名
	private EditText mIPEdit;   // ip
	private EditText mPortEdit; // 端口
	private TextView mBuildMsg; // 版本信息
	private Button mBtnStart;
	private Button mBtnWaiting;
	private LinearLayout mWaitingLayout;
	private LinearLayout mProgressLayout;
	private String mStrIP = "demo.anychat.cn";
	private String mStrName = "name";
	private int mPort = 8906;
	private final int mDefaultRoomID = 1;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_login);
		mCustomApplication = (CustomApplication)getApplication();
		
		InitSDK();
		InitLayout();
		// 读取登录配置表
		readLoginData();
		// 初始化登录配置数据
		initLoginConfig();
		initWaitingTips();

		registerBoradcastReceiver();
		setDisPlayMetrics();
		
		BaseMethod.addActivityToList(this);
	}

	// 初始化SDK
	private void InitSDK() {
		if (mAnyChatSDK == null) {
			mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
			mAnyChatSDK.SetBaseEvent(this);
			mAnyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
					LOCALVIDEOAUTOROTATION);
		}
	}

	// 初始化层
	private void InitLayout() {
		mIPEdit = (EditText) findViewById(R.id.login_ip);
		mNameEdit = (EditText) findViewById(R.id.login_name);
		mPortEdit = (EditText) findViewById(R.id.login_port);
		mBuildMsg = (TextView) findViewById(R.id.buildMsg);
		mBtnStart = (Button) findViewById(R.id.mainUIStartBtn);
		mBtnWaiting = (Button) findViewById(R.id.mainUIWaitingBtn);
		mWaitingLayout = (LinearLayout) findViewById(R.id.waitingLayout);

		// 版本信息
		mBuildMsg.setText("V" + mAnyChatSDK.GetSDKMainVersion() + "."
				+ mAnyChatSDK.GetSDKSubVersion() + " Build time: "
				+ mAnyChatSDK.GetSDKBuildTime());
		mBuildMsg.setGravity(Gravity.CENTER_HORIZONTAL);

		mBtnStart.setOnClickListener(onClickListener);
	}

	private void initLoginConfig() {
		mIPEdit.setText(mStrIP);
		mNameEdit.setText(mStrName);
		mPortEdit.setText(String.valueOf(mPort));
	}
	
	private void setDisPlayMetrics() {
		DisplayMetrics dMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dMetrics);
		ScreenInfo.WIDTH = dMetrics.widthPixels;
		ScreenInfo.HEIGHT = dMetrics.heightPixels;
	}
	// 读取登录数据
	private void readLoginData() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		mStrName = preferences.getString("UserName", "Android01");
		mStrIP = preferences.getString("UserIP", "demo.anychat.cn");
		mPort = preferences.getInt("UserPort", 8906);
	}

	// 登录成功后保存相关数据
	private void saveLoginData() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		Editor preferencesEditor = preferences.edit();
		preferencesEditor.putString("UserIP", mStrIP);
		preferencesEditor.putString("UserName", mStrName);
		preferencesEditor.putInt("UserPort", mPort);
		preferencesEditor.commit();
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			if (checkInputData()) {
				setBtnVisible(SHOWWAITINGSTATEFLAG);
				mStrName = mNameEdit.getText().toString().trim();
				mStrIP = mIPEdit.getText().toString().trim();
				mPort = Integer.parseInt(mPortEdit.getText().toString().trim());

				Log.d("AnyChatx", "name:"+mStrName+ "->ip:"+ mStrIP+ "->port"+ mPort);

                /**
                 *AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
                 *连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
                 *连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
                 */
				mAnyChatSDK.Connect(mStrIP, mPort);

                /***
                 * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
                 * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
                 */
				mAnyChatSDK.Login(mStrName, "");
			}
		}
	};

	private boolean checkInputData() {
		String strName = mNameEdit.getText().toString().trim();
		String strIP = mIPEdit.getText().toString().trim();
		String strPortStr = mPortEdit.getText().toString().trim();

		if (ValueUtils.isStrEmpty(strName)) {
			Toast.makeText(this, "请输入姓名", Toast.LENGTH_LONG).show();
			return false;
		} else if (ValueUtils.isStrEmpty(strIP)) {
			Toast.makeText(this, "请输入IP", Toast.LENGTH_LONG).show();
			return false;
		} else if (ValueUtils.isStrEmpty(strPortStr)) {
			Toast.makeText(this, "请输入端口", Toast.LENGTH_LONG).show();
			return false;
		}

		return true;
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

	private void hideKeyboard() {
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		if (imm.isActive()) {
			imm.hideSoftInputFromWindow(getCurrentFocus()
					.getApplicationWindowToken(),
					InputMethodManager.HIDE_NOT_ALWAYS);
		}
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		mAnyChatSDK.LeaveRoom(-1);
		mAnyChatSDK.Logout();
		mAnyChatSDK.removeEvent(this);
		mAnyChatSDK.Release();
		unregisterReceiver(mBroadcastReceiver);
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			BaseMethod.exitVideoDialog(this);
		}

		return super.onKeyDown(keyCode, event);
	}
	
	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		if (dwErrorCode == 0) {
			saveLoginData();
			hideKeyboard();
			mAnyChatSDK.EnterRoom(mDefaultRoomID, "");
		} else {
			setBtnVisible(SHOWLOGINSTATEFLAG);
			Toast.makeText(this, "登录失败：errorCode: " + dwErrorCode,
					Toast.LENGTH_LONG).show();
		}
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		mCustomApplication
		.setCurProcessIndex(CustomApplication.TAKEPHOTO_PROCESS);
		// 进入房间成功
		Intent intent = new Intent();
		intent.setClass(this, CSingleVideo.class);
		startActivity(intent);
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		mAnyChatSDK.LeaveRoom(-1);
		mAnyChatSDK.Logout();
		Toast.makeText(this, "连接关闭，errorCode：" + dwErrorCode, Toast.LENGTH_LONG).show();
	}

	// 广播
	private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.equals("NetworkDiscon")) {
				Toast.makeText(CLogin.this, "网络已断开！", Toast.LENGTH_LONG)
						.show();
				setBtnVisible(SHOWLOGINSTATEFLAG);
				
				mAnyChatSDK.LeaveRoom(-1);
				mAnyChatSDK.Logout();
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
