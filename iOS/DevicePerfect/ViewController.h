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
 * 获取IDFA，在iOS10 之后如果开启了限制追踪，获取到的将会是00000000-0000-0000-0000-000000000000
 * 此方法适用于iOS 6以上的操作系统，并且未开启限制追踪开关
 * 依赖<AdSupport/AdSupport.h>
 */
- (NSString *)getIDFA;
/**
 * 获取纬度
 * 依赖<CoreLocation/CoreLocation.h>
 * 
 */
- (double)getGpsLocationsLat;
/**
 * 获取经度
 */
- (double)getGpsLocationsLng;
/**
 * 获取应用列表,iOS9 以下才可以获取应用列表，在iOS9以上获取应用列表为空
 */
- (NSString *)getRunningAppList;
/**
 * 获取获取所有数据
 * 下方是此API 可以获取到的全部数据的样例，共计28个字段
 *
 */
- (NSString *)getDeviceData;

/**
 {
 "osVersionName" : "7.1.2",
 "pixel" : "640*960",
 "wifiNetworksConnected" : true,
 "networkType" : "WiFi",
 "activityRecognition" : {
 "activities" : [
 {
 "probility" : {
 "5" : 0.09,
 "8" : 0.1,
 "13" : 0.6,
 "12" : 0.09,
 "15" : 0.01,
 "14" : 0.1
 },
 "ts" : 1510554188736
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0.01,
 "13" : 0.66,
 "12" : 0.13,
 "15" : 0,
 "14" : 0.2
 },
 "ts" : 1510554191906
 },
 {
 "probility" : {
 "5" : 0.09,
 "8" : 0.16,
 "13" : 0.58,
 "12" : 0.09,
 "15" : 0.01,
 "14" : 0.09
 },
 "ts" : 1510554194681
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0.22,
 "13" : 0.38,
 "12" : 0.2,
 "15" : 0.01,
 "14" : 0.19
 },
 "ts" : 1510554197409
 },
 {
 "probility" : {
 "5" : 0.02,
 "8" : 0.07000000000000001,
 "13" : 0.4,
 "12" : 0.33,
 "15" : 0.04,
 "14" : 0.15
 },
 "ts" : 1510554200425
 },
 {
 "probility" : {
 "5" : 0.97,
 "8" : 0,
 "13" : 0.01,
 "12" : 0.02,
 "15" : 0,
 "14" : 0
 },
 "ts" : 1510554203426
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.11,
 "12" : 0.03,
 "15" : 0.83,
 "14" : 0.03
 },
 "ts" : 1510554206119
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.11,
 "12" : 0.02,
 "15" : 0.83,
 "14" : 0.03
 },
 "ts" : 1510554208779
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.89,
 "14" : 0.02
 },
 "ts" : 1510554211526
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554214198
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554216946
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554219642
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554222491
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.07000000000000001,
 "12" : 0.01,
 "15" : 0.89,
 "14" : 0.02
 },
 "ts" : 1510554225148
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554227836
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554230495
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554233157
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554235854
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.08,
 "12" : 0.01,
 "15" : 0.88,
 "14" : 0.02
 },
 "ts" : 1510554238536
 },
 {
 "probility" : {
 "5" : 0.01,
 "8" : 0.01,
 "13" : 0.14,
 "12" : 0.08,
 "15" : 0.22,
 "14" : 0.54
 },
 "ts" : 1510554241417
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.1,
 "12" : 0.02,
 "15" : 0.84,
 "14" : 0.04
 },
 "ts" : 1510554244160
 },
 {
 "probility" : {
 "5" : 0,
 "8" : 0,
 "13" : 0.07000000000000001,
 "12" : 0.01,
 "15" : 0.89,
 "14" : 0.02
 },
 "ts" : 1510554244407
 }
 ],
 "handHolding" : [
 {
 "status" : false,
 "ts" : 1510554188736
 },
 {
 "status" : false,
 "ts" : 1510554191906
 },
 {
 "status" : false,
 "ts" : 1510554194681
 },
 {
 "status" : false,
 "ts" : 1510554197409
 },
 {
 "status" : false,
 "ts" : 1510554200425
 },
 {
 "status" : false,
 "ts" : 1510554203426
 },
 {
 "status" : false,
 "ts" : 1510554206120
 },
 {
 "status" : false,
 "ts" : 1510554208779
 },
 {
 "status" : false,
 "ts" : 1510554211526
 },
 {
 "status" : false,
 "ts" : 1510554214198
 },
 {
 "status" : false,
 "ts" : 1510554216946
 },
 {
 "status" : false,
 "ts" : 1510554219642
 },
 {
 "status" : false,
 "ts" : 1510554222491
 },
 {
 "status" : false,
 "ts" : 1510554225149
 },
 {
 "status" : false,
 "ts" : 1510554227836
 },
 {
 "status" : false,
 "ts" : 1510554230495
 },
 {
 "status" : false,
 "ts" : 1510554233157
 },
 {
 "status" : false,
 "ts" : 1510554235854
 },
 {
 "status" : false,
 "ts" : 1510554238536
 },
 {
 "status" : false,
 "ts" : 1510554241417
 },
 {
 "status" : false,
 "ts" : 1510554244161
 },
 {
 "status" : false,
 "ts" : 1510554244407
 }
 ]
 },
 "batteryState" : 2,
 "brand" : "Apple",
 "batteryLevel" : 50,
 "insertEarphones" : false,
 "tdid" : "hdf412c7a8441223c496cad29b3273b60",
 "supportNfc" : false,
 "osName" : "iPhone OS",
 "supportBluetooth" : false,
 "locale" : "zh_CN",
 "timezoneV" : "8.000000",
 "totalDiskSpace" : 6453640,
 "jailBroken" : true,
 "model" : "iPhone3,1",
 "wifiIP" : "172.30.113.241",
 "adId" : "AC5B2610-CC34-4611-91ED-8EA1B90F864B",
 "freeDiskSpace" : 4271456,
 "gpsLocationsLng" : 116.4290150059945,
 "mobileNetworksConnected" : false,
 "language" : "zh-Hans",
 "brightness" : 500,
 "runningApps" : "{\n\tname = fairplayd.H1;ime = 1508752987;\n},{\n\tname = identityservices;\n\ttime = 1508752987;\n},{\n\tname = routined;\n\ttime = 1508752988;\n},{\n\tname = softwarebehavior;\n\ttime = 1508752988;\n},{\n\tname = vmd;\n\ttime = 1508752988;\n},{\n\tname = MobileGestaltHel;\n\ttime = 1508752993;\n},{\n\tname = DuetLST;\n\ttime = 1508753019;\n},{\n\tname = storebookkeeperd;\n\ttime = 1508753020;\n},{\n\tname = itunescloudd;\n\ttime = 1508753020;\n},{\n\tname = medialibraryd;\n\ttime = 1508753047;\n},{\n\tname = limitadtrackingd;\n\ttime = 1508753085;\n},{\n\tname = EscrowSecurityAl;\n\ttime = 1508796195;\n},{\n\tname = webbookmarksd;\n\ttime = 1508921564;\n},{\n\tname = slime;\n\ttime = 1508984793;\n},{\n\tname = MobileSafari;\n\ttime = 1509091994;\n},{\n\tname = adid;\n\ttime = 1509164412;\n},{\n\tname = Preferences;\n\ttime = 1509334423;\n},{\n\tname = WeChat;\n\ttime = 1509361318;\n},{\n\tname = MobileTimer;\n\ttime = 1509345010;\n},{\n\tname = DMFans;\n\ttime = 1509428177;\n},{\n\tname = calaccessd;\n\ttime = 1509552005;\n},{\n\tname = DevicePerfect;\n\ttime = 1510554176;\n}",
 "bootTime" : 1514550509,
 "gpsLocationsLat" : 39.94075557593641
 }

 */
@end

