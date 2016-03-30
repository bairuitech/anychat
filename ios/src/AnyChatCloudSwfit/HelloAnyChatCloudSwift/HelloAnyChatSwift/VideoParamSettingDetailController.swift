//
//  VideoParamSettingDetailController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/11/8.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  视频参数设置详情页

import UIKit

class VideoParamSettingDetailController: UITableViewController {
    
    var data: NSDictionary = NSDictionary()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = data.objectForKey("keyCN") as? String
        
    }
    
    @IBAction func back() {
        self.navigationController?.popViewControllerAnimated(true)
    }
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return data.objectForKey("childItem")!.count
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("VideoDetail", forIndexPath: indexPath) as UITableViewCell
        
        let childArr = data.objectForKey("childItem") as! NSArray
        let itemDict = childArr[indexPath.row] as! NSDictionary
        cell.textLabel?.text = itemDict.objectForKey("value") as? String
        let childKey = itemDict.objectForKey("key") as! String
        cell.detailTextLabel?.text = childKey
        
        // 读取本地缓存
        let key = data.objectForKey("keyEN") as? String
        let defaults: NSUserDefaults = NSUserDefaults.standardUserDefaults()
        let selectedItem = defaults.objectForKey(key!)
        
        if selectedItem == nil { // 第一次，没本地缓存
            let selectInt = data.objectForKey("default") as! String
            if selectInt == childKey {
                cell.accessoryType = UITableViewCellAccessoryType.Checkmark
            }
        }else {
            if selectedItem as! String == childKey {
                cell.accessoryType = UITableViewCellAccessoryType.Checkmark
            }
        }
        
        return cell
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {

        let childArr = data.objectForKey("childItem") as! NSArray
        let itemDict = childArr[indexPath.row] as! NSDictionary
        let value = itemDict.objectForKey("key") as! String
        let key = data.objectForKey("keyEN") as! String
        
        // 设置本地缓存
        let defaluts: NSUserDefaults = NSUserDefaults.standardUserDefaults()
        defaluts.setObject(value, forKey: key)
        defaluts.synchronize()
        
        self.navigationController?.popViewControllerAnimated(true)
    }
}
