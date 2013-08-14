package com.bairuitech.demo;

import java.util.ArrayList;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatTextMsgEvent;

import android.R.color;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

public class RoomActivity extends Activity implements AnyChatBaseEvent,AnyChatTextMsgEvent{
	private LinearLayout fullLayout;
	private LinearLayout mainLayout;
	private Button sendBtn;

	private ListView userListView;
	private MessageListView messageListView;
	private BaseAdapter userListAdapter;
	
	public AnyChatCoreSDK anychat;
	
	private ArrayList<String> idList = new ArrayList<String> ();
	private ArrayList<String> userList = new ArrayList<String> ();
	private ArrayList<String> messageList = new ArrayList<String> ();
	
	private EditText messageEditText;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        userListAdapter=new UserListListAdapter(this);
        InitialSDK();
        Intent intent = getIntent();
        intent.getIntExtra("RoomID",0);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        InitialLayout();

    }
    
    private void InitialSDK()
    {
        anychat = new AnyChatCoreSDK();
        anychat.SetBaseEvent(this);
        anychat.SetTextMessageEvent(this);
    }
    private void InitialLayout()
    {   
    	this.setTitle("视频聊天");

    	fullLayout =  new LinearLayout(this);
    	fullLayout.setBackgroundResource(R.drawable.chat_bk);
    	//fullLayout.setBackgroundColor(Color.WHITE);
    	fullLayout.setOrientation(LinearLayout.VERTICAL);
    	fullLayout.setOnTouchListener(touchListener);
	    
    	
    	mainLayout =  new LinearLayout(this);
    	mainLayout.setBackgroundColor(Color.TRANSPARENT);
	    mainLayout.setOrientation(LinearLayout.VERTICAL);
	    mainLayout.setOnTouchListener(touchListener);
	    
    	LinearLayout sendLayout =  new LinearLayout(this);
    	sendLayout.setOrientation(LinearLayout.HORIZONTAL);

		messageEditText = new EditText(this);
	    sendBtn  = new Button(this);
	    sendBtn.setText("发送");
		sendBtn.setOnClickListener(listener);
	    
		sendLayout.addView(messageEditText,new LayoutParams(ScreenInfo.WIDTH*4/5,LayoutParams.FILL_PARENT));
		sendLayout.addView(sendBtn,new LayoutParams(ScreenInfo.WIDTH/5,LayoutParams.FILL_PARENT));
		mainLayout.addView(sendLayout,new LayoutParams(LayoutParams.FILL_PARENT,ScreenInfo.HEIGHT/10));
	    
		TextView tvMessage =  new TextView(this);
		tvMessage.setTextColor(Color.WHITE);
		tvMessage.setPadding(0, 2, 0, 2);
		tvMessage.setTextSize(18);
		tvMessage.setText("消息记录");
		tvMessage.setBackgroundColor(Color.GRAY);
		mainLayout.addView(tvMessage,new LayoutParams(LayoutParams.FILL_PARENT,ScreenInfo.HEIGHT*1/20));

		
		messageListView = new MessageListView(this);
		messageListView.SetFileList(messageList);
		
		mainLayout.addView(messageListView,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT*4/10));
		
		TextView tv =  new TextView(this);
		tv.setBackgroundColor(Color.GRAY);
		tv.setTextColor(Color.WHITE);
		tv.setPadding(0, 2, 0, 2);
		tv.setTextSize(18);
		tv.setText("在线人员");
		tv.setBackgroundColor(Color.GRAY);
		mainLayout.addView(tv,new LayoutParams(LayoutParams.FILL_PARENT,ScreenInfo.HEIGHT*1/20));

		userListView = new ListView(this);
		userListView.setCacheColorHint(0);
		userListView.setBackgroundColor(Color.TRANSPARENT);
		userListView.setAdapter(userListAdapter);
		userListView.setOnItemClickListener(itemClickListener);
		LinearLayout.LayoutParams layoutParams=new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT,
				LayoutParams.WRAP_CONTENT );
		layoutParams.weight=1;
		mainLayout.addView(userListView,layoutParams);
    	fullLayout.addView(mainLayout,new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.FILL_PARENT));
    	//fullLayout.addView(btnLayout,new LayoutParams(ScreenInfo.WIDTH,ScreenInfo.HEIGHT/10));
    	this.setContentView(fullLayout);
    }
    
    OnClickListener listener = new OnClickListener()
    {       
		public void onClick(View v) 
		{
			if(v == sendBtn)
			{
				SendMessage();
			}		
		}
    };
    OnItemClickListener itemClickListener=new OnItemClickListener() {

		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			// TODO Auto-generated method stub
			StartVideoChat(arg2);
		}
	};
    public class UserListListAdapter extends BaseAdapter 
	{
		private Context context;

		public UserListListAdapter(Context context) {
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
    
    private void SendMessage()
    {
		anychat.SendTextMessage(-1, 0, messageEditText.getText().toString());
		messageList.add("我说: "+ messageEditText.getText().toString());
		//messageListView.setStackFromBottom(true);
		messageListView.SetFileList(messageList);
		messageEditText.setText("");
		messageListView.setSelection(messageListView.getAdapter().getCount()-1);


    }
    
    public void StartVideoChat(int position)
    {
		   Intent intent=new Intent();
		   intent.putExtra("UserID", idList.get(position));
		   intent.setClass(RoomActivity.this, VideoActivity.class);
	       startActivity(intent);
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
	    				((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(RoomActivity.this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS); 
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
		Log.e("******RoomActivity***********", "RoomActivity  onDestroy");	
 	   anychat.LeaveRoom(-1);
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
		Log.e("********RoomActivity*********", "OnAnyChatEnterRoomMessage");	

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
		Log.e("********RoomActivity*********", "OnAnyChatOnlineUserMessage   "+dwUserNum);	

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
	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		messageList.add(anychat.GetUserName(dwFromUserid)+"说: "+message);
		//messageListView.setStackFromBottom(true);
		messageListView.SetFileList(messageList);
		messageListView.setSelection(messageListView.getAdapter().getCount()-1);
		//messageListView.scrollTo(0, Integer.MAX_VALUE);		
	}

}
