# AE  iOS Wallet SDK

This document provides the information about Wallet SDK.
This section includes the following topics.

## Reference to use HID

### Introductory notes
Due to how the Origo SDK is designed it does not support creating categories or inheriting from it’s classes.

To initialize and configure the SDK use

-[OrigoKeysManager initWithDelegate:options:]
-[OrigoKeysManager setSupportedOpeningTypes:]

There are four Methods in the SDK to handle Seos TSM integration:

-[OrigoKeysManager isEndpointSetup:]
-[OrigoKeysManager setupEndpoint:]
-[OrigoKeysManager updateEndpoint]
-[OrigoKeysManager startup]

In addition to these methods, there are Methods to turn BLE on/off and check the state of BLE

-[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]
-[OrigoKeysManager stopReaderScan]
-[OrigoKeysManager isScanning]

The Methods to communicate with the secure Seos storage are

-[OrigoKeysManager listMobileKeys:]
-[OrigoKeysManager lastAuthenticationInfo:]

Methods to query the SDK for general information

-[OrigoKeysManager healthCheck]
-[OrigoKeysManager walletHealthCheck]
-[OrigoKeysManager deviceHealthCheck]
-[OrigoKeysManager deviceHasBluetoothTurnedOn]
-[OrigoKeysManager deviceSupportsBluetoothLowEnergy]
-[OrigoKeysManager apiVersion]

Methods to handle Readers

-[OrigoKeysManager listReaders]
-[OrigoKeysManager closestReaderWithinRangeOfOpeningType:]

Methods to access data on specific Origo Keys

-[OrigoKeysManager generateOTPForKey:error:]
-[OrigoKeysManager dataForKeyOid:tag:error:]
-[OrigoKeysManager putData:keyOid:tag:error:]
-[OrigoKeysManager activateOrigoKey:error:]
-[OrigoKeysManager deactivateOrigoKey:error:]

Methods to handle Location Services (refer HID Identity Positioning section for more details)

-[OrigoKeysManager getLocationHandler]
-[OrigoKeysManager isLocationServiceRegistered]

## Step 1: Create a new instance of the Origo Keys SDK
The -[OrigoKeysManager initWithDelegate:options:] init method requires two parameters;

delegate: A delegate implementing the OrigoKeysManagerDelegate protocol
options: A dictionary with the following content
OrigoKeysOptionApplicationId a string provided by HID Global that uniquely identifies the application
OrigoKeysOptionVersion a string describing the application name and version will try to connect to. This will be provided by HID Global.
OrigoKeysOptionBeaconUUID a string specifying an iBeacon UUID to monitor when scanning is started in mode “OrigoKeysScanModeOptimizePerformance”. By default, the iBeacon id monitored is “00009999-0000-1000-8000-00177a000002”, but for integrators that deploy own iBeacons, this can now be configured.
OrigoKeysOptionTargets a string specifying the target OrigoSDK/OrigoAppleWallet/OrigoAppleWalletPreview to be passed to SDK. If only Wallet functionality to be consumed integrators will pass OrigoAppleWallet/OrigoAppleWalletPreview.
Apple Pay leverages NFC technology which is also used in HID Signo and HID iCLASS SE readers. When a phone with one or more cards in Apple Wallet (payment card, NFC-based Pass/ticket, etc.) is brought near to the reader, the Apple Wallet card may be displayed on the screen, even if not used for the transaction. The Apple Pay popup may be suppressed when the app is in foreground following option can be used by integrators:

OrigoKeysOptionSuppressApplePay A String specifying with YES or NO to suppress the Apple Pay popup when the App is in foreground or not is available for integrators.By the string is set to NO .To Suppress Apple Pay integrators need to request for special entitlement provisioning profile request from Apple and below key needs to be added to entitlement file after enabling Apple Pay Suppression for Distribution in provisioning profile.

` <key>com.apple.developer.passkit.pass-presentation-suppression</key>`
   `<true/>` 
#### Sample Apple Pay Suppression Code in Swift

```    func createInitializedMobileKeysManager() -> OrigoKeysManager? {
        let version = "\(APPLICATION_ID)-\(Bundle.main.infoDictionary?["CFBundleShortVersionString"] ??  0) (\(Bundle.main.infoDictionary?["CFBundleVersion"] ?? 0))"
        let isApplePayDisable = "YES"
        let config = [
            OrigoKeysOptionApplicationId: APPLICATION_ID,
            OrigoKeysOptionVersion: version,
            OrigoKeysOptionSuppressApplePay :isApplePayDisable
        ]
        return OrigoKeysManager(delegate: self, options: config)
    }
```
#### Sample Apple Pay Suppression Code in Objective C

```
   - (OrigoKeysManager *)createInitializedMobileKeysManager {

    NSString *version = [NSString stringWithFormat:@"%@-%@ (%@)", APPLICATION_ID, [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"], [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]];
    NSString *isApplePayDisable = @"YES";
    NSDictionary *config = @{OrigoKeysOptionApplicationId: APPLICATION_ID, OrigoKeysOptionVersion: version,OrigoKeysOptionSuppressApplePay:isApplePayDisable};
    return [[OrigoKeysManager alloc] initWithDelegate:self options:config];
}
```
Note : Apple Pay cannot be suppressed when the app is in background as per Apple guidelines.

The first time the Origo Keys SDK is used, it will`

Generate secure keys and store these in the Application keychain
Create and initialize a secure storage for Seos Keys
On subsequent runs, the SDK will take care of

Internal SDK upgrades

## Step 2: Check to see if the Key Storage has been setup correctly
Before the SDK can be used to communicate with Readers, the secure storage needs to be initialized and personalized. Call the -[OrigoKeysManager isEndpointSetup:] method of the Origo Keys SDK.

If the result is YES, everything is good to go, and you can call the -[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:] method

If the result is NO, you need to call the -[OrigoKeysManager setupEndpoint:] method, passing an Invitation Code.

## Step 3a: Setting up the endpoint (if endpoint has not yet been set up)
This is expected on a completely new installation. The Seos data storage needs to initialized and configured, and unique encryption keys have to be negotiated and established with the Seos TSM Server. If the -[OrigoKeysManager isEndpointSetup:] returns NO, the SDK has not yet personalized the internal Seos entity. The SDK will take care of Seos personalization when you call -[OrigoKeysManager setupEndpoint:]

The SDK will then

initialize the Seos instance (if i’t not already initialized)
Connect to the Origo Keys Seos TSM and download and install the unique keys for this particular Endpoint
Send a callback to the delegate, either to -[OrigoKeysManagerDelegate origoKeysDidSetupEndpoint] on success, or -[OrigoKeysManagerDelegate origoKeysDidFailToSetupEndpoint:] with and error code on a failure.
What to do on a failure?

If the SDK returns with an error that ends with “RetryError” (e.g. OrigoKeysDeviceSetupFailedRetryError) the application should (if possible) retry the same Invitation code again. The Origo Keys SDK and Server should then be able to pick up where it left off, and endpoint Setup should complete.

## Step 3b: Using an endpoint that has already been setup
If the -[OrigoKeysManager isEndpointSetup:] returns YES, the endpoint has been setup, and is ready to use. It is recommended to call the -[OrigoKeysManager startup] method before using the SDK, this will connect to the Origo Keys Seos TSM to report the current application version, and will send a callback to the delegate when finished.

# SDK Use Cases
This section describes the basic use cases for working with the Origo Keys SDK.

## Updating key info from the Origo Keys Seos TSM Server
Call the -[OrigoKeysManager updateEndpoint] method. The SDK will then connect to the Origo Keys Seos TSM, download updates for the current endpoint, and will then send a callback to the delegate when done. This means that new keys, revocation of keys, etc. will be delivered to the phone from the Seos TSM. This requires Internet connectivity.

Examples on when an update should be performed:

On every startup, after -[OrigoKeysManager startup]
When your application receives a push message indicating that key changes have been done
When the Application user performs a manual update
After updating, the caller will receive a callback, either -[OrigoKeysManagerDelegate origoKeysDidUpdateEndpoint] on success, or -[OrigoKeysManagerDelegate origoKeysDidFailToSetupEndpoint:] containing the error information if the update failed. The error case can occur if there is a problem communicating with the secure storage, or if an other asynchronous method is currently running. When the method has completed synchronizing with the Seos TSM, a call to the callback delegate will be made when the operation completes.

Updates can also uninstall the current endpoint, in that case -[OrigoKeysManagerDelegate origoKeysDidTerminateEndpoint] instead of -[OrigoKeysManagerDelegate origoKeysDidFailToUpdateEndpoint:] is called on the delegate.

## Listing keys on the Secure Storage
Use the -[OrigoKeysManager listMobileKeys:] method to get an NSArray of -[OrigoKeysKey] class Objects. The information returned will either be fetched immediately from the Seos Secure Storage, or from the internal SDK cache if the Seos Secure Storage is currently busy.

Additionally, you can fetch information about the last authenticated key with the -[OrigoKeysManager lastAuthenticationInfo:] method. It will return an -[OrigoKeysLastAuthenticationInfo] object containing information about whether or not the reader has written information to the key: -[OrigoKeysLastAuthenticationInfo authenticationCounter], how many times the key has authenticated: -[OrigoKeysLastAuthenticationInfo isModified] as well as the key that was authenticated: -[OrigoKeysLastAuthenticationInfo lastAuthenticatedOrigoKey].

## Turning BLE communication on/off
Bluetooth LE communication can be turned on or off. Use the -[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:] and -[OrigoKeysManager stopReaderScan] respectively to do this.

Examples on when to use these methods:

If the Origo Keys SDK reports that there are no keys on this endpoint, it makes sense to turn off BLE Scanning to preserve battery
Make sure that the endpoint has been setup before turning on BLE Scanning
Bluetooth scanning can be configured to run in two Scanning Modes.

OrigoKeysScanModeOptimizePerformance
OrigoKeysScanModeOptimizePowerConsumption
If your application is only scanning in the foreground, we recommend that you use OrigoKeysScanModeOptimizePowerConsumption. OrigoKeysScanModeOptimizePerformance will consume more power, but will work better if your application is running in the background.

Additionally, if you want to use background modes, see the chapter on Configuring the application to run in the background

The parameter supportedOpeningTypes is an NSArray of OrigoKeysOpeningType values. You MUST add the opening types that you want to support, for example OrigoKeysOpeningTypeMotion to support Twist and Go opening Type.

### Configuring custom lock service code for readers scanning
In general the default lock service code 2 will be used for majority of the use cases. However, in certain cases like multiple apps powered by Seos running in same phone might cause an issue as multiple apps will try using same lock service code to unlock the door, there by causing BLE Collision. To resolve this issue, lock service code can be configured in the reader as well as in the app.

Lock service code 1 to 32 is allocated for internal purpose. Customizable lock service can be configured from 33 onwards. Please reach out to HID partner services team to get a dedicated lock service code and also to understand how could we configure the same code in the readers.

```
Sample Lock Service Code implementation in Objective C

#define LOCK_SERVICE_CODE_HID 2//Here any 1 custom lock service code can be defined
NSArray *_lockServiceCodes;
- (id)init {
 self = [super init];
if (self) {
// Lock service codes are used to specify what readers the Manager should scan for
_lockServiceCodes = @[@(LOCK_SERVICE_CODE_HID)];
 }
return self;
}
```

Then you can pass lock service code array in the method -[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]

```
Sample Lock Service Code implementation in Swift

let LOCK_SERVICE_CODE_HID = 2  //Custom Lock Service code can be defined
private var lockServiceCodes: [Any] = []  
override init() {
       super.init()
               // Lock service codes are used to specify what readers the Manager should scan for
       lockServiceCodes = [LOCK_SERVICE_CODE_HID]
       }
   }
```
Then you can pass lock service code array in the method origoKeysManager?.startReaderScan(in: scanMode, supportedOpeningTypes: openingTypes!, lockServiceCodes: lockServiceCodes, error: &error)

### Implementing custom mechanics for opening readers
Besides the built-in functionality to open readers. It is possible to implement custom functionality of opening readers. The SDK supports two types of use cases:

The first use case is external trigger or user action: for example an event being sent from one of the devices sensors or a through the press of a button in the applications interface. To list all the readers currently in the devices vicinity use the -[OrigoKeysManager listReaders] method. To get the closest reader within the range of a specific -[OrigoKeysReader OrigoKeysOpeningType] use the -[OrigoKeysManager closestReaderWithinRangeOfOpeningType:] method.

You will then be able to interact with that reader through the -[OrigoKeysManager connectToReader:openingType:error:] method. The SDK exposes the patented Twist and Go motion pattern through the -[OrigoKeysManagerExtendedDelegate origoKeysUserDidUnlockGesture] delegate method, which can be used in this manner.

The second use case is automatically based upon reader advertisements: callbacks will be sent to the -[OrigoKeysManagerExtendedDelegate origoKeysShouldInteractWithScannedReader:] method whenever the SDK receives a new advertisement from a reader.More Details on this callback can be checked under Other Guides -> Custom opening method section. The properties -[OrigoKeysReader meanRssi] and -[OrigoKeysReader rssiList] can be used to estimate the distance of the reader relative to the device. Please note the RSSI value is only a measurement of signal strength and can not be used to determine the exact distance between the device and the reader. Return a boolean indicating the decision to try to interact with the reader or not.

### Getting information about the Endpoint
Use the -[OrigoKeysManager endpointInfo:] method to get information about the current endpoint status. The information returned will either be fetched immediately from the Seos Secure Storage, or from the internal SDK cache if the Seos Secure Storage is currently busy.

### Querying the SDK for warnings
The Origo Keys SDK has a built in method to detect if BLE is supported on the device, or if Bluetooth has been turned off.

Use the -[OrigoKeysManager healthCheck] method to get an NSArray of -[OrigoKeysInfo] class Objects.

It is also possible to use the -[OrigoKeysManager deviceHasBluetoothTurnedOn] and -[OrigoKeysManager deviceSupportsBluetoothLowEnergy] methods to check if the Device supports BLE and has bluetooth turned on.

### Unregistering an endpoint
To unregister endpoint it is required to call -[OrigoKeysManager unregisterEndpoint] method.

If this results in the endpoint being uninstalled, the delegate method -[OrigoKeysManagerDelegate origoKeysDidTerminateEndpoint] has been called, the endpoint is no longer personalized, and the Seos Environment is ready for setup again.

If call to origoKeysManager?.unregisterEndpoint() is failed due to no network /server down issues etc , the delegate method -[OrigoKeysManagerDelegate origoKeysDidFailToUpdateEndpoint:] will be called.

### Configuring the application to run in the background
Behavior has changed between iOS 10 and iOS 11. To ensure compatibility with both applications that need to run in the background and application that only need to run in the foreground, configuration of the background modes has been removed from the SDK, and must be managed by the application.

For applications that only need to run in the foreground, the method `-[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:] with scanMode OrigoKeysScanModeOptimizeBatteryConsumption should be used. In those cases, it is not required to enable background modes according to the description below.

For applications that need to run in the background, the method -[OrigoKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:] with scanMode OrigoKeysScanModeOptimizePerformance should be used. In those cases, it is required to enable background modes according to the description below.

### Enabling background running
For any application that needs to be run in the background, steps 2, 3 and 4 below need to be performed by the application. Step 3 can be performed by the application at any time (e.g. when the application is put in the background, or when it starts) , and step 4 needs to be performed by the application before calling the [OrigoKeysManager startReaderScanInMode: OrigoKeysScanModeOptimizePerformance supportedOpeningTypes:lockServiceCodes:error:] method.

The application needs to instantiate a CLLocationManager to perform steps 2,3 and 4.

Background mode: Location updates For iOS 11, the project setting background mode “Location updates” is required. iOS will suspend operations after approximately 6-8 seconds otherwise.

CLLocationManager::allowsBackgroundLocationUpdates must be set to YES. It is possible to disable the background mode by setting this to NO, e.g. if the apps wants to allow the user to disable the background mode

CLLocationManager::requestAlwaysAuthorization This will present the user with information about the background modes. The appropriate information needs to be added to NSLocationWhenInUseUsageDescription, NSLocationAlwaysAndWhenInUseUsageDescription, NSLocationAlwaysUsageDescription and possibly even to NSLocationUsageDescription in the info.plist.

CLLocationManager::startUpdatingLocation tells iOS to start giving us ranginginformation For iOS 11, this is required if the application needs persistent ranging.

### Killing the app
For the “Killed state”, ranging stops working after approximately 15 to 30 minutes. However, if the user force quits the app by swiping it away, it could be argued that he or she doesn’t want the app running.


## Reference to use Wavelynx

### Usage

`import TapSdk` in the Swift file to use classes and delegate.

## Classes
The following classes are available globally.

### WlWalletController
High level controller exposing functionality for adding passes to the Apple Wallet. The general steps involved in provisioning a pass are as follows:

1. Call `checkEligibility` to check if user can provision passes.
2. The onEligibilityResult delegate method is triggered with eligibility.
3. Display the  “Add to Wallet” button if user is eligible.
4. When user taps “Add to Wallet”, call `startPassProvisioning `.
5. The onProvisioningReady delegate method is triggered, passing the ***provisioningBlob***.
6. Add the card and pass the provisioningBlob to the Tap API add-card request along with the card data.
7. A digitizationReference  is returned in the add-card response.
8. Call `saveToWallet` and pass in the digitizationReference in the saveLink field.
9. The SDK will start the provisioning process and hand it off to the Apple UI flow if everything is successful.


**Singleton instance of the wallet controller. This should be the only instance used.**


-----

## Protocols
The following protocols are available globally.

### WlWalletControllerDelegate

Delegate protocol for a consuming application to implement and handle events associated with wallet credentials.

##### WlWalletController( - : onEligibilityResult:)
Tells the application whether the user/device is eligible to add passes/cards to the wallet.
##### WlWalletController( - : onProvisioningReady:)
Makes the provisioningBlob available after the “Add to Wallet” button has been tapped. A
call to the Tap API to add the card can then be made.
##### WlWalletController( - : onError:)
Triggered when any error occurs. Passes a reason enum.
##### WlWalletControllerProvisioningPending( - :  )
Triggered when provisioning starts. Allows the application UI to display a loading/pending state.
##### WlWalletControllerProvisioningSuccess( - : )
Called following a successful provisioning attempt to the wallet.


## Enumerations
The following enumerations are available globally.

### WlPassResult
Following error codes returned by the WlWalletControllerDelegate.
##### controllerNotBound
The bind method has not been called yet.
##### success
Success case with no error.
 #####  configInvalid
The supplied configuration is invalid.
#####  provisioningError
There was an Apple related error in the provisioning.
#####  alreadyProvisionedOnPhone
A pass is already provisioned for this configuration on the phone.
#####  alreadyProvisionedOnWatch
A pass is already provisioned for this configuration on the watch.
#####  errorGeneratingProvisioningBlob
The provisioning blob could not be generated.


## Example 

#### Controller initialization

 class MyController : WlWalletControllerDelegate {
      * WlWalletController.shared.delegate = self
}


#### checkEligibility()
Check whether the device/user is eligible to add passes to the wallet. 

     WlWalletController.shared.checkEligibility()

This results in a call to the delegate method onEligibilityResult.
    * func wlWalletController(_ controller: TapSdk.WlWalletController, onEligibilityResult isEligible: Bool) {


#### startPassProvisioning()
This function starts the multi-step provisioning process on the device. Calling this function will generate device linking information. The device linking information is **generated and returned in the form of a provisioningBlob, this should be passed to** the Tap API platform through the adding of a virtual card. 

      WlWalletController.shared.startPassProvisioning()

This function will result in a call to the delegate method onProvisioningReady.
    * func wlWalletController(_ controller: TapSdk.WlWalletController, onProvisioningReady provisioningBlob: String) {

#### saveToWallet()

Save a pass to the Apple Wallet. This will kick off the iOS UI flow to add a pass. This function takes in some display metadata for the “Add Pass” UI as well as a link/digitization reference returned from the Tap API. This operation must be kicked off from a view controller in order to present the UI over top of it.

    * WlWalletController.shared.saveToWallet(parentViewController:self,
                    thumbnail: CGImage,displayName: String,
                    description: String,saveLink: String)
  

  Parameters

|  parentViewController | ViewController the “Add Pass” UI will be presented over.  |
| ------------ | ------------ |
|  thumbnail  |   Thumbnail image of card to display in UI.|
|  displayName  |  Displayed name of user for UI. |
|  description  | Displayed pass description for UI.  |
| saveLink   |  Digitization reference returned from Tap API after adding the card. |




If any error occurs in the process, the `onError` delegate method will be triggered with the reason.

     *func wlWalletController(_ controller: TapSdk.WlWalletController, onError reason: TapSdk.WlPassResult) {
