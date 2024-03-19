//
//  OrigoEnvironmentType.h
//  OrigoSDK
//
//  Copyright © 2021 HID Global. All rights reserved.
//

#ifndef OrigoEnvironmentType_h
#define OrigoEnvironmentType_h

/**
 * The different environments of Origo SDK. Ideally you (the integrator) will use `OrigoEnvironmentCert` (integration) during development
 * and `OrigoEnvironmentProd` (production)
 */
typedef NS_ENUM(NSInteger, OrigoEnvironmentType) {
    
    /**
     * Origo Production Environment
     */
    OrigoEnvironmentProd = 8,
    /**
     * Origo Development/Test Environment for Integrator
     */
    OrigoEnvironmentCert = 9,
    /**
     * Origo Pre-Production Environment
     */
    OrigoEnvironmentPreProd = 10,
    /**
     * Origo Test Environment
     */
    OrigoEnvironmentInt = 11,
    /**
     * Origo Development Environment
     */
    OrigoEnvironmentDev = 12,
    
    /**
     * Not a valid environment or No environment detected.
     */
    OrigoEnvironmentUnknown = 15

};

#endif /* OrigoEnvironmentType_h */
