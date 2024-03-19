//
//  OrigoLocationErrorCode.h
//  OrigoSDK
//
//  Copyright © 2021 HID Global. All rights reserved.
//

///
typedef NS_ENUM(NSInteger, OrigoLocationErrorCode)
{
    /** Invalid API key : inconsistent key accross services or key does not match PDB: check for typo in your key, check your site details*/
    OrigoLocationInvalidAPIKey,
    /** Problem occured during a service instantiation / termination */
    OrigoLocationServiceLifeCycle,
    /** Unable to synchronize data for your site: problem with the connection or missing inputs */
    OrigoLocationPositioningDataSyncFailed,
    /** Unsupported OS */
    OrigoLocationUnsupportedOS,
    /** for HID Identity Positioning use, you should not see those. */
    OrigoLocationInternalError,
    /** generic error code */
    OrigoLocationGenericError,
    /** Indicates that the compass need to be calibrated. */
    OrigoLocationCompassCalibrationRequired,
    /** Indicates that the Wifi is off and required by the service */
    OrigoLocationWIFIOnReqiured,
    /** Indicates that the BLE (Bluetooth 4.0) is off and required by the service */
    OrigoLocationBLEOnReqiured,
    /** Indicates that the Location services are off and required by the service. */
    OrigoLocationGPSOnRequired,
    /** Unable to synchronize location data to Origo Cloud*/
    OrigoLocationDataSynchroFailed,
    /**Origo location data retention period expired, please connect the device to the internet*/
    OrigoLocationRetentionPeriodExpired,
    /**Reached maximum storage size for Location Data, please connect the device to the internet.*/
    OrigoLocationMaxStorageReached,
    /** Track option on beacon approach not supported*/
    OrigoLocationTrackOptionNotSupported,
    /** Unknown Error*/
    OrigoLocationUnknownError,
};
