package com.bairuitech.anychat;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.util.Log;


// AnyChat 音频包装类，实现音频采集、播放等
public class AnyChatAudioHelper {
	private final static String TAG = "ANYCHAT";
	private AudioTrack mAudioTrack = null;
	private AudioRecord mAudioRecord = null;
	
	private PlayAudioThread mPlayAudioThread = null;		// 播放线程
	private boolean mPlayThreadExitFlag = false;			// 播放线程退出标志
	private int mMinPlayBufSize = 0;
	private boolean mAudioPlayReleased = false;
	
	private RecordAudioThread mRecordAudioThread = null;	// 采集线程
	private boolean mRecordThreadExitFlag = false;			// 采集线程退出标志
	private int mMinRecordBufSize = 0;
	private boolean mAudioRecordReleased = false;

	// 初始化音频播放器
	public int InitAudioPlayer(int profile) {
		if(mAudioTrack != null)
			return 0;
		Log.d(TAG, "InitAudioPlayer, profile: " + profile);
		int channel, samplerate, samplebit;
		// 根据上层设定的profile来配置参数
		if(profile==1) {
			samplerate = 16000;
			channel = AudioFormat.CHANNEL_CONFIGURATION_MONO;
			samplebit = AudioFormat.ENCODING_PCM_16BIT;
		}
		else if(profile==2) {
			samplerate = 44100;
			channel = AudioFormat.CHANNEL_CONFIGURATION_STEREO;
			samplebit = AudioFormat.ENCODING_PCM_16BIT;
		}
		else {
			return -1;
		}
		try {
			mAudioPlayReleased = false;
			// 获得构建对象的最小缓冲区大小
			mMinPlayBufSize = AudioTrack.getMinBufferSize(samplerate, channel, samplebit);
			mAudioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, samplerate, channel, samplebit, mMinPlayBufSize, AudioTrack.MODE_STREAM);
			
			if (mPlayAudioThread == null)
			{
				mPlayThreadExitFlag = false;
				mPlayAudioThread = new PlayAudioThread();
				mPlayAudioThread.start();
			}
			Log.d(TAG, "mMinPlayBufSize = " + mMinPlayBufSize);
		} catch(Exception e) {
			return -1;
		}
		return 0;
	}
	// 销毁音频播放器
	public void ReleaseAudioPlayer() {
		if(mAudioPlayReleased)
			return;
		mAudioPlayReleased = true;
		Log.d(TAG, "ReleaseAudioPlayer");
		if (mPlayAudioThread != null) {
			mPlayThreadExitFlag = true;
			mPlayAudioThread = null;
		}

		if (mAudioTrack != null){
			try {
				mAudioTrack.stop();				       	
				mAudioTrack.release();
				mAudioTrack = null;
			} catch(Exception e) {
				
			}
		}
	}
	
	/*
	 *  音频播放线程
	 */
	class PlayAudioThread extends Thread
	{
		@Override
		public void run() {
			if(mAudioTrack == null)
				return;
			try {
                android.os.Process.setThreadPriority(
                    android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
            } catch (Exception e) {
            	Log.d(TAG, "Set play thread priority failed: " + e.getMessage());
            }
            try {
            	mAudioTrack.play();	
            }catch(Exception e) {
            	e.printStackTrace();
            }
			Log.d(TAG, "audio play....");
			while(!mPlayThreadExitFlag)
			{
				try {
					byte[] data = AnyChatCoreSDK.FetchAudioPlayBuffer(640);
					mAudioTrack.write(data, 0, data.length);
				}
				catch (Exception e) {
					break;
				}				
			}
			Log.d(TAG, "audio play stop....");
		}
	}
	
	// 初始化音频采集设备
	public int InitAudioRecorder(int profile) {
		if(mAudioRecord != null)
			return 0;
		Log.d(TAG, "InitAudioRecorder, profile: " + profile);
		int channel, samplerate, samplebit;
		// 根据上层设定的profile来配置参数
		if(profile==1) {
			samplerate = 16000;
			channel = AudioFormat.CHANNEL_CONFIGURATION_MONO;
			samplebit = AudioFormat.ENCODING_PCM_16BIT;
		}
		else if(profile==2) {
			samplerate = 44100;
			channel = AudioFormat.CHANNEL_CONFIGURATION_STEREO;
			samplebit = AudioFormat.ENCODING_PCM_16BIT;
		}
		else {
			return -1;
		}
		try {
			mAudioRecordReleased = false;
			// 获得构建对象的最小缓冲区大小
			mMinRecordBufSize = AudioRecord.getMinBufferSize(samplerate, channel, samplebit);
			mAudioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, samplerate, channel, samplebit, mMinRecordBufSize);
			
			// 设置AnyChat的外部音频输入参数
			AnyChatCoreSDK.SetInputAudioFormat(mAudioRecord.getChannelCount(), mAudioRecord.getSampleRate(), 16, 0);
			
			if (mRecordAudioThread == null)
			{
				mRecordThreadExitFlag = false;
				mRecordAudioThread = new RecordAudioThread();
				mRecordAudioThread.start();
			}
			Log.d(TAG, "mMinRecordBufSize = " + mMinRecordBufSize);
		}
		catch(Exception e)
		{
			return -1;
		}
		return 0;
	}
	// 销毁音频采集设备
	public void ReleaseAudioRecorder() {
		if(mAudioRecordReleased)
			return;
		mAudioRecordReleased = true;
		Log.d(TAG, "ReleaseAudioRecorder");
		if (mRecordAudioThread != null) {
			mRecordThreadExitFlag = true;
			mRecordAudioThread = null;
		}
		if (mAudioRecord != null){
			try {
				mAudioRecord.stop();				       	
				mAudioRecord.release();
				mAudioRecord = null;
			} catch(Exception e) {
				
			}
		}
	}
	
	
	/*
	 *  音频采集线程
	 */
	class RecordAudioThread extends Thread
	{
		@Override
		public void run() {
			if(mAudioRecord == null)
				return;
			try {
                android.os.Process.setThreadPriority(
                    android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
            } catch (Exception e) {
            	Log.d(TAG, "Set record thread priority failed: " + e.getMessage());
            }
            try{
            	mAudioRecord.startRecording();
            }catch(Exception e) {
            	e.printStackTrace();
            }
			Log.d(TAG, "audio record....");
			byte [] recordbuf = new byte [640];
			while(!mRecordThreadExitFlag)
			{											
				try {
					int ret = mAudioRecord.read(recordbuf, 0, recordbuf.length);
					if(ret ==  AudioRecord.ERROR_INVALID_OPERATION || ret == AudioRecord.ERROR_BAD_VALUE)
						break;
					// 通过AnyChat的外部音频输入接口将音频采样数据传入内核
					AnyChatCoreSDK.InputAudioData(recordbuf, ret, 0);
				} catch (Exception e) {
					break;
				}
			}
			Log.d(TAG, "audio record stop....");
		}

	}
}