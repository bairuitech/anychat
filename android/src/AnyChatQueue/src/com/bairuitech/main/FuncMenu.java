package com.bairuitech.main;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.anychat.AnyChatObjectEvent;

import com.bairuitech.anychatqueue.QueueActivity;
import com.bairuitech.anychatqueue.YeWuActivity;
import com.bairuitech.callservice.VideoServer;
import com.bairuitech.common.ConfigEntity;
import com.bairuitech.common.ConfigService;
import com.bairuitech.common.CustomApplication;

import com.example.anychatqueue.R;

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
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.SimpleAdapter;
import android.widget.TextView;


public class FuncMenu extends Activity implements AnyChatBaseEvent,OnClickListener,AnyChatObjectEvent {
	
	public ConfigEntity configEntity = new ConfigEntity();
	private CustomApplication mApplication;
	public ProgressDialog waitingpd;
	public static final int ACTIVITY_ID_VIDEOCONFIG = 1;  // 视频配置界面标识
	
	private ImageButton mImgBtnReturn;	         		  // 标题返回
	private TextView mTitleName;						  // 标题名字
	private GridView mMenuGridView;						  //网格布局
	// 存储功能菜单图标和描述
	int[] arrFuncIcons = { R.drawable.stronghold_01, R.drawable.stronghold_02,
			R.drawable.stronghold_03, R.drawable.stronghold_04,
			R.drawable.stronghold_01, R.drawable.stronghold_02,
			R.drawable.stronghold_03, R.drawable.stronghold_04,
			R.drawable.stronghold_01, R.drawable.stronghold_02};
	
	private AnyChatCoreSDK anychat;
	private List<Integer> mobject =new ArrayList<Integer>();
	private ArrayList<HashMap<String, Object>> mArrItem;
	private List<String> list = new ArrayList<String>();;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//自定义标题栏
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.activity_func_menu);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		//得到登陆的身份标识；
		ApplyVideoConfig();	
		InitSDK();
		InitLayout();
	}

	private void InitSDK() {
		// TODO Auto-generated method stub
		//初始化sdk
		if (anychat == null) {
				anychat = AnyChatCoreSDK.getInstance(this);
	}
		anychat.SetBaseEvent(this);//基本登陆事件接口
		anychat.SetObjectEvent(this);//排队事件接口；
	}

	private void InitLayout() {
		
		mApplication = (CustomApplication) getApplication();
		waitingpd = new ProgressDialog(FuncMenu.this);
		this.setTitle("营业厅列表");
		mMenuGridView = (GridView) this.findViewById(R.id.funcmenuGridView);
		
		mTitleName = (TextView) this.findViewById(R.id.titleName);
		mTitleName.setText(R.string.str_funcTitle);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mImgBtnReturn.setOnClickListener(this);
		showIndeterminate1();
	}
	// 根据配置文件配置视频参数
	private void ApplyVideoConfig() {
		ConfigEntity configEntity = ConfigService.LoadConfig(this);
		if (configEntity.configMode == 1) // 自定义视频参数配置
		{
			// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL,
					configEntity.videoBitrate);
			if (configEntity.videoBitrate == 0) {
				// 设置本地视频编码的质量
				AnyChatCoreSDK.SetSDKOptionInt(
						AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL,
						configEntity.videoQuality);
			}
			// 设置本地视频编码的帧率
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL,
					configEntity.videoFps);
			// 设置本地视频编码的关键帧间隔
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL,
					configEntity.videoFps * 4);
			// 设置本地视频采集分辨率
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL,
					configEntity.resolution_width);
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL,
					configEntity.resolution_height);
			// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
			AnyChatCoreSDK.SetSDKOptionInt(
					AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL,
					configEntity.videoPreset);
		}
		// 让视频参数生效
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM,
				configEntity.configMode);
		// P2P设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC,
				configEntity.enableP2P);
		// 本地视频Overlay模式设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY,
				configEntity.videoOverlay);
		// 回音消除设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL,
				configEntity.enableAEC);
		// 平台硬件编码设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC,
				configEntity.useHWCodec);
		// 视频旋转模式设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL,
				configEntity.videorotatemode);
		// 本地视频采集偏色修正设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA,
				configEntity.fixcolordeviation);
		// 视频GPU渲染设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER,
				configEntity.videoShowGPURender);
		// 本地视频自动旋转设置
		AnyChatCoreSDK.SetSDKOptionInt(
				AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
				configEntity.videoAutoRotation);
	}

	private void destroyCurActivity() {
		this.setResult(RESULT_OK);
		
		onPause();
		onDestroy();
		finish();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}
	
	@Override
	protected void onRestart() {
		super.onRestart();
		anychat.SetBaseEvent(this);
		anychat.SetObjectEvent(this);
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

	// 网络断开
	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// 销毁当前界面
		
		destroyCurActivity();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
	}

	
						
				

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.returnImgBtn://按下返回键
			
			anychat.Logout();
			finish();
			break;

		default:
			break;
		}
	}




	@Override
	public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3,
			int dwParam4, String strParam) {
		// TODO Auto-generated method stub
		switch(dwEventType) {
		//营业厅数据同步，回调一次返回一个营业厅对象id（有多少营业厅回调多少次）
		case AnyChatObjectDefine.ANYCHAT_OBJECT_EVENT_UPDATE:	
			mobject.add(dwObjectId);
			break;	
		//进入营业厅
		case AnyChatObjectDefine.ANYCHAT_AREA_EVENT_ENTERRESULT:	
			//获取业务队列id号的数组，执行跳转；
			AnyChatEnterAreaResult(dwObjectType, dwObjectId, dwParam1);				
			break;	
		//数据同步
		case AnyChatObjectDefine.ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH:	
			waitingpd.dismiss();
			DataFinshed(dwObjectType);			
			break;
		default: 
			break;
		}
	}
	

	//进入营业厅的回调，跳转到业务列表
	private void AnyChatEnterAreaResult(int dwObjectType, int dwObjectId,
			int dwParam1) {
		//dwParam1 进入营业厅返回结果，0表示进入营业厅成功
		
			//客户角色
			if(mApplication.getUserType() == 0){
			int[] queueIds = AnyChatCoreSDK.ObjectGetIdList(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE);
			Intent in=new Intent();
			in.putExtra("ids", queueIds);
			in.setClass(FuncMenu.this, YeWuActivity.class);
			startActivity(in);
			waitingpd.dismiss();
			//座席角色
		}else if(mApplication.getUserType() == 2){
			
			int[] Ids = AnyChatCoreSDK.ObjectGetIdList(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE);
			Intent in=new Intent();
			in.putExtra("ids", Ids);
			in.setClass(FuncMenu.this,VideoServer.class);
			startActivity(in);
			waitingpd.dismiss();
		}
		
		
	}
	public void showIndeterminate1(){
		waitingpd.setMessage("加载营业厅...");
		waitingpd.setCancelable(true);
		waitingpd.setProgress(ProgressDialog.STYLE_HORIZONTAL);
		waitingpd.setIndeterminate(true);
		waitingpd.show();
	}
	public void showIndeterminate2(){
		waitingpd.setMessage("进入营业厅...");
		waitingpd.setCancelable(true);
		waitingpd.setProgress(ProgressDialog.STYLE_HORIZONTAL);
		waitingpd.setIndeterminate(true);
		waitingpd.show();
	}
	
	private void DataFinshed(int dwObjectType) {
		// TODO Auto-generated method stub
		//获取了营业厅的ID
		
		if(dwObjectType == AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA) 
		{
			for (int i = 0; i < mobject.size(); i++) {
				String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA,mobject.get(i), AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);
				list.add(name);
			}
				//列表的实现
				mArrItem = new ArrayList<HashMap<String, Object>>();
				for (int index = 0; index <list.size(); index++) {
					HashMap<String, Object> itemMap = new HashMap<String, Object>();
					itemMap.put("ItemImage", arrFuncIcons[index]);
					itemMap.put("ItemText",list.get(index).toString());
					mArrItem.add(itemMap);
				}

				SimpleAdapter sMenuItemAdapter = new SimpleAdapter(this, mArrItem,
						R.layout.funcmenu_cell,
						new String[] { "ItemImage", "ItemText" }, new int[] {
								R.id.funcItemImage, R.id.funcItemText });

				mMenuGridView.setAdapter(sMenuItemAdapter);
				mMenuGridView.setOnItemClickListener(new OnItemClickListener() {

					@Override
					public void onItemClick(AdapterView<?> arg0, View arg1,
							int arg2, long arg3) {
						// TODO Auto-generated method stub
						//服务器同步语句
						showIndeterminate2();
						configEntity.CurrentObjectId = mobject.get(arg2);
						ConfigService.SaveConfig(FuncMenu.this, configEntity);
						
						AnyChatCoreSDK.ObjectControl(
						AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, mobject.get(arg2),
						AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0,
						0, "");	
					}
				});
			}
			
			
			
			
		}


	

}
