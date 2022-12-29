//
//  Misc.m
//  helloAnyChat
//
//  Created by Bairui on 2019/3/26.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatMisc.h"
//#import "AnyChatLog.h"


@implementation AnyChatMisc

///
+ (NSString*)objToJsonString:(id)obj
{
    NSString *jsonString = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:obj
                                                       options:0 // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    if (!jsonData) {
//        BRACDebugLog(@"json化失败: %@", error);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return jsonString;
}

+ (NSDictionary *)jsonStringToDictionary:(NSString *)jsonStr
{
    if (jsonStr == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&error];
    if(error)
    {
//        BRACDebugLog(@"json解析失败: %@", error);
        return nil;
    }
    return dic;
}

//对一个字符串进行base64编码
+ (NSString *)base64EncodeString:(NSString *)string
{
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    return [data base64EncodedStringWithOptions:0];
}

//对一个字符串进行base解码
+ (NSString *)base64DecodeString:(NSString *)string
{
//    BRACDebugLog(@"===>base64解码前:%@",string);
#if DEBUG
//    [AnyChatLog logI:[NSString stringWithFormat:@"===>base64解码前:%@",string],@""];
#endif
    NSData *data = [[NSData alloc]initWithBase64EncodedString:string options:0];
    NSString* rst = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
//    BRACDebugLog(@"===>base64解码后:%@",rst);
#if DEBUG
//    [AnyChatLog logI:[NSString stringWithFormat:@"===>base64解码后:%@",rst],@""];
#endif
    return rst;
}

//UIImage图片转成Base64字符串
//+ (NSString*)base64EncodePic:(UIImage*)originImage{
//    //(NSString*)picName
////    UIImage *originImage = [UIImage imageNamed:picName];
//    NSData *data = UIImageJPEGRepresentation(originImage, 0.5f);
//    NSString *encodedImageStr = [data base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
//    encodedImageStr = [encodedImageStr stringByReplacingOccurrencesOfString:@"\r" withString:@""];
//    encodedImageStr = [encodedImageStr stringByReplacingOccurrencesOfString:@"\n" withString:@""];
//
//    return encodedImageStr;
//}
//
////Base64字符串转UIImage图片
//+ (UIImage*)base64DecodePic:(NSString*)encodedImageStr{
//    NSData *decodedImageData = [[NSData alloc]
//                                initWithBase64EncodedString:encodedImageStr options:NSDataBase64DecodingIgnoreUnknownCharacters];
//    UIImage *decodedImage = [UIImage imageWithData:decodedImageData];
//    return decodedImage;
//}

//范围随机数
+ (int)getRandomNumber:(int)from to:(int)to{
    return (int)(from + (arc4random() % (to - from + 1)));
}

//带排除项的范围随机数
+ (int)getRandomNumber:(int)from to:(int)to exceptNums:(NSArray *)exceptNums {
    while (1) {
        int random = (int)(from + (arc4random() % (to - from + 1)));
        NSString *randomStr = [NSString stringWithFormat:@"%d", random];
        NSString *exceptNumStr = [exceptNums componentsJoinedByString:@""];
//        BRACDebugLog(@"randomStr:%@", randomStr);
        NSCharacterSet *set = [NSCharacterSet characterSetWithCharactersInString:exceptNumStr];
        if ([randomStr rangeOfCharacterFromSet:set].location == NSNotFound) {
            return random;
        }
    }
    return 0;
}

///模型转字典
+(NSDictionary*)modeToDict:(id)modelObject keys:(NSArray<NSString *> *)keyArray{
    return [modelObject dictionaryWithValuesForKeys:keyArray];
}

@end
