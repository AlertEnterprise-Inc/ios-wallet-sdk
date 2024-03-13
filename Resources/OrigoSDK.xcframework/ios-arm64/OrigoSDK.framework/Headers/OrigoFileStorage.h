//
//  OrigoFileStorage.h
//  OrigoSDK
//
//  Copyright © 2022 HID Global. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This class is used to securely store and retrieve the photo ID of the user.
 */

@interface OrigoFileStorage : NSObject

/**
 * Saves and retrieve the Photo
 *
 * @param urlString - url of the Photo ID to be passed
 * @param token - access Token of the Photo ID url to be passed
 * @param completionHandler  -  completion handler to be called with image data Eg : UIImage(data: data!).
 */
- (void)fetchPhotoImage:(NSString *)urlString
           accessToken :(NSString*)token
      completionHandler:(void (^)(NSData * _Nullable, NSError * _Nullable))completionHandler;

@end


/**
 * OrigoDataStorage
 *
 *  This class is helps to trigger location sync on demand.
 *
 */
@interface OrigoDataStorage : NSObject
/**
 * This method helps to trigger the sync for location details manually. OrigoSDK handles location sync automatically, but in case, you like to trigger location sync in a specific scenario, you can use this method.
 *  @param completion - a completion handler 
 */
+ (void)syncLocationData:(void (^ _Nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
