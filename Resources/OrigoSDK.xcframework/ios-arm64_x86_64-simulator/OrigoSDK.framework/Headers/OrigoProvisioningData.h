//
//  OrigoProvisioningData.h
//  OrigoSDK
//

#import <Foundation/Foundation.h>


@interface OrigoProvisioningData : NSObject

@property (strong, nonatomic) NSString *uId; //unique identifier (UID)
@property (strong, nonatomic) NSString *orgId;
@property (strong, nonatomic) NSArray *availableTargets;
@property (strong, nonatomic) NSData *passThumbnailImage;
@property (strong, nonatomic) NSString *passDisplayName;

@end
