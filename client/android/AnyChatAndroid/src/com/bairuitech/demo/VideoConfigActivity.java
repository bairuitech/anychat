package com.bairuitech.demo;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Spinner;

public class VideoConfigActivity extends Activity{
	private LinearLayout fullLayout;
	private LinearLayout mainLayout;
	private Button saveBtn;
	private ConfigEntity configEntity;
	
	private RadioGroup configModeRadioGroup;		// 配置模式组
	
	RadioButton configModeServerBtn;				// 服务器配置
	RadioButton configModeCustomBtn;				// 自定义配置
	
	TextView resolutionLable;
	
	private CheckBox enableP2PBox;
	private CheckBox videoOverlayBox;
	private CheckBox useARMv6Box;
	private CheckBox useAECBox;
	private CheckBox useHWCodecBox;
	private CheckBox videoRotateBox;
	private CheckBox fixColorDeviation;
	private CheckBox videoShowGPURender;
	private CheckBox smoothPlayBox;
	private Spinner videoSizeSpinner;
	private Spinner videoBitrateSpinner;
	private Spinner videoFPSSpinner;
	private Spinner videoQualitySpinner;
	private Spinner videoPresetSpinner;
	private Spinner videoShowDriverSpinner;
	private Spinner audioPlayDriverSpinner;
	private Spinner audioRecordDriverSpinner;
	private Spinner videoCapDriverSpinner;

	private final String[] videoSizeString={"176 x 144", "320 x 240（默认）", "352 x 288", "640 x 480", "720 x 480", "1280 x 720"};
	private final int[] videoWidthValue={176,320,352,640, 720, 1280};
	private final int[] videoHeightValue={144,240,288,480, 480, 720};
	
	private final String[] videoBitrateString={"质量优先模式", "60kbps（默认）", "80kbps", "100kbps", "150kbps", "200kbps", "300kbps", "500kbps", "800kbps", "1Mbps"};
	private final int[]	videoBitrateValue={0,60*1000,80*1000,100*1000,150*1000,200*1000,300*1000,500*1000,800*1000,1000*1000};
	
	private final String[] videofpsString={"2 FPS", "4 FPS", "6 FPS", "8 FPS", "10FPS（默认）", "15FPS", "20FPS", "25FPS"};
	private final int[]	videofpsValue={2,4,6,8,10,15,20,25};
	
	private final String[] videoQualityString={"普通视频质量", "中等视频质量（默认）", "较好视频质量"};
	private final int[] videoQualityValue={2,3,4};
	
	private final String[] videoPresetString={"最高效率，较低质量","较高效率，较低质量","性能均衡（默认）","较高质量，较低效率","最高质量，较低效率"};
	private final int[] videoPresetValue={1,2,3};
	
	private final String[] videoShowDriverString={"内核视频显示驱动", "Android 2.x兼容模式", "Java视频显示驱动"};
	private final int[]	videoShowDriverValue={0,4,5};
	
	private final String[] audioPlayDriverString={"内核音频播放驱动", "Java音频播放驱动"};
	private final int[] audioPlayDriverValue={0,3};
	
	private final String[] audioRecordDriverString={"内核音频采集驱动", "Java音频采集驱动"};
	private final int[] audioRecordDriverValue={0,3};	
	
	private final String[] videoCapDriverString={"内核视频采集驱动", "Video4Linux驱动", "Java视频采集驱动"};
	private final int[] videoCapDriverValue={0,1,3};	
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        configEntity = ConfigService.LoadConfig(this);
   
        InitialLayout();
    }
    
    private void InitialLayout()
    {   
        this.setTitle("配置");
    	fullLayout =  new LinearLayout(this);
    	fullLayout.setBackgroundColor(Color.WHITE);
    	fullLayout.setOrientation(LinearLayout.VERTICAL);
    	fullLayout.setOnTouchListener(touchListener);
	    
    	
    	mainLayout =  new LinearLayout(this);
    	mainLayout.setBackgroundColor(Color.WHITE);
	    mainLayout.setOrientation(LinearLayout.VERTICAL);
	    mainLayout.setOnTouchListener(touchListener);
	    
	    enableP2PBox = new CheckBox(this);
	    enableP2PBox.setText("启用P2P网络连接");
	    enableP2PBox.setTextColor(Color.BLACK);
	    mainLayout.addView(enableP2PBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    enableP2PBox.setChecked(configEntity.enableP2P != 0);
	    
	    videoOverlayBox = new CheckBox(this);
	    videoOverlayBox.setText("Overlay视频模式");
	    videoOverlayBox.setTextColor(Color.BLACK);
	    mainLayout.addView(videoOverlayBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    videoOverlayBox.setChecked(configEntity.videoOverlay != 0);  
	    
	    videoRotateBox = new CheckBox(this);
	    videoRotateBox.setText("翻转视频");
	    videoRotateBox.setTextColor(Color.BLACK);
	    mainLayout.addView(videoRotateBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    videoRotateBox.setChecked(configEntity.videorotatemode != 0); 
	    
	    fixColorDeviation = new CheckBox(this);
	    fixColorDeviation.setText("本地视频采集偏色修正");
	    fixColorDeviation.setTextColor(Color.BLACK);
	    mainLayout.addView(fixColorDeviation,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    fixColorDeviation.setChecked(configEntity.fixcolordeviation!=0);  
	    
	    videoShowGPURender = new CheckBox(this);
	    videoShowGPURender.setText("启用视频GPU渲染");
	    videoShowGPURender.setTextColor(Color.BLACK);
	    mainLayout.addView(videoShowGPURender,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    videoShowGPURender.setChecked(configEntity.videoShowGPURender!=0); 	    
	    
	    smoothPlayBox = new CheckBox(this);
	    smoothPlayBox.setText("视频平滑播放模式");
	    smoothPlayBox.setTextColor(Color.BLACK);
	    mainLayout.addView(smoothPlayBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    smoothPlayBox.setChecked(configEntity.smoothPlayMode != 0);  	    
	    
	    useARMv6Box = new CheckBox(this);
	    useARMv6Box.setText("强制使用ARMv6指令集（安全模式）");
	    useARMv6Box.setTextColor(Color.BLACK);
	    mainLayout.addView(useARMv6Box,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    useARMv6Box.setChecked(configEntity.useARMv6Lib != 0); 
	    
	    useAECBox = new CheckBox(this);
	    useAECBox.setText("启用回音消除（AEC）");
	    useAECBox.setTextColor(Color.BLACK);
	    mainLayout.addView(useAECBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    useAECBox.setChecked(configEntity.enableAEC != 0); 
	    
	    useHWCodecBox = new CheckBox(this);
	    useHWCodecBox.setText("启用平台内置硬件编解码（需重启应用程序）");
	    useHWCodecBox.setTextColor(Color.BLACK);
	    mainLayout.addView(useHWCodecBox,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
	    useHWCodecBox.setChecked(configEntity.useHWCodec != 0);
	    
    	// 插入音频播放驱动设置
    	audioPlayDriverSpinner = InsertSpinnerInterface("音频播放驱动", audioPlayDriverString, audioPlayDriverValue, configEntity.audioPlayDriver);
    	// 插入音频采集驱动设置
    	audioRecordDriverSpinner = InsertSpinnerInterface("音频采集驱动", audioRecordDriverString, audioRecordDriverValue, configEntity.audioRecordDriver);
     	// 插入视频采集驱动设置
    	videoCapDriverSpinner = InsertSpinnerInterface("视频采集驱动", videoCapDriverString, videoCapDriverValue, configEntity.videoCapDriver);
    	//插入视频显示驱动设置
	    videoShowDriverSpinner = InsertSpinnerInterface("视频显示驱动", videoShowDriverString, videoShowDriverValue, configEntity.videoShowDriver);
	    // 插入配置模式选择项
    	TextView configModeLable = new TextView(this);
    	configModeLable.setTextColor(Color.BLACK);
    	configModeLable.setText("选择配置模式：");
    	mainLayout.addView(configModeLable,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
    	
       	configModeRadioGroup = new RadioGroup(this);
    	configModeServerBtn = new RadioButton(this);
    	configModeCustomBtn = new RadioButton(this);
       	configModeServerBtn.setTextColor(Color.BLACK);
    	configModeCustomBtn.setTextColor(Color.BLACK);
    	configModeServerBtn.setText("服务器配置参数");
    	configModeCustomBtn.setText("自定义配置参数");
    	configModeRadioGroup.addView(configModeServerBtn);
    	configModeRadioGroup.addView(configModeCustomBtn);
    	configModeServerBtn.setOnClickListener(listener);
    	configModeCustomBtn.setOnClickListener(listener);

    	if(configEntity.configMode == ConfigEntity.VIDEO_MODE_SERVERCONFIG)
    		configModeServerBtn.setChecked(true);
    	else
    		configModeCustomBtn.setChecked(true);
    	
    	mainLayout.addView(configModeRadioGroup,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
    	    	
    	//插入视频分辨率
    	resolutionLable = new TextView(this);
    	resolutionLable.setTextColor(Color.BLACK);
    	resolutionLable.setText("选择视频分辨率：");
    	mainLayout.addView(resolutionLable,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
    	
    	
    	videoSizeSpinner = new Spinner(this);
    	LinearLayout.LayoutParams videoSizeLP = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
    	videoSizeLP.gravity = Gravity.RIGHT;
    	mainLayout.addView(videoSizeSpinner,videoSizeLP);
    	ArrayAdapter<String> videoSizeAdapter; 
    	videoSizeAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item,videoSizeString);  
    	videoSizeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);  
    	videoSizeSpinner.setAdapter(videoSizeAdapter);  
    	videoSizeSpinner.setVisibility(View.VISIBLE);
    	int iSelectVideoSize = 0;
    	for(int i=0; i<videoWidthValue.length; i++)
    	{
    		if(videoWidthValue[i] == configEntity.resolution_width)
    		{
    			iSelectVideoSize = i;
    			break;
    		}
    	}
    	videoSizeSpinner.setSelection(iSelectVideoSize);

    	//插入码率
    	videoBitrateSpinner = InsertSpinnerInterface("选择视频码率", videoBitrateString, videoBitrateValue, configEntity.videoBitrate);
    	//插入帧率
    	videoFPSSpinner = InsertSpinnerInterface("选择视频帧率", videofpsString, videofpsValue, configEntity.videoFps); 	
    	//插入视频质量
    	videoQualitySpinner = InsertSpinnerInterface("选择视频质量", videoQualityString, videoQualityValue, configEntity.videoQuality);
    	// 插入视频预设参数
    	videoPresetSpinner = InsertSpinnerInterface("选择视频预设参数", videoPresetString, videoPresetValue, configEntity.videoPreset);
    	
    	// 根据配置模式，确定是否需要显示自定义的配置项
    	CustomControlsShow(configEntity.configMode == 0 ? false : true);
    	
    	//加入底部按钮
    	LinearLayout btnLayout =  new LinearLayout(this);
    	btnLayout.setOrientation(LinearLayout.HORIZONTAL);
    	
    	saveBtn = new Button(this);
    	saveBtn.setText("保存设置");
    	btnLayout.addView(saveBtn,new LayoutParams(ScreenInfo.WIDTH,LayoutParams.WRAP_CONTENT));
    	saveBtn.setOnClickListener(listener);

    	
        ScrollView sv = new ScrollView(this);
        sv.addView(mainLayout);
    	fullLayout.addView(sv,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT*8/10));
    	
    	fullLayout.addView(btnLayout,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT/10));
    	this.setContentView(fullLayout);

    }
    
    OnClickListener listener = new OnClickListener()
    {       
		public void onClick(View v) 
		{
			if(v == saveBtn)
			{
				SaveConfig();
			}
			else if(v == configModeServerBtn)
			{
				CustomControlsShow(false);
			}
			else if(v == configModeCustomBtn)
			{
				CustomControlsShow(true);
			}
		}
    };
    
    private void CustomControlsShow(boolean bEnable)
    {
    	videoSizeSpinner.setEnabled(bEnable);
		videoBitrateSpinner.setEnabled(bEnable);
		videoFPSSpinner.setEnabled(bEnable);
		videoQualitySpinner.setEnabled(bEnable);
		videoPresetSpinner.setEnabled(bEnable);
    }
    
    private void SaveConfig()
    {
    	configEntity.configMode = configModeServerBtn.isChecked() ? ConfigEntity.VIDEO_MODE_SERVERCONFIG : ConfigEntity.VIDEO_MODE_CUSTOMCONFIG;
    	
    	configEntity.resolution_width = videoWidthValue[videoSizeSpinner.getSelectedItemPosition()];
    	configEntity.resolution_height = videoHeightValue[videoSizeSpinner.getSelectedItemPosition()];
    	configEntity.videoBitrate = videoBitrateValue[videoBitrateSpinner.getSelectedItemPosition()];
    	configEntity.videoFps = videofpsValue[videoFPSSpinner.getSelectedItemPosition()];    	
    	configEntity.videoQuality = videoQualityValue[videoQualitySpinner.getSelectedItemPosition()];  
    	configEntity.videoPreset = videoPresetValue[videoPresetSpinner.getSelectedItemPosition()]; 

    	configEntity.videoOverlay = videoOverlayBox.isChecked() ? 1 : 0;
    	configEntity.videorotatemode = videoRotateBox.isChecked() ? 1 : 0;
    	configEntity.fixcolordeviation = fixColorDeviation.isChecked() ? 1 : 0;
    	configEntity.videoShowGPURender = videoShowGPURender.isChecked() ? 1 : 0;
    	if(configEntity.videoCapDriver==1)			// Video4Linux驱动不支持Overlay模式
    		configEntity.videoOverlay = 0;

    	configEntity.smoothPlayMode = smoothPlayBox.isChecked() ? 1 : 0;
    	
    	configEntity.enableP2P = enableP2PBox.isChecked() ? 1 : 0;
    	configEntity.useARMv6Lib = useARMv6Box.isChecked() ? 1 : 0;
    	configEntity.enableAEC = useAECBox.isChecked() ? 1 : 0;
     	configEntity.useHWCodec = useHWCodecBox.isChecked() ? 1 : 0;
     	configEntity.videoShowDriver = videoShowDriverValue[videoShowDriverSpinner.getSelectedItemPosition()];
     	configEntity.audioPlayDriver = audioPlayDriverValue[audioPlayDriverSpinner.getSelectedItemPosition()];     	
     	configEntity.audioRecordDriver = audioRecordDriverValue[audioRecordDriverSpinner.getSelectedItemPosition()];
     	configEntity.videoCapDriver = videoCapDriverValue[videoCapDriverSpinner.getSelectedItemPosition()];     	
    	ConfigService.SaveConfig(this, configEntity);
		
		this.setResult(HallActivity.ACTIVITY_ID_VIDEOCONFIG);
		this.finish();
    }
    
    
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
	    				((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(VideoConfigActivity.this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
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
    
    private Spinner InsertSpinnerInterface(String caption, String[] context, int[] value, int select) {
    	TextView lable = new TextView(this);
    	lable.setTextColor(Color.BLACK);
    	lable.setText(caption+"：");
    	mainLayout.addView(lable,new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT));
    	
    	Spinner spinner = new Spinner(this);
    	LinearLayout.LayoutParams LP = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
    	LP.gravity = Gravity.RIGHT;
    	mainLayout.addView(spinner,LP);
    	ArrayAdapter<String> Adapter; 
    	Adapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item, context);  
    	Adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);  
    	spinner.setAdapter(Adapter);  
    	spinner.setVisibility(View.VISIBLE);
    	int offset = 0;
    	for(int i=0; i<value.length; i++)
    	{
    		if(value[i] == select)
    		{
    			offset = i;
    			break;
    		}
    	}
    	spinner.setSelection(offset);
    	return spinner;
    }

}
