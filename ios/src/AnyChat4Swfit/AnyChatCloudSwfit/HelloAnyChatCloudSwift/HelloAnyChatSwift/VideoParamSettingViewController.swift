//
//  VideoParamSettingViewController.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/11/3.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  视频参数设置主界面

import UIKit

class VideoParamSettingViewController: UITableViewController {

    let titles = ["网络参数设置","视频参数控制","本地视频参数设置"]
    let keys = ["usep2p","useserverparam","videoresolution","videobitrate","videoframerate","videopreset","videoquality"]
    let resolutionWidthArr:[Int32] = [1280,640,480,352,192]
    let resolutionHeightArr:[Int32] = [720,480,360,288,144]
    var groupArr :NSArray = []
    var selectData = NSDictionary()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.loadData()
        
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        self.tableView.reloadData()
    }
    
    func loadData() {
        let path: String = NSBundle.mainBundle().pathForResource("VideoParamSetting.plist", ofType: nil)!
        groupArr = NSArray(contentsOfFile:path)!
    }

    // MARK: - Table view data source
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 3
    }

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section < 2 {
            return 1
        }else {
            return groupArr.count
        }
    }
    
    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return titles[section]
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("ParamSetting", forIndexPath: indexPath) as UITableViewCell
        cell
        if indexPath.section == 0 {
            cell.textLabel?.text = "优先P2P"
            let p2pSwitch: UISwitch = UISwitch()
            // 读取本地缓存
            let defaults: NSUserDefaults = NSUserDefaults.standardUserDefaults()
            p2pSwitch.setOn(defaults.boolForKey(keys[0]), animated: false)
            cell.accessoryView = p2pSwitch
            p2pSwitch.addTarget(self, action: "p2pChange:", forControlEvents:.ValueChanged)
            cell.detailTextLabel?.text = ""
            cell.selectionStyle = UITableViewCellSelectionStyle.None
        }else if indexPath.section == 1 {
            cell.textLabel?.text = "使用服务器视频参数"
            let serverParamSwitch: UISwitch = UISwitch()
            // 读取本地缓存
            let defaults: NSUserDefaults = NSUserDefaults.standardUserDefaults()
            serverParamSwitch.setOn(defaults.boolForKey(keys[1]), animated: false)
            serverParamSwitch.addTarget(self, action: "serverParamChange:", forControlEvents: .ValueChanged)
            cell.accessoryView = serverParamSwitch
            cell.detailTextLabel?.text = ""
            cell.selectionStyle = UITableViewCellSelectionStyle.None
        }else {
            let ocDict = groupArr[indexPath.row] as! NSDictionary
            cell.textLabel!.text = ocDict.objectForKey("keyCN") as? String
            let key = ocDict.objectForKey("keyEN") as? String
            
            // 读取本地缓存
            let defaults: NSUserDefaults = NSUserDefaults.standardUserDefaults()
            let selectedItem = defaults.objectForKey(key!)
            let childArr = ocDict.objectForKey("childItem") as! NSArray
            if selectedItem == nil { // 第一次，没本地缓存
                let defaultSel = ocDict.objectForKey("default") as! String
                for dict in childArr {
                    let ocDict = dict as! NSDictionary
                    let childKey = ocDict.objectForKey("key") as! String
                    if defaultSel == childKey {
                        cell.detailTextLabel?.text = ocDict.objectForKey("value") as? String
                    }
                }
            }else { // 有本地缓存
                for dict in childArr {
                    let ocDict = dict as! NSDictionary
                    let childKey = ocDict.objectForKey("key") as! String
                    if selectedItem as! String == childKey {
                        cell.detailTextLabel?.text = ocDict.objectForKey("value") as? String
                    }
                }
            }

            cell.accessoryType = UITableViewCellAccessoryType.DisclosureIndicator
            
        }
        
        
        return cell
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        if indexPath.section>1 {
            selectData = groupArr[indexPath.row] as! NSDictionary
            self.performSegueWithIdentifier("Detail", sender: self)
        }
        self.tableView.deselectRowAtIndexPath(indexPath, animated: false) // 取消选中状态
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "Detail" {
            let videoDetailVC = segue.destinationViewController as! VideoParamSettingDetailController;
            videoDetailVC.data = self.selectData
        }
    }
    
    func p2pChange(sender: UISwitch) {
        // 设置本地缓存
        let defaluts: NSUserDefaults = NSUserDefaults.standardUserDefaults()
        defaluts.setBool(sender.on, forKey: keys[0])
        defaluts.synchronize()  // 同步
        
    }
    
    func serverParamChange(sender: UISwitch) {
        // 设置本地缓存
        let defaluts: NSUserDefaults = NSUserDefaults.standardUserDefaults()
        defaluts.setBool(sender.on, forKey: keys[1])
        defaluts.synchronize() // 同步
    }
    
    @IBAction func back() {
        self.navigationController?.popViewControllerAnimated(true)
        self.setupAnyChatVideoParam()
    }
    
    // AnyChat 参数配置
    func setupAnyChatVideoParam() {
        // 读取本地缓存
        let defaults: NSUserDefaults = NSUserDefaults.standardUserDefaults()
        let p2p = defaults.boolForKey(keys[0])
        let serverparam = defaults.boolForKey(keys[1])
        let resolution = defaults.objectForKey(keys[2])
        let bitrate = defaults.objectForKey(keys[3])
        let frameRate = defaults.objectForKey(keys[4])
        let preset = defaults.objectForKey(keys[5])
        let quality = defaults.objectForKey(keys[6])

        AnyChatPlatform.SetSDKOptionInt(BRAC_SO_NETWORK_P2PPOLITIC, p2p ? 1 : 0)    // P2P

        if !serverparam {

            // 分辨率
            if resolution == nil {
                let ocDict = groupArr[0] as! NSDictionary
                let defaultStr = ocDict.objectForKey("default") as! String
                let defaultInt = Int(defaultStr)!
                let arrWidthIndex = resolutionWidthArr[defaultInt]
                let arrHeightIndex = resolutionHeightArr[defaultInt]
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL, arrWidthIndex)
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, arrHeightIndex)
            }else {
                let selectedStr = resolution as! String
                let selectedInt = Int(selectedStr)!
                let arrWidthIndex = resolutionWidthArr[selectedInt]
                let arrHeightIndex = resolutionHeightArr[selectedInt]
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL, arrWidthIndex)
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, arrHeightIndex)
            }

            // 码率
            if bitrate == nil {
                let ocDict = groupArr[1] as! NSDictionary
                let defaultStr = ocDict.objectForKey("default") as! String
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL, Int32(bitrate as! String)!)
            }

            // 帧率
            if frameRate == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.objectForKey("default") as! String
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL, Int32(frameRate as! String)!)
            }

            // 预设参数
            if preset == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.objectForKey("default") as! String
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL, Int32(preset as! String)!)
            }

            // 视频质量
            if quality == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.objectForKey("default") as! String
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL, Int32(quality as! String)!)
            }
            
        }
        
        AnyChatPlatform.SetSDKOptionInt(BRAC_SO_LOCALVIDEO_APPLYPARAM, serverparam ? 0 : 1) //本地参数
    }
    
}
