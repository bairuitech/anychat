package com.bairuitech.bussinesscenter;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.util.Log;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.callcenter.R;
import com.bairuitech.callcenter.VideoActivity;
import com.bairuitech.util.BaseConst;
import com.bairuitech.util.BaseMethod;
import com.bairuitech.util.ScreenInfo;

public class BussinessCenter{

	public static AnyChatCoreSDK anychat;
	private static BussinessCenter mBussinessCenter;
	private MediaPlayer mMediaPlaer;
	public static SessionItem sessionItem;
	public static ScreenInfo mScreenInfo;
	public static Activity mContext;
	public static ArrayList<UserItem> mOnlineFriendItems;
	public static ArrayList<Integer> mOnlineFriendIds;

	public static int selfUserId;
	public static boolean bBack = false;// 程序是否在后台
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
		mOnlineFriendItems = new ArrayList<UserItem>();
		mOnlineFriendIds = new ArrayList<Integer>();
	}

	/***
	 * 播放接收到呼叫音乐提示
	 * @param context	上下文    
	 */
	private void playCallReceivedMusic(Context context) {
		mMediaPlaer = MediaPlayer.create(context, R.raw.call);
		mMediaPlaer.setOnCompletionListener(new OnCompletionListener() {

			@Override
			public void onCompletion(MediaPlayer mp) {
				// TODO Auto-generated method stub
				mMediaPlaer.start();
			}
		});
		mMediaPlaer.start();
	}

	/***
	 * 停止播放
	 */
	public void stopSessionMusic() {
		if (mMediaPlaer == null)
			return;
		try {
			mMediaPlaer.pause();
			mMediaPlaer.stop();
			mMediaPlaer.release();
			mMediaPlaer = null;
		} catch (Exception e) {
			Log.i("media-stop", "er");
		}
	}

	/***
	 * @param userId 用户id
	 * @param status 用户在线状态，1是上线，0是下线  
	 */
	public void onUserOnlineStatusNotify(int userId, int status) {
		// TODO Auto-generated method stub
		String strMsg = "";
		UserItem userItem = getUserItemByUserId(userId);
		if (userItem == null)
			return;
		if (status == UserItem.USERSTATUS_OFFLINE) {
			if (mOnlineFriendIds.indexOf(userId) >= 0) {
				mOnlineFriendItems.remove(userItem);
				mOnlineFriendIds.remove((Object) userId);
			}
			strMsg = userItem.getUserName() + "下线";
		} else {
			strMsg = userItem.getUserName() + "上线";
		}
		if (mContext != null)
			BaseMethod.showToast(strMsg, mContext);
	}

	public void realse() {
		anychat = null;
		mOnlineFriendItems = null;
		mMediaPlaer = null;
		mScreenInfo = null;
		mContext = null;
		mBussinessCenter = null;
	}

	public void realseData() {
		mOnlineFriendItems.clear();
		mOnlineFriendIds.clear();
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
	public static void VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, String szUserStr) {
		anychat.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
	}

	public void onVideoCallRequest(int dwUserId, int dwFlags,
			int dwParam, String szUserStr) {
		// TODO Auto-generated method stub
		playCallReceivedMusic(mContext);
		// 如果程序在后台，通知有呼叫请求
		if (bBack) {
			UserItem item = getUserItemByUserId(dwUserId);
			Bundle bundle = new Bundle();
			if (item != null) {
				bundle.putString("USERNAME", item.getUserName()	+ mContext.getString(R.string.sessioning_reqite));
			} else {
				bundle.putString("USERNAME", "some one call you");
			}
			bundle.putInt("USERID", dwUserId);
			BaseMethod.sendBroadCast(mContext, BaseConst.ACTION_BACK_EQUESTSESSION, bundle);
		}
	}

	public void onVideoCallReply(int dwUserId, int dwErrorCode,
			int dwFlags, int dwParam, String szUserStr) {
		// TODO Auto-generated method stub
		String strMessage = null;
		switch (dwErrorCode) {
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_BUSY:
			strMessage = mContext.getString(R.string.str_returncode_bussiness);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE:
			strMessage = mContext.getString(R.string.str_returncode_requestrefuse);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_OFFLINE:
			strMessage = mContext.getString(R.string.str_returncode_offline);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT:
			strMessage = mContext.getString(R.string.str_returncode_requestcancel);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_TIMEOUT:
			strMessage = mContext.getString(R.string.str_returncode_timeout);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SESSION_DISCONNECT:
			strMessage = mContext.getString(R.string.str_returncode_disconnect);
			break;
		case AnyChatDefine.BRAC_ERRORCODE_SUCCESS:
			break;
		default:
			break;
		}
		if (strMessage != null) {
			BaseMethod.showToast(strMessage, mContext);
			// 如果程序在后台，通知通话结束
			if (bBack) {
				Bundle bundle = new Bundle();
				bundle.putInt("USERID", dwUserId);
				BaseMethod.sendBroadCast(mContext,
						BaseConst.ACTION_BACK_CANCELSESSION, null);
			}
			stopSessionMusic();
		}
	}

	public void onVideoCallStart(int dwUserId, int dwFlags, int dwParam,
			String szUserStr) {
		// TODO Auto-generated method stub
		stopSessionMusic();
		sessionItem = new SessionItem(dwFlags, selfUserId, dwUserId);
		sessionItem.setRoomId(dwParam);
		Intent intent = new Intent();
		intent.setClass(mContext, VideoActivity.class);
		mContext.startActivity(intent);
	}

	public void onVideoCallEnd(int dwUserId, int dwFlags, int dwParam,
			String szUserStr) {
		// TODO Auto-generated method stub
		sessionItem = null;
	}

	/***
	 * 通过用户id获取用户对象
	 * 
	 * @param userId
	 *            用户id
	 * @return
	 */
	public UserItem getUserItemByUserId(int userId) {

		int size = mOnlineFriendItems.size();
		for (int i = 0; i < size; i++) {
			UserItem userItem = mOnlineFriendItems.get(i);
			if (userItem != null && userItem.getUserId() == userId) {
				return userItem;
			}
		}
		return null;
	}

	public UserItem getUserItemByIndex(int index) {
		try {
			return mOnlineFriendItems.get(index);
		} catch (Exception e) {
			// TODO: handle exception
			return null;
		}
	}

	/***
	 * 获取好友数据
	 */
	public void getOnlineFriendDatas() {
		mOnlineFriendItems.clear();
		mOnlineFriendIds.clear();
		// 获取本地ip
		String ip = anychat.QueryUserStateString(-1,
				AnyChatDefine.BRAC_USERSTATE_LOCALIP);
		UserItem userItem = new UserItem(selfUserId, selfUserName, ip);
		// 获取用户好友userid列表
		int[] friendUserIds = anychat.GetUserFriends();
		int friendUserId = 0;
		mOnlineFriendItems.add(userItem);
		mOnlineFriendIds.add(selfUserId);
		if (friendUserIds == null)
			return;
		for (int i = 0; i < friendUserIds.length; i++) {
			friendUserId = friendUserIds[i];
			int onlineStatus = anychat.GetFriendStatus(friendUserId);
			if (onlineStatus == UserItem.USERSTATUS_OFFLINE) {
				continue;
			}
			userItem = new UserItem();
			userItem.setUserId(friendUserId);
			// 获取好友昵称
			String nickName = anychat.GetUserInfo(friendUserId,
					UserItem.USERINFO_NAME);
			if (nickName != null)
				userItem.setUserName(nickName);
			// 获取好友IP地址
			String strIp = anychat.GetUserInfo(friendUserId,
					UserItem.USERINFO_IP);
			if (strIp != null)
				userItem.setIp(strIp);
			mOnlineFriendItems.add(userItem);
			mOnlineFriendIds.add(friendUserId);
		}
	}

}
