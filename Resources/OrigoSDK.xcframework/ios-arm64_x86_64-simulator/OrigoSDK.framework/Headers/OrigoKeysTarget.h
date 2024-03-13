//
//  OrigoKeysTarget.h
//  OrigoSDK
//
//  Copyright © 2023 HID Global. All rights reserved.
//

/**
 * Represents the target credential storage provider for an `issuanceToken`.
 */
typedef NS_ENUM(NSInteger, OrigoKeysTarget) {
    /**
     * Provision the credential into HID Origo secure storage
     */
    OrigoSDK = 0,
    /**
     * Provision the credential into Apple Wallet
     */
    OrigoAppleWallet = 1,
    /**
     * Provision the credential into Apple Wallet with Preview data
     */
    OrigoAppleWalletPreview = 2,
    /**
     * Provision the credential for HID Identity Positioning
     */
    OrigoIdentityPositioning = 3
};

