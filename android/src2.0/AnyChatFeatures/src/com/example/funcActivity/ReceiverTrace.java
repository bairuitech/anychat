package com.example.funcActivity;

import java.util.Timer;
import java.util.TimerTask;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.anychatfeatures.R;
import com.example.common.ValueUtils;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class ReceiverTrace extends Activity implements AnyChatBaseEvent{
	private final int MSG_UPDATETRACE = 1;
	private int msClientSenderPacket;			// 客户端发送的数据包
	private int msReceiverGetPacket;			// 接受者受到的数据包
	private int msServerReceiverPacket;			// 服务器接受到的数据包
	
	private TextView mRSenderIPAddress;
	private TextView mRSenderPacket;
	
	private TextView mRServerIPAddress;
	private TextView mRServerReceiverPacket;
	private ImageView mRServerIcon;
	private int [] mRServerIconID = {R.drawable.server1, R.drawable.server2, R.drawable.server3};// 服务器动画三图片
	private int mServerIconIndex = 1;
	
	private TextView mRReceiverIPAddress;
	private TextView mRReceiverGetPacket;
	private TextView mRReceiverLostRate;

	private ImageButton btnBack;		  // 返回
	private TextView titleName;			  // 标题
	private ImageButton btnSet;		      // 标题
	
	// 数据传送箭头动画图标
	private ImageView []mRSendDown = new ImageView[3];
	private ImageView []mRSendUp = new ImageView[3];
	private ImageView []mReceiverDown = new ImageView[3];
	private int mPacketIconTransfeIndex = 1;
	
	
	private Handler mHandler;
	private TimerTask mTimerTask;
	private Timer mTimer = null;
	
	private AnyChatCoreSDK anyChatSDK;
	private String strSenderIP;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.reeciver_trace);

		anyChatSDK = AnyChatCoreSDK.getInstance(this);
		anyChatSDK.SetBaseEvent(this);
		
		initLayout();
		updateTime();
		initUpdateTraceTimer();
	}

	private void initLayout(){
		SharedPreferences preferences = getSharedPreferences("LoginInfo", 0);
		String strIP = preferences.getString("UserIP", "demo.anychat.cn");
		
		mRSenderIPAddress = (TextView)findViewById(R.id.rSenderIPAddress);
		mRSenderPacket = (TextView)findViewById(R.id.senderPacket);
		
		mRServerIPAddress = (TextView)findViewById(R.id.rServerIPAddress);
		mRServerReceiverPacket = (TextView)findViewById(R.id.rServerReceiverPacket);
		mRServerIcon = (ImageView)findViewById(R.id.rServerIcon);
		
		mRReceiverIPAddress = (TextView)findViewById(R.id.rReceiverIPAddress);
		mRReceiverGetPacket = (TextView)findViewById(R.id.rReceiverGetPacket);
		mRReceiverLostRate = (TextView)findViewById(R.id.rReceiverLostRate);
		
		btnBack = (ImageButton) this.findViewById(R.id.btnBack);
		titleName = (TextView) this.findViewById(R.id.titleName);
		btnSet = (ImageButton) this.findViewById(R.id.btnSet);
		
		mRSendDown[0] = (ImageView)this.findViewById(R.id.RSendDown1);
		mRSendDown[1] = (ImageView)this.findViewById(R.id.RSendDown2);
		mRSendDown[2] = (ImageView)this.findViewById(R.id.RSendDown3);
		
		mRSendUp[0] = (ImageView)this.findViewById(R.id.RSendUp1);
		mRSendUp[1] = (ImageView)this.findViewById(R.id.RSendUp2);
		mRSendUp[2] = (ImageView)this.findViewById(R.id.RSendUp3);
		
		mReceiverDown[0] = (ImageView)this.findViewById(R.id.ReceiverDown1);
		mReceiverDown[1] = (ImageView)this.findViewById(R.id.ReceiverDown2);
		mReceiverDown[2] = (ImageView)this.findViewById(R.id.ReceiverDown3);
		
		btnBack.setOnClickListener(onClickListener);
		btnSet.setVisibility(View.INVISIBLE);
		titleName.setText("网络检测评估");
		strSenderIP=getSenderIP();
		mRSenderIPAddress.setText("IP地址：" +strSenderIP);
		mRSenderPacket.setText("发送数据包：0");
		
		mRServerIPAddress.setText("IP地址：" + strIP);
		mRServerReceiverPacket.setText("收到数据包：");
		
		mRReceiverIPAddress.setText("IP地址：" + anyChatSDK.GetUserIPAddr(-1));
		mRReceiverGetPacket.setText("收到数据包：0");
		mRReceiverLostRate.setText("丢包率：0");
	}
	
	OnClickListener onClickListener = new OnClickListener() {

		@Override
		public void onClick(View arg0) {
			switch (arg0.getId()) {
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
					// 如果发送者是后进来的，会造成发送者的ip为空，再从新获取一下
					if(ValueUtils.isStrEmpty(strSenderIP)) {
						strSenderIP=getSenderIP();
						mRSenderIPAddress.setText("IP地址：" +strSenderIP);
					}
					
					msClientSenderPacket = AnyChatCoreSDK.GetSDKOptionInt(166);
					msReceiverGetPacket = AnyChatCoreSDK.GetSDKOptionInt(164);
					msServerReceiverPacket = AnyChatCoreSDK.GetSDKOptionInt(165);
					float lostPacketRate;
					if (msServerReceiverPacket == 0 || (msClientSenderPacket - msReceiverGetPacket) < 0) {
						lostPacketRate = 0.f;
					}else {
						lostPacketRate = (((float)(msClientSenderPacket - msReceiverGetPacket)/(float)msServerReceiverPacket) *100.f);
					}
					
					mRSenderPacket.setText("发送数据包：" + msClientSenderPacket);
					mRServerReceiverPacket.setText("收到的数据：" + msServerReceiverPacket);
					mRReceiverLostRate.setText("丢包率：" + String.format("%.2f", lostPacketRate) + "%");
					
					mRReceiverGetPacket.setText("收到数据包：" + msReceiverGetPacket);
					
					// 刷新服务器接受动画
					if (mServerIconIndex >= 3) {
						mServerIconIndex = 0;
					}else {
						mRServerIcon.setImageResource(mRServerIconID[mServerIconIndex]);
						mServerIconIndex++;
					}
					
					// 刷新数据包传输动画
					if (mPacketIconTransfeIndex >= 3) {
						mPacketIconTransfeIndex = 0;
					}
					
					for (int i = 0; i < 3; i++) {
						if(i == mPacketIconTransfeIndex){
							mRSendDown[i].setImageResource(R.drawable.red_down);
							mRSendUp[2-i].setImageResource(R.drawable.red_up);
							mReceiverDown[i].setImageResource(R.drawable.red_down);
						}else {
							mRSendDown[i].setImageResource(R.drawable.blue_down);
							mRSendUp[2-i].setImageResource(R.drawable.blue_up);
							mReceiverDown[i].setImageResource(R.drawable.blue_down);
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
	
	private String getSenderIP(){
		String strSenderIP = anyChatSDK.QueryUserStateString(AnyChatCoreSDK.GetSDKOptionInt(167) ,AnyChatDefine.BRAC_USERSTATE_INTERNETIP);
		return strSenderIP;
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
		}

		if (anyChatSDK != null) {
			anyChatSDK.LeaveRoom(-1);
			anyChatSDK.removeEvent(this);
		}
		AnyChatCoreSDK.SetSDKOptionInt(163, 0);
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
