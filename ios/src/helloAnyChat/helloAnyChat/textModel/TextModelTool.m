//
//  TextModelTool.m
//  HelloAnyChat
//
//  Created by Mac on 16/5/19.
//  Copyright © 2016年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TextModelTool.h"

#define TextFile [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:@"text.data"]

@implementation TextModelTool

+ (void)saveText:(TextModel *)model {
    [NSKeyedArchiver archiveRootObject:model toFile:TextFile];
}

+ (TextModel *)textModel {
    TextModel *text = [NSKeyedUnarchiver unarchiveObjectWithFile:TextFile];
    return text;
}

@end
