 package com.bairuitech.main;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.common.BaseConst;
import com.bairuitech.common.BaseMethod;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.common.DialogFactory;
import com.bairuitech.main.LoginActivity;
import com.example.anychatqueueplusplus.R;


public class AgentServiceActivity extends Activity implements 
		OnClickListener, AnyChatBaseEvent, AnyChatVideoCallEvent,AnyChatObjectEvent
		 {
	
	List<Map<String, Object>> list = new ArrayList<Map<String,Object>>();
	private AnyChatCoreSDK anychat;
	private Dialog dialog;
	private Button start;
	private ImageButton mImgBtnReturn;	// 标题返回
	private TextView mTitleName;		// 标题名字
	private int[] queueIds;
	private ListView listView;
	private SimpleAdapter adapter;
	private CustomApplication mApplication;
     /** 自动路由 **/
     private int isAutoMode;
     /** 1服务端设置，0客户端设置 **/
     private int mUserSetting;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		//自定义标题栏
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.myvideo);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);
		//初始化sdk
		initSdk();
		//初始化布局
		initView();

        isAutoMode = getIntent().getIntExtra("isAutoMode", 0);
        mUserSetting = getIntent().getIntExtra("userSetting", 0);
		AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT, mApplication.getUserID(), AnyChatObjectDefine.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_CLOSEED, 0, 0, 0, "");
	}

	private void initView() {
		//全局变量
		mApplication = (CustomApplication)getApplication();
		
		//获取营业厅的队列列表Id数组
		queueIds = AnyChatCoreSDK.ObjectGetIdList(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE);
		//获取适配器的数据
		for (int i = 0; i < queueIds.length; i++) {
			
	        	Map<String, Object> map = new HashMap<String, Object>();
	        	//获取业务字符名称；
	        	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,queueIds[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
	        	//获取业务排队人数；
	        	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
	        	//添加数据
	        	map.put("name", name);
	        	map.put("number",number);
	        	map.put("id", queueIds[i]);
	        	//集合数据；
	        	list.add(map);
	        }
		 
		adapter = new SimpleAdapter(AgentServiceActivity.this, list, R.layout.videoserver_listviewitem, new String[]{"name","number"}, new int[]{R.id.id_tv_queue,R.id.id_tv_number});
		listView = (ListView) findViewById(R.id.id_listview_server);
		listView.setAdapter(adapter);
		
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mTitleName.setText("队列列表");
		mTitleName.setTextColor(getResources().getColor(R.color.white));
		
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setOnClickListener(this);
		
		start = (Button) findViewById(R.id.id_btn_startserver);
		start.setOnClickListener(this);
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
			
			 if (dialog != null && dialog.isShowing()) dialog.dismiss();
		}
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		initSdk();
        AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT, mApplication.getUserID(), AnyChatObjectDefine.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_WAITTING, 0, 0, 0, "");
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
		BussinessCenter.mContext = AgentServiceActivity.this;
		initSdk();
		dataUpdate();
		super.onResume();
	}

	private void dataUpdate() {
		// TODO Auto-generated method stub
		for (int i = 0; i < queueIds.length; i++) {
        	//获取业务字符名称；
        	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,queueIds[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
        	//获取业务排队人数；
        	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
        	//添加数据
        	list.get(i).put("name", name);
        	list.get(i).put("number",number);
        	adapter.notifyDataSetChanged();
        }
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		BussinessCenter.getBussinessCenter().realse();
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

	private void initSdk() {
		if (anychat == null) {
			anychat = new AnyChatCoreSDK();
		}
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetObjectEvent(this);
		Log.i("ANYCHAT", "initSdk");
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		// TODO Auto-generated method stub
		if (event.getAction() == KeyEvent.ACTION_DOWN
				&& event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
			
			alertDialog();
		}
		
		return super.dispatchKeyEvent(event);
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

	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if(dwErrorCode==0)
		{
			BussinessCenter.selfUserName=anychat.GetUserName(dwUserId);
		} else {
			BaseMethod.showToast(this.getString(R.string.str_login_failed) + "(ErrorCode:" + dwErrorCode + ")",	this);
		}
	}
	//当用户进入房间的时候会触发
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

		if (dwErrorCode == 0) {
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			dialog = DialogFactory.getDialog(DialogFactory.DIALOG_NETCLOSE,
					DialogFactory.DIALOG_NETCLOSE, this,mApplication);
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

	public void OnAnyChatVideoCallEvent(int dwEventType, int targetUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub
		switch (dwEventType) {

		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST:
			BussinessCenter.getBussinessCenter().onVideoCallRequest(
                    targetUserId, dwFlags, dwParam, userStr);
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_REQUEST,
                    targetUserId, this,mApplication);
			dialog.show();
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY:
			BussinessCenter.getBussinessCenter().onVideoCallReply(
                    targetUserId, dwErrorCode, dwFlags, dwParam, userStr);
			
			if (dwErrorCode == AnyChatDefine.BRAC_ERRORCODE_SUCCESS) {
				dialog = DialogFactory.getDialog(
						DialogFactory.DIALOGID_CALLING, targetUserId,
						AgentServiceActivity.this,mApplication);
				dialog.show();

			} else {
				if (dialog != null && dialog.isShowing()) {
					dialog.dismiss();
				}
                anychat.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, targetUserId, 0, 0, 0, "");
			}
			break;
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_START:
			Log.e("queueactivity","会话开始回调");
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			BussinessCenter.getBussinessCenter().onVideoCallStart(
                    targetUserId, dwFlags, dwParam, userStr, mApplication);
			break;
        case AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH:
            Log.e("queueactivity", "会话结束回调");
            AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT, mApplication.getUserID(), AnyChatObjectDefine.ANYCHAT_AGENT_CTRL_FINISHSERVICE, 0, 0, 0, 0, "");
            break;
		}
	}

	@Override
	public void onClick(View arg0) {
		// TODO Auto-generated method stub
		switch (arg0.getId()) {
		case R.id.id_btn_startserver:
			//开始服务
            if (isAutoMode == 0 && mUserSetting == 0) {
                AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT, mApplication.getUserID(), AnyChatObjectDefine.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_WAITTING, 0, 0, 0, "");
            } else {
                AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT, mApplication.getUserID(), AnyChatObjectDefine.ANYCHAT_AGENT_CTRL_SERVICEREQUEST, 0, 0, 0, 0, "");
            }
			break;
		case R.id.returnImgBtn:
			
			alertDialog();		
			break;
		default:
			break;
		}
	}

	private void alertDialog() {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setMessage("您确定退出当前营业厅吗？")
		.setPositiveButton("确定", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				//退出营业厅
				AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA,mApplication.getCurrentAreaId(), AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");	
			}
		}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
					
			@Override
			public void onClick(DialogInterface dialog, int which) {	
			}
		}).create().show();
	}


	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {

		switch (dwEventType) {
		
		case AnyChatObjectDefine.ANYCHAT_AGENT_EVENT_SERVICENOTIFY:
			//当客户角色是座席（服务器发的一个广播所有的座席都会触发到故需加限制条件)
			if(mApplication.getUserType() == 2 && dwParam1 == mApplication.getUserID())
			{
				anychat.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST, dwParam2, 0, 0, 0, "");
			}
			 if(isAutoMode == 0 && mUserSetting == 0 && mApplication.getUserType() == 1 && dwParam2 == mApplication.getUserID())
            {
                anychat.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST, dwParam1, 0, 0, 0, "");
            }
			break;	
		case AnyChatObjectDefine.ANYCHAT_AGENT_EVENT_STATUSCHANGE:	
			    if (dwObjectType == AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AGENT && mApplication.getUserID() == dwObjectId) {
			        if (dwParam1 == AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_WAITTING) {
			        	start.setText("准备状态");
			        }else if (dwParam1 == AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_WORKING){
			        	start.setText("忙碌状态");
			        }else if (dwParam1 == AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_PAUSED){
			        	start.setText("离开状态");
			        }else if (dwParam1 == AnyChatObjectDefine.ANYCHAT_AGENT_STATUS_CLOSEED){
			        	start.setText("未服务状态");
			        }
			    }
			break;
		case AnyChatObjectDefine.ANYCHAT_AGENT_EVENT_WAITINGUSER:				
			BaseMethod.showToast("暂时无人排队中...", AgentServiceActivity.this);		
			break;
			
		case AnyChatObjectDefine.ANYCHAT_AREA_EVENT_LEAVERESULT:  
			
			finish();
			break;
			
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_STATUSCHANGE:
			
			for(int i=0;i<list.size();i++){
				int CurrentQueueId = Integer.parseInt(list.get(i).get("id").toString())	;
				if(dwObjectId == CurrentQueueId){
					int number1 = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwObjectId,AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
					list.get(i).put("number", number1);
					adapter.notifyDataSetChanged();
				}
			}
			break;
		default:
			break;
		}
	}


}
