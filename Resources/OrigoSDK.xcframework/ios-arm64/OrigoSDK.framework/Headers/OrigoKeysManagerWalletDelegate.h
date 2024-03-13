// OrigoKeysManagerWalletDelegate.h
// Copyright (c) 2021 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "OrigoKeysManagerDelegate.h"
#import <PassKit/PassKit.h>

/**
 * Extension delegate of `OrigoKeysManagerDelegate`.
 * @warning This delegate extension is only for Apple Wallet use cases. 
 */
@protocol OrigoKeysManagerWalletDelegate <OrigoKeysManagerDelegate>

/**
 * Callback to provide an indication of Add to Apple Wallet button action
 * @note since HID Origo SDK version 1.8.1.
 */
@optional
- (void)origoKeysDidSetupSecureElementPasses;


@optional
- (void)origoKeysDidFailToSetupWallet:(NSError*)error;


/**
 * Callback to provide an indication of success or failure when adding a Pass to
 * Apple Wallet.
 * @param error - The cause of the failure, code is one of `OrigoKeysErrorCode`.
 * @note since HID Origo SDK version 1.8.0.
 */
@optional
- (void)origoKeysDidFinishAddingSecureElementPasses:(NSArray *)secureElementPasses withError:(NSError *)error;


@end
