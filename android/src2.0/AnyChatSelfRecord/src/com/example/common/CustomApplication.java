package com.example.common;

import android.app.Application;

public class CustomApplication extends Application {
	// 步骤流程索引
	public static final int LOGIN_PROCESS = 1;				// 登录
	public static final int TAKEPHOTO_PROCESS = 2;			// 拍照
	public static final int PREVIEWPHTOT_PROCESS = 3;		// 拍照预览
	public static final int VIDEORECORDING_PROCESS = 4; 	// 录像
	public static final int PREVIDEORECORDING_PROCESS = 5;	// 录像预览
	public static final int FILEUPLOAD_PROCESS = 6;        	// 上传
	public static final int INFOCHECK_PROCESS = 7;			// 审核
	
	private int mCurProcessIndex;
	private String mStrTakePhotoPath;
	private String mStrVideoRecordingPath;
	
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
	}
	
	public void setCurProcessIndex(int processIndex) {
		mCurProcessIndex = processIndex;
	}
	
	public int getCurProcessIndex() {
		return mCurProcessIndex;
	}
	
	public void setTakePhotoPath(String picPath) {
		mStrTakePhotoPath = picPath;
	}
	
	public String getTakePhotoPath() {
		return mStrTakePhotoPath;
	}
	
	public void setVideoRecordingPath(String videoPath) {
		mStrVideoRecordingPath = videoPath;
	}
	
	public String getVideoRecordingPath() {
		return mStrVideoRecordingPath;
	}
}
