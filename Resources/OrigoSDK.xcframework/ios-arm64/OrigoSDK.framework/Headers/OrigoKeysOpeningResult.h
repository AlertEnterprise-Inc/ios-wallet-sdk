// OrigoKeysOpeningResult.h
// Copyright (c) 2018 HID Origo Mobile Services
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "OrigoKeysReader.h"

/**
 * This class represents the result of a reader opening.
 */
@interface OrigoKeysOpeningResult : NSObject

/**
 * Status of the connection
 */
@property(nonatomic) OrigoKeysOpeningStatusType status;

/**
 * Opening status payload. EOT fragmend body. Application specific data that was returned from the lock.
 *
 * @return additional payload related to the opening, default is nil.
 */
@property(nonatomic) NSData *statusPayload;

@end
