package com.bairuitech.anychatqueue;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
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
import com.bairuitech.viewadapter.YeWuAdapter;
import com.example.anychatqueue.R;
import com.example.common.ConfigEntity;
import com.example.common.ConfigService;


public class YeWuActivity extends Activity implements AnyChatBaseEvent,AnyChatObjectEvent, OnClickListener{
	private ListView listView;
	private YeWuAdapter adapter;
	private AnyChatCoreSDK anyChatSDK;
	private ConfigEntity configEntity = new ConfigEntity();
	private int[] ids;
	public List<Map<String, Object>> list = new ArrayList<Map<String,Object>>();
	private ImageButton mImgBtnReturn;
	private TextView 	mTitleName;	
	public ProgressDialog pd;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.activity_yewu);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar); 

        InitSDK();
        initView();
    }

	private void initView() {
		//拿取传过来的数据；
        Intent intent = getIntent();
        ids = intent.getIntArrayExtra("ids");
        configEntity  = ConfigService.LoadConfig(YeWuActivity.this);
        for (int i = 0; i < ids.length; i++) {
        	System.out.println("队列Id值==>"+ids[i]);
        	Map<String, Object> map = new HashMap<String, Object>();
        	//获取业务字符名称；
        	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,ids[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
        	//获取业务排队人数；
        	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, ids[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
        	map.put("name", name);
        	map.put("number",number);
        	map.put("id", ids[i]);
        	//集合数据；
        	list.add(map);
        }
        pd = new ProgressDialog(YeWuActivity.this);
        
        mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setOnClickListener(this);
	
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mTitleName.setText("业务办事大厅");
       //适配界面
		listView = (ListView) findViewById(R.id.yewu_listview);
        adapter = new YeWuAdapter(YeWuActivity.this,list,pd);
        listView.setAdapter(adapter);
	}
    
    @Override
    protected void onRestart() {
    	// TODO Auto-generated method stub
    	if(anyChatSDK == null){
    	anyChatSDK = AnyChatCoreSDK.getInstance(this);
    	}
    	anyChatSDK.SetBaseEvent(this);
    	anyChatSDK.SetObjectEvent(this);
    	 for (int i = 0; i < ids.length; i++) {
         	//获取业务字符名称；
         	String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,ids[i], AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
         	//获取业务排队人数；
         	int number = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, ids[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
         	//
         	list.get(i).put("name", name);
         	list.get(i).put("number",number);
         }
    	 adapter.notifyDataSetChanged();
    	super.onRestart();
    }
   
    private void InitSDK() {
		// TODO Auto-generated method stub
    	if(anyChatSDK == null){
    		anyChatSDK = AnyChatCoreSDK.getInstance(this);
    	}
    	
    	anyChatSDK.SetBaseEvent(this);
    	anyChatSDK.SetObjectEvent(this);
	}
    
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK){
			
			//退出营业厅（进营业厅，出营业厅，加入队列，出队列都是这个方法）
			int id = configEntity.CurrentObjectId;
			AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, id,AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0,0, "");				
		
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
		
	}
	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub
	
	}
	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub
	
	}
	private void destroyCurActivity() {
		
		onPause();
		onDestroy();
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub
		// 销毁当前界面
		destroyCurActivity();
		
	}
	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		
		switch(dwEventType) {
		//营业厅数据同步，回调一次返回一个营业厅对象id（有多少营业厅回调多少次）
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_ENTERRESULT:	
			
			int mbefore = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwObjectId, AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_BEFOREUSERNUM);
			Intent in=new Intent();
			in.putExtra("order", mbefore);
			in.setClass(YeWuActivity.this, QueueActivity.class);
			startActivity(in);
			pd.dismiss();
			break;
		//离开服务区域回调
		case AnyChatObjectDefine.ANYCHAT_AREA_EVENT_LEAVERESULT:	
			destroyCurActivity();
			break;
			
		case AnyChatObjectDefine.ANYCHAT_QUEUE_EVENT_STATUSCHANGE:	
			//更新列表数据
			for (int i = 0; i < ids.length;i++ ) {
				if(dwObjectId == ids[i]){
					int number1 = AnyChatCoreSDK.ObjectGetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, ids[i],AnyChatObjectDefine.ANYCHAT_QUEUE_INFO_LENGTH);
					list.get(i).put("number", number1);
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
				AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, configEntity.CurrentObjectId,AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0,0, "");
				finish();
				break;
			default:
				break;
			}
		
	}
	
}
