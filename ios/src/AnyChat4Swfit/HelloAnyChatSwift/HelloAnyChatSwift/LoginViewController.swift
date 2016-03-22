//
//  LoginViewController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/10/31.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  登录界面

import UIKit
import Alamofire

enum LoginVCLoginMode {
    case GeneralLogin
    case SignLogin
}

class LoginViewController: UIViewController, AnyChatNotifyMessageDelegate, UIAlertViewDelegate{
    
    @IBOutlet weak var userNameTF: UITextField!
    @IBOutlet weak var roomTF: UITextField!
    @IBOutlet weak var ipTF: UITextField!
    @IBOutlet weak var portTF: UITextField!
    @IBOutlet weak var guidTF: UITextField!
    
    var loginMode = LoginVCLoginMode.GeneralLogin;
    
    let myAnyChat = AnyChatPlatform()   // AnyChat对象
    let userName = "ANYCHATSWIFT"       // 用户名
    let ip = "cloud.anychat.cn"       // IP
    let port = "8906"                   // 端口号
    let guid = "fbe957d1-c25a-4992-9e75-d993294a5d56"                       // 应用ID(GUID)
    let roomId: Int32 = 1               // 房间号
    let userId: Int32 = 1001
    let signUrl = "http://demo.anychat.cn:8930/"
    
    // MARK: - Life
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "登录"
        
        self.setup()
        self.anyChatSetup()
        
    }
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.navigationBar.hidden = true
    }
    
    override func viewWillDisappear(animated: Bool) {
        super.viewWillDisappear(animated)
        self.navigationController?.navigationBar.hidden = false
    }
    
    deinit {
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    // MARK: - Notification
    //消息观察者方法
    func AnyChatNotifyHandler(notify: NSNotification) {
        myAnyChat.OnRecvAnyChatNotify(notify.userInfo)
    }
    
    // MARK: - AnyChat Delegate
    // 连接服务器消息
    func OnAnyChatConnect(bSuccess: Bool) {
        if bSuccess {
            print("connect success")
        }else {
            AnyChatPlatform.Logout()    // 连接失败，直接logout，相当于关闭AnyChat断网重连功能
            MBProgressHUD.hideHUD()
            print("connent error")
        }
    }
    // 用户登陆消息
    func OnAnyChatLogin(dwUserId: Int32, _ dwErrorCode: Int32) {
        if dwErrorCode == 0 {
            print("login success")
            // 进入房间
            AnyChatPlatform.EnterRoom(Int32(self.roomTF.text!)!, nil)
        }else {
            print("login error")
        }
    }
    // 用户进入房间消息
    func OnAnyChatEnterRoom(dwRoomId: Int32, _ dwErrorCode: Int32) {
        if dwErrorCode == 0 {
            print("enter room success")
            MBProgressHUD.hideHUD()
            // segment跳转到用户列表界面
            self.performSegueWithIdentifier("UserList", sender: self)
        }else {
            print("enter room error")
        }
    }
    // 房间在线用户消息
    func OnAnyChatOnlineUser(dwUserNum: Int32, _ dwRoomId: Int32) {
        
    }
    // 用户进入房间消息
    func OnAnyChatUserEnterRoom(dwUserId: Int32) {
        print("user enter room")
        self.updateUserList()
    }
    // 用户退出房间消息
    func OnAnyChatUserLeaveRoom(dwUserId: Int32) {
        print("user leave room")
        self.updateUserList()
    }
    // 网络断开消息
    func OnAnyChatLinkClose(dwErrorCode: Int32) {
        
    }
    
    // MARK: - Custom
    func setup() {
        
        ipTF.text = ip;
        portTF.text = port;
        userNameTF.text = userName;
        guidTF.text = guid;
        roomTF.text = String(self.roomId)
        
        //空白区取消键盘（添加手势响应）
        let tapGasture = UITapGestureRecognizer(target: self, action: "viewTapped:")
        self.view.addGestureRecognizer(tapGasture)
    }
    
    func anyChatSetup() {
        
        myAnyChat.notifyMsgDelegate = self
        
        AnyChatPlatform.InitSDK(0)  // 初始化系统
        
        // 通知中心
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "AnyChatNotifyHandler:" as Selector, name: "ANYCHATNOTIFY", object: nil)
    }
    
    func viewTapped(sender:UITapGestureRecognizer) {
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
    @IBAction func submit(sender: UIButton) {

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
        
        if (loginMode == .SignLogin) {
            if (guidTF.text == "") {
                MBProgressHUD .showError("应用ID不能为空")
                return;
            }
        }
        
        MBProgressHUD.showMessage("正在登录中...")
        if loginMode == .GeneralLogin && guidTF.text != "" {
            // 应用ID设置
            AnyChatPlatform.SetSDKOptionString(BRAC_SO_CLOUD_APPGUID, guidTF.text);
        }
        // 服务器连接
        AnyChatPlatform.Connect(ipTF.text!, Int32(portTF.text!)!);
        
        if loginMode == .SignLogin && guidTF.text != "" {
            
            self.signLoginRequest()
            
        }else if loginMode == .GeneralLogin {
            // 普通登录
            AnyChatPlatform .Login(userNameTF.text, nil);
        }
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        if segue.identifier == "UserList" {
            
            let allUserIDs = self.getAllUserId()
            if  allUserIDs != nil {
                let userVC = segue.destinationViewController as! UserViewController;
                userVC.allUserIDs = allUserIDs!
            }
        }
    }
    
    func alertView(alertView: UIAlertView, clickedButtonAtIndex buttonIndex: Int) {

    }
    
    func getAllUserId() ->Array<Int32>? {
        let userIDs = AnyChatPlatform.GetOnlineUser()  // 获取房间在线用户id
        if userIDs.count > 0 {
            // 转Int32
            var allUserIDs = [Int32]();
            for uid in userIDs {
                allUserIDs.append(Int32(uid.intValue))
            }
            return allUserIDs
        }else {
            return nil
        }
        
    } 

    @IBAction func onRadioBtn(sender: UIButton) {
        if (sender.titleLabel?.text == "签名登录") {
            loginMode = .SignLogin;
        }else {
            loginMode = .GeneralLogin;
        }
    }
    
    func signLoginRequest() {
        let parameters = [
            "userid": String(userId),
            "strUserid": "",
            "appid": guid
        ]
        Alamofire.request(.POST, self.signUrl, parameters:parameters ).responseJSON {response in
            
            print(response)
            switch response.result {
            case .Success:
                //把得到的JSON数据转为字典
                if let jsonDict = response.result.value as? NSDictionary{

                    let errorcode = jsonDict.valueForKey("errorcode") as! Int
                    if  errorcode == 0 {
                        
                        let sigStr = jsonDict.valueForKey("sigStr") as! String
                        print (jsonDict.valueForKey("timestamp"));
                        let timestamp = jsonDict.valueForKey("timestamp") as! Int
                        // 扩展登录
                        AnyChatPlatform .LoginEx(self.userNameTF.text, self.userId, nil, self.guid, Int32(timestamp), sigStr, nil)
                    }else {
                        print("Request Error, ErrorCode:%d",errorcode);
                    }
                    
                }
            case .Failure(let error):
                print(error)
            }
            
            
        }
    }
    
    
    
}
