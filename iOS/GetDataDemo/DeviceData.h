//
//  ViewController.h
//  UIDemoGetData
//
//  Created by Caroline on 2017/9/27.
//  Copyright © 2017年 冯Caroline. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DeviceData : NSObject

/**
 * 获取IDFA
 */
+ (NSString *)getIDFA;
/**
 * 获取纬度
 */
+ (double)getGpsLocationsLat;
/**
 * 获取经度
 */
+ (double)getGpsLocationsLng;
/**
 * 获取应用列表,iOS9 以下才可以获取应用列表
 */
+ (NSString *)getRunningAppList;
/**
 * 获取获取所有数据
 */

+ (NSString *)getDeviceData;

//获取已经获取到的字段
+ (NSDictionary *)getDictionary;
@end

