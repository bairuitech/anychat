//
//  TextModelTool.h
//  HelloAnyChat
//
//  Created by Mac on 16/5/19.
//  Copyright © 2016年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TextModel.h"

@interface TextModelTool : NSObject

+ (void)saveText:(TextModel *)model;

+ (TextModel *)textModel;

@end
