sailthru-mobile-ios
===================

Welcome to the **Sailthru SDK** distribution site!

You will find everything you need to incorporate Sailthru's iOS SDK into your applications. If you add yourself to the **Watch List** by tapping on the **Watch** button, you will get notified each time the repository changes.

If you just happened on this site, you can discover how Sailthru can can address your company's marketing challenges and transform its business [here](http://www.sailthru.com/why-sailthru/).

## Contents

1. README (This file)- High level overview of the SDK Library 
2. [SailThruSDK/README](SailThruSDK/README "Library Readme") - Core Library README. Including FAQ, Version changes and implementation details 
3. LICENSE - all content in this repository is released under the Apache Version 2 License
4. SailthruSDKdemoManual - contains a sample project that demonstrates how to link the SDK manually into an app
5. SailthruSDK - the SDK header files, and two static libraries, one for iOS6 and one for iOS7. Please use the latest possible version for your app.
6. SailthruSDKdemoPods - contains a sample project that uses Cocopods—it has a Podfile, and uses the Cocoapods public repository to retrieve and load the SDK. Note that the SailthruSDK.podspec file contains subspecs, with the default subspec being iOS7 but the linkage for iOS6 too.

If you have not heard about [CocoaPods](http://cocoapods.org) before, it's an open source system by which users can better manage the inclusion of mutiple external libraries or open source code.


Each distribution is tagged using [sematic versioning](http://semver.org) that has the form X.Y.Z. 

### Full Content

1.Choose a **Release** from the GitHub release menu, which lets your retrieve a zip archive of the release, which includes every file in this repository. This archive is equivalent to older distributions that you received from your Sailthru account manager.

2. Clone the proper repository version using **git**, then checkout the desired release (which is prefixed by a 'v' character). On the command line this would take the form of: 

    $ git clone https://github.com/sailthru/sailthru-mobile-ios.git
    $ git checkout tags/vX.Y.Z # X.Y.Z, or just don't run this command to get the latest

### CocoaPods

If you haven't heard of [CocoaPods](cocoapods.org) before, you can learn about it by browsing their site or reading the [RayWenderlich](http://www.raywenderlich.com/12139/introduction-to-cocoapods) and [Bart Jacobs](http://code.tutsplus.com/tutorials/streamlining-cocoa-development-with-cocoapods--mobile-15938) tutorials. In a nutshell, **CocoaPods** lets you integrate multiple external libraries or open source projects into your primary project, and maintain them as they morph over time.

1. If you want to experiment, you can use one of the **Full Content** methods to retrieve all files, then open the **SailthruDemo.workspace** file contained in the **SailthruSDKdemoPods** folder, and examine how all everything gets wired together.

2. To just retrieve a newer spec, update your **Podfile** to reference the desired release, then run:

    $ pod update
    
within your project directory.

Your **Podfile** will contain a line similar to:

    pod 'Sailthru_SDK_iOS', '~> 3.2.7'  # or 'Sailthru_SDK_iOS/ios7'
    # Note that the primary subspec points to the latest version

or for the iOS6 version:

    pod 'Sailthru_SDK_iOS/ios6', '~> 3.2.7'
    
## Version Verification

The SDK supports a **version** method, so you can verify in your code that in fact you've retrieved the desired distribution release.

## Deep Linking

Sailthru provides the ability for your push campaigns to set key/value pairs—both strings—along with the alert text. To achieve a 'deep-link', your app needs the ability to translate a key/value into a series of actions so that it can present an appropriate view when the user taps on the notification.

For example, if your app uses a REST interface, and uses 'product_id' to uniquely identify products, the notification could include a key/value pair such as '{ "product_id": "20134" }' in addition to the alert message of 'You should love this great new widget!'. 

When your app finds this particular key/value pair, it would first see if the product '20134' was currently cached within the app, and if so, navigate to a view that displays it prior to showing any UI. Otherwise, it could pop a spinner, inform the user in a HUD that it's retrieving that product, then show it once received. If plain product numbers don't make sense in your app, then send it a URL to something that's actionable within the app.

To avoid popping spinners, you can use 'silent' push notifications (ones with no alert text) that inform the app of potential products that may be included in a subsequent alert-style notification; the app would then use background fetch to retrieve and store them. 

Alternately, always use 'silent' push notifications, include the alert text as a key/value pair, and when your app has retrieved the relevant information it can pop a local notification that to the user looks no different than a remote one.

## FAQ

Answers to Frequently Asked Questions
------------------------------------------

Q: Have you tested with iOS8?
A: Yes - the SDK (iOS7+ version) works properly with no changes. Also, you can message the SDK from Swift
   source files.

Q: How can I test that Push Notifictaions are functional?
A: You can use API Test on my.sailthru.com. Documentation is found on [docs.sailthru.com](http://docs.sailthru.com/documentation/products/mobile-push-notification-sending)

Q: How do I obtain the key/value data included contained in Push Notification?
A: Client added JSON data (key/value pairs), when provided, get added to the 'aps' dictionary with
   a 'json' key, and returned by 'didReceiveRemoteNotification:isBooting:'. Both keys and values are
   NSStrings, even if numeric. For example:
<code>

    {

     aps = {

           alert = "Howdie Partner!";

     };

     json =    {

        "key" = "value";

        "2" = "55";        // Strings!

     };

    }

</code>

Q: What versions will you support now that iOS8 is GA?
A: The SDK will contain a single library in the iOS7+ directory (iOS6 support will be dropped).

Q: What are the most common problems integrating the Sailthru SDK?
A:
 - uploading push certificates with passwords
 - forgetting to add the "-ObjC" flag to the linker (step 3 below)
 - not passing the correct "mode" and/or "appID" in the registration message

Q: How do I obtain the key/value data that I added to my Push Notification?
A: Client added JSON data (key/value pairs through the UI), when attached, are moved as a dictionary
   to the top level dictionary with a key of "json", and are thus a peer toe the Apple supplied "aps"
   dictionary. The modified dictionary is then returned by the manager's
   'didReceiveRemoteNotification:isBooting:' method

Q: Does the SDK hard link to system frameworks, and if not, which ones must my app add?
A: The library "optionally" links the 'Foundation' and 'SystemConfiguration' frameworks, thus
   client apps must link to SystemConfiguration if not already doing so.

Q: Does the SDK add categories to any of the standard Foundation classes?
A: No, the SDK does not use categories on anything other than its own classes.

Q: Does the SDK pollute my app's namespace with classes other than "ST..." prefixed classes?
A: No.

Q: Do you use AFNetworking, or other frequently used Open Source software?
A: Every line of code in the SDK is under our control - while we do use Apple's Reachability source,
   the Reachability class is (now) prefixed with 'ST'.

Q: Does the SDK use the iOS file system?
A: Yes, it mostly uses a single file but could create a second temporarily, saved in the
   "Application Support" folder (path obtained from NSSearchPathForDirectoriesInDomains), and marks
   both with the "Do Not Backup" attribute and the data is encrypted.

Q: Does the app ever use HTTP?
A: No, it only uses HTTPS.

Q: Does the .a file include symbols?
A: Yes, the app contains all symbols (to better guide crash analysis in the remote chance encounter
   an exception in our software). If you strip your app or create a separate symbol file the library
   symbols are managed by Xcode the same way.

Q: What is the code size of the library?
A: There is no simple answer to this - the library (.a file) has architectures lipo'd into it for all
   valid device and simulator architectures, and contains the full symbol table to assist in exception
   resolution. A Q&A on StackOverflow shows at least one technique  you can use to determine the
   stripped size of one architecture: http://stackoverflow.com/q/22995744/1633251
   For the 3.3.0 library, arm64, the size is about 125,000 bytes (TEXT+DATA)

Q: What does Sailthru mean when it deprecates something?
A: That feature will be gone in the next release.

## Notes

Brenden Mulligan, co-founder and designer at **Cluster**, [documented the approach](http://techcrunch.com/2014/04/04/the-right-way-to-ask-users-for-ios-permissions/) on **TechCrunch** that his company uses to increase the percentage of users who allow push notifications etc. Definitely worth a read!


Copyright (c) 2014 Sailthru, Inc    
