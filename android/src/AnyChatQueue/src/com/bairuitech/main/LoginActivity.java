package com.bairuitech.main;





import java.util.HashMap;

import org.json.JSONException;
import org.json.JSONObject;

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
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.View.OnClickListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class LoginActivity extends Activity implements AnyChatBaseEvent,AnyChatObjectEvent {
	private String mStrIP = "cluster.anychat.cn";		//默认ip
	private String mStrName = "Tom";				//自定义
	private int mSPort = 8906;						//端口
	private String mStrGuid;						
	private int index = 0;
	private static final int REQUEST_SIGNED = 1;
	private final int SHOWLOGINSTATEFLAG = 1; 		// 显示的按钮是登陆状态的标识
	private final int SHOWWAITINGSTATEFLAG = 2; 	// 显示的按钮是等待状态的标识
	private final int LOCALVIDEOAUTOROTATION = 1; 	// 本地视频自动旋转控制
	private final int ACTIVITY_ID_MAINUI = 1; 	    // MainActivity的id标致，onActivityResult返回
	private int USER_TYPE_ID; 					//0代表是进入客户界面，2代表是接入座席界面
	private static final String url = "http://192.168.6.116:8980";
	private EditText mEditGuid;						//Guid
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
	private Spinner spinner;
	
	private static final int REQUEST_SUCESS = 1;
	private Handler handler = new Handler(){
		public void handleMessage(Message msg) {
			if(msg.what == REQUEST_SIGNED){
				JSONObject object;
				try {
					object = new JSONObject(msg.obj.toString());
					int errCode = object.optInt("errorcode");
					int timeStamp = object.optInt("timestamp");
					String signedStr = object.optString("sigStr");
					if(errCode == 0){
						anyChatSDK.LoginEx(mStrName,1001, "1001", mStrName, timeStamp, signedStr,"");
					}
					
				} catch (JSONException e) {
					e.printStackTrace();
				}
				
			}
		};
	};

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
			anyChatSDK = AnyChatCoreSDK.getInstance(LoginActivity.this);
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
		mEditGuid = (EditText) findViewById(R.id.main_et_guid);
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
		
		
		spinner = (Spinner) findViewById(R.id.spinner);
		String[] arr = {"普通登录","签名登录"};
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(LoginActivity.this, android.R.layout.simple_spinner_item, arr);
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spinner.setAdapter(adapter);
		spinner.setSelection(0);
		spinner.setOnItemSelectedListener(new OnItemSelectedListener() {

			@Override
			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				// TODO Auto-generated method stub
				if(arg2 == 0){
					index = 0;
				}else if(arg2 == 1){
					index = 1;
				}
				
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub
				index = 0;
			}
		});
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
				setBtnVisible(SHOWWAITINGSTATEFLAG);
				mStrName = mEditName.getText().toString().trim();
				mStrIP = mEditIP.getText().toString().trim();
				mSPort = Integer.parseInt(mEditPort.getText().toString()
						.trim());
				//设置GUID
				mStrGuid = mEditGuid.getText().toString().trim();
				
				if(index == 0){
					if (checkInputData()) {
						
						if(!TextUtils.isEmpty(mStrGuid)){
							AnyChatCoreSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_CLOUD_APPGUID, mStrGuid);
						}
						//连接服务器
						anyChatSDK.Connect(mStrIP, mSPort);
						anyChatSDK.Login(mStrName, "");//登录
					}
				}else if(index == 1){
					if(!TextUtils.isEmpty(mStrGuid)){
						AnyChatCoreSDK.SetSDKOptionString(AnyChatDefine.BRAC_SO_CLOUD_APPGUID, mStrGuid);
					}
					if(null != mStrGuid && !mStrGuid.equals("")){
						final HashMap<String, String> map = new HashMap<String, String>();
						map.put("userid","1001");
						map.put("strUserid", "1001");
						map.put("appid", "90A9545C-30F7-4F5A-8B56-9CB111706A24");
						
						new Thread(){
							public void run() {
								
								String result = HttpUtil.httpRequestPost(url, map);
								
								if(null == result){
									System.out.println("请求失败");
								}else{
									Message msg = Message.obtain(handler,REQUEST_SIGNED,result);
									handler.sendMessage(msg);
									System.out.println(result);
								}
							};
						}.start();
					}else{
						setBtnVisible(SHOWLOGINSTATEFLAG);
						Toast.makeText(LoginActivity.this,"appId不能为空",Toast.LENGTH_LONG).show();
					}
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
		mEditGuid.setText(mStrGuid);
	}

	// 读取登陆数据
	private void readLoginDate() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		mStrIP = preferences.getString("UserIP", "cloud.anychat.cn");
		mStrName = preferences.getString("UserName", "Android");
		mSPort = preferences.getInt("UserPort", 8906);
		mStrGuid = preferences.getString("userGuid","fbe957d1-c25a-4992-9e75-d993294a5d56");
	}

	// 保存登陆相关数据
	private void saveLoginData() {
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		Editor preferencesEditor = preferences.edit();
		preferencesEditor.putString("UserIP", mStrIP);
		preferencesEditor.putString("UserName", mStrName);
		preferencesEditor.putInt("UserPort", mSPort);
		preferencesEditor.putString("userGuid", mStrGuid);
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
			
			Intent intent = new Intent(LoginActivity.this,FuncMenuActivity.class);
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
					mToast = Toast.makeText(LoginActivity.this, "网络已断开!",
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
