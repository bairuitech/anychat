//
//  UIView+AdaptScreenWidth.h
//  TestXib
//
//  Created by lbs on 2018/8/14.
//  Copyright © 2018年 by. All rights reserved.
//

#import <UIKit/UIKit.h>

// 基准屏幕宽度
#define kRefereWidth (414.0)
// 以屏幕宽度为固定比例关系，来计算对应的值。假设：基准屏幕宽度375，floatV=10；当前屏幕宽度为750时，那么返回的值为20
#define AdaptW(floatValue) (floatValue*[[UIScreen mainScreen] bounds].size.width/kRefereWidth)


typedef NS_ENUM(NSInteger, AdaptScreenWidthType) {
    AdaptScreenWidthTypeConstraint = 1<<0, /**< 对约束的constant等比例 */
    AdaptScreenWidthTypeFontSize = 1<<1, /**< 对字体等比例 */
    AdaptScreenWidthTypeCornerRadius = 1<<2, /**< 对圆角等比例 */
    AdaptScreenWidthTypeAll = 1<<3, /**< 对现有支持的属性等比例 */
};

@interface UIView (AdaptScreen)

/**
 遍历当前view对象的subviews和constraints，对目标进行等比例换算
 
 @param type 想要和基准屏幕等比例换算的属性类型
 @param exceptViews 需要对哪些类进行例外
 */
- (void)adaptScreenWidthWithType:(AdaptScreenWidthType)type
                     exceptViews:(NSArray<Class> *)exceptViews;

@end
