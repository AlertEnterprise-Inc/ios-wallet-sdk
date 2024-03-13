//
//  OrigoLocationHandlerDelegate.h
//  OrigoSDK
//
//  Copyright © 2021 HID Global. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "OrigoLocationErrorCode.h"

/**
 * OrigoLocationHandlerDelegate has set of callback methods for various event of HID Identity Positioning location services.
 */
@protocol OrigoLocationHandlerDelegate <NSObject>

/**
  
 Notifies errors that occurs during the location service with error code. Refer 'Error Codes ->Origo Location Error Code' section in the documentation for more details about "OrigoLocationErrorCode".
 
  @param errorCode  Error code
 */
- (void)origoLocationHandlerDidReceiveError:(OrigoLocationErrorCode)errorCode;

/**
 * Notifies when HID Identity Positioning Credential is revoked and no longer location service enabled in the device.
 * All running IP services will be stopped and IP services related data will be cleared from the Origo Secured Storage, before this callback.
 */
- (void)origoLocationHandlerDidRevokeIPCredential;

@optional
/**
 * Notifies when ever a patch of location details are synced with Origo Cloud.
 */
- (void)origoLocationHandlerDidFinishLocationSync;

@optional
/**
 * Notifies when the "-[OrigoNAOLocationHandler syncSiteInfo]" method completes the site information synchronization successfully.
 */
- (void)origoLocationHandlerDidFinishSiteInfoSync;

@end
