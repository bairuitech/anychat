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
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.tableView.reloadData()
    }
    
    func loadData() {
        let path: String = Bundle.main.path(forResource: "VideoParamSetting.plist", ofType: nil)!
        groupArr = NSArray(contentsOfFile:path)!
    }

    // MARK: - Table view data source
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section < 2 {
            return 1
        }else {
            return groupArr.count
        }
    }
    
    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return titles[section]
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "ParamSetting", for: indexPath) as UITableViewCell
        cell
        if indexPath.section == 0 {
            cell.textLabel?.text = "优先P2P"
            let p2pSwitch: UISwitch = UISwitch()
            // 读取本地缓存
            let defaults: UserDefaults = UserDefaults.standard
            p2pSwitch.setOn(defaults.bool(forKey: keys[0]), animated: false)
            cell.accessoryView = p2pSwitch
            p2pSwitch.addTarget(self, action: #selector(VideoParamSettingViewController.p2pChange(_:)), for:.valueChanged)
            cell.detailTextLabel?.text = ""
            cell.selectionStyle = UITableViewCellSelectionStyle.none
        }else if indexPath.section == 1 {
            cell.textLabel?.text = "使用服务器视频参数"
            let serverParamSwitch: UISwitch = UISwitch()
            // 读取本地缓存
            let defaults: UserDefaults = UserDefaults.standard
            serverParamSwitch.setOn(defaults.bool(forKey: keys[1]), animated: false)
            serverParamSwitch.addTarget(self, action: #selector(VideoParamSettingViewController.serverParamChange(_:)), for: .valueChanged)
            cell.accessoryView = serverParamSwitch
            cell.detailTextLabel?.text = ""
            cell.selectionStyle = UITableViewCellSelectionStyle.none
        }else {
            let ocDict = groupArr[indexPath.row] as! NSDictionary
            cell.textLabel!.text = ocDict.object(forKey: "keyCN") as? String
            let key = ocDict.object(forKey: "keyEN") as? String
            
            // 读取本地缓存
            let defaults: UserDefaults = UserDefaults.standard
            let selectedItem = defaults.object(forKey: key!)
            let childArr = ocDict.object(forKey: "childItem") as! NSArray
            if selectedItem == nil { // 第一次，没本地缓存
                let defaultSel = ocDict.object(forKey: "default") as! String
                for dict in childArr {
                    let ocDict = dict as! NSDictionary
                    let childKey = ocDict.object(forKey: "key") as! String
                    if defaultSel == childKey {
                        cell.detailTextLabel?.text = ocDict.object(forKey: "value") as? String
                    }
                }
            }else { // 有本地缓存
                for dict in childArr {
                    let ocDict = dict as! NSDictionary
                    let childKey = ocDict.object(forKey: "key") as! String
                    if selectedItem as! String == childKey {
                        cell.detailTextLabel?.text = ocDict.object(forKey: "value") as? String
                    }
                }
            }

            cell.accessoryType = UITableViewCellAccessoryType.disclosureIndicator
            
        }
        
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        if indexPath.section>1 {
            selectData = groupArr[indexPath.row] as! NSDictionary
            self.performSegue(withIdentifier: "Detail", sender: self)
        }
        self.tableView.deselectRow(at: indexPath, animated: false) // 取消选中状态
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "Detail" {
            let videoDetailVC = segue.destination as! VideoParamSettingDetailController;
            videoDetailVC.data = self.selectData
        }
    }
    
    func p2pChange(_ sender: UISwitch) {
        // 设置本地缓存
        let defaluts: UserDefaults = UserDefaults.standard
        defaluts.set(sender.isOn, forKey: keys[0])
        defaluts.synchronize()  // 同步
        
    }
    
    func serverParamChange(_ sender: UISwitch) {
        // 设置本地缓存
        let defaluts: UserDefaults = UserDefaults.standard
        defaluts.set(sender.isOn, forKey: keys[1])
        defaluts.synchronize() // 同步
    }
    
    @IBAction func back() {
        self.navigationController?.popViewController(animated: true)
        self.setupAnyChatVideoParam()
    }
    
    // AnyChat 参数配置
    func setupAnyChatVideoParam() {
        // 读取本地缓存
        let defaults: UserDefaults = UserDefaults.standard
        let p2p = defaults.bool(forKey: keys[0])
        let serverparam = defaults.bool(forKey: keys[1])
        let resolution = defaults.object(forKey: keys[2])
        let bitrate = defaults.object(forKey: keys[3])
        let frameRate = defaults.object(forKey: keys[4])
        let preset = defaults.object(forKey: keys[5])
        let quality = defaults.object(forKey: keys[6])

        AnyChatPlatform.setSDKOptionInt(BRAC_SO_NETWORK_P2PPOLITIC, p2p ? 1 : 0)    // P2P

        if !serverparam {

            // 分辨率
            if resolution == nil {
                let ocDict = groupArr[0] as! NSDictionary
                let defaultStr = ocDict.object(forKey: "default") as! String
                let defaultInt = Int(defaultStr)!
                let arrWidthIndex = resolutionWidthArr[defaultInt]
                let arrHeightIndex = resolutionHeightArr[defaultInt]
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL, arrWidthIndex)
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, arrHeightIndex)
            }else {
                let selectedStr = resolution as! String
                let selectedInt = Int(selectedStr)!
                let arrWidthIndex = resolutionWidthArr[selectedInt]
                let arrHeightIndex = resolutionHeightArr[selectedInt]
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL, arrWidthIndex)
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, arrHeightIndex)
            }

            // 码率
            if bitrate == nil {
                let ocDict = groupArr[1] as! NSDictionary
                let defaultStr = ocDict.object(forKey: "default") as! String
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL, Int32(bitrate as! String)!)
            }

            // 帧率
            if frameRate == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.object(forKey: "default") as! String
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL, Int32(frameRate as! String)!)
            }

            // 预设参数
            if preset == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.object(forKey: "default") as! String
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL, Int32(preset as! String)!)
            }

            // 视频质量
            if quality == nil {
                let ocDict = groupArr[2] as! NSDictionary
                let defaultStr = ocDict.object(forKey: "default") as! String
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL, Int32(defaultStr)!)
            }else {
                AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL, Int32(quality as! String)!)
            }
            
        }
        
        AnyChatPlatform.setSDKOptionInt(BRAC_SO_LOCALVIDEO_APPLYPARAM, serverparam ? 0 : 1) //本地参数
    }
    
}
