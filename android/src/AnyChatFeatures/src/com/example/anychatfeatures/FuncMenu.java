package com.example.anychatfeatures;

import java.util.ArrayList;
import java.util.HashMap;

import com.example.anychatfeatures.R;
import com.example.anychatfeatures.R.string;
import com.example.common.CustomApplication;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class FuncMenu extends Activity {
	public static final int FUNC_VOICEVIDEO = 1;
	public static final int FUNC_TEXTCHAT = 2;
	public static final int FUNC_ALPHACHANNEL = 3;
	public static final int FUNC_FILETRANSFER = 4;
	public static final int FUNC_VIDEO = 5;
	public static final int FUNC_PHOTOGRAPH = 6;
	public static final int FUNC_VIDEOCALL = 7;

	private ImageButton mImgBtnReturn;
	private TextView mTitleName;
	private GridView mMenuGridView;
	private final int mMenuCount = 7;
	private CustomApplication mCustomApplication;
	private ArrayList<HashMap<String, Object>> mArrItem;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.funcmenu);
		
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);  
		InitLayout();
		registerBoradcastReceiver();
	}

	private void InitLayout() {
		this.setTitle("AnyChat功能菜单");
		mCustomApplication = (CustomApplication) getApplication();
		mMenuGridView = (GridView) this.findViewById(R.id.funcmenuGridView);
		mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
		mTitleName = (TextView) this.findViewById(R.id.titleName);

		String[] arrFuncNames = { getString(R.string.voiceVideoInteraction),
				getString(R.string.textChat), getString(R.string.alphaChannel),
				getString(R.string.fileTransfer), getString(R.string.video),
				getString(R.string.photograph), getString(R.string.videoCall) };

		int[] arrFuncIcons = { R.drawable.voicevideo, R.drawable.textchat,
				R.drawable.alphachannel, R.drawable.filetransfer,
				R.drawable.video, R.drawable.photograph, R.drawable.videocall };

		mArrItem = new ArrayList<HashMap<String, Object>>();
		for (int index = 0; index < mMenuCount; ++index) {
			HashMap<String, Object> itemMap = new HashMap<String, Object>();
			itemMap.put("ItemImage", arrFuncIcons[index]);
			itemMap.put("ItemText", arrFuncNames[index]);
			mArrItem.add(itemMap);
		}

		SimpleAdapter sMenuItemAdapter = new SimpleAdapter(this, mArrItem,
				R.layout.funcmenu_cell,
				new String[] { "ItemImage", "ItemText" }, new int[] {
						R.id.funcItemImage, R.id.funcItemText });

		mMenuGridView.setAdapter(sMenuItemAdapter);
		mMenuGridView.setOnItemClickListener(onListClickListener);
		mTitleName.setText(R.string.str_funcTitle);
		mImgBtnReturn.setOnClickListener(onBtnClick);
	}

	OnItemClickListener onListClickListener = new OnItemClickListener() {

		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {

			// 不同的功能模块进入不同的房间，从1开始，1~7房间，如语音视频聊天进入1号房间，文字聊天进入2号房间。。。
			mCustomApplication.setCurOpenFuncUI(arg2 + 1);
			openRolesListActivity(arg2 + 1);
		}
	};
	
	OnClickListener onBtnClick = new OnClickListener() {
		@Override
		public void onClick(View v) {
			destroyCurActivity();
		}
	};

	// 音视频交互
	private void openRolesListActivity(int sEnterRoomID) {
		Intent intent = new Intent(this, RolesListActivity.class);
		intent.putExtra("roomID", sEnterRoomID);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK
				| Intent.FLAG_ACTIVITY_CLEAR_TOP);
		startActivity(intent);
	}

	// 广播
	private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.equals("NetworkDiscon")) {
				destroyCurActivity();
			}
		}
	};

	public void registerBoradcastReceiver() {
		IntentFilter myIntentFilter = new IntentFilter();
		myIntentFilter.addAction("NetworkDiscon");
		// 注册广播
		registerReceiver(mBroadcastReceiver, myIntentFilter);
	}

	private void destroyCurActivity() {
		onPause();
		onDestroy();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
		finish();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}
}
