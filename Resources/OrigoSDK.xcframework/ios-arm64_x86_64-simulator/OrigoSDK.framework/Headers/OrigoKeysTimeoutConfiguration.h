// OrigoKeysTimeoutConfiguration.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Bluetooth reader timeout parameters.
 * Configuration for the BLE reader communication for overriding default values regarding Reader communication.
 *
 */
@interface OrigoKeysTimeoutConfiguration : NSObject

/**
 * Default APDU fragment timeout
 */
#define DEFAULT_MAX_TIME_BETWEEN_FRAGMENTS 0.2

/**
 * Default APDU timeout
 */
#define DEFAULT_MAX_TIME_BETWEEN_APDUS 1.0

/**
 * Default connection timeout
 */
#define DEFAULT_MAX_TIME_CONNECTION 3.0

/**
 * Set APDU fragment timeout between queued APDU fragments.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxTimeBetweenFragments;
/**
 * Set timeout between APDU's.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxTimeBetweenApdus;

/**
 * Set the timeout before aborting the connection during connection establishment.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxConnectionTime;

@end
