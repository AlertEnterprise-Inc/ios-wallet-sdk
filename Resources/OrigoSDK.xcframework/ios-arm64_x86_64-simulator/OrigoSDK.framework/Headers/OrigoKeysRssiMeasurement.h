// OrigoKeysRssiMeasurement.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>

@class OrigoClock;

/*
 * Represents One RSSI Value Sample
 */
@interface OrigoKeysRssiMeasurement : NSObject

@property(nonatomic, assign, readonly) NSInteger rssiValue;

@property(nonatomic, assign, readonly) NSTimeInterval measuredAtIntervalSince1970;

/**
 * Will construct a new measurement, setting the measuredAtIntervalSince1970 to current time
 */
+ (OrigoKeysRssiMeasurement *)fromRssiValue:(NSInteger)rssiValue withClock:(OrigoClock*)clock;

@end
