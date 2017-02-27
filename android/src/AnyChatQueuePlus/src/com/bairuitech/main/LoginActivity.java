package com.bairuitech.main;

import java.util.ArrayList;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.common.ScreenInfo;
import com.bairuitech.common.ValueUtils;
import com.example.anychatqueueplusplus.R;
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
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class LoginActivity extends Activity implements AnyChatBaseEvent, AnyChatObjectEvent, OnItemSelectedListener {
	private String mStrIP = "demo.anychat.cn"; // 默认ip
	private String mStrName = "Tom"; // 自定义
	private int mSPort = 8906; // 端口
	private final int SHOWLOGINSTATEFLAG = 1; // 显示的按钮是登陆状态的标识
	private final int SHOWWAITINGSTATEFLAG = 2; // 显示的按钮是等待状态的标识
	private final int LOCALVIDEOAUTOROTATION = 1; // 本地视频自动旋转控制
	private final int ACTIVITY_ID_MAINUI = 1; // MainActivity的id标致，onActivityResult返回
	private int mUserTypeCode; // 0代表是进入客户界面，2代表是接入座席界面
	private EditText mEditIP; // ip
	private EditText mEditPort; // 端口
	private EditText mEditName; // 用户名
	private TextView mBottomConnMsg; // 连接服务器状态
	private TextView mBottomBuildMsg; // 版本编译信息
	private Button mBtnStart; // 开始登录
	private Button mBtnWaiting; // 登陆等待状态
	private LinearLayout mWaitingLayout; // 登录加载层
	private LinearLayout mProgressLayout; // 加载动画层
	private CustomApplication mCustomApplication; // 存储全局变量
	private Toast mToast;
	private RadioGroup rg;
	public AnyChatCoreSDK anyChatSDK;

	// 新增信息设置功能
	private String mQueueTypeJson = "";

	private Spinner spUserSetting;// 信息设置
	private String settingArr[] = { "客户端设置","服务端设置" };
	private int mUserSetting = 0;// 被选中的下标

	private Spinner spModeAuto;// 自动路由
	private String autoModeArr[] = { "开启","关闭" };
	private int autoModeIndex = 0;// 被选中的下标

	private Spinner spModeAutoStrategy;// 路由策略
	private String modeStrategy[] = { "队列组", "技能组" };
	private int modeStrategyIndex = 0;// 被选中的下标

	private View viewClientSetting;// 客户端设置容器
	private LinearLayout viewAgentContainer;// 坐席设置的容器

	private LinearLayout teamContainer;// 队列容器
	private ArrayList<CheckBox> teamCbs = new ArrayList<CheckBox>();

	private LinearLayout techContainer;// 技能组容器
	private ArrayList<CheckBox> techCbs = new ArrayList<CheckBox>();

	/**
	 * 初始化
	 */
	private void InitAgentLayout() {
		// 1.初始化spanner
		spUserSetting = (Spinner) findViewById(R.id.spanner_user_setting);// 信息设置
		ArrayAdapter<String> userSettingAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item,
				settingArr);
		userSettingAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spUserSetting.setAdapter(userSettingAdapter);

		spModeAuto = (Spinner) findViewById(R.id.sp_mode_auto);// 自动路由
		ArrayAdapter<String> modeAutoAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item,
				autoModeArr);
		modeAutoAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spModeAuto.setAdapter(modeAutoAdapter);

		spModeAutoStrategy = (Spinner) findViewById(R.id.sp_mode_strategy);// 路由策略
		ArrayAdapter<String> modeStrategyAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item,
				modeStrategy);
		modeStrategyAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spModeAutoStrategy.setAdapter(modeStrategyAdapter);

		// 2.初始化容器
		viewAgentContainer = (LinearLayout) findViewById(R.id.ll_agent_container);
		teamContainer = (LinearLayout) findViewById(R.id.ll_team_queue);
		techContainer = (LinearLayout) findViewById(R.id.ll_tech_queue);
		viewClientSetting = findViewById(R.id.ll_client_setting);

		for (int i = 0; i < teamContainer.getChildCount(); i++) {
			teamCbs.add((CheckBox) teamContainer.getChildAt(i));
		}
		for (int i = 0; i < techContainer.getChildCount(); i++) {
			techCbs.add((CheckBox) techContainer.getChildAt(i));
		}

		// 3.设置事件监听
		spUserSetting.setOnItemSelectedListener(this);
		spModeAuto.setOnItemSelectedListener(this);
		spModeAutoStrategy.setOnItemSelectedListener(this);
	}

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);

		setDisPlayMetrics();
		mCustomApplication = (CustomApplication) getApplication();

		InitSDK();
		InitLayout();
		// 初始化
		InitAgentLayout();
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
		anyChatSDK.SetBaseEvent(this);// 基本事件
		anyChatSDK.SetObjectEvent(this);// 营业厅排队事件
		anyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);// 初始化sdk

		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION, LOCALVIDEOAUTOROTATION);
	}

	// 初始化布局层
	private void InitLayout() {
		mEditIP = (EditText) this.findViewById(R.id.mainUIEditIP);
		mEditPort = (EditText) this.findViewById(R.id.mainUIEditPort);
		mEditName = (EditText) this.findViewById(R.id.main_et_name);
		mBottomConnMsg = (TextView) this.findViewById(R.id.mainUIbottomConnMsg);
		mBottomBuildMsg = (TextView) this.findViewById(R.id.mainUIbottomBuildMsg);
		mBtnStart = (Button) this.findViewById(R.id.mainUIStartBtn);
		mBtnWaiting = (Button) this.findViewById(R.id.mainUIWaitingBtn);
		mWaitingLayout = (LinearLayout) this.findViewById(R.id.waitingLayout);

		mBottomConnMsg.setText("No content to the server");

		// 初始化bottom_tips信息
		mBottomBuildMsg.setText(" V" + anyChatSDK.GetSDKMainVersion() + "." + anyChatSDK.GetSDKSubVersion()
				+ "  Build time: " + anyChatSDK.GetSDKBuildTime());

		mBottomBuildMsg.setGravity(Gravity.CENTER_HORIZONTAL);
		mBtnStart.setOnClickListener(OnClickListener);
		rg = (RadioGroup) findViewById(R.id.id_rg_btn);
		rg.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				if (checkedId == R.id.customer) {
					mUserTypeCode = 0;
					viewAgentContainer.setVisibility(View.GONE);
				} else {
					mUserTypeCode = 2;
					viewAgentContainer.setVisibility(View.VISIBLE);
				}
			}
		});
	}

	OnClickListener OnClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			// 登录
			case R.id.mainUIStartBtn:
				mStrName = mEditName.getText().toString().trim();
				mStrIP = mEditIP.getText().toString().trim();
				mSPort = Integer.parseInt(mEditPort.getText().toString().trim());

				if (checkInputData()) {
					setBtnVisible(SHOWWAITINGSTATEFLAG);
					/**
					 * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
					 * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
					 * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
					 */
					anyChatSDK.Connect(mStrIP, mSPort); // 连接服务器

					/***
					 * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
					 * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=
					 * 2211&highlight=%C7%A9%C3%FB
					 */
					anyChatSDK.Login(mStrName, "");// 登录
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
		mStrIP = preferences.getString("UserIP", "demo.anychat.cn");
		mStrName = preferences.getString("UserName", "Android");
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
		}

		// 设置相关信息
		if (mUserTypeCode == 2) { // 座席
			// 1.判断是服务器设置还是客户端设置
			if (mUserSetting == 0) { // 客户端设置
				if (modeStrategyIndex == 0) {// 队列组
					// 获取所选中元素
					ArrayList<Integer> selects = new ArrayList<Integer>();
					for (int i = 0; i < teamCbs.size(); i++) {
						if (teamCbs.get(i).isChecked()) {
							selects.add(Integer.valueOf("200" + (i+1)));
						}
					}
					if (selects.size() == 0) {
						Toast.makeText(this, "没有选择队列分组", Toast.LENGTH_SHORT).show();
						return false;
					} else {
						int flag = mUserTypeCode;
						if (autoModeIndex == 0) {
							flag += AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AUTOMODE;
						}
                        mQueueTypeJson = "{\"flags\":" + flag + ",\"priority\":10,\"queuegroups\":" + selects.toString() + "}";
					}
				} else {// 技能组
						// 获取选中的元素
					ArrayList<Integer> selects = new ArrayList<Integer>();
					for (int i = 0; i < techCbs.size(); i++) {
						if (techCbs.get(i).isChecked()) {
							selects.add(Integer.valueOf("100" + (i+1)));
						}
					}
					if (selects.size() == 0) {
						Toast.makeText(this, "没有选择技能分组", Toast.LENGTH_SHORT).show();
						return false;
					} else {
						int flag = mUserTypeCode;
						if (autoModeIndex == 0) {
							flag += AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AUTOMODE;
						}
                        mQueueTypeJson = "{\"flags\":" + flag + ",\"priority\":10,\"skillgroups\":" + selects.toString() + "}";
					}
				}
			}
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
			LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT,
					LayoutParams.WRAP_CONTENT);
			params.setMargins(5, 5, 5, 5);
			ProgressBar progressBar = new ProgressBar(this, null, android.R.attr.progressBarStyleLarge);
			mProgressLayout.addView(progressBar, params);
			mProgressLayout.setVisibility(View.GONE);
			mWaitingLayout.addView(mProgressLayout, new LayoutParams(params));
		}
	}

	// 对键盘显示进行控制
	private void hideKeyboard() {
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		if (imm.isActive()) {
			imm.hideSoftInputFromWindow(getCurrentFocus().getApplicationWindowToken(),
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

			// 保存用户id和用户角色信息
			mCustomApplication.setSelfUserName(mEditName.getText().toString());
			mCustomApplication.setUserID(dwUserId);
			mCustomApplication.setUserType(mUserTypeCode);
			mBottomConnMsg.setText("Connect to the server success.");

			Intent intent = new Intent(LoginActivity.this, FuncMenuActivity.class);

			intent.putExtra("userSetting", mUserSetting);// 1服务端设置，0客户端设置
            intent.putExtra("autoMode", autoModeIndex);// 1关闭，0开启
			intent.putExtra("modeStrategy", modeStrategyIndex);// 0:队列，1技能
			intent.putExtra("queueTypeJson", mQueueTypeJson);
			intent.putExtra("dwUserId", dwUserId);
			intent.putExtra("userTypeCode", mUserTypeCode);//账户类型(客户、坐席)
			startActivity(intent);
			setBtnVisible(SHOWLOGINSTATEFLAG);
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
					mToast = Toast.makeText(LoginActivity.this, "网络已断开!", Toast.LENGTH_SHORT);
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
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2,
			int dwParam3, int dwParam4, String strParam) {

	}

	@Override
	public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
		// 1.用户设置
		if (parent == spUserSetting) {
            mUserSetting = position;
			if (position == 1) {// 服务端设置
				viewClientSetting.setVisibility(View.GONE);
			} else {
				viewClientSetting.setVisibility(View.VISIBLE);
			}
		}
		// 2.路由模式
		if (parent == spModeAuto) {
			autoModeIndex = position;
		}
		// 3.路由策略
		if (parent == spModeAutoStrategy) {
			modeStrategyIndex = position;
			if (position == 0) {
				teamContainer.setVisibility(View.VISIBLE);
				techContainer.setVisibility(View.GONE);
			} else {
				teamContainer.setVisibility(View.GONE);
				techContainer.setVisibility(View.VISIBLE);
			}
		}
	}

	@Override
	public void onNothingSelected(AdapterView<?> arg0) {

	}

}
