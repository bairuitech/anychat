//
//  User.swift
//  HelloAnyChatSwift
//
//  Created by bairuitech on 15/11/2.
//  Copyright © 2015年 bairuitech. All rights reserved.
//  用户模型

import UIKit

class User: NSObject {
    var name: String
    var uid: Int32
    
    init(name: String, uid: Int32) {
        self.name = name
        self.uid = uid
        
        super.init()
    }
}