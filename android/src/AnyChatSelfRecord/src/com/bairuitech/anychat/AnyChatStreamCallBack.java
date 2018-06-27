package com.bairuitech.anychat;

// AnyChat媒体数据回调接口
public interface AnyChatStreamCallBack {
	// 视频数据回调接口
    public void OnAnyChatVideoDataCallBack(int userid, int streamindex, byte[] buf, int len, int width, int height);
    // 音频数据回调接口
    public void OnAnyChatAudioDataCallBack(int userid, int streamindex, byte[] buf, int len, int timestamp, int channels, int samplespersecond, int bitspersample);
}