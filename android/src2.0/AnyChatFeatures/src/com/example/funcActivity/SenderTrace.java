package com.example.funcActivity;

import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.anychatfeatures.R;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.ContactsContract.CommonDataKinds.Im;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class SenderTrace extends Activity implements AnyChatBaseEvent{
	private String TAG = "AnyChatx";
	
	private final int MSG_UPDATETRACE = 1;	
	private int msClientSenderPacket;
	private int msClientReceiverPacket;
	private int msServerReceiverPacket;
	
	private TextView mClientIPAddress;
	private TextView mClientSenderPacket;
	private TextView mClentReceiverPacket;
	private TextView mLostPacketRate;
	
	private TextView mServerIPAddress;
	private TextView mServerReceiverPacket;
	private ImageView mSenderServerIcon;
	private int [] mSenderServerIconID = {R.drawable.server1, R.drawable.server2, R.drawable.server3};
	private int mServerIconIndex = 1;
	
	private EditText mControlSpeed;
	private Button mStartDebug;
	private Button mEndDebug;	
	
	private ImageButton btnBack;		  // 返回
	private TextView titleName;			  // 标题
	private ImageButton btnSet;
	
	private ImageView []mSenderDown = new ImageView[3];
	private ImageView []mSenderUp = new ImageView[3];
	private int mPacketIconTransfeIndex = 1;
	
	private Handler mHandler;
	private TimerTask mTimerTask;
	private Timer mTimer = null;
	private AnyChatCoreSDK anyChatSDK;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.sender_trace);
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		
		initLayout();		
		updateTime();
	}
	
	private void initLayout(){
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		String strIP = preferences.getString("UserIP", "demo.anychat.cn");
		
		mClientIPAddress = (TextView)findViewById(R.id.clientIPAddress);
		mClientSenderPacket = (TextView)findViewById(R.id.clientSenderPacket);
		mClentReceiverPacket = (TextView)findViewById(R.id.clentReceiverPacket);
		mLostPacketRate = (TextView)findViewById(R.id.lostPacketRate);
		
		mServerIPAddress = (TextView)findViewById(R.id.serverIPAddress);
		mServerReceiverPacket = (TextView)findViewById(R.id.serverReceiverPacket);
		mSenderServerIcon = (ImageView)findViewById(R.id.senderServerIcon);
		
		mControlSpeed = (EditText)findViewById(R.id.controlSpeed);
		mStartDebug = (Button)findViewById(R.id.startDebug);
		mEndDebug = (Button)findViewById(R.id.endDebug);
		
		btnBack = (ImageButton) this.findViewById(R.id.btnBack);
		titleName = (TextView) this.findViewById(R.id.titleName);
		btnSet = (ImageButton) this.findViewById(R.id.btnSet);
		
		mSenderDown[0] = (ImageView)this.findViewById(R.id.senderDown1);
		mSenderDown[1] = (ImageView)this.findViewById(R.id.senderDown2);
		mSenderDown[2] = (ImageView)this.findViewById(R.id.senderDown3);
		mSenderUp[0] = (ImageView)this.findViewById(R.id.senderUp1);
		mSenderUp[1] = (ImageView)this.findViewById(R.id.senderUp2);
		mSenderUp[2] = (ImageView)this.findViewById(R.id.senderUp3);		
		
		mStartDebug.setOnClickListener(onClickListener);
		mEndDebug.setOnClickListener(onClickListener);
		btnBack.setOnClickListener(onClickListener);
		btnSet.setVisibility(View.INVISIBLE);
		titleName.setText("网络检测评估");
		
		mClientIPAddress.setText("IP地址：" + anyChatSDK.GetUserIPAddr(-1));
		
		mClientSenderPacket.setText("发送数据包：0");
		mClentReceiverPacket.setText("收到的数据：0");
		mLostPacketRate.setText("丢包率：0.00%");
		
		mServerIPAddress.setText("IP地址：" + strIP);
		mServerReceiverPacket.setText("收到数据包：0");
		mControlSpeed.setText("100");		
	}
	
	OnClickListener onClickListener = new OnClickListener() {

		@Override
		public void onClick(View arg0) {
			switch (arg0.getId()) {
			case R.id.startDebug:
				int ControlSpeed = Integer.parseInt(mControlSpeed.getText().toString().trim());
				if (ControlSpeed > 0) {
					AnyChatCoreSDK.SetSDKOptionInt(161, 1000);
					AnyChatCoreSDK.SetSDKOptionInt(162, ControlSpeed*1000);
					AnyChatCoreSDK.SetSDKOptionInt(163, 1);
					
					mStartDebug.setVisibility(View.GONE);
					mEndDebug.setVisibility(View.VISIBLE);
					
					initUpdateTraceTimer();
				}
				
				break;
			case R.id.endDebug:
				if (mTimer != null) {
					mTimer.cancel();
					mTimer = null;
					AnyChatCoreSDK.SetSDKOptionInt(163, 0);
					mSenderServerIcon.setImageResource(mSenderServerIconID[0]);
					mStartDebug.setVisibility(View.VISIBLE);
					mEndDebug.setVisibility(View.GONE);
				}
				break;
			case R.id.btnBack:
				finish();
				break;
			default:
				break;
			}
		}
	};
	
	// 1秒刷新一下界面数据和动画
	private void updateTime(){
		mHandler = new Handler(){
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch (msg.what) {
				case MSG_UPDATETRACE:
					msClientSenderPacket = AnyChatCoreSDK.GetSDKOptionInt(166);
					msClientReceiverPacket = AnyChatCoreSDK.GetSDKOptionInt(164);
					msServerReceiverPacket = AnyChatCoreSDK.GetSDKOptionInt(165);
					float lostPacketRate;
					if ((msClientSenderPacket - msClientReceiverPacket) < 0) {
						lostPacketRate = 0.f;
					}else {
						lostPacketRate = (((float)(msClientSenderPacket - msClientReceiverPacket)/(float)msClientSenderPacket) * 100.f);
					}
					
					mClientSenderPacket.setText("发送数据包：" + msClientSenderPacket);
					mClentReceiverPacket.setText("收到的数据：" + msClientReceiverPacket);
					mLostPacketRate.setText("丢包率：" + String.format("%.2f", lostPacketRate) + "%");
					
					mServerReceiverPacket.setText("收到数据包：" + msServerReceiverPacket);
					
					// 刷新服务器接受动画
					if (mServerIconIndex >= 3) {
						mServerIconIndex = 0;
					}else {
						mSenderServerIcon.setImageResource(mSenderServerIconID[mServerIconIndex]);
						mServerIconIndex++;
					}
					
					// 刷新数据包传输动画
					if (mPacketIconTransfeIndex >= 3) {
						mPacketIconTransfeIndex = 0;
					}
					
					for (int i = 0; i < 3; i++) {
						if(i == mPacketIconTransfeIndex){
							mSenderDown[i].setImageResource(R.drawable.red_down);
							mSenderUp[2-i].setImageResource(R.drawable.red_up);
						}else {
							mSenderDown[i].setImageResource(R.drawable.blue_down);
							mSenderUp[2-i].setImageResource(R.drawable.blue_up);
						}
					}
					
					mPacketIconTransfeIndex++;
					break;
				default:
					break;
				}
			}
		};
	}
	
	private void initUpdateTraceTimer(){
		if (mTimer == null) {
			mTimer = new Timer();
		}
		
		mTimerTask = new TimerTask() {
			
			@Override
			public void run() {
				mHandler.sendEmptyMessage(MSG_UPDATETRACE);				
			}
		};
		
		mTimer.schedule(mTimerTask, 1000, 1000);
	}
	
	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		if (mTimer != null) {
			mTimer.cancel();
			mTimer = null;
			if (anyChatSDK != null)
				anyChatSDK.removeEvent(this);
			AnyChatCoreSDK.SetSDKOptionInt(163, 0);
		}
	}
	
	private void destroyCurActivity() {
		onPause();
		onDestroy();
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
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
		destroyCurActivity();
		finish();
	}
}
