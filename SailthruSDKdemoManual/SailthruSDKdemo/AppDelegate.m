//
//  AppDelegate.m
//  SailthruSDKdemo
//
//  Copyright (c) 2013-2014 Sailthru, Inc. All rights reserved.
//

#import "AppDelegate.h"
#import "SailthruSDK.h"

#import "ViewController.h"

// These routines here only for this demo - you do not need this code in your app.
// Since this app cannot really get a push token, it converts a real one we got during texting,
// saved as a string - but the SDK needs the token as a NSData object, just as iOS delivers it.
static NSString __attribute__((unused)) *dataToHex(NSData *data)
{
    NSMutableString *str    = [NSMutableString stringWithCapacity:100];
    const unsigned char *p  = data.bytes;
    NSUInteger len          = data.length;
    
    for(NSUInteger i = 0; i < len; ++i)
        [str appendFormat:@"%02.2X", p[i]];
    
    return [str copy];
}

static NSData __attribute__((unused)) *hexToData(NSString *str)
{
    const char *ptr     = [str cStringUsingEncoding:NSASCIIStringEncoding];
    NSUInteger len      = str.length / 2;
    NSMutableData *data = [NSMutableData dataWithCapacity:len];
    
    while(len--)
    {
        char num[5] = (char[]){ '0', 'x', 0, 0, 0 };
        num[2]      = *ptr++;
        num[3]      = *ptr++;
        uint8_t n   = (uint8_t)strtol(num, NULL, 0);
        
        [data appendBytes:&n length:1];
    }
    
    return [data copy];
}

@interface AppDelegate ()
{
	STManager *stManager;
}

@end

@interface AppDelegate (STManagerDelegate) <STManagerDelegate>
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	stManager = [STManager sailthruManagerWithDelegate:self];
	stSetLogThreshold(STLogTypeInformative);	// the default is stCritical, set it to informative to see what the SDK is doing
	
	NSDictionary *pushDict =launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey];
	[self handlePushNotification:pushDict isBooting:YES];	// handles case of null push dictionary

	[[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
		
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
	self.viewController = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
	self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

// Example Code
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
	NSLog(@"DID REGISTER DEVICE TOKEN [len = %zd] %@", [deviceToken length], deviceToken);
	
	NSString *token = dataToHex(deviceToken);
	UIPasteboard *pb = [UIPasteboard generalPasteboard];
	[pb setString:token];

	UIAlertView *v = [[UIAlertView alloc] initWithTitle:@"Token Received!" message:@"Its on the clipboard - paste it into a mail to yourself" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[v show];

// We really suggest using this strategy. Set a build flag so when building for the app store you
// have the proper options set.
#ifdef DEPLOYMENT					// See the Target build setting, Preprocessing
	STSDKMode apnsMode = STSDKModeProduction;
	NSString *appID		= @"1234567890ABCD";			// the string returned by Sailthru when you register your app
#else
	STSDKMode apnsMode = STSDKModeDevelopement;
	NSString *appID		= @"DCBA9876543210";			// the string returned by Sailthru when you register your app
	#warning Sailthru Registration using Development Mode.	// nice trick for Development builds - you won't see any warning in a Production build.
#endif
	
	// assume you have the user's ID at this time - if not just wait til you get it
	NSString *uid		= @"fred@gmail.com";
	NSString *domain	= @"myHorizonDomain";
	NSString *apiKey	= @"Your Company's api_key";

	// after this it will be possible to push notifications from Sailthru to the user
	BOOL ret = [stManager registerUsingSDKMode:apnsMode horizonDomain:domain apiKey:apiKey appID:appID userIDtype:STUserTypeMail userID:uid token:deviceToken];

	assert(ret); // in development, treat a failure here as a hard hard error!
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
	NSLog(@"YIKES! registration failed!!! Error: %@", error);
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
	NSLog(@"WOW: got notification! state=%zd %@", [[UIApplication sharedApplication] applicationState], userInfo);
	
	[UIApplication sharedApplication].applicationIconBadgeNumber = 0;	// probably redundant

	[self handlePushNotification:userInfo isBooting:NO];
}

// Single handler for push notifications
- (BOOL)handlePushNotification:(NSDictionary *)dict isBooting:(BOOL)booting
{
	if(!dict) return NO;

	// important to do this - it lets the SDK tag future events to the embedded "push ID"
	dict = [stManager didReceiveRemoteNotification:dict isBooting:(BOOL)booting];

	BOOL ret = NO;
	NSLog(@"PUSH NOTIFICATION ============================ boot=%d dict: %@", booting, dict);
	
	NSDictionary *dict2 = (NSDictionary *)(dict[@"aps"]);
	NSString *msg = dict2[@"alert"];
	if(msg) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"PUSH NOTIFICATION" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
		[alert show];
	}
	return ret;
}

@end

@implementation AppDelegate (STManagerDelegate)

- (void)registrationSucceeded:(BOOL)success error:(NSString *)errorMsg
{
	// You should get success==YES if all info entered correctly
}

// Sent on the Main Thread after a complex push notification is complete.
- (void)pushNotification:(NSDictionary *)info
{
	// disabled for now - see STManager.h 
}

@end

