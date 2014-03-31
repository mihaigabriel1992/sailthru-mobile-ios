sailthru-mobile-ios
===================

Welcome to the **Sailthru SDK** distribution site!

You will find everything you need to incorporate Sailthru's iOS SDK into your applications. If you add yourself to the **Watch List** by tapping on the **Watch** button, you will get notified each time the repository changes.

If you just happened on this site, you can discover how Sailthru can can address your company's marketing challenges and transform its business [here](http://www.sailthru.com/why-sailthru/).

## Contents

1. README - this file
2. LICENSE - all content in this repository is released under the Apache Version 2 License
3. SailthruSDKdemoManual - contains a sample project that demonstrates how to link the SDK manually into an app
4. SailthruSDK - the SDK header files, and two static libraries, one for iOS6 and one for iOS7. Please use the latest possible version for your app.
5. SailthruSDKdemoPods - contains a sample project that uses Cocopods—it has a Podfile, and uses the Cocoapods public repository to retrieve and load the SDK. Note that the SailthruSDK.podspec file contains subspecs, with the default subspec being iOS7 but the linkage for iOS6 too.

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

    pod 'Sailthru_SDK_iOS', '~> 3.2.6'  # or 'Sailthru_SDK_iOS/ios7'
    # Note that the primary subspec points to the latest version

or for the iOS6 version:

    pod 'Sailthru_SDK_iOS/ios6', '~> 3.2.6'
    
## Version Verification

The SDK supports a **version** method, so you can verify in your code that in fact you've retrieved the desired distribution release.



Copyright (c) 2014 Sailthru, Inc    
