
//  DeviceData.m
//  UIDemoGetData
//
//  Created by Caroline on 2017/9/27.
//  Copyright © 2017年 Caroline. All rights reserved.
//

#import "DeviceData.h"
#import <AdSupport/AdSupport.h>
#import <CoreLocation/CoreLocation.h>
#import <sys/sysctl.h>
#import "TalkingData.h"
#import <MapKit/MapKit.h>

@interface DeviceData ()<CLLocationManagerDelegate>
@property (nonatomic,strong) NSDictionary *dict;
@property (nonatomic,strong) CLLocationManager *locationmanager;
@property (nonatomic,assign) double locationsLat;
@property (nonatomic,assign) double locationsLng;

@end

@implementation DeviceData
+(instancetype)shareInstance {
    static dispatch_once_t onceToken;
    static DeviceData *_shareInstance;
    
    dispatch_once(&onceToken, ^{
        _shareInstance = [[self alloc] init];
        
    });
    return _shareInstance;
}
- (instancetype)init
{
    self = [super init];
    
    if ([CLLocationManager locationServicesEnabled]) {
        _locationmanager = [[CLLocationManager alloc]init];
        _locationmanager.delegate = self;
        _locationmanager.desiredAccuracy = kCLLocationAccuracyBest;
        [self startLocation];
    }
    
    return self;
}
+ (NSString *)getDeviceData {
    @try {
        NSDictionary *dic = [self getDictionary];
        if (dic == nil || ![dic isKindOfClass:[NSDictionary class]]) {
            return nil;
        }
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic options:NSJSONWritingPrettyPrinted error:nil];
        return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    } @catch (NSException *exception) {
    }
    return nil;
    
}

+ (NSString *)getIDFA {
    static NSString *results = nil;
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 6.0f) {
        return nil;
    }
    
    if (results) {
        return results;
    }
    
    @try {
        for (int i=0; i<5; i++) {
            results = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
            if (results) {
                break;
            }
        }
    } @catch (NSException *exception) {
    }
    
    
    return results;
}



+ (double)getGpsLocationsLat {
    return [DeviceData shareInstance].locationsLat;
}

+ (double)getGpsLocationsLng {
    return [DeviceData shareInstance].locationsLng;
}

+ (NSString *)getRunningAppList {
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0f) {
        NSArray *arr = @[@"wechat"];
        NSString *str = [arr componentsJoinedByString:@","];
        return str;
    }
    
    @try {
        int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
        u_int miblen = 4;
        size_t size;
        int st = sysctl(mib, miblen, NULL, &size, NULL, 0);
        struct kinfo_proc *process = NULL;
        struct kinfo_proc *newprocess = NULL;
        
        do {
            size += size / 10;
            newprocess = realloc(process, size);
            if (!newprocess) {
                if (process) {
                    free(process);
                }
                return nil;
            }
            process = newprocess;
            st = sysctl(mib, miblen, process, &size, NULL, 0);
        } while (st == -1 && errno == ENOMEM);
        
        if (st == 0) {
            if (size % sizeof(struct kinfo_proc) == 0) {
                size_t nprocess = size / sizeof(struct kinfo_proc);
                if (nprocess) {
                    NSMutableArray * array = [NSMutableArray array];
                    NSDictionary *systemProcesses = [self systemProcesses];
                    for (long i = nprocess - 1; i >= 0; i--) {
                        if (process[i].kp_eproc.e_pcred.p_rgid == 501) {
                            @try {
                                NSString *processName = [NSString stringWithUTF8String:process[i].kp_proc.p_comm];
                                if (nil == [systemProcesses objectForKey:processName]) {
                                    NSNumber *processTime = [NSNumber numberWithLong:process[i].kp_proc.p_un.__p_starttime.tv_sec];
                                    NSMutableDictionary *processInfo = [NSMutableDictionary dictionary];
                                    [processInfo setObject:processName forKey:@"name"];
                                    [processInfo setObject:processTime forKey:@"time"];
                                    [array addObject:processInfo];
                                }
                            } @catch (NSException *exception) {
                            }
                        }
                    }
                    free(process);
                    NSString *rasString = [array componentsJoinedByString:@","];
                    return rasString;
                }
            }
        }
    } @catch (NSException *exception) {
    }
    return nil;
}

-(void)startLocation{
    self.locationmanager = [[CLLocationManager alloc] init];
    self.locationmanager.delegate = self;
    self.locationmanager.desiredAccuracy = kCLLocationAccuracyBest;
    self.locationmanager.distanceFilter = 100.0f;
    if ([[[UIDevice currentDevice] systemVersion] doubleValue] >8.0){
        [self.locationmanager requestWhenInUseAuthorization];
    }
    if ([[UIDevice currentDevice].systemVersion floatValue] >= 8.0) {
        _locationmanager.allowsBackgroundLocationUpdates =YES;
    }
    [self.locationmanager startUpdatingLocation];
    
}
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    switch (status) {
            
        case kCLAuthorizationStatusNotDetermined:
            if ([self.locationmanager respondsToSelector:@selector(requestAlwaysAuthorization)]) {
                [self.locationmanager requestWhenInUseAuthorization];
            }
            break;
        default:
            break;
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    
    
    CLLocation *newLocation = locations[0];
    
    CLLocationCoordinate2D oldCoordinate = newLocation.coordinate;
    self.locationsLat = oldCoordinate.latitude;
    self.locationsLng = oldCoordinate.longitude;
    
    NSLog(@"旧的经度：%f,旧的纬度：%f",oldCoordinate.longitude,oldCoordinate.latitude);
    
    [manager stopUpdatingLocation];
    
    
}


+ (NSDictionary *)getDictionary {
    NSMutableDictionary *dataDic = [[NSMutableDictionary alloc]init];
    [dataDic setObject:[TalkingData getDeviceID] forKey:@"tdid"];
    [dataDic setObject:[self getIDFA] forKey:@"adId"];
    [dataDic setObject:[NSNumber numberWithLong:[TalkingData getBootTime]] forKey:@"bootTime"];
    [dataDic setObject:[TalkingData getBrand] forKey:@"brand"];
    [dataDic setObject:[TalkingData getModel] forKey:@"model"];
    [dataDic setObject:[TalkingData getOsName] forKey:@"osName"];
    [dataDic setObject:[TalkingData getOsVersionName] forKey:@"osVersionName"];
    NSString *pixel = [NSString stringWithFormat:@"%d*%d", [TalkingData getWidthPixels], [TalkingData getHeightPixels]];
    [dataDic setObject:pixel forKey:@"pixel"];
    [dataDic setObject:[NSNumber numberWithInt:[TalkingData getBrightness]]forKey:@"brightness"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData getJailBroken]] forKey:@"jailBroken"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData isSupportNfcModule]] forKey:@"supportNfc"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData isSupportBluetoothModule]] forKey:@"supportBluetooth"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData isInsertEarphone]] forKey:@"insertEarphones"];
    [dataDic setValue:[NSNumber numberWithLong:[TalkingData getTotalDiskSpace]] forKey:@"totalDiskSpace"];
    [dataDic setValue:[NSNumber numberWithLong:[TalkingData getFreeDiskSpace]] forKey:@"freeDiskSpace"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData isWiFiDataConnected]] forKey:@"wifiNetworksConnected"];
    [dataDic setValue:[NSNumber numberWithBool:[TalkingData isMobileDataConnected]] forKey:@"mobileNetworksConnected"];
    [dataDic setObject:[TalkingData getCurrentNetworkType] forKey:@"networkType"];
    [dataDic setObject:[TalkingData getCurrentNetworkIP] forKey:@"wifiIP"];
    [dataDic setObject:[NSNumber numberWithInt:[TalkingData getBatteryLevel]] forKey:@"batteryLevel"];
    [dataDic setObject:[NSNumber numberWithInt:[TalkingData getBatteryState]] forKey:@"batteryState"];
    [dataDic setObject:[TalkingData getSystemLocale] forKey:@"locale"];
    [dataDic setObject:[TalkingData getSystemLanguage] forKey:@"language"];
    [dataDic setValue:[NSString stringWithFormat:@"%f",[TalkingData getSystemTimezoneV]]forKey:@"timezoneV"];
    [dataDic setValue:[NSNumber numberWithDouble:[self getGpsLocationsLat]]forKey:@"gpsLocationsLat"];
    [dataDic setValue:[NSNumber numberWithDouble:[self getGpsLocationsLng]]forKey:@"gpsLocationsLng"];
    [dataDic setObject:[self getRunningAppList] forKey:@"runningApps"];
    [dataDic setObject:[TalkingData getActivityRecognition] forKey:@"activityRecognition"];
    return  dataDic;
    
}



+ (NSDictionary *)systemProcesses {
    NSMutableDictionary *systemProcesses = [NSMutableDictionary dictionary];
    [systemProcesses setObject:@"1" forKey:@"timed"];
    [systemProcesses setObject:@"1" forKey:@"iaptransportd"];
    [systemProcesses setObject:@"1" forKey:@"ptpd"];
    [systemProcesses setObject:@"1" forKey:@"backboardd"];
    [systemProcesses setObject:@"1" forKey:@"mediaserverd"];
    [systemProcesses setObject:@"1" forKey:@"fairplayd.N90"];
    [systemProcesses setObject:@"1" forKey:@"imagent"];
    [systemProcesses setObject:@"1" forKey:@"kbd"];
    [systemProcesses setObject:@"1" forKey:@"BTServer"];
    [systemProcesses setObject:@"1" forKey:@"installd"];
    [systemProcesses setObject:@"1" forKey:@"deleted"];
    [systemProcesses setObject:@"1" forKey:@"SpringBoard"];
    [systemProcesses setObject:@"1" forKey:@"aggregated"];
    [systemProcesses setObject:@"1" forKey:@"apsd"];
    [systemProcesses setObject:@"1" forKey:@"itunesstored"];
    [systemProcesses setObject:@"1" forKey:@"lsd"];
    [systemProcesses setObject:@"1" forKey:@"xpcd"];
    [systemProcesses setObject:@"1" forKey:@"accountsd"];
    [systemProcesses setObject:@"1" forKey:@"tccd"];
    [systemProcesses setObject:@"1" forKey:@"softwareupdatese"];
    [systemProcesses setObject:@"1" forKey:@"MobileMail"];
    [systemProcesses setObject:@"1" forKey:@"BlueTool"];
    [systemProcesses setObject:@"1" forKey:@"assetsd"];
    [systemProcesses setObject:@"1" forKey:@"afcd"];
    [systemProcesses setObject:@"1" forKey:@"mobile_assertion"];
    [systemProcesses setObject:@"1" forKey:@"notification_pro"];
    [systemProcesses setObject:@"1" forKey:@"afcd"];
    [systemProcesses setObject:@"1" forKey:@"syslog_relay"];
    [systemProcesses setObject:@"1" forKey:@"MobilePhone"];
    [systemProcesses setObject:@"1" forKey:@"profiled"];
    [systemProcesses setObject:@"1" forKey:@"syncdefaultsd"];
    [systemProcesses setObject:@"1" forKey:@"mobile_installat"];
    [systemProcesses setObject:@"1" forKey:@"voiced"];
    [systemProcesses setObject:@"1" forKey:@"springboardservi"];
    [systemProcesses setObject:@"1" forKey:@"debugserver"];
    [systemProcesses setObject:@"1" forKey:@"MobileSMS"];
    [systemProcesses setObject:@"1" forKey:@"gamed"];
    [systemProcesses setObject:@"1" forKey:@"GameCenterUIServ"];
    [systemProcesses setObject:@"1" forKey:@"atc"];
    [systemProcesses setObject:@"1" forKey:@"librariand"];
    [systemProcesses setObject:@"1" forKey:@"ubd"];
    [systemProcesses setObject:@"1" forKey:@"pasteboardd"];
    [systemProcesses setObject:@"1" forKey:@"fairplayd.N94"];
    [systemProcesses setObject:@"1" forKey:@"dataaccessd"];
    [systemProcesses setObject:@"1" forKey:@"aosnotifyd"];
    [systemProcesses setObject:@"1" forKey:@"assistivetouchd"];
    [systemProcesses setObject:@"1" forKey:@"mediaremoted"];
    [systemProcesses setObject:@"1" forKey:@"assistantd"];
    [systemProcesses setObject:@"1" forKey:@"assistant_servic"];
    [systemProcesses setObject:@"1" forKey:@"geod"];
    
    return systemProcesses;
}



@end
