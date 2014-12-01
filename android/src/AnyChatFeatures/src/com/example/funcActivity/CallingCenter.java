package com.example.funcActivity;

import android.app.Activity;
import android.content.Context;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.util.Log;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.anychatfeatures.R;

public class CallingCenter {
	private static AnyChatCoreSDK anyChatSDK;
	private MediaPlayer mMediaPlayer;
	private static CallingCenter mCallingCenter;
	public static Activity mContext;
	
	private CallingCenter() {
		initParams();
	}
	
	public static CallingCenter getInstance()
	{
		if (null == mCallingCenter)
			mCallingCenter = new CallingCenter();
		
		return mCallingCenter;
	}
	
	private void initParams(){
		anyChatSDK = new AnyChatCoreSDK();
	}
	
	public void onVideoCallRequest(int dwUserId, int dwFlags,
			int dwParam, String szUserStr) {
		playCallReceivedMusic(mContext);
	}

	public void onVideoCallReply(int dwUserId, int dwErrorCode,
			int dwFlags, int dwParam, String szUserStr) {
		if (dwErrorCode != AnyChatDefine.BRAC_ERRORCODE_SUCCESS){
			stopSessionMusic();
		}
	}
	
	/***
	 * 发送呼叫事件
	 * @param dwEventType	视频呼叫事件类型       
	 * @param dwUserId		目标userid       
	 * @param dwErrorCode	出错代码       
	 * @param dwFlags		功能标志        
	 * @param dwParam		自定义参数，传给对方        
	 * @param szUserStr		自定义参数，传给对方         
	 */
	public void VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, String szUserStr) {
		anyChatSDK.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
	}
	
	/***
	 * 播放接收到呼叫音乐提示
	 * @param context	上下文    
	 */
	public void playCallReceivedMusic(Context context) {
		mMediaPlayer = MediaPlayer.create(context, R.raw.call);		
		mMediaPlayer.setOnCompletionListener(new OnCompletionListener() {

			@Override
			public void onCompletion(MediaPlayer mp) {
				// TODO Auto-generated method stub
				mMediaPlayer.start();
			}
		});
		mMediaPlayer.start();
	}

	/***
	 * 停止播放
	 */
	public void stopSessionMusic() {
		if (mMediaPlayer == null)
			return;
		try {
			mMediaPlayer.pause();
			mMediaPlayer.stop();
			mMediaPlayer.release();
			mMediaPlayer = null;
		} catch (Exception e) {
			Log.i("media-stop", "er");
		}
	}

}

