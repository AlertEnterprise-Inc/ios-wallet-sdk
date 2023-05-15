#AE  iOS Wallet SDK
This document provides the information about Wallet SDK.
This section includes the following topics.

###Usage

`import TapSdk` in the Swift file to use classes and delegate.

##Classes
The following classes are available globally.

###WlWalletController
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

##Protocols
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


##Enumerations
The following enumerations are available globally.

###WlPassResult
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

####Controller initialization

 class MyController : WlWalletControllerDelegate {
      * WlWalletController.shared.delegate = self
}


####checkEligibility()
Check whether the device/user is eligible to add passes to the wallet. 

     WlWalletController.shared.checkEligibility()

This results in a call to the delegate method onEligibilityResult.
    * func wlWalletController(_ controller: TapSdk.WlWalletController, onEligibilityResult isEligible: Bool) {


####startPassProvisioning()
This function starts the multi-step provisioning process on the device. Calling this function will generate device linking information. The device linking information is **generated and returned in the form of a provisioningBlob, this should be passed to** the Tap API platform through the adding of a virtual card. 

      WlWalletController.shared.startPassProvisioning()

This function will result in a call to the delegate method onProvisioningReady.
    * func wlWalletController(_ controller: TapSdk.WlWalletController, onProvisioningReady provisioningBlob: String) {

####saveToWallet()

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
