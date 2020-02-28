//
//  LoginViewController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/10/31.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  登录界面

import UIKit
// FIXME: comparison operators with optionals were removed from the Swift Standard Libary.
// Consider refactoring the code to use the non-optional operators.
fileprivate func < <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
  switch (lhs, rhs) {
  case let (l?, r?):
    return l < r
  case (nil, _?):
    return true
  default:
    return false
  }
}

// FIXME: comparison operators with optionals were removed from the Swift Standard Libary.
// Consider refactoring the code to use the non-optional operators.
fileprivate func > <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
  switch (lhs, rhs) {
  case let (l?, r?):
    return l > r
  default:
    return rhs < lhs
  }
}

//import Alamofire

class LoginViewController: UIViewController, AnyChatNotifyMessageDelegate, UIAlertViewDelegate{
    
    @IBOutlet weak var userNameTF: UITextField!
    @IBOutlet weak var roomTF: UITextField!
    @IBOutlet weak var ipTF: UITextField!
    @IBOutlet weak var portTF: UITextField!

    
    let myAnyChat = AnyChatPlatform()   // AnyChat对象
    let userName = "ANYCHATSWIFT"       // 用户名
    let ip = "demo.anychat.cn"       // IP
    let port = "8906"                   // 端口号
    let roomId: Int32 = 1               // 房间号
    let userId: Int32 = 1001
    
    // MARK: - Life
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "登录"
        
        self.setup()
        self.anyChatSetup()
        
    }
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.navigationBar.isHidden = true
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.navigationController?.navigationBar.isHidden = false
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
    
    override var prefersStatusBarHidden : Bool {
        return true
    }
    
    // MARK: - Notification
    //消息观察者方法
    func AnyChatNotifyHandler(_ notify: Notification) {
        myAnyChat.onRecvAnyChatNotify(notify.userInfo)
    }
    
    // MARK: - AnyChat Delegate
    // 连接服务器消息
    func onAnyChatConnect(_ bSuccess: Bool) {
        if bSuccess {
            print("connect success")
        }else {
            AnyChatPlatform.logout()    // 连接失败，直接logout，相当于关闭AnyChat断网重连功能
            MBProgressHUD.hide()
            print("connent error")
        }
    }
    // 用户登陆消息
    func onAnyChatLogin(_ dwUserId: Int32, _ dwErrorCode: Int32) {
        if dwErrorCode == 0 {
            print("login success")
            // 进入房间
            AnyChatPlatform.enterRoom(Int32(self.roomTF.text!)!, nil)
        }else {
            print("login error")
        }
    }
    // 用户进入房间消息
    func onAnyChatEnterRoom(_ dwRoomId: Int32, _ dwErrorCode: Int32) {
        if dwErrorCode == 0 {
            print("enter room success")
            MBProgressHUD.hide()
            // segment跳转到用户列表界面
            self.performSegue(withIdentifier: "UserList", sender: self)
        }else {
            print("enter room error")
        }
    }
    // 房间在线用户消息
    func onAnyChatOnlineUser(_ dwUserNum: Int32, _ dwRoomId: Int32) {
        
    }
    // 用户进入房间消息
    func onAnyChatUserEnterRoom(_ dwUserId: Int32) {
        print("user enter room")
        self.updateUserList()
    }
    // 用户退出房间消息
    func onAnyChatUserLeaveRoom(_ dwUserId: Int32) {
        print("user leave room")
        self.updateUserList()
    }
    // 网络断开消息
    func onAnyChatLinkClose(_ dwErrorCode: Int32) {
        
    }
    
    // MARK: - Custom
    func setup() {
        
        ipTF.text = ip;
        portTF.text = port;
        userNameTF.text = userName;
//        guidTF.text = guid;
        roomTF.text = String(self.roomId)
        
        //空白区取消键盘（添加手势响应）
        let tapGasture = UITapGestureRecognizer(target: self, action: #selector(LoginViewController.viewTapped(_:)))
        self.view.addGestureRecognizer(tapGasture)
    }
    
    func anyChatSetup() {
        
        myAnyChat.notifyMsgDelegate = self
        
        AnyChatPlatform.initSDK(0)  // 初始化系统
        
        // 通知中心
        NotificationCenter.default.addObserver(self, selector: #selector(LoginViewController.AnyChatNotifyHandler(_:)), name: NSNotification.Name(rawValue: "ANYCHATNOTIFY"), object: nil)
    }
    
    func viewTapped(_ sender:UITapGestureRecognizer) {
        self.view.endEditing(true)
    }
    
    // 更新用户列表
    func updateUserList() {
        if (self.navigationController?.childViewControllers.count > 1) {
            // 导航子控制器
            let childVCArr = self.navigationController?.childViewControllers
            for childVC in childVCArr! {
                if childVC is UserViewController {
                    let allUserIDs = self.getAllUserId()
                    let userVC = childVC as! UserViewController
                    userVC.allUserIDs = allUserIDs
                    userVC.tableView .reloadData();
                }
            }
            
        }
    }
    
    // MARK: - Action
    @IBAction func submit(_ sender: UIButton) {

        if userNameTF.text == "" {
            userNameTF.text = userName
        }
        if ipTF.text == "" {
            ipTF.text = ip
        }
        if portTF.text == "" {
            portTF.text = port
        }
        if roomTF.text == "" {
            roomTF.text = String(roomId)
        }
        
        
        MBProgressHUD.showMessage("正在登录中...")

        // 服务器连接
        /*AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
        连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
        连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
        */
        AnyChatPlatform.connect(ipTF.text!, Int32(portTF.text!)!);
        
        // 普通登录
        /*AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
         详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
        */
        AnyChatPlatform .login(userNameTF.text, nil);

    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        if segue.identifier == "UserList" {
            
            let allUserIDs = self.getAllUserId()
            if  allUserIDs != nil {
                let userVC = segue.destination as! UserViewController;
                userVC.allUserIDs = allUserIDs!
            }
        }
    }
    
    func alertView(_ alertView: UIAlertView, clickedButtonAt buttonIndex: Int) {

    }
    
    func getAllUserId() ->Array<Int32>? {
        let userIDs = AnyChatPlatform.getOnlineUser()  // 获取房间在线用户id
        if userIDs?.count > 0 {
            // 转Int32
            var allUserIDs = [Int32]();
            for uid in userIDs! {
                allUserIDs.append(Int32((uid as AnyObject).int32Value))
            }
            return allUserIDs
        }else {
            return nil
        }
        
    } 
  
}
