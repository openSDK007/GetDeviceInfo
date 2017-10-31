//
//  AppDelegate.h
//  DevicePerfect
//
//  Created by 冯婷婷 on 2017/10/20.
//  Copyright © 2017年 冯婷婷. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

