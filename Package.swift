// swift-tools-version: 5.8
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "AEWalletSDK",
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "AEWalletSDK",
            targets: ["AEWalletSDK","TapSdk","OrigoSDK","SeosMobileKeysSDK","BerTlv","CocoaLumberjack","JSONModel","Mixpanel"]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],
    targets: [
        .target(
            name: "AEWalletSDK",
            dependencies: []),
        .binaryTarget(name: "TapSdk", path: "artifacts/TapSdk.xcframework"),
        .binaryTarget(name: "SeosMobileKeysSDK", path: "Resources/SeosMobileKeysSDK.xcframework"),
        .binaryTarget(name: "OrigoSDK", path: "Resources/OrigoSDK.xcframework"),
        .binaryTarget(name: "BerTlv", path: "Resources/Release-universal/BerTlv.xcframework"),
        .binaryTarget(name: "CocoaLumberjack", path: "Resources/Release-universal/CocoaLumberjack.xcframework"),
        .binaryTarget(name: "JSONModel", path: "Resources/Release-universal/JSONModel.xcframework"),
        .binaryTarget(name: "Mixpanel", path: "Resources/Release-universal/Mixpanel.xcframework"),
        .testTarget(
            name: "AEWalletSDKTests",
            dependencies: ["AEWalletSDK"]),
    ]
)
