// OrigoKeysManagerExtendedDelegate.h
// Copyright (c) 2021 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "OrigoKeysManagerDelegate.h"

/**
 * Extension delegate of `OrigoKeysManagerDelegate`
 * @warning this delegate extension is only for advanced use cases. Please consider this before using this delegate.
 * For instance, the tap use case is already supported by the SDK by simply passing `OrigoKeysOpeningTypeProximity` to
 * `-[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]`.
 */
@protocol OrigoKeysManagerExtendedDelegate <OrigoKeysManagerDelegate>

/**
 * IMPORTANT: Only implement this callback method if you absolutely need scan results for all Readers.
 * If this method is NOT implemented, the SDK assumes that it returns YES. See below.
 * This is a callback method  for each advertisement the SDK receives from all seen readers in the vicinity.
 * If this callback is implemented, the SDK will call this function for each and every RSSI value measurement,
 * which could impact battery consumption of your application.
 *
 * When this method in implemented and returns NO, the SDK will not run its internal Opening Triggers for this particular
 * OrigoKeysReader RSSI measurement. In practice, this means that the Reader will be ignored.
 * If this method is implemented and returns YES, the SDK will process the RSSI values.
 * If this method is NOT IMPLEMENTED, the SDK will assume that the response was YES.
 *
 * Possible use cases for this method includes but is not limited to:
 *  - Custom opening triggers (e.g. custom RSSI value analysis etc)
 *  - Disabling SDK built-in unlock mechanisms temporarily, while at the same time the SDK keeps scanning.
 *
 *
 * @return NO id the OrigoKeysReader should be ignored, otherwise YES
 * @warning This is a low-level method that should only be implemented for custom opening behaviors,
 * i.e. not one of the types in `OrigoKeysOpeningType`.
 * @param origoKeysReader - The reader that sent the advertisement
 * @note since version 5.1
 */
@optional
- (BOOL)origoKeysShouldInteractWithScannedReader:(OrigoKeysReader *)origoKeysReader;

/**
 * Callback for when the user did an unlock gesture. If this method is implemented, the SDK will enable it’s own built-in
 * - motion detection, even if the MobileKeysOpeningType “Motion” is not specified eh nscanning
 *
 *  @note since version 5.1
 *  @note This is an optional method
 */
@optional
- (void)origoKeysUserDidUnlockGesture;


/**
 * Implement this method to observe, when the user enters the Readers's region.
 * @param beaconUUID - Readers Beacon UUID
 */
-(void)origoKeysUserDidEnterReaderRegion:(nullable NSString *)beaconUUID;


/**
 * Implement this method to observe, when the user exits the Readers's region.
 * @param beaconUUID - Readers Beacon UUID
 */

-(void)origoKeysUserDidExitReaderRegion:(nullable NSString *)beaconUUID;


@end
