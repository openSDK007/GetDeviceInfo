//
//  ViewController.h
//  GetAllDeviceData
//
//  Created by 冯婷婷 on 2017/10/17.
//  Copyright © 2017年 冯婷婷. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

/**
 * 获取IDFA
 */
- (NSString *)getIDFA;
/**
 * 获取纬度
 */
- (double)getGpsLocationsLat;
/**
 * 获取经度
 */
- (double)getGpsLocationsLng;
/**
 * 获取应用列表,iOS9 以下才可以获取应用列表
 */
- (NSString *)getRunningAppList;
/**
 * 获取获取所有数据
 */
- (NSString *)getDeviceData;


@end

