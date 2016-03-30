//
//  VideoViewController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/11/1.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  视频聊天界面

import UIKit
import AVFoundation

class Persion {}

class VideoViewController: UIViewController, UIActionSheetDelegate {

    var remoteUserId: Int32 = 0
    var localCaptureLayer :AVCaptureVideoPreviewLayer? = AVCaptureVideoPreviewLayer()
    
    @IBOutlet weak var remoteVideoView: UIImageView!
    @IBOutlet weak var localVideoView: UIView!
    @IBOutlet weak var timerLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "视频通话"
        
        self.setup()
        self.setupVideoView()
        self.startVideoChat()
        
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.navigationBar.hidden = true
    }
    
    override func viewWillDisappear(animated: Bool) {
        super.viewWillDisappear(animated)
        self.navigationController?.navigationBar.hidden = false
    }
    
    func setup() {
        
        self.setupTimerLabel()
    }
    
    func setupTimerLabel() {
        let timerLabel = MZTimerLabel(label: self.timerLabel)
        timerLabel.timeFormat = "▷ HH:mm:ss"
        timerLabel.start()
    }

    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    func setupVideoView() {
        
        // 防锁屏
        UIApplication.sharedApplication().idleTimerDisabled = true
        
        // 设置本地视频窗口的layer属性
        self.localVideoView.layer.borderColor = UIColor.whiteColor().CGColor
        self.localVideoView.layer.borderWidth = 1.0
        self.localVideoView.layer.cornerRadius = 4.0
        self.localVideoView.layer.masksToBounds = true
        
    }
    
    func startVideoChat() {
        
        // 枚举本地视频采集设备
        let videoDeviceArr = AnyChatPlatform.EnumVideoCapture()
        // 选择指定的视频采集设备
        if videoDeviceArr.count > 1 {
            // 前置摄像头
            AnyChatPlatform.SelectVideoCapture(videoDeviceArr.objectAtIndex(1) as! String)
        }
        
        // 本地设置
        AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_OVERLAY, 1) // 采用 Overlay 模式
        AnyChatPlatform.UserCameraControl(-1, true)
        AnyChatPlatform.UserSpeakControl(-1, true)
        AnyChatPlatform.SetVideoPos(-1, self, 0, 0, 0, 0)
        
        // 远程方设置
        AnyChatPlatform.UserSpeakControl(self.remoteUserId, true)
        AnyChatPlatform.UserCameraControl(self.remoteUserId, true)
        AnyChatPlatform.SetVideoPos(self.remoteUserId, self.remoteVideoView, 0, 0, 0, 0)
    }
    
    //创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
    func OnLocalVideoInit(session: AVCaptureSession) {
        self.localCaptureLayer = AVCaptureVideoPreviewLayer(session: session)
        self.localCaptureLayer!.frame = CGRectMake(0, 0, 100, 130)
        self.localCaptureLayer!.videoGravity = AVLayerVideoGravityResizeAspectFill
        self.localVideoView.layer.addSublayer(self.localCaptureLayer!)
    }
    
    func OnLocalVideoRelease(sender: AnyObject) {
        self.localCaptureLayer = nil
    }
    
    func actionSheet(actionSheet: UIActionSheet, clickedButtonAtIndex buttonIndex: Int) {
        if buttonIndex == 0 {
            self.finishVideoChat()
            self.navigationController?.popViewControllerAnimated(true)
        }
    }
    
    func finishVideoChat() {
        // 关闭摄像头/麦克风
        AnyChatPlatform.UserSpeakControl(-1, false)
        AnyChatPlatform.UserCameraControl(-1, false)
        AnyChatPlatform.UserSpeakControl(self.remoteUserId, false)
        AnyChatPlatform.UserCameraControl(self.remoteUserId, false)
    }
    
    @IBAction func endCallAction() {
        let actionSheet = UIActionSheet(title: "确定结束会话?", delegate: self, cancelButtonTitle: "取消", destructiveButtonTitle: "确定")
        actionSheet.showInView(self.view)
    }
}
