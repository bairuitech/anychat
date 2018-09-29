//
//  UserViewController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/11/2.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  在线用户列表

import UIKit

class UserViewController: UITableViewController, UIAlertViewDelegate, DZNEmptyDataSetSource, DZNEmptyDataSetDelegate {

    var allUserIDs :[Int32]? = [Int32]() {
        
        didSet {
            self.getAllUser(allUserIDs)
        }
        
    }
    
    var allUser = [User]()                          // 所有用户(User对象数组)
    var remoteUserId: Int32 = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.tableView.emptyDataSetSource = self;
        self.tableView.emptyDataSetDelegate = self;
        
    }

    // MARK: - Table view data source
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if allUserIDs == nil {
            return 0
        }else {
            return allUser.count
        }
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "UserList", for: indexPath) as UITableViewCell
        
        let user = allUser[indexPath.row] as User
        cell.textLabel?.text = user.name                // 用户名
        cell.detailTextLabel?.text = String(user.uid)   // 用户ID
        let imageName = "face\((arc4random() % 5) + 1)" // 随机头像
        cell.imageView?.image = UIImage(named: imageName)
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let selectUser = self.allUser[indexPath.row]
        self.remoteUserId = selectUser.uid
        
        self.performSegue(withIdentifier: "Video", sender: self)
        
        // 取消选中状态
        self.tableView.deselectRow(at: indexPath, animated: false)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "Video" {
            let videoVC = segue.destination as! VideoViewController;
            videoVC.remoteUserId = self.remoteUserId
        }
    }
    
    func alertView(_ alertView: UIAlertView, clickedButtonAt buttonIndex: Int) {
        if buttonIndex == 1 {
            // 离开本房间
            AnyChatPlatform.leaveRoom(-1)
            // 注销
            AnyChatPlatform.logout()
            self.navigationController?.popViewController(animated: true)
        }
    }
    
    // MARK: - EmptyData
    func image(forEmptyDataSet scrollView: UIScrollView!) -> UIImage! {
        return UIImage(named: "empty_bg")
    }
    func title(forEmptyDataSet scrollView: UIScrollView!) -> NSAttributedString! {
        let attrs = [NSFontAttributeName: UIFont.boldSystemFont(ofSize: 14), NSForegroundColorAttributeName:UIColor.lightGray]
        return NSAttributedString(string:"用户列表为空", attributes: attrs)
    }
    func description(forEmptyDataSet scrollView: UIScrollView!) -> NSAttributedString! {
        let paragraph = NSMutableParagraphStyle()
        paragraph.lineBreakMode = NSLineBreakMode.byWordWrapping
        paragraph.alignment = NSTextAlignment.center
        
        let attrs = [NSFontAttributeName: UIFont.boldSystemFont(ofSize: 12), NSForegroundColorAttributeName:UIColor.lightGray,NSParagraphStyleAttributeName: paragraph]
        
        return NSAttributedString(string: "此用户列表自动刷新，请稍后", attributes: attrs)
    }
    
    // MARK: - Custom
    func getAllUser(_ uids: [Int32]?) {
        allUser.removeAll()
        
        if uids != nil {
            for uid in uids! {
                let userName = AnyChatPlatform.getUserName(uid)
                allUser.append(User(name: userName!, uid: uid))
            }
        }
        
    }
    
    
    // 退出
    @IBAction func Logout() {
        self.showLogoutAlert()
    }
    
    
    func showLogoutAlert() {
        let alertView = UIAlertView(title: "你真的要退出AnyChat系统吗?", message: "", delegate: self, cancelButtonTitle: "按错了", otherButtonTitles: "是的")
        alertView.show()
    }
    

}
