package com.bairuitech.demo;

import java.util.ArrayList;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;

import android.R.color;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

// 可视电话界面
public class VideoCallActivity extends Activity implements AnyChatBaseEvent{
	private LinearLayout fullLayout;
	private LinearLayout mainLayout;
		private ListView userListView;

	public AnyChatCoreSDK anychat;
	private BaseAdapter userListAdapter;
	private ArrayList<String> idList = new ArrayList<String> ();
	private ArrayList<String> userList = new ArrayList<String> ();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        userListAdapter=new UserListAdapter(this);
        InitialSDK();
        Intent intent = getIntent();
        intent.getIntExtra("RoomID",0);
        InitialLayout();

    }
    private void InitialSDK()
    {
        anychat = AnyChatCoreSDK.getInstance(VideoCallActivity.this);
        anychat.SetBaseEvent(this);
    }
    
    private void InitialLayout()
    {   
    	this.setTitle("视频电话");

    	fullLayout =  new LinearLayout(this);
    	fullLayout.setBackgroundResource(R.drawable.videophonebk);
    	//fullLayout.setBackgroundColor(Color.WHITE);
    	fullLayout.setOrientation(LinearLayout.VERTICAL);
    	fullLayout.setOnTouchListener(touchListener);
	    
    	mainLayout =  new LinearLayout(this);
    	mainLayout.setBackgroundColor(Color.TRANSPARENT);
	    mainLayout.setOrientation(LinearLayout.VERTICAL);
	    mainLayout.setOnTouchListener(touchListener);
	    
    	LinearLayout sendLayout =  new LinearLayout(this);
    	sendLayout.setOrientation(LinearLayout.HORIZONTAL);

		TextView tv =  new TextView(this);
		tv.setBackgroundColor(Color.GRAY);
		tv.setTextColor(Color.WHITE);
		tv.setPadding(0, 2, 0, 2);
		tv.setTextSize(18);
		tv.setText("在线好友");
		tv.setBackgroundColor(Color.GRAY);
		mainLayout.addView(tv,new LayoutParams(LayoutParams.FILL_PARENT,ScreenInfo.HEIGHT*1/20));

		userListView = new ListView(this);
		userListView.setBackgroundColor(Color.TRANSPARENT);
		userListView.setCacheColorHint(0);
		userListView.setTranscriptMode(ListView.TRANSCRIPT_MODE_ALWAYS_SCROLL);
		userListView.setAdapter(userListAdapter);
		userListView.setOnItemClickListener(itemClickListener);
		LinearLayout.LayoutParams layoutParams=new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT );
		layoutParams.weight=1;
		mainLayout.addView(userListView,layoutParams);;
    	fullLayout.addView(mainLayout,new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.FILL_PARENT));
    	this.setContentView(fullLayout);
    }
    

    OnItemClickListener itemClickListener=new OnItemClickListener() {

  		@Override
  		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
  				long arg3) {
  			// TODO Auto-generated method stub
  			StartVideoChat(arg2);
  		}
  	};
    public void StartVideoChat(int position)
    {
		   Intent intent=new Intent();
		   intent.putExtra("UserID", idList.get(position));
		   intent.setClass(VideoCallActivity.this, VideoActivity.class);
	       startActivity(intent);
    }
      public class UserListAdapter extends BaseAdapter 
  	{
  		private Context context;

  		public UserListAdapter(Context context) {
  			this.context = context;
  		}

  		@Override
  		public int getCount() {
  			return userList.size();
  		}

  		@Override
  		public Object getItem(int position) {
  			return userList.get(position);
  		}

  		@Override
  		public long getItemId(int position) {
  			return position;
  		}

  		@Override
  		public View getView(int position, View convertView, ViewGroup parent) {
  			TextView tv =  new TextView(context);
  			tv.setTextColor(Color.YELLOW);
  			tv.setPadding(4, 4, 4, 4);
  			tv.setTextSize(24);
  			tv.setBackgroundColor(color.black);
  			tv.setText(userList.get(position));
  			return tv;
  		}
  	}
    
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
	    				((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(VideoCallActivity.this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
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
    
    protected void onDestroy(){

 	   anychat.LeaveRoom(-1);
 	   anychat.removeEvent(this);
    	super.onDestroy();
    }
    
    protected void onResume() {
        anychat.SetBaseEvent(this);
        idList.clear();
        userList.clear();
        int[] userID = anychat.GetOnlineUser();
    	for(int i=0; i<userID.length ; i++)
    	{
    		idList.add(""+userID[i]);
    	}
    	for(int i=0; i<userID.length ; i++)
    	{
    		userList.add(anychat.GetUserName(userID[i]));
    	}
    	userListAdapter.notifyDataSetChanged();
        super.onResume();
    }
    
	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub


	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub
		
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
		if(bEnter)
		{
			idList.add(""+dwUserId);
    		userList.add(anychat.GetUserName(dwUserId));
    		userListAdapter.notifyDataSetChanged();
		}
		else
		{
			for(int i=0;i<idList.size();i++)
			{
				if(idList.get(i).equals(""+dwUserId))
				{
					idList.remove(i);
					userList.remove(i);
					userListAdapter.notifyDataSetChanged();
				}
			}
		}
	}


}
