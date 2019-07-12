//
//  ACFeatureCollectionCell.m
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/10.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ACFeatureCollectionCell.h"

@interface ACFeatureCollectionCell ()

@property (weak, nonatomic) IBOutlet UIImageView *imgView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;

@end

@implementation ACFeatureCollectionCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
}


- (void)configCellByImage:(UIImage *)image
                     name:(NSString *)name {
    
    self.imgView.image = image;
    self.nameLabel.text = name;
    
    if([UIScreen mainScreen].bounds.size.width <= 320) {
        
        self.nameLabel.font = [UIFont systemFontOfSize:12];
    } else {
        
        self.nameLabel.font = [UIFont systemFontOfSize:AdaptW(14)];

    }
}
@end
