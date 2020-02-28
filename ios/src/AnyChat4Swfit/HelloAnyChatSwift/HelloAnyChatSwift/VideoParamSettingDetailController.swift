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
        self.title = data.object(forKey: "keyCN") as? String
        
    }
    
    @IBAction func back() {
        self.navigationController?.popViewController(animated: true)
    }
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return (data.object(forKey: "childItem")! as AnyObject).count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "VideoDetail", for: indexPath) as UITableViewCell
        
        let childArr = data.object(forKey: "childItem") as! NSArray
        let itemDict = childArr[indexPath.row] as! NSDictionary
        cell.textLabel?.text = itemDict.object(forKey: "value") as? String
        let childKey = itemDict.object(forKey: "key") as! String
        cell.detailTextLabel?.text = childKey
        
        // 读取本地缓存
        let key = data.object(forKey: "keyEN") as? String
        let defaults: UserDefaults = UserDefaults.standard
        let selectedItem = defaults.object(forKey: key!)
        
        if selectedItem == nil { // 第一次，没本地缓存
            let selectInt = data.object(forKey: "default") as! String
            if selectInt == childKey {
                cell.accessoryType = UITableViewCellAccessoryType.checkmark
            }
        }else {
            if selectedItem as! String == childKey {
                cell.accessoryType = UITableViewCellAccessoryType.checkmark
            }
        }
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {

        let childArr = data.object(forKey: "childItem") as! NSArray
        let itemDict = childArr[indexPath.row] as! NSDictionary
        let value = itemDict.object(forKey: "key") as! String
        let key = data.object(forKey: "keyEN") as! String
        
        // 设置本地缓存
        let defaluts: UserDefaults = UserDefaults.standard
        defaluts.set(value, forKey: key)
        defaluts.synchronize()
        
        self.navigationController?.popViewController(animated: true)
    }
}
