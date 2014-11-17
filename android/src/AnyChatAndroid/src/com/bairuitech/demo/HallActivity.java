package com.bairuitech.demo;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;

public class HallActivity extends Activity implements AnyChatBaseEvent{
	
	public static final int ACTIVITY_ID_VIDEOCONFIG = 1;		// 视频配置界面标识
	
	private LinearLayout fullLayout;
	private LinearLayout mainLayout;
	//private Button backBtn;
	private Button videoConfigBtn;
	private Button watchTVBtn;			// 电视直播
	private Button selfVideoBtn;		// 即拍即传
	
	private Button videoChatBtn;
	private Button videoPhoneBtn;

	private final int titleHeight = 30;
	
	public AnyChatCoreSDK anychat;
	
	private boolean IsDisConnect = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        InitialSDK();
        InitialLayout();
    }
    private void InitialSDK()
    {
        anychat = new AnyChatCoreSDK();
        anychat.SetBaseEvent(this);
        ApplyVideoConfig();
    }
    private void InitialLayout()
    {   
    	fullLayout =  new LinearLayout(this);
    	fullLayout.setBackgroundResource(R.drawable.hall_bk);
    	//fullLayout.setBackgroundColor(Color.WHITE);
    	fullLayout.setOrientation(LinearLayout.VERTICAL);
    	fullLayout.setOnTouchListener(touchListener);
    	
    	mainLayout =  new LinearLayout(this);
    	mainLayout.setBackgroundColor(Color.TRANSPARENT);
	    mainLayout.setOrientation(LinearLayout.VERTICAL);
	    mainLayout.setOnTouchListener(touchListener);

		LinearLayout roomLayout1 =  new LinearLayout(this);
		roomLayout1.setOrientation(LinearLayout.HORIZONTAL);
		
		Resources res = getResources();
		Drawable image = res.getDrawable(R.drawable.room);
		image.setBounds(0, 0, ScreenInfo.WIDTH/5, ScreenInfo.WIDTH/5);

		videoChatBtn  = new Button(this);
		videoChatBtn.setTag(1);
		videoChatBtn.setCompoundDrawables( null,image, null, null);
		videoChatBtn.setText("视频聊天");
		videoChatBtn.setOnClickListener(listener);
		roomLayout1.addView(videoChatBtn,new LayoutParams(ScreenInfo.WIDTH/4,ScreenInfo.WIDTH/4+titleHeight));

		videoPhoneBtn  = new Button(this);
		videoPhoneBtn.setTag(2);
		videoPhoneBtn.setCompoundDrawables( null,image, null, null);
		videoPhoneBtn.setText("可视电话");
		videoPhoneBtn.setOnClickListener(listener);
		
		roomLayout1.addView(videoPhoneBtn,new LayoutParams(ScreenInfo.WIDTH/4,ScreenInfo.WIDTH/4+titleHeight));

		watchTVBtn  = new Button(this);
		watchTVBtn.setTag(3);
		watchTVBtn.setCompoundDrawables( null,image, null, null);
		watchTVBtn.setText("电视直播");
		watchTVBtn.setOnClickListener(listener);
		roomLayout1.addView(watchTVBtn,new LayoutParams(ScreenInfo.WIDTH/4,ScreenInfo.WIDTH/4+titleHeight));		

		selfVideoBtn  = new Button(this);
		selfVideoBtn.setTag(4);
		selfVideoBtn.setCompoundDrawables( null,image, null, null);
		selfVideoBtn.setText("即拍即传");
		selfVideoBtn.setOnClickListener(listener);
		roomLayout1.addView(selfVideoBtn,new LayoutParams(ScreenInfo.WIDTH/4,ScreenInfo.WIDTH/4+titleHeight));

		mainLayout.addView(roomLayout1,ScreenInfo.WIDTH, ScreenInfo.WIDTH/4+titleHeight);
		
		LinearLayout configLayout =  new LinearLayout(this);
		configLayout.setOrientation(LinearLayout.HORIZONTAL);
		
		Drawable imageConfig = res.getDrawable(R.drawable.config);
		imageConfig.setBounds(0, 0, ScreenInfo.WIDTH/5, ScreenInfo.WIDTH/5);
		
    	videoConfigBtn  = new Button(this);
    	videoConfigBtn.setBackgroundColor(Color.TRANSPARENT);
		videoConfigBtn.setCompoundDrawables( null,imageConfig, null, null);
		videoConfigBtn.setText("设置");
		videoConfigBtn.setOnClickListener(listener);
		configLayout.addView(videoConfigBtn,new LayoutParams(ScreenInfo.WIDTH/4,ScreenInfo.WIDTH/4+titleHeight));
		
		Drawable cameraImage = res.getDrawable(R.drawable.camera);
		cameraImage.setBounds(0, 0, ScreenInfo.WIDTH/5, ScreenInfo.WIDTH/5);
		
		mainLayout.addView(configLayout,ScreenInfo.WIDTH, ScreenInfo.WIDTH/4+titleHeight);

		
		videoChatBtn.setBackgroundColor(Color.TRANSPARENT);
		videoPhoneBtn.setBackgroundColor(Color.TRANSPARENT);
		selfVideoBtn.setBackgroundColor(Color.TRANSPARENT);
		watchTVBtn.setBackgroundColor(Color.TRANSPARENT);

    	
        ScrollView sv = new ScrollView(this);
        sv.addView(mainLayout);
    	fullLayout.addView(sv,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT*9/10));
    	//fullLayout.addView(btnLayout,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT/10));
    	this.setContentView(fullLayout);
    }
    
    OnClickListener listener = new OnClickListener()
    {       
		public void onClick(View v) 
		{
			if(v == videoConfigBtn)
			{
				startActivityForResult(new Intent("com.bairuitech.demo.VideoConfigActivity"), ACTIVITY_ID_VIDEOCONFIG);
			}
			else if(v == watchTVBtn)
			{
				Intent intent = new Intent();  
				intent.putExtra("RoomID", Integer.parseInt(v.getTag().toString()));
				intent.putExtra("mode", 1);		// 下载模式
		        intent.setClass(HallActivity.this, LiveVideoActivity.class); 
		        startActivity(intent);
			}
			else if(v == selfVideoBtn)
			{
				Intent intent = new Intent();  
				intent.putExtra("RoomID", Integer.parseInt(v.getTag().toString()));
				intent.putExtra("mode", 2);		// 上传模式
		        intent.setClass(HallActivity.this, LiveVideoActivity.class); 
		        startActivity(intent);
			}
			else
			{
		        anychat.EnterRoom(Integer.parseInt(v.getTag().toString()), "");				
			}
		}
    };
   
    private 
    OnTouchListener touchListener =  new OnTouchListener()
    {
		@Override
		public boolean onTouch(View v, MotionEvent e) {
			// TODO Auto-generated method stub
	        switch (e.getAction()) 
	        {
	    		case MotionEvent.ACTION_DOWN:
	    			try
	    			{
	    				((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(HallActivity.this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
	    			}
	    			catch(Exception excp)
	    			{
	    				
	    			}
	    			break;
	    		case MotionEvent.ACTION_UP:

	    			break;
	        }
	        return false;
		}
    };
    
    protected void onDestroy() {
    	anychat.LeaveRoom(-1);
    	anychat.Logout();
    	anychat.Release();	// 关闭SDK，不再返回登录界面

    	if(!IsDisConnect)
    	{
    		android.os.Process.killProcess(android.os.Process.myPid());
    	}
    	else
    	{
 		   Intent itent=new Intent();
	       itent.setClass(HallActivity.this, LoginActivity.class);
	       startActivity(itent);
    	}
    	super.onDestroy();
    	//System.exit(0);
    }
    
    protected void onResume() {
        anychat.SetBaseEvent(this);
        super.onResume();
    }
    
	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
	    if(dwErrorCode == 0)
	    {
	    	if(dwRoomId == 1)
	    	{
				Intent intent = new Intent();  
				intent.putExtra("RoomID", dwRoomId);
				intent.setClass(HallActivity.this, RoomActivity.class); 
				startActivity(intent);   
	    	}
	    	else
	    	{
				Intent intent = new Intent();  
				intent.putExtra("RoomID", dwRoomId);
				intent.setClass(HallActivity.this, VideoCallActivity.class); 
				startActivity(intent); 	    		
	    	}
	    }
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub
		IsDisConnect = true;
		this.finish();
		
	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
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
	
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		if(resultCode == RESULT_OK)
		{
			ApplyVideoConfig();
		}
	}

	// 根据配置文件配置视频参数
	private void ApplyVideoConfig()
	{
		ConfigEntity configEntity = ConfigService.LoadConfig(this);
		if(configEntity.configMode == 1)		// 自定义视频参数配置
		{
			// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL, configEntity.videoBitrate);
			if(configEntity.videoBitrate==0)
			{
				// 设置本地视频编码的质量
				AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL, configEntity.videoQuality);
			}
			// 设置本地视频编码的帧率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL, configEntity.videoFps);
			// 设置本地视频编码的关键帧间隔
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL, configEntity.videoFps*4);
			// 设置本地视频采集分辨率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL, configEntity.resolution_width);
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, configEntity.resolution_height);
			// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL, configEntity.videoPreset);
		}
		// 让视频参数生效
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM, configEntity.configMode);
		// P2P设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC, configEntity.enableP2P);
		// 本地视频Overlay模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY, configEntity.videoOverlay);
		// 回音消除设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL, configEntity.enableAEC);
		// 平台硬件编码设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC, configEntity.useHWCodec);
		// 视频旋转模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL, configEntity.videorotatemode);
		// 视频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER, configEntity.videoCapDriver);
		// 本地视频采集偏色修正设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA, configEntity.fixcolordeviation);
		// 视频显示驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL, configEntity.videoShowDriver);
		// 音频播放驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_PLAYDRVCTRL, configEntity.audioPlayDriver);
		// 音频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_RECORDDRVCTRL, configEntity.audioRecordDriver);
		// 视频GPU渲染设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER, configEntity.videoShowGPURender);
		// 本地视频自动旋转设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION, configEntity.videoAutoRotation);
	}
}
