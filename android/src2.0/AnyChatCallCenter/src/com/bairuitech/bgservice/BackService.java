package com.bairuitech.bgservice;

import java.util.List;

import com.bairuitech.bussinesscenter.BussinessCenter;
import com.bairuitech.callcenter.R;
import com.bairuitech.util.BaseConst;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

public class BackService extends Service {
	private ActivityManager activityManager;
	List<RunningAppProcessInfo> appProcesses;
	private String packageName;
	private boolean bStop = false;
	private boolean bFirstShow = true;
	public final static int BACK_NOTIFICATION_APP = 0x457893;
	public final static int BACK_NOTIFICATIONID_BASE = 0x888;
	public RequestSdkBroadCast mBroadCastRecevier;

	class RequestSdkBroadCast extends BroadcastReceiver {

		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
			if (intent.getAction().equals(BaseConst.ACTION_BACK_CANCELSESSION)) {
				Bundle bundle = intent.getExtras();
				if (bundle != null) {
					int userId = bundle.getInt("USERID");
					cancelNotification(BACK_NOTIFICATIONID_BASE+userId);
				}
			}
			if (intent.getAction().equals(BaseConst.ACTION_BACK_EQUESTSESSION)) {
				Bundle bundle = intent.getExtras();
				if (bundle != null) {

					int userId = bundle.getInt("USERID");
					showNotification(bundle.getString("USERNAME"),
							BACK_NOTIFICATIONID_BASE + userId);
				}
			}
			if (intent.getAction().equals(
					BaseConst.ACTION_BACK_CANCELNOTIFYTION)) {
				cancelNotification();
			}

		}

	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		registerBroad();
		super.onCreate();
	}

	private void registerBroad() {
		mBroadCastRecevier = new RequestSdkBroadCast();
		IntentFilter intentFilter = new IntentFilter(
				BaseConst.ACTION_BACK_EQUESTSESSION);
		this.registerReceiver(mBroadCastRecevier, intentFilter);
		intentFilter = new IntentFilter(BaseConst.ACTION_BACK_CANCELSESSION);
		this.registerReceiver(mBroadCastRecevier, intentFilter);
		intentFilter = new IntentFilter(BaseConst.ACTION_BACK_CANCELNOTIFYTION);
		this.registerReceiver(mBroadCastRecevier, intentFilter);

	}

	@Override
	protected void finalize() throws Throwable {
		// TODO Auto-generated method stub
		super.finalize();
	}

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		activityManager = (ActivityManager) this
				.getSystemService(Context.ACTIVITY_SERVICE);
		packageName = this.getPackageName();
		new Thread() {
			public void run() {
				try {
					while (!bStop) {
						if (isAppOnForeground()) {
							if (!bFirstShow) {
								cancelNotification();
								bFirstShow = true;
								BussinessCenter.bBack = false;
							}
						} else {
							if (bFirstShow) {
								showNotification(
										BackService.this
												.getString(R.string.BACKING_RUNING),
										BACK_NOTIFICATION_APP);
								bFirstShow = false;
								BussinessCenter.bBack = true;
							}
						}

						Thread.sleep(1000);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}.start();

		return super.onStartCommand(intent, flags, startId);
	}

	/**
	 * 检查程序是否在前台运行
	 * @return 是否在前台运行
	 */
	public boolean isAppOnForeground() {
		// Returns a list of application processes that are running on the
		// device
		/*
		 * ComponentName currentCompoentName = activityManager
		 * .getRunningTasks(2).get(0).topActivity; Log.i(TAG,
		 * currentCompoentName.getClassName());
		 */appProcesses = activityManager.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses) {
			// The name of the process that this object is associated with.
			if (appProcess.processName.equals(packageName)
					&& appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
				return true;
			}
		}

		return false;
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		this.unregisterReceiver(mBroadCastRecevier);
		bStop = true;
		super.onDestroy();
	}

	/***
	 * 显示指定通知
	 * 
	 * @param strTitle
	 *            通知内容
	 * @param notification_id
	 *            通知id
	 */
	public void showNotification(String strText, int notification_id) {
		// 得到NotificationManager
		Log.i("ANYCHAT", "showNotification");
		NotificationManager notificationManager = (NotificationManager) getSystemService(android.content.Context.NOTIFICATION_SERVICE);
		Notification notification = new Notification(R.drawable.ic_launcher,
				strText, System.currentTimeMillis());
		notification.flags |= Notification.FLAG_SHOW_LIGHTS;
		notification.flags |= Notification.FLAG_AUTO_CANCEL;
		notification.defaults = Notification.DEFAULT_LIGHTS;
		notification.ledARGB = Color.BLUE;
		notification.ledOnMS = 100;
		notification.ledOffMS = 100;
		Intent notificationIntent = new Intent(BussinessCenter.mContext,
				BussinessCenter.mContext.getClass());
		notificationIntent.putExtra("action", 2);
		notificationIntent.setAction(Intent.ACTION_MAIN);
		notificationIntent.addCategory(Intent.CATEGORY_LAUNCHER);
		PendingIntent contentIntent = PendingIntent.getActivity(
				BussinessCenter.mContext, 0, notificationIntent,
				PendingIntent.FLAG_UPDATE_CURRENT);
		notification
				.setLatestEventInfo(this,
						this.getString(R.string.BACKING_RUNING), strText,
						contentIntent);
		notificationManager.notify(notification_id, notification);
	}

	public void cancelNotification(int notificationId) {

		try {
			NotificationManager notificationManager = (NotificationManager) getSystemService(android.content.Context.NOTIFICATION_SERVICE);
			notificationManager.cancel(notificationId);
		} catch (Exception e) {

		}
	}
	public void cancelNotification() {

		try {
			NotificationManager notificationManager = (NotificationManager) getSystemService(android.content.Context.NOTIFICATION_SERVICE);
			notificationManager.cancelAll();
		} catch (Exception e) {

		}
	}

}
