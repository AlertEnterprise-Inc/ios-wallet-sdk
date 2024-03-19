//
//  OrigoLocationHandlerDelegate.h
//  OrigoSDK
//
//  Copyright © 2021 HID Global. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OrigoKeysReader.h"

@protocol OrigoIPReaderPresenceDelegate<NSObject>

- (void)oipReaderAppeared:(OrigoKeysReader *)reader;
- (void)oipReaderDisappeared:(OrigoKeysReader *)reader;

@end
