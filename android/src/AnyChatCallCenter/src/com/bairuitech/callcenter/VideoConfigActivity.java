package com.bairuitech.callcenter;

import com.bairuitech.util.ConfigService;
import com.bairuitech.util.ConfigEntity;
import com.bairuitech.util.ScreenInfo;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Spinner;

public class VideoConfigActivity extends Activity{
	private Button saveBtn;
	private ConfigEntity configEntity;
	
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
	private CheckBox videoAutoRotation;
	private Spinner videoSizeSpinner;
	private Spinner videoBitrateSpinner;
	private Spinner videoFPSSpinner;
	private Spinner videoQualitySpinner;
	private Spinner videoPresetSpinner;

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
	private final int[] videoPresetValue={1,2,3,4,5};
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        configEntity = ConfigService.LoadConfig(this);
        setContentView(R.layout.videoconfig);
        getScrennInfo();
        InitialLayout();
    }
    private void getScrennInfo()
    {
    	DisplayMetrics dMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dMetrics);
		ScreenInfo.WIDTH=dMetrics.widthPixels;
		ScreenInfo.HEIGHT=dMetrics.heightPixels;
    }
    private void InitialLayout()
    {   
        this.setTitle("配置");
        
        // 启用P2P网络连接
	    enableP2PBox =  (CheckBox)this.findViewById(R.id.enableP2PBox);
	    enableP2PBox.setTextColor(Color.BLACK);
	    enableP2PBox.setChecked(configEntity.enableP2P != 0);
	    
	    // Overlay视频模式
	    videoOverlayBox = (CheckBox)this.findViewById(R.id.videoOverlayBox);
	    videoOverlayBox.setTextColor(Color.BLACK);
	    videoOverlayBox.setChecked(configEntity.videoOverlay != 0);  
	    
	    // 翻转视频
	    videoRotateBox = (CheckBox)this.findViewById(R.id.videoRotateBox);
	    videoRotateBox.setTextColor(Color.BLACK);
	    videoRotateBox.setChecked(configEntity.videorotatemode != 0); 
	    
	    // 本地视频采集偏色修正
	    fixColorDeviation = (CheckBox)this.findViewById(R.id.fixColorDeviation);
	    fixColorDeviation.setTextColor(Color.BLACK);
	    fixColorDeviation.setChecked(configEntity.fixcolordeviation!=0);  
	    
	    // 启用视频GPU渲染
	    videoShowGPURender = (CheckBox)this.findViewById(R.id.videoShowGPURender);
	    videoShowGPURender.setTextColor(Color.BLACK);
	    videoShowGPURender.setChecked(configEntity.videoShowGPURender!=0); 	    
	    
	    //本地视频跟随设备自动旋转
	    videoAutoRotation = (CheckBox)this.findViewById(R.id.videoAutoRotation);
	    videoAutoRotation.setTextColor(Color.BLACK);
	    videoAutoRotation.setChecked(configEntity.videoAutoRotation != 0);  	    
	  
	    // 强制使用ARMv6指令集（安全模式）
	    useARMv6Box = (CheckBox)this.findViewById(R.id.useARMv6Box);
	    useARMv6Box.setTextColor(Color.BLACK);
	    useARMv6Box.setChecked(configEntity.useARMv6Lib != 0); 
	    
	    // 启用回音消除（AEC）
	    useAECBox = (CheckBox)this.findViewById(R.id.useAECBox);
	    useAECBox.setTextColor(Color.BLACK);
	    useAECBox.setChecked(configEntity.enableAEC != 0); 
	    
	    // 启用平台内置硬件编解码（需重启应用程序）
	    useHWCodecBox = new CheckBox(this);
	    useHWCodecBox.setTextColor(Color.BLACK);
	    useHWCodecBox.setChecked(configEntity.useHWCodec != 0);
	    
	    // 插入配置模式选择项
    	TextView configModeLable = (TextView)this.findViewById(R.id.configModelLable);
    	configModeLable.setTextColor(Color.BLACK);
   	
    	configModeServerBtn = (RadioButton)findViewById(R.id.serverModelConfigBtn);
    	configModeCustomBtn = (RadioButton)findViewById(R.id.customModelConfigBtn);
       	configModeServerBtn.setTextColor(Color.BLACK);
    	configModeCustomBtn.setTextColor(Color.BLACK);
    	configModeServerBtn.setOnClickListener(listener);
    	configModeCustomBtn.setOnClickListener(listener);

    	if(configEntity.configMode == ConfigEntity.VIDEO_MODE_SERVERCONFIG)
    		configModeServerBtn.setChecked(true);
    	else
    		configModeCustomBtn.setChecked(true);
    		    	
    	//插入视频分辨率
    	resolutionLable = (TextView)this.findViewById(R.id.resolutionTV);
    	resolutionLable.setTextColor(Color.BLACK);
    	resolutionLable.setText("选择视频分辨率：");

    	videoSizeSpinner = (Spinner)this.findViewById(R.id.videoSizeSpinner);
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
    	videoBitrateSpinner = InsertSpinnerInterface(1, videoBitrateString, videoBitrateValue, configEntity.videoBitrate);
    	//插入帧率
    	videoFPSSpinner = InsertSpinnerInterface(2, videofpsString, videofpsValue, configEntity.videoFps); 	
    	//插入视频质量
    	videoQualitySpinner = InsertSpinnerInterface(3, videoQualityString, videoQualityValue, configEntity.videoQuality);
    	// 插入视频预设参数
    	videoPresetSpinner = InsertSpinnerInterface(4, videoPresetString, videoPresetValue, configEntity.videoPreset);
    	
    	// 根据配置模式，确定是否需要显示自定义的配置项
    	CustomControlsShow(configEntity.configMode == 0 ? false : true);
    	
    	//加入底部按钮
    	LinearLayout btnLayout =  new LinearLayout(this);
    	btnLayout.setOrientation(LinearLayout.HORIZONTAL);
    	
    	saveBtn =  (Button)this.findViewById(R.id.saveBtn);

    	saveBtn.setOnClickListener(listener);
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

    	configEntity.videoAutoRotation = videoAutoRotation.isChecked() ? 1 : 0;
    	
    	configEntity.enableP2P = enableP2PBox.isChecked() ? 1 : 0;
    	configEntity.useARMv6Lib = useARMv6Box.isChecked() ? 1 : 0;
    	configEntity.enableAEC = useAECBox.isChecked() ? 1 : 0;
     	configEntity.useHWCodec = useHWCodecBox.isChecked() ? 1 : 0;   	
    	ConfigService.SaveConfig(this, configEntity);
		
		this.setResult(RESULT_OK);
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
    
    private Spinner InsertSpinnerInterface(int spinnerIndex, String[] context, int[] value, int select) {
    	Spinner spinner = null;
		if (spinnerIndex == 1){
			spinner = (Spinner)this.findViewById(R.id.videoBitrateSpinner);
		}else if (spinnerIndex == 2) {
			spinner = (Spinner)this.findViewById(R.id.videoFPSSpinner);
		}else if (spinnerIndex == 3) {
			spinner = (Spinner)this.findViewById(R.id.videoQualitySpinner);
		}else if (spinnerIndex == 4) {
			spinner = (Spinner)this.findViewById(R.id.videoPresetSpinner);
		}
		
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
