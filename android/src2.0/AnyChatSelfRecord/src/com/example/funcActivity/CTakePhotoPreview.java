package com.example.funcActivity;

import java.io.File;

import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.example.anychatselfrecord.R;
import com.example.common.BaseMethod;
import com.example.common.CustomApplication;
import com.example.common.ScreenInfo;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
  
public class CTakePhotoPreview extends Activity implements AnyChatBaseEvent{
	AnyChatCoreSDK mAnyChatSDK;
	private ImageView mPreviewPicIV; // 拍照图片预览view
	private CustomApplication mCustomApplication;
	private TextView mReTakePhotoBtn;
	private Button mTakePhotoNextStepBtn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.pic_preview);
		mCustomApplication = (CustomApplication) getApplication();
		mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
		mAnyChatSDK.SetBaseEvent(this);

		InitLayout();

		BaseMethod.addActivityToList(this);
		registerBoradcastReceiver();
	}

	private void InitLayout() {
		mPreviewPicIV = (ImageView) findViewById(R.id.previewPhoto);
		mReTakePhotoBtn = (TextView) findViewById(R.id.retakephotoBtn);
		mTakePhotoNextStepBtn = (Button) findViewById(R.id.takephoto_nextstep);

		mReTakePhotoBtn.setOnClickListener(onClickListener);
		mTakePhotoNextStepBtn.setOnClickListener(onClickListener);

		File file = new File(mCustomApplication.getTakePhotoPath());
		if (file.exists()) {
			mPreviewPicIV.setImageBitmap(BaseMethod.getImageThumbnail(
					mCustomApplication.getTakePhotoPath(),
					180, 240));//ScreenInfo.WIDTH, ScreenInfo.HEIGHT - 60
		}
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
		unregisterReceiver(mBroadcastReceiver);
		onDestroy();
		finish();
		BaseMethod.removeActivityFromList(this);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		if (mAnyChatSDK != null) {
			mAnyChatSDK.removeEvent(this);
		}
	
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.retakephotoBtn:
				mCustomApplication
						.setCurProcessIndex(CustomApplication.TAKEPHOTO_PROCESS);
				destroyCurActivity();
				overridePendingTransition(R.anim.push_right_in,
						R.anim.push_right_out);
				BaseMethod.removeActivityFromList(CTakePhotoPreview.this);
				break;
			case R.id.takephoto_nextstep:
				mCustomApplication
						.setCurProcessIndex(CustomApplication.VIDEORECORDING_PROCESS);
				destroyCurActivity();
				overridePendingTransition(R.anim.push_left_in,
						R.anim.push_left_out);
				BaseMethod.removeActivityFromList(CTakePhotoPreview.this);
				break;
			default:
				break;
			}
		}
	};

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			BaseMethod.exitVideoDialog(this);
			return true;
		}

		return super.onKeyDown(keyCode, event);
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
		// 销毁当前界面
		destroyCurActivity();
		Intent mIntent = new Intent("NetworkDiscon");
		// 发送广播
		sendBroadcast(mIntent);
	}
}
