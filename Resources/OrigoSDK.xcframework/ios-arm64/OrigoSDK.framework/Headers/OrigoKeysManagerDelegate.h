// OrigoKeysManagerDelegate.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "OrigoKeysReader.h"
#import "OrigoProvisioningData.h"

NS_ASSUME_NONNULL_BEGIN
@class OrigoKeysReader;
@class OrigoKeysOpeningResult;
@class OrigoKeysEndpointUpdateSummary;

/**
 * Delegate protocol to implement for callbacks from the `OrigoKeysManager` class
 * @see `OrigoKeysManager`
 */
@protocol OrigoKeysManagerDelegate

/**
 * Callback for when `-[OrigoKeysManager startup]` was successfully completed.
 * @note since version 2.0
 */
- (void)origoKeysDidStartup;

/**
 * Callback for when `-[OrigoKeysManager startup]` failed.
 * @param error - The cause of the failure, code is one of `origoKeysErrorCode`.
 * @note since version 2.0
 */
- (void)origoKeysDidFailToStartup:(NSError *)error;

/**
 * Callback for when `-[OrigoKeysManager setupEndpoint]` was successfully completed. The endpoint is now setup.
 * @note since version 2.0
 */
- (void)origoKeysDidSetupEndpoint;

/**
 * Callback for when `-[OrigoKeysManager setupEndpoint]` failed. The endpoint hasn't been setup.
 * @param error - The cause of the failure, code is one of `OrigoKeysErrorCode`.
 * @note since version 2.0
 */
- (void)origoKeysDidFailToSetupEndpoint:(NSError *)error;


@optional
/**
 * Callback for when `-[OrigoKeysManager updateEndpoint]` was successfully completed and the endpoint has been updated.
 * @note since version 2.0. There are two versions of this callback, both have been marked @optional for technical reasons,
 * but at least one of them should be implemented
 * @see -[OrigoKeysManagerDelegate OrigoKeysDidUpdateEndpointWithSummary:]
 */
- (void)origoKeysDidUpdateEndpoint;


@optional
/**
 * Callback for when `-[OrigoKeysManager  setupEndpoint:target:]` was called when passing target name as "OrigoAppleWalletPreview"
 * @param provisioningData provides required data response to identify whether given invite code/issuance token is Seos/Non-Seos(Apple Wallet).
 * @param error - If there is no provisioning data , it returns the specific error .
 */
- (void)origoKeysDidFinishRedemption:(OrigoProvisioningData *)provisioningData withError:(nullable NSError *)error;



@optional
/**
 * Callback for when `-[OrigoKeysManager updateEndpoint]` was successfully completed and the endpoint has been updated.
 * @note since version 6.2. There are two versions of this callback, both have been marked @optional for technical reasons,
 * but at least one of them should be implemented
 * @param endpointUpdateSummary a summary of the update performed
 * @see -[OrigoKeysManagerDelegate OrigoKeysDidUpdateEndpoint]
 */
- (void)origoKeysDidUpdateEndpointWithSummary:(OrigoKeysEndpointUpdateSummary *) endpointUpdateSummary;
/**
 * Callback for when `-[OrigoKeysManager updateEndpoint]` failed. The endpoint wasn't updated.
 * @param error - The cause of the failure, code is one of `OrigoKeysErrorCode`.
 * @note since version 2.0
 */
- (void)origoKeysDidFailToUpdateEndpoint:(NSError *)error;

/**
 * Callback for when the endpoint has been terminated. This can happen even without calling `-[OrigoKeysManager updateEndpoint]`.
 From version 6.0.0 this will also be called if the SDK detects a fatal error with the local Seos Vault. The expected behaviour
 when this callback is made is to restart personalization.
 * @note since version 2.0
 */
- (void)origoKeysDidTerminateEndpoint;

/**
 * Callback for when the application has just connected to reader.
 * @param reader - The reader which the application has connected to.
 * @param type - The type of opening which connected the application with reader.
 * @note since version 4.0
 */
- (void)origoKeysDidConnectToReader:(OrigoKeysReader *)reader openingType:(OrigoKeysOpeningType)type;

/**
 * Callback for when a connection has failed.
 * @param reader - The reader which the application failed to connect to.
 * @param type - The type of opening which initiated the connection attempt.
 * @param status - Status of the failed connection
 * @note since version 2.0
 */
- (void)origoKeysDidFailToConnectToReader:(OrigoKeysReader *)reader openingType:(OrigoKeysOpeningType)type openingStatus:(OrigoKeysOpeningStatusType)status;

/**
 * Callback for when the application disconnected the reader.
 * @param reader - The reader which application has disconnected from.
 * @param type - The type of opening which initiated the connection attempt.
 * @param result - Status of the failed connection
 * @note since version 4.0
 */
- (void)origoKeysDidDisconnectFromReader:(OrigoKeysReader *)reader openingType:(OrigoKeysOpeningType)type openingResult:(OrigoKeysOpeningResult *)result;

/**
 * Decides if application should allow connection to reader. This will be called by the library
 * prior to attempting connect to reader.
 * @param reader - The reader which the application is considering connecting to.
 * @param type - The type of opening which initiated the connection attempt.
 * @note since version 2.0
 */
- (BOOL)origoKeysShouldAttemptToOpen:(OrigoKeysReader *  _Nullable)reader openingType:(OrigoKeysOpeningType)type;

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
 * @param OrigoKeysReader - The reader that sent the advertisement
 * @note since version 5.1
 * @deprecated this delegate callback will be moved to `OrigoKeysManagerExtendedDelegate`
 */
@optional
- (BOOL)origoKeysShouldInteractWithScannedReader:(OrigoKeysReader *)origoKeysReader DEPRECATED_MSG_ATTRIBUTE("This delegate callback will moved to OrigoKeysManagerExtendedDelegate");


/**
 * Callback for when the user did an unlock gesture. If this method is implemented, the SDK will enable it's own built-in
 * motion detection, even if the OrigoKeysOpeningType "Motion" is not specified eh nscanning
 *
 * @note since version 2.0
 * @deprecated this delegate callback will be moved to `OrigoKeysManagerExtendedDelegate`
 */
@optional
- (void)origoKeysUserDidUnlockGesture DEPRECATED_MSG_ATTRIBUTE("This delegate callback will moved to OrigoKeysManagerExtendedDelegate");


/**
 * An optional callback for when the reader gets inactive.
 * @param reader - The reader that stopped updating RSSI
 */
@optional
- (void)origoKeysReaderDisappeared:(OrigoKeysReader*) reader;


/**
 * An optional callback for when the reader appeared in vicinity.
 * @param reader - The reader that appeared in vicinity
 */
@optional
- (void)origoKeysReaderAppeared:(OrigoKeysReader*) reader;


/**
 * An optional callback for when the reader updated.
 * @param reader - The reader that just updated
 */
@optional
- (void)origoKeysReaderUpdated:(OrigoKeysReader*) reader;



@end
NS_ASSUME_NONNULL_END
