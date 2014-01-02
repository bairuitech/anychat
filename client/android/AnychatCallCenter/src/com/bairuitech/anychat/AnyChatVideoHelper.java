package com.bairuitech.anychat;



import java.nio.ByteBuffer;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;


//AnyChat 视频显示包装类，实现Java层面的视频播放
public class AnyChatVideoHelper {
	private int MAX_VIDEO_NUM = 10;
	VideoRenderer render[];
	
	public AnyChatVideoHelper() {
		render = new VideoRenderer[MAX_VIDEO_NUM];
	}
	
	public int bindVideo(SurfaceHolder holder) {
		for(int i=0; i<MAX_VIDEO_NUM; i++) {
			if(render[i] != null && render[i].GetUserId() == -1) {
				render[i] = null;
			}
		}
		int index = -1;
		for(int i=0; i<MAX_VIDEO_NUM; i++) {
			if(render[i] == null) {
				render[i] = new VideoRenderer(holder);
				index = i;
				break;
			}
		}
		return index;
	}
	
	public void SetVideoUser(int index, int userid) {
		if(index < 0 || index >= MAX_VIDEO_NUM)
			return;
		if(render[index] == null)
			return;
		render[index].SetUserId(userid);
	}
	
	public int SetVideoFmt(int userid, int width, int height) {
		VideoRenderer r = GetRenderByUserId(userid);
		if(r == null)
			return -1;
		r.CreateBitmap(width, height);
		return 0;
	}
	
	public void ShowVideo(int userid, byte [] mPixel, int rotation, int mirror) {
		VideoRenderer r = GetRenderByUserId(userid);
		if(r == null)
			return;
		r.DrawByteBuffer(mPixel, rotation, mirror);
	}
	
	private VideoRenderer GetRenderByUserId(int userid) {
		for(int i=0; i<MAX_VIDEO_NUM; i++) {
			if(render[i] != null) {
				if(render[i].GetUserId() == userid) {
					return render[i];
				}
			}	
		}
		return null;
	}
	
}



class VideoRenderer implements Callback {
    // the bitmap used for drawing.
    private Bitmap bitmap = null;
    private SurfaceHolder surfaceHolder;
    // Rect of the source bitmap to draw
    private Rect srcRect = new Rect();
    // Rect of the destination canvas to draw to
    private Rect dstRect = new Rect();
    // private float dstTopScale = 0;
    private float dstBottomScale = 1;
    // private float dstLeftScale = 0;
    private float dstRightScale = 1;
    
    private int mUserid = -1;
	
	
    public VideoRenderer(SurfaceHolder holder) {
        if(holder == null)
            return;
        mUserid = 0;			// 未知状态
        surfaceHolder = holder;
        holder.addCallback(this);
    }
    
    // 获取当前视频显示单元绑定的用户ID
    public int GetUserId() 				{		return mUserid;			}
    // 设置用户ID
    public void SetUserId(int userid)	{		mUserid = userid;   	}
    
    // surfaceChanged and surfaceCreated share this function
    private void changeDestRect(int dstWidth, int dstHeight) {
        dstRect.right = (int)(dstRect.left + dstRightScale * dstWidth);
        dstRect.bottom = (int)(dstRect.top + dstBottomScale * dstHeight);
    }
    
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		changeDestRect(width, height);
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Canvas canvas = holder.lockCanvas();
        if(canvas != null) {
            Rect dst = holder.getSurfaceFrame();
            if(dst != null) {
                changeDestRect(dst.right - dst.left, dst.bottom - dst.top);
            }
            holder.unlockCanvasAndPost(canvas);
        }
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		bitmap = null;
		surfaceHolder = null;
		mUserid = -1;
	}

	public Bitmap CreateBitmap(int width, int height) {
        if (bitmap == null) {
            try {
                android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_DISPLAY);
            }
            catch (Exception e) {
            }
        }
        if(bitmap != null && (srcRect.bottom != height || srcRect.right != width))
        	bitmap = null;
        if(bitmap == null) {
	        bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
	        srcRect.left = 0;
	        srcRect.top = 0;
	        srcRect.bottom = height;
	        srcRect.right = width;        	
        }
        return bitmap;
    }

    public void SetCoordinates(float left, float top,  float right, float bottom) {
        // dstLeftScale = left;
        // dstTopScale = top;
        dstRightScale = right;
        dstBottomScale = bottom;
    }

    public void DrawByteBuffer(byte [] mPixel, int rotation, int mirror) {
        if(bitmap == null)
            return;
        ByteBuffer byteBuffer = ByteBuffer.wrap( mPixel );		// 将 byte 数组包装到缓冲区中
        byteBuffer.rewind();
        bitmap.copyPixelsFromBuffer(byteBuffer);
        Canvas canvas = surfaceHolder.lockCanvas();
        if(canvas != null) {
        	if(rotation != 0 || mirror != 0)
        	{
        		Paint paint = new Paint();
        		paint.setAntiAlias(true);		// 抗锯齿
        		Matrix matrix = canvas.getMatrix();
        		matrix.setRotate(rotation, (float) bitmap.getWidth() / 2, (float) bitmap.getHeight() / 2);
        		float fScalex = (float)canvas.getWidth()/(float)bitmap.getWidth();
        		float fScaley = (float)canvas.getHeight()/(float)bitmap.getHeight();
        		if(mirror != 0) {			
        			matrix.postScale(-fScalex, fScaley);
        			matrix.postTranslate((float)canvas.getWidth(), 0);
        		} else {
        			matrix.postScale(fScalex, fScaley);
        		}
        		canvas.drawColor(Color.BLACK);
        		canvas.drawBitmap(bitmap, matrix, paint);
        	}
        	else {   
        		canvas.drawBitmap(bitmap, null, dstRect, null);
        	}
            surfaceHolder.unlockCanvasAndPost(canvas);
        }
    }
    
}