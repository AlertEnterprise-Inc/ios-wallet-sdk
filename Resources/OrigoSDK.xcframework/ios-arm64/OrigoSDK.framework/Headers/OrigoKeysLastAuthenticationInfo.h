// OrigoKeysLastAuthenticationInfo.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>

@class OrigoKeysKey;

/**
 * Object representing the last authenticated key in the Seos Secure Storage
 */
@interface OrigoKeysLastAuthenticationInfo : NSObject

/**
 * @return Returns the `OrigoKeysKey` that was authenticated
 * @see OrigoKeysKey class
 */
@property(nonatomic, strong) OrigoKeysKey *lastAuthenticatedOrigoKey;

/**
 * @return a counter representing how many times the key has authenticated with a reader
 */
@property(nonatomic) NSUInteger authenticationCounter;

/**
 * @return whether or not the reader has written anything to the key
 */
@property(nonatomic) BOOL isModified;

@end
