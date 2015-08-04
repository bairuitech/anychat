package com.bairuitech.main;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.util.Log;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.common.BaseConst;
import com.bairuitech.common.BaseMethod;
import com.bairuitech.common.CustomApplication;
import com.bairuitech.common.ScreenInfo;
import com.example.anychatqueue.R;

public class BussinessCenter{

	public  static AnyChatCoreSDK anychat;
	private static BussinessCenter mBussinessCenter;
	private MediaPlayer mMediaPlayer;
	public static ScreenInfo mScreenInfo;
	public static Activity mContext;
	public static int selfUserId;
	public static boolean bBack = false;
	public static String selfUserName;
	
	private BussinessCenter() {
		initParams();
	}

	public static BussinessCenter getBussinessCenter() {
		if (mBussinessCenter == null)
			mBussinessCenter = new BussinessCenter();
		return mBussinessCenter;
	}

	private void initParams() {
		anychat = AnyChatCoreSDK.getInstance(mContext);
	}

	/***
	 * 播放接收到呼叫音乐提示音
	 * @param context	上下文  
	 */
	private void playCallReceivedMusic(Context context) {
		//播放声音
		mMediaPlayer = MediaPlayer.create(context, R.raw.call);
		mMediaPlayer.setOnCompletionListener(new OnCompletionListener() {

			@Override
			public void onCompletion(MediaPlayer mp) {
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

public void realse() {
		anychat = null;
		mMediaPlayer = null;
		mScreenInfo = null;
		mContext = null;
		mBussinessCenter = null;
	}

	/***
	 * 视频呼叫事件处理
	 * @param dwEventType	视频呼叫事件类型       
	 * @param dwUserId		目标userid       
	 * @param dwErrorCode	出错代码       
	 * @param dwFlags		功能标志        
	 * @param dwParam		自定义参数，传给对方        
	 * @param szUserStr		自定义参数，传给对方         
	 */
	public static void VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, String szUserStr) {
		
		if(null == anychat) {System.out.println("anychat is null");}
		anychat.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
	}

	public void onVideoCallRequest(int dwUserId, int dwFlags,
			int dwParam, String szUserStr) {
		//播放音乐
		playCallReceivedMusic(mContext);
		
	}

	public void onVideoCallReply(int dwUserId, int dwErrorCode,
			int dwFlags, int dwParam, String szUserStr) {
		// 回复类型处理
		String strMessage = null;
		switch (dwErrorCode) {
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_BUSY:
			strMessage = mContext.getString(R.string.str_returncode_bussiness);
			BaseMethod.showToast(strMessage, mContext);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE:
			strMessage = mContext.getString(R.string.str_returncode_requestrefuse);
			BaseMethod.showToast(strMessage, mContext);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_OFFLINE:
			strMessage = mContext.getString(R.string.str_returncode_offline);
			BaseMethod.showToast(strMessage, mContext);
			stopSessionMusic();
			mContext.finish();
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT:
			strMessage = mContext.getString(R.string.str_returncode_requestcancel);
			BaseMethod.showToast(strMessage, mContext);
			stopSessionMusic();
			mContext.finish();
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_TIMEOUT:
			strMessage = mContext.getString(R.string.str_returncode_timeout);
			BaseMethod.showToast(strMessage, mContext);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_DISCONNECT:
			strMessage = mContext.getString(R.string.str_returncode_disconnect);
			BaseMethod.showToast(strMessage, mContext);
			stopSessionMusic();
			Intent intent2 = new Intent(mContext, LoginActivity.class);
			intent2.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			mContext.startActivity(intent2);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SUCCESS:
			break;
		default:
			break;
		}
			// 如果程序在后台，通知通话结束
			if (bBack) {
				Bundle bundle = new Bundle();
				bundle.putInt("USERID", dwUserId);
				BaseMethod.sendBroadCast(mContext,
						BaseConst.ACTION_BACK_CANCELSESSION, null);
			}
			stopSessionMusic();
		
	}

	public void onVideoCallStart(int dwUserId, int dwFlags, int dwParam,
			String szUserStr,CustomApplication mApplication) {
		//呼叫开始事件响应
		stopSessionMusic();
		mApplication.setTargetUserId(dwUserId);
		mApplication.setRoomId(dwParam);
		//界面是在这里跳转的
		Intent intent = new Intent();
		intent.setClass(mContext, VideoActivity.class);
		mContext.startActivity(intent);
	}

	public void onVideoCallEnd(int dwUserId, int dwFlags, int dwParam,
			String szUserStr) {
	
		Intent intent = new Intent();
		intent.setClass(mContext, QueueActivity.class);
		mContext.startActivity(intent);
		mContext.finish();
	
	}

}


