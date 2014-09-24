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

## Notes

Brenden Mulligan, co-founder and designer at **Cluster**, [documented the approach](http://techcrunch.com/2014/04/04/the-right-way-to-ask-users-for-ios-permissions/) on **TechCrunch** that his company uses to increase the percentage of users who allow push notifications etc. Definitely worth a read!


Copyright (c) 2014 Sailthru, Inc    
