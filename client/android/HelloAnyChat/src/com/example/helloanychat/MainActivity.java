package com.example.helloanychat;

import java.util.ArrayList;
import java.util.List;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements AnyChatBaseEvent {
	public AnyChatCoreSDK anyChatSDK;

	private ListView role_listView;
	private EditText edit_ip;
	private EditText edit_port;
	private EditText edit_name;
	private EditText edit_hourseID;
	private TextView bottom_connState;
	private TextView bottom_tips;
	private Button btn_start;
	private Button btn_logout;
	private Button btn_waiting;

	private List<RoleInfo> roleInfoList = new ArrayList<RoleInfo>();
	private RoleListAdapter adapter;

	private boolean bNeedRelease = false;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);

		InitSDK();
		initViews();
	}

	private void InitSDK() {
		if (anyChatSDK == null) {
			anyChatSDK = new AnyChatCoreSDK();
			anyChatSDK.SetBaseEvent(this);
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_CORESDK_USEARMV6LIB, 1);
			anyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);

			// 视频采集驱动设置
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER, 3);
			// 视频显示驱动设置
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL, 5);
			// 音频播放驱动设置
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_AUDIO_PLAYDRVCTRL, 3);
			// 音频采集驱动设置
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_AUDIO_RECORDDRVCTRL, 3);

			bNeedRelease = true;
		}
	}

	private void initViews() {
		role_listView = (ListView) this.findViewById(R.id.role_listview);
		edit_ip = (EditText) this.findViewById(R.id.main_et_ip);
		edit_port = (EditText) this.findViewById(R.id.main_et_port);
		edit_name = (EditText) this.findViewById(R.id.main_et_name);
		edit_hourseID = (EditText) this.findViewById(R.id.main_et_hourseID);
		bottom_connState =(TextView)this.findViewById(R.id.main_bottom_connState);
		bottom_tips = (TextView) this.findViewById(R.id.main_bottom_tips);
		btn_start = (Button) this.findViewById(R.id.main_btn_start);
		btn_logout = (Button) this.findViewById(R.id.main_btn_logout);
		btn_waiting = (Button)this.findViewById(R.id.main_btn_waiting);
	
		role_listView.setDivider(null);
		bottom_connState.setText("Not content to the server");
		//初始化bottom_tips信息
		bottom_tips.setText(" V" + anyChatSDK.GetSDKMainVersion()
				+ "."+ anyChatSDK.GetSDKSubVersion() +"  Build time: "+anyChatSDK.GetSDKBuildTime());
		bottom_tips.setGravity(Gravity.CENTER_HORIZONTAL);
		btn_start.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if (checkInputData()) {
					//setLoginPicRun(true);
					
					setBtnVisible(2);
					
					String strIP = edit_ip.getEditableText().toString();
					int sPort = Integer.parseInt(edit_port.getEditableText()
							.toString());
					String roleName = edit_name.getEditableText().toString();
					anyChatSDK.Connect(strIP, sPort);
					anyChatSDK.Login(roleName, "");
					
				}
			}
		});
		
		btn_logout.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				setBtnVisible(1);
				anyChatSDK.Logout();
				role_listView.setAdapter(null);
				bottom_connState.setText("Not connnect to the server");
			}
		});
	}

	private boolean checkInputData() {
		String ip = edit_ip.getText().toString().trim();
		String port = edit_port.getText().toString().trim();
		String name = edit_name.getText().toString().trim();
		String hourseID = edit_hourseID.getText().toString().trim();

		if (ValueUtils.isStrEmpty(ip)) {
			bottom_connState.setText("请输入IP");
			return false;
		} else if (ValueUtils.isStrEmpty(port)) {
			bottom_connState.setText("请输入端口号");
			return false;
		} else if (ValueUtils.isStrEmpty(name)) {
			bottom_connState.setText("请输入姓名");
			return false;
		} else if (ValueUtils.isStrEmpty(hourseID)) {
			bottom_connState.setText("请输入房间号");
			return false;
		} else {
			return true;
		}
	}

	//1、2和3分别表示把登陆、等待和登出显示出来，其他的两个隐藏了
	private void setBtnVisible(int index)
	{
		if (index ==1)
		{
			btn_start.setVisibility(View.VISIBLE);
			btn_logout.setVisibility(View.GONE);
			btn_waiting.setVisibility(View.GONE);
		}
		else if (index ==2) {
			btn_start.setVisibility(View.GONE);
			btn_logout.setVisibility(View.GONE);
			btn_waiting.setVisibility(View.VISIBLE);
		}
		else if (index==3) {
			btn_start.setVisibility(View.GONE);
			btn_logout.setVisibility(View.VISIBLE);
			btn_waiting.setVisibility(View.GONE);
		}
	}

	private void hideKeyboard()
	{
		InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);  
		if (imm.isActive()) { 
			imm.hideSoftInputFromWindow(getCurrentFocus().getApplicationWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
		}
	}
	protected void onDestroy() {
		if (bNeedRelease) {
			anyChatSDK.Release(); // �ر�SDK
		}
		anyChatSDK.Logout();
		super.onDestroy();
	}

	protected void onResume() {
		anyChatSDK.SetBaseEvent(this);
		super.onResume();
	}
	
	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		if (!bSuccess) {
			setBtnVisible(1);
			btn_start.setClickable(true);
			Toast.makeText(this, "连接服务器失败，自动重连，请稍后...", Toast.LENGTH_SHORT)
					.show();
		}
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		if (dwErrorCode == 0) {
			setBtnVisible(3);
			hideKeyboard();
			
			Toast.makeText(this, "登录成功！", Toast.LENGTH_SHORT).show();
			bNeedRelease = false;
			int sHourseID = Integer.valueOf(edit_hourseID.getEditableText()
					.toString());
			anyChatSDK.EnterRoom(sHourseID, "");

			// finish();
		} else {
			setBtnVisible(1);
			Toast.makeText(this, "登录失败，错误代码：" + dwErrorCode, Toast.LENGTH_SHORT)
					.show();
		}
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		System.out.println("getEditableText()");
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		roleInfoList.clear();
		int[] userID = anyChatSDK.GetOnlineUser();
		for (int index = 0; index < userID.length; ++index) {
			RoleInfo info = new RoleInfo();
			info.setName(anyChatSDK.GetUserName(userID[index]));
			info.setUserID(String.valueOf(userID[index]));
			roleInfoList.add(info);
		}


		adapter = new RoleListAdapter(MainActivity.this, roleInfoList);
		role_listView.setAdapter(adapter);

		if (userID.length == 0) {
			bottom_connState.setText("房间里没有人");
		} else {
			bottom_connState.setText("Connect to the server success.");
			role_listView.setOnItemClickListener(new OnItemClickListener() {

				@Override
				public void onItemClick(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					onSelectItem(arg2);
				}
			});
		}
	}

	private void onSelectItem(int postion) {
		String strUserID = roleInfoList.get(postion).getUserID();
		Intent intent = new Intent();
		intent.putExtra("UserID", strUserID);
		intent.setClass(this, VideoActivity.class);
		startActivity(intent);
	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		System.out.println("OnAnyChatUserAtRoomMessage");
		if(bEnter){
			RoleInfo info = new RoleInfo();
			info.setUserID(String.valueOf(dwUserId));
			info.setName(anyChatSDK.GetUserName(dwUserId));
			roleInfoList.add(info);
			adapter.notifyDataSetChanged();
		}else {
			
			for (int i = 0; i < roleInfoList.size(); i++) {
				if(roleInfoList.get(i).getUserID().equals(""+dwUserId))
				{
					roleInfoList.remove(i);
					adapter.notifyDataSetChanged();
				}
			}
		}
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		setBtnVisible(1);
		Toast.makeText(this, "连接关闭，error：" + dwErrorCode, Toast.LENGTH_SHORT)
				.show();
	}

}
