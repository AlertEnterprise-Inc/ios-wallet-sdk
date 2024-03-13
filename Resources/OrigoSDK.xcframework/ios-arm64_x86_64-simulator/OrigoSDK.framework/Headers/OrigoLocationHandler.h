//
//  OrigoLocationHandler.h
//  OrigoSDK
//
//  Copyright © 2022 HID Global. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "OrigoLocationHandlerDelegate.h"

/**
 * This is the class that handles HID Identity Positioning Events.
 * <p>
 *  On the successful redemption of Identity Postioning Issuance Token, by default, an instance of OrigoLocationHandler will be created and maintained in OrigoKeyManager.
 * </p>
 * <p>
 * At anytime, use "getLocationHandler" method from OrigoKeyManager to get the running instance of OrigoLocationHandler.
 * </p>
 */

@protocol OrigoLocationHandler <NSObject>

/** Start Service
 <p>
 The location services will start, if not already running.
 </p>
 */
- (void)start;

/** Stop Service
 <p>
 The location services will stop, if already running.
 </p>
 */
- (void)stop;

/** Status of location service
  <p>
  Returns Yes, if the location service is started and currently monitoring, otherwise returns No.
  </p>
 */
- (BOOL)hasStarted;

/** Synchronize Site Information
 <p>
 Fetches the latest PDB for beacon approach and reader PSN's for reader approach from the Origo Backend.
 </p>
 */
- (void) syncSiteInfo;

/** Set Delegate
 <p>
 Pass the listener object instance which adapts all the required methods of OrigoLocationHandlerDelegate.
 </p>
 */
- (void)setDelegate:(id<OrigoLocationHandlerDelegate> _Nullable)delegate;

/**
 <p>
 Use track() method when you manually want to track user position at any time.
 
 Note: Make sure you called start() method, before calling track().
 </p>
 */
- (void)track;

@end
