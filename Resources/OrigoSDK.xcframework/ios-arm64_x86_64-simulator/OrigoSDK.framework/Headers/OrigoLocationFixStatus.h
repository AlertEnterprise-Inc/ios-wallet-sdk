//
//  OrigoLocationFixStatus.h
//  OrigoSDK
//
//  Copyright © 2021 HID Global. All rights reserved.
//

#import <Foundation/Foundation.h>

///OrigoLocationFixStatus
///
///An Enum that indicate various cases of location update errors.
typedef NS_ENUM(NSInteger, OrigoLocationFixStatus)
{
    /** A critical error has occurred: location is not available; details about the error are returned by onError callback. */
    OrigoLocationFixStatusOutOfService,
    /** Location is unavailable for lack of sensor input: sensors could have been turned off or device might be going off-site. */
    OrigoLocationFixStatusTemporaryUnavailable,
    /** Location fixes are being produced at a normal rate. */
    OrigoLocationFixStatusFixAvailable,
    /** Location is unavailable as device is off-site. */
    OrigoLocationFixStatusFixUnavailable,
    /** Location is available, but is not computed according to mobile site data (mobile site only) */
    OrigoLocationFixStatusCoarseLocation,
};
