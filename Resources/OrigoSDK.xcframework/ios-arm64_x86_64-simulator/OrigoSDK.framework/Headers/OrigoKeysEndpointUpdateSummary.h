//
//  OrigoKeysEndpointUpdateSummary.h
//  OrigoSDK
//
//  Copyright © 2018 HID Global. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OrigoKeysEndpointUpdateSummary : NSObject {
    
}

/**
 * NSDate representing when this TSM update started
 */
@property(nonatomic, strong) NSDate *updateDate;
/**
 * NSTimeInterval representing the internal time the TSM updat took
 */
@property(nonatomic) NSTimeInterval  updateDuration;

/**
 * Number of issued keys in the update
 */
@property(nonatomic) NSUInteger keyIssuedCount;
/**
 * Number of revoked keys in the update
 */
@property(nonatomic) NSUInteger keyRevokedCount;
/**
 * Number of updated keys in the update
 */
@property(nonatomic) NSUInteger keyUpdatedCount;

/**
 * Used internally by the SDK to count keys issued
 */
- (void)addKeyIssued;
/**
 * Used internally by the SDK to count keys revoked
 */
- (void)addKeyRevoked;
/**
 * Used internally by the SDK to count keys updated
 */
- (void)addKeyUpdated;
@end



