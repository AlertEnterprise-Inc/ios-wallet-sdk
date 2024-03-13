// OrigoDelegateProxy.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import "OrigoKeysManager.h"

#import <Foundation/Foundation.h>
#import "OrigoKeysManagerDelegate.h"
#import "OrigoEventManager.h"
#import "OrigoKeysManagerWalletDelegate.h"
#import "OrigoReaderLocationHandler.h"
#import "OrigoIPReaderPresenceDelegate.h"

#if __has_include(<SeosMobileKeysSDK/SeosMobileKeysSDK.h>)
#import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
#define HAS_SEOS_MODULE_FRAMEWORK
#endif

#ifdef HAS_SEOS_MODULE_FRAMEWORK
@interface OrigoDelegateProxy : NSObject <MobileKeysManagerExtendedDelegate>
#else
@interface OrigoDelegateProxy : NSObject <OrigoKeysManagerWalletDelegate>
#endif

@property(nonatomic, strong) OrigoEventManager *eventManager;
@property(nonatomic, strong) OrigoKeysManager *origoKeysManager;
@property(nonatomic, strong) NSString *code;

- (instancetype)initWithDelegate:(id)delegate;
- (void)updateOIPDelegateForReaders:(id<OrigoIPReaderPresenceDelegate>)delegate;
- (BOOL)respondsToUserDidUnlockGesture;
- (void)origoKeysDidSetupSecureElementPasses;
- (void)origoKeysWalletAddingSecureElementPasses:(NSArray *)secureElementPasses withError:(NSError *)error;
- (void)origoKeysSetupRedemption:(OrigoProvisioningData *)provisioningData withError:(NSError *)error;
- (void)origoKeysDidFailToSetupWallet:(NSError*)error;

- (void)origodidSetUpforOIP;
- (void)mobileKeysDidFailToSetupEndpoint:(NSError *)error;

- (void)regionMonitoringEvent :(BOOL)isEntered :(NSString*)beaconID;

@end
