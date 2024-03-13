// OrigoKeysReader.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.
#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
/**
 * The maximum age of an RSSI Value
 */
@class OrigoKeysRssiMeasurement;
#define MAX_RSSI_AGE 3.0

/**
 *
 * OrigoKeysOpeningStatus enum
 *
 */

typedef NS_ENUM(NSInteger, OrigoKeysOpeningStatusType) {
    /**
     * Reader communication was successful. Please note that the API cannot determine if access was granted,
     * only that the communication with the reader succeeded
     */
    OrigoKeysOpeningStatusTypeSuccess = 0,
    /**
     * Reader communication failed. This could happen if the detected BLE device was not really a Reader, or that it
     * failed to recognize the API Connection attempt
     */
    OrigoKeysOpeningStatusTypeBluetoothCommunicationFailed = 1,
    /**
     * One of the timeouts triggered (either in the reader or in the SDK)
     */
    OrigoKeysOpeningStatusTypeTimedOut = 2,
    /**
     * The reader that the SDK tried to connect to was not in range
     */
    OrigoKeysOpeningStatusTypeOutOfRange = 3,
    /**
     * The SDK could not connect to the reader since another session to Seos is currently open
     */
    OrigoKeysOpeningStatusTypeBusy = 4,
    /**
     * Opening type was motion, but closest reader does not support motion opening
     */
    OrigoKeysOpeningStatusTypeMotionNotSupported = 5,
    /**
     * Opening type was proximity, but closest reader does not support proximity opening.
     */
    OrigoKeysOpeningStatusTypeTapNotSupported = 6,
    /**
     * Reader reported that a valid key was not found
     */
    OrigoKeysOpeningStatusTypeOrigoKeyNotFound = 7,
    /**
     * The interval between openings of this specific reader was to small
     */
    OrigoKeysOpeningStatusTypeReaderAntiPassback = 8,
    /**
     * The reader reported that an unknown error occurred
     */
    OrigoKeysOpeningStatusTypeReaderFailure = 9,
    /**
     * BLE communication is in a deadlock state!
     */
    OrigoKeysOpeningStatusTypeBluetoothCommunicationFailedWithDeadLock = 10,
    /**
     * Device timeout early (The reader found that the phone timeout)
     */
    OrigoKeysOpeningStatusTypeDeviceTimedOutEarly = 11,
    /**
     * Device timeout APDU (The reader found that the phone timeout)
     */
    OrigoKeysOpeningStatusTypeDeviceTimedOutApdu = 12,
    /**
     * Device timeout Fragment (The reader found that the phone timeout)
     */
    OrigoKeysOpeningStatusTypeDeviceTimedOutFragment = 13,
    /**
     * Reader timeout BLE (The phone found that the reader timeout)
     */
    OrigoKeysOpeningStatusTypeReaderTimedOutBle = 14,
    /**
     * Reader timeout APDU (The phone found that the reader timeout)
     */
    OrigoKeysOpeningStatusTypeReaderTimedOutApdu = 15,
    /**
     * Reader timeout Fragment (The phone found that the reader timeout)
     */
    OrigoKeysOpeningStatusTypeReaderTimedOutFragment = 16,
    /**
     * Generic status about opening type not supported
     */
    OrigoKeysOpeningStatusTypeOpeningTypeNotSupported = 17


};

/**
 *
 * Representation of the various opening types supported by the SDK. For Proximity, Motion and Seamless,
 * the SDK will normally handle these automatically if these opening types are enabled when scanning. See
 * the documentation for [OrigoKeysManager connectToReader:openingType:error:] for more information on this.
 *
 */
typedef NS_ENUM(NSInteger, OrigoKeysOpeningType) {
    /**
     * Default value used if the OpeningType could not be determined
     */
    OrigoKeysOpeningTypeUnknown = 0x00,
    /**
     * Proximity (tap) type Opening Type. This opening type is normally managed by the SDK by specifying
     * it when scanning. the SDK will monitor locks that support this opening type
     */
    OrigoKeysOpeningTypeProximity = 0x01,
    /**
     * Motion (Twist and Go) Opening Type
     */
    OrigoKeysOpeningTypeMotion = 0x02,
    /**
     * Seamless (Vicinity) opening type
     */
    OrigoKeysOpeningTypeSeamless = 0x04,
    /**
     * Application specific (Pulse open) Opening Type.
     */
    OrigoKeysOpeningTypeApplicationSpecific = 0x08,
    
    /**
     * Enhanced solution protocol for Tap opening
     */
    OrigoKeysOpeningTypeEnhancedTap = 0x40
};

/**
 * Enum for describing what Seos BLE Protocol Version that the Reader is using
 * @note since version 1.0.9
 */
typedef NS_ENUM(NSInteger, OrigoKeysReaderProtocolVersion) {
    /**
     * Using legacy protocol, will not be supported in production systems, only in pilots
     */
    OrigoBleProtocolLegacy = 0,
    /**
     * Using the standard ASSA ABLOY BLE Reader Protocol
     */
    OrigoBleProtocolV1 = 1,
    /**
     * Reader protocol could not be determined
     */
    OrigoBleProtocolUnknown = 0xFFFF
};

/**
 * This indicates the role at which the reader object is functioning.
 */
typedef NS_ENUM(NSInteger, OrigoKeysReaderType) {
    /**
     * Peripheral - it only emits advertisement.
     */
    OrigoKeysReaderTypeBlePeripheral = 0x00,
    
    /**
     * Peripheral - it can scan for advertisement.
     */
    OrigoKeysReaderTypeBleCentral    = 0x01,
    
    /**
     * HTTP based (for future).
     */
    OrigoKeysReaderTypeHttpRest      = 0x02
};

/**
 * Representation of a BLe reader.
 */
@interface OrigoKeysReader : NSObject <NSCoding,NSCopying>

/**
 * Universally unique identifier for the Reader
 */
@property(nonatomic, strong, nullable) NSString *uuid;

/**
 * The reader's name, as given by the Reader itself
 */
@property(nonatomic, strong, nullable) NSString *name;

/**
 * The local name, as given by the advertised manufacturer data
 */
@property(nonatomic, strong, nullable) NSString *localName;

/**
 * An array with the supported opening types.
 */
@property(nonatomic, strong, nullable) NSArray *supportedOpeningTypes;

/**
 * Time of the last received RSSI update
 */
@property(nonatomic, strong, readonly) NSDate *lastRSSIUpdate;

/**
 * Type of reader
 */
@property(nonatomic) OrigoKeysReaderType readerType;

/**
 * An optional scan response data
 */
@property(nonatomic, strong, nullable) NSData *optionalScanResponseData;

/**
 * Reader PSN
*/
@property(nonatomic, strong, nullable) NSString *readerPSN;

/**
 * A Boolean returns the reader is favourite reader or not
*/
@property(nonatomic) BOOL isFavourite;


/**
 * Creates an instance of a OrigoKeysReader object.
 * @param name - The reader's name
 * @param uuid - Unique reader identifier
 * @param version - Version of the protocol used in exchange between reader and device
 * @param rssiValuesForOpeningTypes - Dictionary containing a minimum RSSI for each opening type.
 */
- (nullable instancetype)initWithName:(nullable NSString *)name uuid:(nonnull NSString *)uuid protocolVersion:(OrigoKeysReaderProtocolVersion)version rssiValueForOpeningTypes:(nonnull NSDictionary *)rssiValuesForOpeningTypes;

/**
 * Creates an instance of a OrigoKeysReader object.
 * @param name - The reader's name
 * @param uuid - Unique reader identifier
 * @param version - Version of the protocol used in exchange between reader and device
 * @param supportedOpeningTypes -
 * @param rssiValuesForOpeningTypes - Dictionary containing a minimum RSSI for each opening type.
 */
- (nullable instancetype)initWithName:(nullable NSString *)name uuid:(nullable NSString *)uuid protocolVersion:(OrigoKeysReaderProtocolVersion)version supportedOpeningTypes:(nullable NSArray *)supportedOpeningTypes rssiValueForOpeningTypes:(nonnull NSDictionary *)rssiValuesForOpeningTypes requiresTimeoutFreeSession:(BOOL)requiresTimeoutFreeSession;

/**
 * Returns YES if reader supports opening type
 * @param openingType - Opening type to query
 */
- (BOOL)supportsOpeningType:(OrigoKeysOpeningType)openingType;

/**
 * Returns the mean of the recently measured RSSI values.
 * Returns INT_MIN if number of measured values aren't enough.
 */
- (NSInteger)meanRssi;

/**
 * Returns YES if the reader is in range of the specified `OrigoKeysOpeningType`, NO otherwise.
 * @param openingType - Opening type to query
 */
- (BOOL)isInRangeFor:(OrigoKeysOpeningType)openingType;

/**
 * A list of RSSIMeasurement objects (maximum of three entries) showing the most recent measured Received Signal Strength Indications (RSSI values)
 */
- (NSArray<OrigoKeysRssiMeasurement *>*) rssiList;
/**
 * A longer list of RSSIMeasurement objects (maximum of 50 entries) showing the most recent measured Received Signal Strength Indications (RSSI values)
 */
- (NSArray<OrigoKeysRssiMeasurement *>*) rssiHistory;

/**
 * Returns a readable description about the reader.
 */
- (NSString *)description;


#pragma mark Favorite Door API calls

/**
 * Allow user to add a reader as a favorite reader.
 * Returns the status and error if any.
 */
-(void)addFavoriteReader :(OrigoKeysReader*)reader withResponse:(void (^)(BOOL success, NSError *_Nullable error))responseHandler;


/**
 * Allow user to delete a favorite reader.
 * Returns the status and error if any.
 */
-(void)deleteFavoriteReader :(OrigoKeysReader*)reader withResponse:(void (^)(BOOL success, NSError *_Nullable error))responseHandler;

/**
 * Allow user to delete all favorite readers.
 * Returns the status and error if any.
 */
-(void)deleteAllFavoriteReaders :(void (^)(BOOL success, NSError *_Nullable error))responseHandler;

/**
 * Allow user to get all favorite readers.
 * Returns list of favorite readers in an array format.
 */

- (void)listFavoriteReaders:(void (^)(NSArray *_Nullable favoriteReaders, NSError *_Nullable error))responseHandler;




@end
NS_ASSUME_NONNULL_END
