//
//  ViewController.m
//  GetAllDeviceData
//
//  Created by Caroline on 2017/10/17.
//  Copyright © 2017年 caroline. All rights reserved.
//

#import "ViewController.h"
#import <AdSupport/AdSupport.h>
#import <CoreLocation/CoreLocation.h>
#import <sys/sysctl.h>
//#import "TalkingData.h"
#import <MapKit/MapKit.h>
#import "DeviceData.h"

@interface ViewController ()<CLLocationManagerDelegate>

@property (nonatomic,strong) NSDictionary *dict;
@property (nonatomic,strong) CLLocationManager *locationmanager;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self startLocation];
}

- (IBAction)btnClickGetData:(id)sender {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc]initWithDictionary:[DeviceData getDictionary]];
    
    [dic setObject:[NSNumber numberWithDouble:self.locationsLat] forKey:@"gpsLocationsLat"];
    [dic setObject:[NSNumber numberWithDouble:self.locationsLng] forKey:@"gpsLocationsLng"];
    if (dic == nil || ![dic isKindOfClass:[NSDictionary class]]) {
        return ;
    }
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic options:NSJSONWritingPrettyPrinted error:nil];
    NSString *jsonStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    
    NSLog(@"getDeviceData--%@",jsonStr);

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
- (void)returnText:(locationBlock)block {
     __weak typeof (self) weakself = self;  
    weakself.locationBlock = block;
}
- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    
    
    CLLocation *newLocation = locations[0];
    CLLocationCoordinate2D oldCoordinate = newLocation.coordinate;
    self.locationsLat = oldCoordinate.latitude;
    self.locationsLng = oldCoordinate.longitude;
    if (self.locationBlock != nil) {
        self.locationBlock(oldCoordinate.latitude,oldCoordinate.longitude);
    }
    NSLog(@"旧的经度：%f,旧的纬度：%f",oldCoordinate.longitude,oldCoordinate.latitude);
    
    [manager stopUpdatingLocation];
    
    
}


@end
