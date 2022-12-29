//
//  Misc.h
//  helloAnyChat
//
//  Created by Bairui on 2019/3/26.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface AnyChatMisc : NSObject

//对象与字符串互转

+ (NSString*)objToJsonString:(id)obj;
+ (NSDictionary *)jsonStringToDictionary:(NSString *)jsonStr;
+ (NSDictionary*)modeToDict:(id)modelObject keys:(NSArray<NSString *> *)keyArray;

//base64编解码
+ (NSString *)base64EncodeString:(NSString *)string;
+ (NSString *)base64DecodeString:(NSString *)string;

////图片与base64互转
//+ (NSString*)base64EncodePic:(UIImage*)originImage;
//+ (UIImage*)base64DecodePic:(NSString*)encodedImageStr;

//随机数
+ (int)getRandomNumber:(int)from to:(int)to;
//不包含某些数字的随机数
+ (int)getRandomNumber:(int)from to:(int)to exceptNums:(NSArray *)exceptNums;

@end

