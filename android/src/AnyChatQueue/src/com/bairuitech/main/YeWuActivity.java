package com.bairuitech.main;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;
import com.bairuitech.anychatqueue.QueueActivity;
import com.bairuitech.anychatqueue.YeWuAdapter;
import com.bairuitech.common.BaseMethod;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.main.LoginServer;
import com.example.anychatqueue.R;


public class YeWuActivity extends Activity implements AnyChatBaseEvent,AnyChatObjectEvent, OnClickListener{
	private ListView listView;				
	private YeWuAdapter adapter;			//适配器
	private AnyChatCoreSDK anychat;			//sdk对象	
	public List<Map<String, Object>> queueList = new ArrayList<Map<String,Object>>();//适配器-集合参数
	
	private ImageButton mImgBtnReturn;
	private TextView 	mTitleName;	
	public ProgressDialog pd;				//进度提示
	public CustomApplication mApplication;	//全局变量类
	private int[] queueIds;					//获取队列数组	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //自定义标题栏
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.activity_yewu);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar); 
        //初始化sdk
        InitSDK();
        //初始化布局组件
        initView();
    }

	private void initView() {
		
		//获取营业厅的队列列表Id数组
		queueIds = AnyChatCoreSDK.ObjectGetIdList(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE);
		//获取适配器的数据
        for (int i = 0; i < queueIds.length; i++) {
        	
        	Map<String, Object> map = new HashMap<String, Object>();
        	//获取业务字符名称；
        	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,queueIds[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
        	//获取业务排队人数；
        	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
        	map.put("name", name);
        	map.put("number",number);
        	map.put("id", queueIds[i]);
        	//集合数据；
        	queueList.add(map);
        }
      
        //进度提示
        pd = new ProgressDialog(YeWuActivity.this);
        //标题栏
        mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setOnClickListener(this);
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mTitleName.setText("队列列表");
        //全局变量类初始化
		mApplication = (CustomApplication) getApplication();
		//适配界面
		listView = (ListView) findViewById(R.id.yewu_listview);
        adapter = new YeWuAdapter(YeWuActivity.this,queueList,pd,mApplication);
        listView.setAdapter(adapter);
	}

    
    @Override
    protected void onRestart() {
    	// TODO Auto-generated method stub
    	if(anychat == null){
    	anychat = AnyChatCoreSDK.getInstance(this);
    	}
    	anychat.SetBaseEvent(this);
    	anychat.SetObjectEvent(this);
    	//数据更新
    	dataUpdate();
    	super.onRestart();
    }

	private void dataUpdate() {
		
		for (int i = 0; i < queueIds.length; i++) {
         	//获取业务字符名称；
         	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,queueIds[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
         	//获取业务排队人数；
         	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
         	//
         	queueList.get(i).put("name", name);
         	queueList.get(i).put("number",number);
         }
    	 adapter.notifyDataSetChanged();
	}
   
    private void InitSDK() {
		// TODO Auto-generated method stub
    	//单例模式获取sdk对象
    	if(anychat == null){
    		anychat = AnyChatCoreSDK.getInstance(this);
    	}
    	
    	anychat.SetBaseEvent(this);
    	anychat.SetObjectEvent(this);
	}
    
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK){
			
			//退出营业厅（进营业厅，出营业厅，加入队列，出队列都是这个方法）
			alertDialog();	
		
		}		

		return super.onKeyDown(keyCode, event);
	}
	private void alertDialog() {
		AlertDialog.Builder builder = new AlertDialog.Builder(YeWuActivity.this);
		builder.setMessage("您确定要退出营业厅？")
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					
					public void onClick(DialogInterface dialog, int which) {
						//离开营业厅
						AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA,mApplication.getCurrentAreaId(),AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERLEAVE, 0,0,0,0, "");
					}
				}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
					
					public void onClick(DialogInterface dialog, int which) {
						
					}
				}).create().show();
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
		BaseMethod.showToast("网络断开连接",YeWuActivity.this);
		anychat.Logout();
		Intent intent = new Intent(YeWuActivity.this,LoginServer.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
		startActivity(intent);
		
	}
	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		
		switch(dwEventType) {
		
		//营业厅数据同步，回调一次返回一个营业厅对象id（有多少营业厅回调多少次）
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_ENTERRESULT:	
			
			Intent in=new Intent();
			in.setClass(YeWuActivity.this, QueueActivity.class);
			startActivity(in);
			pd.dismiss();
			break;
		
		//离开服务区域回调
		case AnyChatObjectDefine.ANYCHAT_AREA_EVENT_LEAVERESULT:
			System.out.println("退出营业厅触发"+dwObjectId);
			onPause();
			onDestroy();
			finish();
			break;
		
		//用户队列状态变化事件回调
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_STATUSCHANGE:	
			//更新列表数据	
			for (int i = 0; i < queueIds.length;i++ ) {
				//遍历查找
				if(dwObjectId == queueIds[i]){
					int number1 = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
					queueList.get(i).put("number", number1);
					adapter.notifyDataSetChanged();
					break;
				}
			}
			break;
			
		default: 
			break;
		}
	}

	@Override
	public void onClick(View arg0) {
			// TODO Auto-generated method stub
			switch (arg0.getId()) {
			case R.id.returnImgBtn://按下返回键
				//leave area event;
				alertDialog();
				break;
			default:
				break;
			}
		
	}
	
}
