//
//  TCAntiFraudAgent.h
//  TCAntiFraudAgent
//
//  Created by Robin on 25/12/2017.
//  Copyright © 2017 TendCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 API请求类型
 
 - APITypeRiskScore: 获取风险评估分
 - APITypeRiskDetail: 获取风险详细信息
 */
typedef NS_ENUM(NSUInteger, TCAPIType) {
    APITypeRiskScore = 0,
    APITypeRiskDetail
};


/**
 事件类型
 */
typedef NS_ENUM(NSUInteger, TCEventType) {
    EventTypeApply = 1, //申请
    EventTypeActive = 2, //激活
    EventTypeLogin = 3, //登录
    EventTypePayment = 4, //支付
    EventTypeRegister = 5 //注册
};

@interface TCFintechParams: NSObject

@property (nonatomic, strong) NSString *idfa; //Required with idfa, 待侦测设备的idfa
@property (nonatomic, strong) NSString *ip; //设备当前的IP地址
@property (nonatomic, strong) NSString *mac; //设备的mac地址
@property (nonatomic, strong) NSString *wifiMac; //设备的wifi mac地址
@property (nonatomic, strong) NSString *imsi; //设备的imsi地址(mcc+mnc)
@property (nonatomic, assign) TCEventType eventType;
@property (nonatomic, assign) int64_t eventTime;

// User Info
@property (nonatomic, strong) NSString *idCard; //用户的身份证号
@property (nonatomic, strong) NSString *name; //用户的姓名
@property (nonatomic, strong) NSString *phone; //手机号
@property (nonatomic, strong) NSString *bankCard; //银行卡号
@property (nonatomic, strong) NSString *email; //邮箱地址
@property (nonatomic, strong) NSString *address; //地址

@property (nonatomic, strong) NSArray *installApplist;
@property (nonatomic, strong) NSArray *runningAppList;

@end

#if TARGET_OS_IOS
typedef NS_ENUM(NSUInteger, TCAccountType) {
    TCAccountTypeAnonymous      = 0,    // 匿名账户
    TCAccountTypeRegistered     = 1,    // 显性注册账户
    TCAccountTypeSinaWeibo      = 2,    // 新浪微博
    TCAccountTypeQQ             = 3,    // QQ账户
    TCAccountTypeTencentWeibo   = 4,    // 腾讯微博
    TCAccountTypeND91           = 5,    // 91账户
    TCAccountTypeWeiXin         = 6,    // 微信
    TCAccountTypeType1          = 11,   // 自定义类型1
    TCAccountTypeType2          = 12,   // 自定义类型2
    TCAccountTypeType3          = 13,   // 自定义类型3
    TCAccountTypeType4          = 14,   // 自定义类型4
    TCAccountTypeType5          = 15,   // 自定义类型5
    TCAccountTypeType6          = 16,   // 自定义类型6
    TCAccountTypeType7          = 17,   // 自定义类型7
    TCAccountTypeType8          = 18,   // 自定义类型8
    TCAccountTypeType9          = 19,   // 自定义类型9
    TCAccountTypeType10         = 20    // 自定义类型10
};
#endif

@interface TCAntiFraudAgent : NSObject
/**
 *  @method getDeviceID
 *  获取SDK所使用的DeviceID
 *  @return DeviceID
 */
+ (NSString *)getDeviceID;

/**
 *  @method setLogEnabled
 *  统计日志开关（可选）
 *  @param  enable      默认是开启状态
 */
+ (void)setLogEnabled:(BOOL)enable;

#if TARGET_OS_IOS
/**
 *  @method    startAgent:channelId:
 *  初始化统计实例，请在application:didFinishLaunchingWithOptions:方法里调用
 *  @param  appId      应用的唯一标识，风控后台注册得到
 *  @param  channelId   渠道名，如“app store”（可选）
 */
+ (void)startAgent:(NSString *)appId channelId:(NSString *)channelId;
#endif


#if TARGET_OS_IOS
/**
 *    @method    setAntiCheatingEnabled
 *  是否开启反作弊功能
 *    @param     enabled     默认是开启状态
 */
+ (void)setAntiCheatingEnabled:(BOOL)enabled;
#endif


#if TARGET_OS_IOS
/**
 *  @method onRegister  注册
 *  @param  accountId   账户ID
 *  @param  type        账户类型
 *  @param  name        账户昵称
 */
+ (void)onRegister:(NSString *)accountId type:(TCAccountType)type name:(NSString *)name;

/**
 *  @method onLogin     登录
 *  @param  accountId   账户ID
 *  @param  type        账户类型
 *  @param  name        账户昵称
 */
+ (void)onLogin:(NSString *)accountId type:(TCAccountType)type name:(NSString *)name;

/**
 *  @method onLogin
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onLogin:(NSString *)accountId type:(TCAccountType)type;

/**
 *  @method onApply
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onApply:(NSString *)accountId type:(TCAccountType)type;

/**
 *  @method onActivate
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onActivate:(NSString *)accountId type:(TCAccountType)type;

#endif

/**
 *  @method onPay           支付
 *  @param  accountId       账户ID          类型:NSString
 */
+ (void)onPay:(NSString *)accountId;

/**
 风险侦测接口
 
 @param businessSceneId Required; 业务场景id，需要找客户经理配置
 @param apiKey DMK apiKey
 @param apiToken DMK apiToken
 @param apiType 接口请求类型，详见 ‘APIType’
 @param riskServiceVersion TalkingData风险侦测服务的版本
 @param fintechParams 附加参数
 @param success 请求成功回调
 @param failure 请求失败回调
 */
+ (void)riskDetection:(NSString *)businessSceneId
               apiKey:(NSString *)apiKey
             apiToken:(NSString *)apiToken
              apiType:(TCAPIType)apiType
       serviceVersion:(NSString *)riskServiceVersion
               params:(TCFintechParams *)fintechParams
    completionSuccess:(void (^)(id jsonObject, NSHTTPURLResponse *response))success
              failure:(void (^)(NSError *error))failure;

#if TARGET_OS_IOS
/**
 * 获取开机时间
 */
+ (long)getBootTime;

/**
 * 获取设备品牌
 */
+ (NSString *)getBrand;

/**
 * 获取设备型号
 */
+ (NSString *)getModel;

/**
 * 获取系统名称
 */
+ (NSString *)getOsName;

/**
 * 获取系统版本
 */
+ (NSString *)getOsVersionName;

/**
 * 获取屏幕宽度
 */
+ (int)getWidthPixels;

/**
 * 获取屏幕高度
 */
+ (int)getHeightPixels;

/**
 * 获取屏幕亮度
 */
+ (int)getBrightness;

/**
 * 是否越狱
 */
+ (BOOL)getJailBroken;

/**
 * 是否支持NFC
 */
+ (BOOL)isSupportNfcModule;

/**
 * 是否支持蓝牙
 */
+ (BOOL)isSupportBluetoothModule;

/**
 * 是否插入耳机
 */
+ (BOOL)isInsertEarphone;

/**
 * 获取磁盘总量
 */
+ (long)getTotalDiskSpace;

/**
 * 获取磁盘剩余量
 */
+ (long)getFreeDiskSpace;

/**
 * 是否连接WiFi
 */
+ (BOOL)isWiFiDataConnected;

/**
 * 是否连接蜂窝移动网络
 */
+ (BOOL)isMobileDataConnected;

/**
 * 获取当前网络类型
 */
+ (NSString *)getCurrentNetworkType;

/**
 * 获取内网IP
 */
+ (NSString *)getCurrentNetworkIP;

/**
 * 获取电池电量百分比
 */
+ (int)getBatteryLevel;

/**
 * 是否在充电，是否充满电
 */
+ (int)getBatteryState;

/**
 * 获取所在国家信息
 */
+ (NSString *)getSystemLocale;

/**
 * 获取语言信息
 */
+ (NSString *)getSystemLanguage;

/**
 * 获取时区信息
 */
+ (float)getSystemTimezoneV;

/**
 * 获取行为识别信息。若此时无行为识别结果，则返回nil！
 */
+ (NSDictionary *)getActivityRecognition;
#endif

@end


