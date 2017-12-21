//
//  ViewController.m
//  GetAllDeviceData
//
//  Created by Caroline on 2017/10/17.
//  Copyright © 2017年 Caroline. All rights reserved.
//

#import "ViewController.h"
#import <AdSupport/AdSupport.h>
#import <CoreLocation/CoreLocation.h>
#import <sys/sysctl.h>
#import <MapKit/MapKit.h>
#import "TCFintech.h"

@interface ViewController ()<CLLocationManagerDelegate>

@property (nonatomic,strong) NSDictionary *dict;
@property (nonatomic,strong) CLLocationManager *locationmanager;
@property (nonatomic,assign) double locationsLat;
@property (nonatomic,assign) double locationsLng;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self startLocation];

   
}
- (IBAction)btnClickGetData:(id)sender {
    [self getDeviceData];
    NSLog(@"Device---%@",[self getDeviceData]);
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

- (NSString *)getDeviceData {
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

- (NSDictionary *)getDictionary {
    NSMutableDictionary *dataDic = [[NSMutableDictionary alloc]init];
    
    [dataDic setObject:[TCAntiFraud getDeviceID] forKey:@"tdid"];
    [dataDic setObject:[self getIDFA] forKey:@"adId"];
    [dataDic setObject:[NSNumber numberWithLong:[TCAntiFraud getBootTime]] forKey:@"bootTime"];
    [dataDic setObject:[TCAntiFraud getBrand] forKey:@"brand"];
    [dataDic setObject:[TCAntiFraud getModel] forKey:@"model"];
    [dataDic setObject:[TCAntiFraud getOsName] forKey:@"osName"];
    [dataDic setObject:[TCAntiFraud getOsVersionName] forKey:@"osVersionName"];
    NSString *pixel = [NSString stringWithFormat:@"%d*%d", [TCAntiFraud getWidthPixels], [TCAntiFraud getHeightPixels]];
    [dataDic setObject:pixel forKey:@"pixel"];
    [dataDic setObject:[NSNumber numberWithInt:[TCAntiFraud getBrightness]]forKey:@"brightness"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud getJailBroken]] forKey:@"jailBroken"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud isSupportNfcModule]] forKey:@"supportNfc"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud isSupportBluetoothModule]] forKey:@"supportBluetooth"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud isInsertEarphone]] forKey:@"insertEarphones"];
    [dataDic setValue:[NSNumber numberWithLong:[TCAntiFraud getTotalDiskSpace]] forKey:@"totalDiskSpace"];
    [dataDic setValue:[NSNumber numberWithLong:[TCAntiFraud getFreeDiskSpace]] forKey:@"freeDiskSpace"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud isWiFiDataConnected]] forKey:@"wifiNetworksConnected"];
    [dataDic setValue:[NSNumber numberWithBool:[TCAntiFraud isMobileDataConnected]] forKey:@"mobileNetworksConnected"];
    [dataDic setObject:[TCAntiFraud getCurrentNetworkType] forKey:@"networkType"];
    [dataDic setObject:[TCAntiFraud getCurrentNetworkIP] forKey:@"wifiIP"];
    [dataDic setObject:[NSNumber numberWithInt:[TCAntiFraud getBatteryLevel]] forKey:@"batteryLevel"];
    [dataDic setObject:[NSNumber numberWithInt:[TCAntiFraud getBatteryState]] forKey:@"batteryState"];
    [dataDic setObject:[TCAntiFraud getSystemLocale] forKey:@"locale"];
    [dataDic setObject:[TCAntiFraud getSystemLanguage] forKey:@"language"];
    [dataDic setValue:[NSString stringWithFormat:@"%f",[TCAntiFraud getSystemTimezoneV]]forKey:@"timezoneV"];
    [dataDic setValue:[NSNumber numberWithDouble:[self getGpsLocationsLat]]forKey:@"gpsLocationsLat"];
    [dataDic setValue:[NSNumber numberWithDouble:[self getGpsLocationsLng]]forKey:@"gpsLocationsLng"];
    [dataDic setObject:[self getRunningAppList] forKey:@"runningApps"];
    if ([TCAntiFraud getActivityRecognition]!= nil) {
        [dataDic setObject:[TCAntiFraud getActivityRecognition] forKey:@"activityRecognition"];
    }
    
    return  dataDic;
}

- (NSString *)getIDFA {
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



-(double)getGpsLocationsLat {
   
    return self.locationsLat;
}

- (double)getGpsLocationsLng {
    return self.locationsLng;
}

- (NSString *)getRunningAppList {
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0f) {
        return @"";
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

- (NSDictionary *)systemProcesses {
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
