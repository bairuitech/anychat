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
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if allUserIDs == nil {
            return 0
        }else {
            return allUser.count
        }
    }

    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("UserList", forIndexPath: indexPath) as UITableViewCell
        
        let user = allUser[indexPath.row] as User
        cell.textLabel?.text = user.name                // 用户名
        cell.detailTextLabel?.text = String(user.uid)   // 用户ID
        let imageName = "face\((arc4random() % 5) + 1)" // 随机头像
        cell.imageView?.image = UIImage(named: imageName)
        return cell
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        let selectUser = self.allUser[indexPath.row]
        self.remoteUserId = selectUser.uid
        
        self.performSegueWithIdentifier("Video", sender: self)
        
        // 取消选中状态
        self.tableView.deselectRowAtIndexPath(indexPath, animated: false)
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "Video" {
            let videoVC = segue.destinationViewController as! VideoViewController;
            videoVC.remoteUserId = self.remoteUserId
        }
    }
    
    func alertView(alertView: UIAlertView, clickedButtonAtIndex buttonIndex: Int) {
        if buttonIndex == 1 {
            // 离开本房间
            AnyChatPlatform.LeaveRoom(-1)
            // 注销
            AnyChatPlatform.Logout()
            self.navigationController?.popViewControllerAnimated(true)
        }
    }
    
    // MARK: - EmptyData
    func imageForEmptyDataSet(scrollView: UIScrollView!) -> UIImage! {
        return UIImage(named: "empty_bg")
    }
    func titleForEmptyDataSet(scrollView: UIScrollView!) -> NSAttributedString! {
        let attrs = [NSFontAttributeName: UIFont.boldSystemFontOfSize(14), NSForegroundColorAttributeName:UIColor.lightGrayColor()]
        return NSAttributedString(string:"用户列表为空", attributes: attrs)
    }
    func descriptionForEmptyDataSet(scrollView: UIScrollView!) -> NSAttributedString! {
        let paragraph = NSMutableParagraphStyle()
        paragraph.lineBreakMode = NSLineBreakMode.ByWordWrapping
        paragraph.alignment = NSTextAlignment.Center
        
        let attrs = [NSFontAttributeName: UIFont.boldSystemFontOfSize(12), NSForegroundColorAttributeName:UIColor.lightGrayColor(),NSParagraphStyleAttributeName: paragraph]
        
        return NSAttributedString(string: "此用户列表自动刷新，请稍后", attributes: attrs)
    }
    
    // MARK: - Custom
    func getAllUser(uids: [Int32]?) {
        allUser.removeAll()
        
        if uids != nil {
            for uid in uids! {
                let userName = AnyChatPlatform.GetUserName(uid)
                allUser.append(User(name: userName, uid: uid))
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
