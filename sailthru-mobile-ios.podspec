Pod::Spec.new do |s|
  s.name                  = 'sailthru-mobile-ios'
  s.license               = { :type => 'Apache License, Version 2.0', :file => 'LICENSE.txt' }
  s.homepage              = 'https://github.com/sailthru/sailthru-mobile-ios'
  s.author                = "Sailthru, Inc"
  s.version               = '3.2.8'
  s.summary               = 'Supports Sailthru Push Notifications and Analytics.'
  s.platform              = :ios
  s.ios.deployment_target = '7.0'
  s.source                = { :git => 'https://github.com/sailthru/sailthru-mobile-ios.git', :tag => s.version.to_s }
  s.requires_arc          = true

  s.source_files = "*.h"
  s.preserve_paths = 'libSailthru.a'
  s.library = 'Sailthru'
  s.framework = 'UIKit'

  #s.preserve_path         = "libSailthru*"
  #s.ios.vendored_libraries      = "libSailthru*"
  #s.library               = 'Sailthru'

  s.xcconfig              = { 'LIBRARY_SEARCH_PATHS' => '$(SRC_ROOT)/Pods/sailthru-mobile-ios/' }

  s.description           = <<-DESC
The SailthruSDK is provided to current Sailthru, Inc clients who have an iOS App. Clients
can use the SDK to register a user with Sailthru, and thus create the linkage necessary to 
support push notifications. The client app may optionally send tracking information, by sending
in tags and URLs, and obtain recommendations (URLs) to show the user as desired.
DESC
end
