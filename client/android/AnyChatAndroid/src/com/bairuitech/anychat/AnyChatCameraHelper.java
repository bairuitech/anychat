package com.bairuitech.anychat;


import java.util.List;

import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.hardware.Camera.CameraInfo;
import android.hardware.Camera.Size;
import android.util.Log;
import android.view.SurfaceHolder;


// AnyChat Camera包装类，实现本地视频采集
public class AnyChatCameraHelper implements SurfaceHolder.Callback{
	private final static String TAG = "ANYCHAT";
	private Camera mCamera =null;
	private boolean bIfPreview = false;
	private boolean bNeedCapture = false;
	private int iCurrentCameraId = 0;
	private SurfaceHolder currentHolder = null;
	private int mVideoPixfmt = -1;
	
	public final int CAMERA_FACING_BACK = 0;
	public final int CAMERA_FACING_FRONT = 1;
	
	// 初始化摄像机，在surfaceCreated中调用
	private void initCamera()
	{
		if (null == mCamera)
			return;
		try {
			if (bIfPreview) {
				mCamera.stopPreview();// stopCamera();
				mCamera.setPreviewCallback(null);
			}
			/* Camera Service settings */
			Camera.Parameters parameters = mCamera.getParameters();
			
			// 获取camera支持的相关参数，判断是否可以设置
			List<Size> previewSizes = mCamera.getParameters().getSupportedPreviewSizes();

			// 获取当前设置的分辩率参数
			int iSettingsWidth = AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL);
			int iSettingsHeight = AnyChatCoreSDK.GetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL);
			boolean bSetPreviewSize = false;
			for (int i = 0; i < previewSizes.size(); i++) {
				Size s = previewSizes.get(i);
				if(s.width == iSettingsWidth && s.height == iSettingsHeight) {
					bSetPreviewSize = true;
					parameters.setPreviewSize(iSettingsWidth, iSettingsHeight);
					break;
				}
			}
			parameters.setPreviewFrameRate(25);
			// 指定的分辩率不支持时，用默认的分辩率替代
			if(!bSetPreviewSize)
				parameters.setPreviewSize(320, 240);
			
			// 设置视频数据格式
			parameters.setPreviewFormat(ImageFormat.NV21);
			// 参数设置生效
			try {
				mCamera.setParameters(parameters);
			} catch(Exception e){
				
			}
			// 设置视频输出回调函数，通过AnyChat的外部视频输入接口传入AnyChat内核进行处理
			mCamera.setPreviewCallback(new Camera.PreviewCallback() {
				@Override
				public void onPreviewFrame(byte[] data, Camera camera) {
					if(data.length !=0 && bNeedCapture)
			 			AnyChatCoreSDK.InputVideoData(data, data.length, 0);
				}
			});
			mCamera.startPreview(); // 打开预览画面
			bIfPreview = true;

			// 获取设置后的相关参数
			if(mCamera.getParameters().getPreviewFormat() == ImageFormat.NV21)
				mVideoPixfmt = AnyChatDefine.BRAC_PIX_FMT_NV21;
			else if(mCamera.getParameters().getPreviewFormat() == ImageFormat.YV12)
				mVideoPixfmt = AnyChatDefine.BRAC_PIX_FMT_YV12;
			else if(mCamera.getParameters().getPreviewFormat() == ImageFormat.NV16)
				mVideoPixfmt = AnyChatDefine.BRAC_PIX_FMT_NV16;
			else if(mCamera.getParameters().getPreviewFormat() == ImageFormat.YUY2)
				mVideoPixfmt = AnyChatDefine.BRAC_PIX_FMT_YUY2;
			else if(mCamera.getParameters().getPreviewFormat() == ImageFormat.RGB_565)
				mVideoPixfmt = AnyChatDefine.BRAC_PIX_FMT_RGB565;
			else
				Log.e(TAG, "unknow camera privew format:" + mCamera.getParameters().getPreviewFormat());
			
			Camera.Size previewSize = mCamera.getParameters().getPreviewSize();
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_EXTVIDEOINPUT, 1);
			AnyChatCoreSDK.SetInputVideoFormat(mVideoPixfmt, previewSize.width, previewSize.height, mCamera.getParameters().getPreviewFrameRate(), 0);
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	// 摄像头采集控制
	public void CaptureControl(boolean bCapture) {
		bNeedCapture = bCapture;
		if(bNeedCapture && mVideoPixfmt != -1)
		{
			try {
				Camera.Size previewSize = mCamera.getParameters().getPreviewSize();
				AnyChatCoreSDK.SetInputVideoFormat(mVideoPixfmt, previewSize.width, previewSize.height, mCamera.getParameters().getPreviewFrameRate(), 0);
			} catch (Exception ex) {

			}
		}
	}

	// 获取系统中摄像头的数量
	public int GetCameraNumber() {
		try {
			return Camera.getNumberOfCameras();
		} catch (Exception ex) {
			return 0;
		}
	}
	// 自动对焦
	public void CameraAutoFocus() {
		if(mCamera == null || !bIfPreview)
			return;
		try {		
			mCamera.autoFocus(null);
		} catch (Exception ex) {

		}
	}
	
	// 切换摄像头
	public void SwitchCamera() {
		try {
			if(Camera.getNumberOfCameras() == 1 || currentHolder == null)
				return;
			iCurrentCameraId = (iCurrentCameraId==0) ? 1 : 0;
			if(null != mCamera)	{
				mCamera.stopPreview(); 
				mCamera.setPreviewCallback(null);
				bIfPreview = false; 
				mVideoPixfmt = -1;
				mCamera.release();
				mCamera = null;     
			}

			mCamera = Camera.open(iCurrentCameraId);
			mCamera.setPreviewDisplay(currentHolder);
			initCamera();
		} catch (Exception ex) {
			if(null != mCamera) {
				mCamera.release();
				mCamera = null; 
				mVideoPixfmt = -1;
			}
		}
	}
	
	// 选择摄像头
	public void SelectVideoCapture(int facing) {
		for (int i = 0; i < Camera.getNumberOfCameras(); i++) 
		{
			CameraInfo info = new CameraInfo();
			Camera.getCameraInfo(i, info);
			if (info.facing == facing) {
				iCurrentCameraId = i;
				break;
			}
		}
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
		
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		try {
			mCamera = Camera.open(iCurrentCameraId);
			currentHolder = holder;
			mCamera.setPreviewDisplay(holder);//set the surface to be used for live preview
			initCamera();
		} catch (Exception ex) {
			if(null != mCamera) {
				mCamera.release();
				mCamera = null;
				mVideoPixfmt = -1;
			}
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		if(null != mCamera)	{
			try {
				mCamera.stopPreview();
				mCamera.setPreviewCallback(null);
				bIfPreview = false; 
				mCamera.release();
				mCamera = null;
			} catch (Exception ex) {
				mCamera = null;
				bIfPreview = false; 
			}
		}
		currentHolder = null;
		mVideoPixfmt = -1;
	}

	
	

}