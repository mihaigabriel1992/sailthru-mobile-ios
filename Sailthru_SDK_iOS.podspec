Pod::Spec.new do |s|
  s.name                  = 'Sailthru_SDK_iOS'
  s.license               = 'LICENSE.txt'
  #s.license               = 'Apache License, Version 2.0'
  #s.license               = { :type => 'Apache License, Version 2.0' }
  #s.license               = 'BSD'
  s.version               = '3.2.6'
  s.summary               = 'Supports Sailthru Push Notifications and Analytics.'
  s.homepage              = 'https://github.com/sailthru/sailthru-mobile-ios'
  s.author                = "Sailthru, Inc"
  s.platform              = :ios
  s.ios.deployment_target = '7.0'
  #s.source                = { :git => 'https://github.com/sailthru/sailthru-mobile-ios.git', :branch => 'master', :tag => "v" +  s.version.to_s }
  s.source                = { :git => 'https://github.com/sailthru/sailthru-mobile-ios.git', :tag => 'v3.2.6' }
  s.requires_arc          = true
  #s.public_header_files   = "Headers/Public/*.h"
  s.default_subspec       = 'iOS7'
  s.subspec 'iOS7' do |sp|
    sp.source_files        = 'SailthruSDKdemoManual/SailThruSDK/*.h'
    sp.preserve_paths      = 'SailthruSDKdemoManual/SailThruSDK/README'
	sp.ios.vendored_library = 'SailthruSDKdemoManual/SailThruSDK/iOS7/libSailthru.a'
    sp.library             = 'Sailthru'
    sp.xcconfig            = { 'LIBRARY_SEARCH_PATHS' => '$(SRC_ROOT)/Pods/Sailthru_SDK_iOS/SailthruSDKdemoManual/SailThruSDK/iOS7' }
    sp.frameworks          = 'Foundation', 'UIKit'
    sp.platform              = :ios
    sp.ios.deployment_target = '7.0'
  end

  s.subspec 'iOS6' do |sp|
    sp.source_files        = 'SailthruSDKdemoManual/SailThruSDK/*.h'
    sp.preserve_paths      = 'SailthruSDKdemoManual/SailThruSDK/README'
	sp.ios.vendored_library = 'SailthruSDKdemoManual/SailThruSDK/iOS7/libSailthru.a'
    sp.library             = 'Sailthru'
    sp.xcconfig            = { 'LIBRARY_SEARCH_PATHS' => '$(SRC_ROOT)/Pods/Sailthru_SDK_iOS/SailthruSDKdemoManual/SailThruSDK/iOS6' }
    sp.frameworks          = 'Foundation', 'UIKit'
    sp.platform              = :ios
    sp.ios.deployment_target = '6.0'
  end
  s.description           = <<-DESC
The SailthruSDK is provided to current Sailthru, Inc clients who have an iOS App. Clients
can use the SDK to register a user with Sailthru, and thus create the linkage necessary to 
support push notifications. The client app may optionally send tracking information, by sending
in tags and URLs, and obtain recommendations (URLs) to show the user as desired.
DESC
end
