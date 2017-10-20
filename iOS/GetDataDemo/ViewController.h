//
//  ViewController.h
//  GetDataDemo
//
//  Created by 冯婷婷 on 2017/9/29.
//  Copyright © 2017年 冯婷婷. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^locationBlock)(double lat,double lng);
@interface ViewController : UIViewController
@property (nonatomic,assign) double locationsLat;
@property (nonatomic,assign) double locationsLng;
@property (nonatomic,strong) NSMutableDictionary *dictionaryLoc;
@property (nonatomic, copy) locationBlock locationBlock;
- (void)returnText:(locationBlock)block;
@end

