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
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.navigationBar.isHidden = true
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.navigationController?.navigationBar.isHidden = false
    }
    
    func setup() {
        
        self.setupTimerLabel()
    }
    
    func setupTimerLabel() {
        let timerLabel = MZTimerLabel(label: self.timerLabel)
        timerLabel?.timeFormat = "▷ HH:mm:ss"
        timerLabel?.start()
    }

    override var prefersStatusBarHidden : Bool {
        return true
    }
    
    func setupVideoView() {
        
        // 防锁屏
        UIApplication.shared.isIdleTimerDisabled = true
        
        // 设置本地视频窗口的layer属性
        self.localVideoView.layer.borderColor = UIColor.white.cgColor
        self.localVideoView.layer.borderWidth = 1.0
        self.localVideoView.layer.cornerRadius = 4.0
        self.localVideoView.layer.masksToBounds = true
        
    }
    
    func startVideoChat() {
        
        // 枚举本地视频采集设备
        let videoDeviceArr = AnyChatPlatform.enumVideoCapture()
        // 选择指定的视频采集设备
        if (videoDeviceArr?.count)! > 1 {
            // 前置摄像头
            AnyChatPlatform.selectVideoCapture(videoDeviceArr?.object(at: 1) as! String)
        }
        
        // 本地设置
        AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_OVERLAY, 1) // 采用 Overlay 模式
        AnyChatPlatform.userCameraControl(-1, true)
        AnyChatPlatform.userSpeakControl(-1, true)
        AnyChatPlatform.setVideoPos(-1, self, 0, 0, 0, 0)
        
        // 远程方设置
        AnyChatPlatform.userSpeakControl(self.remoteUserId, true)
        AnyChatPlatform.userCameraControl(self.remoteUserId, true)
        AnyChatPlatform.setVideoPos(self.remoteUserId, self.remoteVideoView, 0, 0, 0, 0)
    }
    
    //创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
    func OnLocalVideoInit(_ session: AVCaptureSession) {
        self.localCaptureLayer = AVCaptureVideoPreviewLayer(session: session)
        self.localCaptureLayer!.frame = CGRect(x: 0, y: 0, width: 100, height: 130)
        self.localCaptureLayer!.videoGravity = AVLayerVideoGravityResizeAspectFill
        self.localVideoView.layer.addSublayer(self.localCaptureLayer!)
    }
    
    func OnLocalVideoRelease(_ sender: AnyObject) {
        self.localCaptureLayer = nil
    }
    
    func actionSheet(_ actionSheet: UIActionSheet, clickedButtonAt buttonIndex: Int) {
        if buttonIndex == 0 {
            self.finishVideoChat()
            self.navigationController?.popViewController(animated: true)
        }
    }
    
    func finishVideoChat() {
        // 关闭摄像头/麦克风
        AnyChatPlatform.userSpeakControl(-1, false)
        AnyChatPlatform.userCameraControl(-1, false)
        AnyChatPlatform.userSpeakControl(self.remoteUserId, false)
        AnyChatPlatform.userCameraControl(self.remoteUserId, false)
    }
    
    @IBAction func endCallAction() {
        let actionSheet = UIActionSheet(title: "确定结束会话?", delegate: self, cancelButtonTitle: "取消", destructiveButtonTitle: "确定")
        actionSheet.show(in: self.view)
    }
}
