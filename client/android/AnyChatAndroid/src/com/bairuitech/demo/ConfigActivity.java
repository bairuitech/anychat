package com.bairuitech.demo;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

public class ConfigActivity extends Activity{
	private LinearLayout fullLayout;
	private LinearLayout mainLayout;
	private Button saveBtn;
	private ConfigEntity configEntity;
	private EditText ipEditText;
	private EditText portEditText;
	
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
    	
		LayoutParams normalEditLayoutLp =  new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
    	
    	//加入IP
    	LinearLayout ipLayout =  new LinearLayout(this);
    	ipLayout.setPadding(10, 0, 0, 0);
    	ipLayout.setOrientation(LinearLayout.HORIZONTAL);
    	
    	TextView ipLabel = new TextView(this);
    	ipLabel.setTextColor(Color.BLACK);
    	ipLabel.setText("IP地址：");
    	ipLayout.addView(ipLabel,new LayoutParams(ScreenInfo.WIDTH/5,LayoutParams.WRAP_CONTENT));
    	
    	ipEditText = new  EditText(this);
    	ipEditText.setText(configEntity.ip);

    	ipLayout.addView(ipEditText,new LayoutParams(ScreenInfo.WIDTH*4/5-20,LayoutParams.WRAP_CONTENT));
    	mainLayout.addView(ipLayout,normalEditLayoutLp);
    	
    	//加入用户名
    	LinearLayout portLayout =  new LinearLayout(this);
    	portLayout.setPadding(10, 0, 0, 0);
    	portLayout.setOrientation(LinearLayout.HORIZONTAL);
    	
    	TextView portLabel = new TextView(this);
    	portLabel.setTextColor(Color.BLACK);
    	portLabel.setText("端口：");
    	portLayout.addView(portLabel,new LayoutParams(ScreenInfo.WIDTH/5,LayoutParams.WRAP_CONTENT));
    	
    	portEditText = new  EditText(this);
    	portEditText.setText(""+configEntity.port);

    	portLayout.addView(portEditText,new LayoutParams(ScreenInfo.WIDTH*4/5-20,LayoutParams.WRAP_CONTENT));
    	mainLayout.addView(portLayout,normalEditLayoutLp);
    	
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
		}
    };
    
    private void SaveConfig()
    {
    	configEntity.ip = ipEditText.getText().toString();
    	configEntity.port = Integer.parseInt(portEditText.getText().toString());

    	ConfigService.SaveConfig(this, configEntity);
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
	    				((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(ConfigActivity.this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
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

}
