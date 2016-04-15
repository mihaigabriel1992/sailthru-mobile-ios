Pod::Spec.new do |s|
  s.name                  = 'Sailthru_SDK_iOS'
  s.license               = { :type => 'Apache License, Version 2.0', :file => 'LICENSE.txt' }
  s.version               = '3.8.1'
  s.summary               = 'Supports Sailthru Push Notifications and Analytics.'
  s.homepage              = 'https://github.com/sailthru/sailthru-mobile-ios'
  s.author                = { 'Sailthru, Inc' => 'mobile@sailthru.com' }
  s.platform              = :ios
  s.ios.deployment_target = '8.0'
  s.source                = { :git => 'https://github.com/sailthru/sailthru-mobile-ios.git', :branch => 'master', :tag => "v" +  s.version.to_s }
  s.requires_arc          = true
  s.default_subspec       = 'ios8+'
  s.subspec 'ios8+' do |sp|
    sp.source_files        = "SailThruSDK/*.h"
    sp.preserve_paths      = 'SailThruSDK/README', 'SailThruSDK/ios8+/libSailthru.a'
	sp.ios.vendored_library = 'SailThruSDK/ios8+/libSailthru.a'
    sp.library             = 'Sailthru'
    sp.xcconfig            = { 'LIBRARY_SEARCH_PATHS' => '$(PODS_ROOT)/Sailthru_SDK_iOS/SailThruSDK/ios8+' }
    sp.frameworks          = 'Foundation', 'SystemConfiguration'
    sp.platform              = :ios
    sp.ios.deployment_target = '8.0'
  end

  s.description           = <<-DESC
The SailthruSDK is provided to current Sailthru, Inc clients who have an iOS App. Clients
can use the SDK to register a user with Sailthru, and thus create the linkage necessary to 
support push notifications. The client app may optionally send tracking information, by sending
in tags and URLs, and obtain recommendations (URLs) to show the user as desired.
DESC
end
