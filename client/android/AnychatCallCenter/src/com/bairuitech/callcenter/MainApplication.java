package com.bairuitech.callcenter;

import com.bairuitech.util.ScreenInfo;

import android.app.Application;
import android.content.res.Configuration;

public class MainApplication extends Application {

	public static  ScreenInfo screenInfo;

	// public static final float scale = 210f / 297f;
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		// TODO Auto-generated method stub
		super.onConfigurationChanged(newConfig);

		/*
		 * CANVAS_WIDTH = MainApplication.SCREEN_WIDTH; CANVAS_HEIGHT = (int)
		 * (MainApplication.SCREEN_WIDTH / scale);
		 */
	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
	}

	@Override
	public void onLowMemory() {
		// TODO Auto-generated method stub
		super.onLowMemory();
	}

	@Override
	public void onTerminate() {
		// TODO Auto-generated method stub
		super.onTerminate();
	}

}
