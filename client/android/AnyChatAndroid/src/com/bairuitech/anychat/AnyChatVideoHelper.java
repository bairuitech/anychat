package com.bairuitech.anychat;



import java.nio.ByteBuffer;
import android.graphics.Bitmap;
import android.graphics.Canvas;
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
	
	public void ShowVideo(int userid, byte [] mPixel) {
		VideoRenderer r = GetRenderByUserId(userid);
		if(r == null)
			return;
		r.DrawByteBuffer(mPixel);
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

    public void DrawByteBuffer(byte [] mPixel) {
        if(bitmap == null)
            return;
        ByteBuffer byteBuffer = ByteBuffer.wrap( mPixel );		// 将 byte 数组包装到缓冲区中
        byteBuffer.rewind();
       
        bitmap.copyPixelsFromBuffer(byteBuffer);
        Canvas canvas = surfaceHolder.lockCanvas();
        if(canvas != null) {
            canvas.drawBitmap(bitmap, srcRect, dstRect, null);
            surfaceHolder.unlockCanvasAndPost(canvas);
        }
    }

	
	
	
	
	
	
	
	
}