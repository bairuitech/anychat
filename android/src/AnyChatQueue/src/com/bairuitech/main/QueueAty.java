package com.bairuitech.main;

import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.anychat.AnyChatVideoCallEvent;
import com.bairuitech.common.BaseMethod;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.common.DialogFactory;
import com.bairuitech.main.LoginAty;
import com.example.anychatqueue.R;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

 public class QueueAty extends Activity implements AnyChatBaseEvent,AnyChatVideoCallEvent,AnyChatObjectEvent{
	private Button  quickButton;
	private AnyChatCoreSDK anychat;
	private Dialog dialog;
	private TextView showTextView;				
	private ImageButton mImgBtnReturn;
	private TextView mTitleName,timeshow;		
	public CustomApplication mApplication;		//全局变量类
	private final int TIME_UPDATE = 291;		//Handler发送消息,队列人数的实时更新
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//自定义标题栏
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.activity_queue);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar); 
		
		//初始化SDK
		initSdk();
		//初始化布局组件
		initView();
		
	}
	private void initView() {
		//全局变量类的对象初始化
		mApplication = (CustomApplication) getApplication();
		//标题栏的设置
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setVisibility(View.GONE);
		
		String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mTitleName.setText(name+"-排队等待中");
		//队列的长度
		int length = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
		//排在自己前面的人数
		int morder = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_BEFOREUSERNUM);
		showTextView = (TextView) findViewById(R.id.queue_show);
		showTextView.setText("当前排队人数共:"+length+"人,您现在排在第 "+(morder+1)+" 位");
		//实时更新显示时间
		timeshow = (TextView) findViewById(R.id.queue_time);
		final Handler myhHandler = new Handler(){
			@Override
			public void handleMessage(Message msg) {
				if(msg.what == TIME_UPDATE){					
			int seconds = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_WAITTIMESECOND);
			timeshow.setText("您已等待了 "+BaseMethod.getTimeShowStringTwo(seconds));
				}
			}
			
		};
		new Timer().schedule(new TimerTask() {
			
			@Override
			public void run() {
				
				myhHandler.sendEmptyMessage(TIME_UPDATE);
			}
		}, 0,1000);
		
		
		quickButton = (Button) findViewById(R.id.queue_btn);
		quickButton.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				
				alertDialog();
			}
		});
	}
	
	private void alertDialog() {
		AlertDialog.Builder builder = new AlertDialog.Builder(QueueAty.this);
			builder.setMessage("您确定要退出当前排队吗?")
					.setPositiveButton("确定", new DialogInterface.OnClickListener() {
						
						public void onClick(DialogInterface dialog, int which) {
							AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
							finish();
						}
					}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
						
						public void onClick(DialogInterface dialog, int which) {
							
						}
					}).create().show();
	}
	
	
	//sdk 初始化
	private void initSdk() {
		// TODO Auto-generated method stub
		if (anychat == null) {
			anychat = AnyChatCoreSDK.getInstance(this);
		}
		anychat.SetBaseEvent(this);
		anychat.SetVideoCallEvent(this);
		anychat.SetObjectEvent(this);
		Log.i("ANYCHAT", "initSdk");
	}
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		BussinessCenter.mContext = QueueAty.this;
		super.onResume();
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
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		BussinessCenter.getBussinessCenter().realse();
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
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
	
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
		//网络断开时跳到主页面
		Toast.makeText(QueueAty.this, this.getString(R.string.str_serverlink_close), Toast.LENGTH_LONG).show();
			Intent intent = new Intent();
			intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			intent.setClass(this,LoginAty.class);
			this.startActivity(intent);	
		
	}
	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		// TODO Auto-generated method stub
		switch (dwEventType) {
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_STATUSCHANGE:
			//队列数据更新
			dataChange(dwObjectId);
			break;
		default:
			break;
		}
	}
	private void dataChange(int dwObjectId) {
		
		if(dwObjectId == mApplication.getCurrentQueueId()){
			
			int length = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwObjectId, AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
			int mbefore = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,dwObjectId, AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_BEFOREUSERNUM);
			showTextView.setText("当前排队人数共:"+length+"人,您现在排在第 "+(mbefore+1)+" 位");
		}
	}
	
	@Override
	public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId,
			int dwErrorCode, int dwFlags, int dwParam, String userStr) {
		// TODO Auto-generated method stub
		switch (dwEventType) {

		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST:
			//呼叫请求事件
			BussinessCenter.getBussinessCenter().onVideoCallRequest(
					dwUserId, dwFlags, dwParam, userStr);
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			
			mApplication.setTargetUserName(anychat.GetUserName(dwUserId));
			dialog = DialogFactory.getDialog(DialogFactory.DIALOGID_REQUEST,
					dwUserId, this,mApplication);
			dialog.show();
			 break;
			
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY:
			//呼叫成功的时候的所做出的反应；
			Log.e("queueactivity","呼叫成功等待对方反应的回调");
			BussinessCenter.getBussinessCenter().onVideoCallReply(
					dwUserId, dwErrorCode, dwFlags, dwParam, userStr);
			if (dwErrorCode == AnyChatDefine.BRAC_ERRORCODE_SUCCESS) {
				dialog = DialogFactory.getDialog(
						DialogFactory.DIALOGID_CALLING, dwUserId,
						QueueAty.this,mApplication);
				dialog.show();

			} else {
				if (dialog != null && dialog.isShowing()) {
					dialog.dismiss();
				}
			}
			break;
			
		case AnyChatDefine.BRAC_VIDEOCALL_EVENT_START:
			Log.e("queueactivity","会话开始回调");
			if (dialog != null && dialog.isShowing())
				dialog.dismiss();
			BussinessCenter.getBussinessCenter().onVideoCallStart(
					dwUserId, dwFlags, dwParam, userStr,mApplication);
			break;
		}
	}

}
