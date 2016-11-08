package com.bairuitech.common;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import com.example.anychatqueueplusplus.R;



import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.text.TextPaint;
import android.view.Gravity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class BaseMethod {

	public static int dip2px(Context context, float dipValue) {
		final float scale = context.getResources().getDisplayMetrics().density;
		return (int) (dipValue * scale + 0.5f);
	}

	public static int px2dip(Context context, float pxValue) {
		final float scale = context.getResources().getDisplayMetrics().density;
		return (int) (pxValue / scale + 0.5f);
	}

	public static void showToast(String strContent, Activity context) {
		Toast mToast = new Toast(context);
		View view = context.getLayoutInflater().inflate(
				R.layout.common_toastview, null);
		TextView textView = (TextView) view
				.findViewById(R.id.txt_toast);
		textView.setText(strContent);
		mToast.setView(view);
		mToast.setDuration(Toast.LENGTH_SHORT);
		mToast.setGravity(Gravity.CENTER, 0, 0);
		mToast.show();
	}

	public static String getVersion(Context context) {
		try {
			return "Version:" + context.getPackageManager().getPackageInfo("com.bairuitech.callcenter", 0).versionName;
		} catch (NameNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
			return "";
		}
	}

	/**
	 * 发�?�广�?
	 * @param context	上下�?
	 * @param strAction	动作
	 * @param bundle	数据 
	 */
	public static void sendBroadCast(Context context, String strAction,	Bundle bundle) {
		Intent intent = new Intent();
		if (bundle != null)
			intent.putExtras(bundle);
		intent.setAction(strAction);
		context.sendBroadcast(intent);
	}

	public static String getStrTime(final Date date) {
		SimpleDateFormat tm = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.US);
		String strTime = "";
		try {
			strTime = tm.format(date);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return strTime;
	}

	public static Date getDateTime(final String strTime) {
		SimpleDateFormat tm = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.US);
		Date date = null;
		try {
			date = tm.parse(strTime);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return date;
	}
	public static void settextborder(TextView view){
	
		TextPaint tpPaint = view.getPaint();
		tpPaint.setFakeBoldText(true);
		
	}
	
	public static String getTimeShowString(int seconds)
	{
		String strShow=new String();
		int hour = seconds / (60*60);
		int min = (seconds/60) % 60;
		int s = seconds % 60;
		String hourStr = (hour >= 10) ? "" + hour : "0" + hour;
		String minStr = (min >= 10) ? "" + min : "0" + min;
		String seondStr = (s >= 10) ? "" + s : "0" + s;
		strShow = hourStr + ":" + minStr + ":" + seondStr;
		return strShow;
	}
	public static String getTimeShowStringTwo(int Seconds){
		
		String strtime = new String();
		int hour = Seconds / (60*60);
		int min = (Seconds/60) % 60;
		int s = Seconds % 60;
		String hourStr = (hour >= 10) ? "" + hour : "0" + hour;
		String minStr = (min >= 10) ? "" + min : "0" + min;
		String seondStr = (s >= 10) ? "" + s : "0" + s;
		
		strtime = hourStr + "时" + minStr + "分" + seondStr+"秒";
		return strtime;
	}
}
