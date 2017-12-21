//
//  TCFintech.h
//  __MyProjectName__
//
//  Created by Biao Hou on 11-11-14.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IOS
typedef NS_ENUM(NSUInteger, TCAntiFraudAccountType) {
    TCAntiFraudAccountTypeAnonymous      = 0,    // 匿名账户
    TCAntiFraudAccountTypeRegistered     = 1,    // 显性注册账户
    TCAntiFraudAccountTypeSinaWeibo      = 2,    // 新浪微博
    TCAntiFraudAccountTypeQQ             = 3,    // QQ账户
    TCAntiFraudAccountTypeTencentWeibo   = 4,    // 腾讯微博
    TCAntiFraudAccountTypeND91           = 5,    // 91账户
    TCAntiFraudAccountTypeWeiXin         = 6,    // 微信
    TCAntiFraudAccountTypeType1          = 11,   // 自定义类型1
    TCAntiFraudAccountTypeType2          = 12,   // 自定义类型2
    TCAntiFraudAccountTypeType3          = 13,   // 自定义类型3
    TCAntiFraudAccountTypeType4          = 14,   // 自定义类型4
    TCAntiFraudAccountTypeType5          = 15,   // 自定义类型5
    TCAntiFraudAccountTypeType6          = 16,   // 自定义类型6
    TCAntiFraudAccountTypeType7          = 17,   // 自定义类型7
    TCAntiFraudAccountTypeType8          = 18,   // 自定义类型8
    TCAntiFraudAccountTypeType9          = 19,   // 自定义类型9
    TCAntiFraudAccountTypeType10         = 20    // 自定义类型10
};
#endif


#if TARGET_OS_IOS
@interface TCAntiFraudOrder : NSObject

/**
 *  @method createOrder
 *  @param  orderId          订单id         类型:NSString
 *  @param  total            订单总价        类型:int
 *  @param  currencyType     币种           类型:NSString
 */
+ (TCAntiFraudOrder *)createOrder:(NSString *)orderId total:(int)total currencyType:(NSString *)currencyType;

/**
 *  @method addItemWithCategory
 *  @param  itemId           商品Id         类型:NSString
 *  @param  category         商品类别        类型:NSString
 *  @param  name             商品名称        类型:NSString
 *  @param  unitPrice        商品单价        类型:int
 *  @param  amount           商品数量        类型:int
 */
- (TCAntiFraudOrder *)addItem:(NSString *)itemId category:(NSString *)category name:(NSString *)name unitPrice:(int)unitPrice amount:(int)amount;

@end


@interface TCAntiFraudShoppingCart : NSObject

/**
 *  @method createShoppingCart
 */
+ (TCAntiFraudShoppingCart *)createShoppingCart;

/**
 *  @method addItem
 *  @param  itemId           商品Id         类型:NSString
 *  @param  category         商品类别        类型:NSString
 *  @param  name             商品名称        类型:NSString
 *  @param  unitPrice        商品单价        类型:int
 *  @param  amount           商品数量        类型:int
 */
- (TCAntiFraudShoppingCart *)addItem:(NSString *)itemId category:(NSString *)category name:(NSString *)name unitPrice:(int)unitPrice amount:(int)amount;

@end
#endif

// 以下枚举用于WatchApp页面追踪
typedef enum {
    TCAntiFraudPageTypeGlance = 1,
    TCAntiFraudPageTypeNotification = 2,
    TCAntiFraudPageTypeWatchApp = 3
} TCAntiFraudPageType;

@interface TCAntiFraud: NSObject

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
 *  @method setExceptionReportEnabled
 *  是否捕捉程序崩溃记录（可选）
    如果需要记录程序崩溃日志，请将值设成YES，并且在初始化后尽早调用
 *  @param  enable      默认是 NO
 */
+ (void)setExceptionReportEnabled:(BOOL)enable;

/**
 *  @method setSignalReportEnabled
 *  是否捕捉异常信号（可选）
    如果需要开启异常信号捕捉功能，请将值设成YES，并且在初始化后尽早调用
 *  @param  enable      默认是NO
 */
+ (void)setSignalReportEnabled:(BOOL)enable;
#endif



#if TARGET_OS_IOS
/**
 *  @method	sessionStarted:withChannelId:
 *  初始化统计实例，请在application:didFinishLaunchingWithOptions:方法里调用
 *  @param  appKey      应用的唯一标识，统计后台注册得到
 *  @param  channelId   渠道名，如“app store”（可选）
 */
+ (void)sessionStarted:(NSString *)appKey withChannelId:(NSString *)channelId;
#endif


#if TARGET_OS_IOS
/**
 *	@method	setAntiCheatingEnabled
 *  是否开启反作弊功能
 *	@param 	enabled 	默认是开启状态
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
+ (void)onRegister:(NSString *)accountId type:(TCAntiFraudAccountType)type name:(NSString *)name;

/**
 *  @method onLogin     登录
 *  @param  accountId   账户ID
 *  @param  type        账户类型
 *  @param  name        账户昵称
 */
+ (void)onLogin:(NSString *)accountId type:(TCAntiFraudAccountType)type name:(NSString *)name;

/**
 *  @method onLogin
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onLogin:(NSString *)accountId type:(TCAntiFraudAccountType)type;

/**
 *  @method onApply
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onApply:(NSString *)accountId type:(TCAntiFraudAccountType)type;

/**
 *  @method onActivate
 *  @param  accountId       账户ID
 *  @param  type            账户类型
 */
+ (void)onActivate:(NSString *)accountId type:(TCAntiFraudAccountType)type;
#endif


/**
 *  @method	trackPageBegin
 *  开始跟踪某一页面（可选），记录页面打开时间
    建议在viewWillAppear或者viewDidAppear方法里调用
 *  @param  pageName    页面名称（自定义）
 */
+ (void)trackPageBegin:(NSString *)pageName;

/**
 *  @method trackPageBegin:withPageType:
 *  开始跟踪WatchApp某一页面（可选），记录页面打开时间
    建议在willActivate方法里调用
 *  @param  pageName    页面名称（自定义）
 *  @param  pageType    页面类型（TCAntiFraudPageType枚举类型）
 */
+ (void)trackPageBegin:(NSString *)pageName withPageType:(TCAntiFraudPageType)pageType;

/**
 *  @method trackPageEnd
 *  结束某一页面的跟踪（可选），记录页面的关闭时间
    此方法与trackPageBegin方法结对使用，
    在iOS应用中建议在viewWillDisappear或者viewDidDisappear方法里调用
    在Watch应用中建议在DidDeactivate方法里调用
 *  @param  pageName    页面名称，请跟trackPageBegin方法的页面名称保持一致
 */
+ (void)trackPageEnd:(NSString *)pageName;

#if TARGET_OS_IOS
/**
 *  @method onPlaceOrder    下单
 *  @param  accountId       账户ID          类型:NSString
 *  @param  order           订单            类型:TCAntiFraudOrder
 */
+ (void)onPlaceOrder:(NSString *)accountId order:(TCAntiFraudOrder *)order;

/**
 *  @method onPay           支付
 *  @param  accountId       账户ID          类型:NSString
 */
+ (void)onPay:(NSString *)accountId;
/**
 *  @method onOrderPaySucc  支付
 *  @param  accountId       账户ID          类型:NSString
 *  @param  payType         支付类型         类型:NSString
 *  @param  order           订单详情         类型:TCAntiFraudOrder
 */
+ (void)onOrderPaySucc:(NSString *)accountId payType:(NSString *)payType order:(TCAntiFraudOrder *)order;

/**
 *  @method onViewItem
 *  @param  itemId           商品Id         类型:NSString
 *  @param  category         商品类别        类型:NSString
 *  @param  name             商品名称        类型:NSString
 *  @param  unitPrice        商品单价        类型:int
 */
+ (void)onViewItem:(NSString *)itemId category:(NSString *)category name:(NSString *)name unitPrice:(int)unitPrice;

/**
 *  @method onAddItemToShoppingCart
 *  @param  itemId           商品Id         类型:NSString
 *  @param  category         商品类别        类型:NSString
 *  @param  name             商品名称        类型:NSString
 *  @param  unitPrice        商品单价        类型:int
 *  @param  amount           商品数量        类型:int
 */
+ (void)onAddItemToShoppingCart:(NSString *)itemId category:(NSString *)category name:(NSString *)name unitPrice:(int)unitPrice amount:(int)amount;

/**
 *  @method onViewShoppingCart
 *  @param  shoppingCart    购物车信息       类型:TalkingDataShoppingCart
 */
+ (void)onViewShoppingCart:(TCAntiFraudShoppingCart *)shoppingCart;
#endif




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
 * 获取传感器信息
 */
+ (NSDictionary *)getActivityRecognition;


@end
