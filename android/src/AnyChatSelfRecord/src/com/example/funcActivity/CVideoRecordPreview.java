package com.example.funcActivity;

import java.io.File;

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
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnPreparedListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.VideoView;

public class CVideoRecordPreview extends Activity implements AnyChatBaseEvent{
	AnyChatCoreSDK mAnyChatSDK;
	public int state = 0;
	public static final int PLAYING = 1;
	private final int ACTIVITY_ID_FILEUPLOAD = 6;

	ImageView mVideoPreviewIV;
	Button mReVideoRecordBtn;
	Button mVideoRecordNestStepBtn;
	Button mVideoPlaybackBtn;
	VideoView mVideoViewPlay;
	SeekBar mSeekBar;

	private CustomApplication mCustomApplication;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.video_preview);
		mCustomApplication = (CustomApplication) getApplication();
		mAnyChatSDK = AnyChatCoreSDK.getInstance(this);
		mAnyChatSDK.SetBaseEvent(this);

		InitLayout();
		BaseMethod.addActivityToList(this);
		registerBoradcastReceiver();
	}

	private void InitLayout() {
		mVideoPreviewIV = (ImageView) findViewById(R.id.previewVideo);
		mReVideoRecordBtn = (Button) findViewById(R.id.reVideoRecordBtn);
		mVideoRecordNestStepBtn = (Button) findViewById(R.id.videoRecord_nextstep);
		mVideoPlaybackBtn = (Button) findViewById(R.id.videoPlaybackBtn);
		mVideoViewPlay = (VideoView) findViewById(R.id.videoViewPlay);
		mSeekBar = (SeekBar) findViewById(R.id.seekBar);

		mReVideoRecordBtn.setOnClickListener(onClickListener);
		mVideoRecordNestStepBtn.setOnClickListener(onClickListener);
		mVideoPlaybackBtn.setOnClickListener(onClickListener);
		mVideoPreviewIV.setOnClickListener(onClickListener);

		File file = new File(mCustomApplication.getVideoRecordingPath());
		if (file.exists()) {
			mVideoPreviewIV.setImageBitmap(BaseMethod.getVideoThumbnail(
					mCustomApplication.getVideoRecordingPath(),
					ScreenInfo.WIDTH, ScreenInfo.HEIGHT - 60,
					MediaStore.Images.Thumbnails.MICRO_KIND));
		}

		mSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				if (fromUser) {
					mVideoViewPlay.seekTo(progress);
					mVideoViewPlay.start();
				}
			}

			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub

			}

			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub

			}

		});

		mVideoViewPlay.setOnPreparedListener(new OnPreparedListener() {

			@Override
			public void onPrepared(MediaPlayer mp) {
				mSeekBar.setMax(mp.getDuration());
				startTh();
				System.out.println("onPrepared");
			}
		});
	}

	OnClickListener onClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.reVideoRecordBtn:
				mCustomApplication
						.setCurProcessIndex(CustomApplication.VIDEORECORDING_PROCESS);
				destroyCurActivity();
				overridePendingTransition(R.anim.push_right_in,
						R.anim.push_right_out);
				BaseMethod.removeActivityFromList(CVideoRecordPreview.this);
				break;
			case R.id.previewVideo:
			case R.id.videoPlaybackBtn:
				state = PLAYING;
				mVideoViewPlay.setVideoPath(mCustomApplication
						.getVideoRecordingPath());
				mVideoViewPlay.start();
				mVideoPreviewIV.setVisibility(View.GONE);
				mVideoViewPlay.setVisibility(View.VISIBLE);
				mSeekBar.setVisibility(View.VISIBLE);
				break;
			case R.id.videoRecord_nextstep:
				mCustomApplication
						.setCurProcessIndex(CustomApplication.FILEUPLOAD_PROCESS);
				Intent intent = new Intent();
				intent.setClass(CVideoRecordPreview.this, CFileUpload.class);
				startActivityForResult(intent, ACTIVITY_ID_FILEUPLOAD);
				destroyCurActivity();
				overridePendingTransition(R.anim.push_left_in,
						R.anim.push_left_out);
				BaseMethod.removeActivityFromList(CVideoRecordPreview.this);
				break;
			default:
				break;
			}
		}
	};

	private Handler handler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			mSeekBar.setProgress(mVideoViewPlay.getCurrentPosition());
		}

	};

	public void startTh() {

		Thread th = new Thread() {

			@Override
			public void run() {
				while (state == PLAYING) {
					handler.sendEmptyMessage(0);
					System.out.println("sendEmptyMessage");
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};

		th.start();
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

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}
	
	@Override
	protected void onRestart() {
		super.onRestart();
		mAnyChatSDK.SetBaseEvent(this);
	}
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			BaseMethod.exitVideoDialog(this);
		}

		return super.onKeyDown(keyCode, event);
	}

	private void destroyCurActivity() {
		onDestroy();
		finish();
		BaseMethod.removeActivityFromList(this);
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
