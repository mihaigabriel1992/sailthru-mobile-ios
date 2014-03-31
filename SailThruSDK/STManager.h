//
//  STManager.h
//  libSailthru
//
//  Copyright (c) 2013-2014 Sailthru, Inc. All rights reserved.
//

// Reachability flags
#define kSailthruUp				@"sailthruUp"
#define kInternetUp				@"internetUp"

typedef enum {
	STEAnonIdentifier=1,	///< An anonymous account—no email yet
	STEMailIdentifier		///< Parameter will be an email address in the familiar 'name@@account' format
} STUserIdentifier;

/**
 Tracking information is tagged with the Push ID until the app backgrounds,
 a time period is exceeded, or your app removes the tagging explicitly.
*/
typedef enum {
	stUntilBackgrounded,	///< When the user switches to another app - the default
	st05minutes,			///< 5 minutes after the push note is received
	st15minutes,			///< 15 minutes after the push note is received,
	st60minutes,			///< One hour
	st24hours,				///< One day

	stPushNotePerEnd		///< just marks the end of the enumeration
} STPushNotePersistence;

typedef enum {
	stDevelopmentMode,		// Development APNS
	stProductionMode		// Production APNS
} STPushNoteMode;

/**
 Allows the Sailthru SDK to advise you of various events.
 All messages are sent on the main queue.
*/
@protocol STManagerDelegate <NSObject>
/**
 This method was renamed \b pleaseRegisterWithoutPushToken, please switch
 to using it.
 */
@optional
- (void)pleaseRegisterWithoutPushToken __attribute__((deprecated("Renamed as \"pleaseRegisterWithoutUserID\"")));
@required
/**
 If you tried to register for push notifications on launch, but
 for whatever reason the device cannot connect with an APN server,
 no error message is sent (by Apple). Sailthru sends this delegate message
 after 1 minute if you do not attempt to register, and every minute thereafter,
 until you call finally send it
 a register message.
@note
 If you wish to shut this message off, then send the @a registerUsingMode: message with a
 nil token—all other parameters are ignored.
*/
- (void)pleaseRegisterWithoutUserID;

/**
 Sent after the registration with Sailthru completes. If all parameters were
 correct, then success should be @b YES otherwise @b errorMsg
 will provide the reason.
 @param success - did register succeed and return an HID
 @param errorMsg - if success is @b NO</b>, then this string gives you a reason.
 There are only a small number of cases that can result in failure. The best strategy
 for these are to log them to your web site and notify Sailthru with the exact message.
 @note The SDK will continue to try to perform registration on network failures and timeouts.
 If you send a \i registerUsingMode:</a> message before an earlier one
 has sent this delegate message, you may or may not get the first message before the latter.
 */
- (void)registrationSucceeded:(BOOL)success error:(NSString *)errorMsg;

@optional

/**
 Issued when the status of the cellular or wifi network changes - you can examine
 the three properties below to see what changed.
*/
- (void)internetStatusChanged;

/**
 Mostly for Sailthru internal debugging—sent when all pending events have been successfully
 transferred to Sailthru.
 @note It's possible to get more than one such message when the queue drains.
*/
- (void)messageQueueDrained;

/**
 Mostly for debugging—indicates the SDK has dissassociated the last pushID from outgoing tracking events.
*/
- (void)pushNoteDisassociated;

/**
 Delegate response to the @a recommend:</a> message. Network errors or an inoperable network return an error.
 @param items An array of one or more NSDictionaries.
 @param error If the request failed, and items is nil, then some reason.
 @return Each dictionary in @a items contains some or all of the following keys:
 @returns @a consumed: URL previously offered to the user
 @returns @a date: when created (UNIX seconds since 1970 format)
 @returns @a description: a detailed description
 @returns @a heat: the relative popularity of the article on the site
 @returns @a image: array of image URLs, currently "full" and "thumb"
 @returns @a score: the relative weight of the article for the individual user
 @returns @a tags: array of tags applicable to this recommendation
 @returns @a title: suggested title for the URL
 @returns @a url: where to find the recommendation
 @returns @a views: recommended to the user this many times already
 @note If the user account is relatively new, and the Sailthru Recommendation Engine
 has nothing to recommend, an error indication is generated (not an empty items array).


 The recommendation Service is relatively new API and additional keys may appear.
*/
- (void)recommendations:(NSArray *)items error:(NSError *)error;

@end

@interface STManager : NSObject

/**
 Permit the library to use Cellular data. Defaults to YES.
*/
@property (nonatomic, assign) BOOL useCellular __attribute__((deprecated("iOS7 lets users control this")));

// If interested you can query these (they use Apple's 'ReachAbility' class)
@property (nonatomic, assign, readonly) BOOL internetUp;	///< Either wifi or cellular data is available
@property (nonatomic, assign, readonly) BOOL wifiUp;		///< Wifi is available
@property (nonatomic, assign, readonly) BOOL cellularUp;	/** Cellular networking is available */

/*
 Creates the shared instance of the Sailthru Manager.
 @param del The delegate receiving response messages. The delegate is weakly retained.
 @returns The singleton STManager object.
 @note Unfortunately, Xcode won't display class comments: rdar://16252256
*/
+ (instancetype)sailthruManagerWithDelegate:(id <STManagerDelegate>)del;

/*
 After the singleton STManager is created, this method returns it.
 @returns The singleton manager, or @c nil if that was not yet created.
 @note Unfortunately, Xcode won't display class comments: rdar://16252256
*/
+ (instancetype)sailthruManager;

/**
 The means to register an identified or anonymous user.
 
 @param apnsMode Use @a stDevelopmentMode for development and @a stProductionMode for submission
 to the app store. The suggested way to use these in your code is by having some define declared only for
 production builds, and then wrapping a @a STPushNoteMode variable in defines.
 
 @code
 #ifdef DEPLOYMENT
     STPushNoteMode apnsMode = stProductionMode;
	 NSString *appID = @"....";
 #else
     STPushNoteMode apnsMode = stDevelopmentMode;
	 NSString *appID = @"....";
	 #warning Sailthru Registration using Development Mode.
 #endif @endcode
 
 @param domain: The @e Horizon @e Domain, obtained from @e Settings/Setup/Domains on @e my.sailthru.com.
 
 @param apiKey: Your @e API Keyey, obtained from @e Settings/Setup/API&Postback on @e my.sailthru.com.
 
 @param appID Generated by Sailthru when you first registered your application. Production and development
 apps are assigned different values. Available under @e Settings/Channels/MobileApps on @e my.sailthru.com.
 
 @param userIDtype @a STEAnonIdentifier or @a STEMailType.
 
 @param uid When using @a STEMailType, an email address (e.g. @e fred@gmail.com), ignored with @a STEAnonIdentifier.
 
 @param token @a NSData object returned from @a -didRegisterForRemoteNotificationsWithDeviceToken. See @e Notes.
 
 @returns @a YES if all parameters were provided correctly, @a NO otherwise (includeing providing a @a nil token
 to disable the @a pleaseRegisterWithoutUserID messages.
 
 @note If you for any reason decide not to register a user, you can disable the @a pleaseRegisterWithoutUserID
 reminder delegate message by sending the registeration message
 with a @c nil token—all other parameters are ignored. You might want to do this, for instance, during development.
*/
- (BOOL)registerUsingMode:(STPushNoteMode)apnsMode horizonDomain:(NSString *)domain apiKey:(NSString *)apiKey appID:(NSString *)appID userIDtype:(STUserIdentifier)usertype userID:(NSString *)uid token:(NSData *)token;

/** 
 The App must notify the SDK when Sailthru generated push notifications are received.
 @param userInfo The dictionary containing the full push payload.
 @param isBooting If @a YES, this push launched the app.
 @returns The input parameter @a userInfo, unmodified.
 @note If the notification came from Sailthru, an identifier is extracted from the dictionary, 
 which is used to tag subsequent events—otherwise nothing changes.
 The return value may change in the future with @e Rich @e Push.
*/
- (NSDictionary *)didReceiveRemoteNotification:(NSDictionary *)userInfo isBooting:(BOOL)booting;

/**
 Set the desired handling for push notification tagging. All events you send after the initial
 reception of the push notification are tagged with the identifier of the received notification.
 This tagging occurs for some time after the SDK receives the above @a didReceiveRemoteNotification
 message from your client app.
 @param behavior An enumerated lists of events or time expiration that define when tagging stops.
 The default is @a stUntilBackgrounded.
*/
- (void)setEventTaggingBehavior:(STPushNotePersistence)behavior;


/**
 Convenience method to determine the current tagging behavior.
 @returns One of the @a STPushNotePersistence enumerated values.
*/
- (STPushNotePersistence)eventTaggingBehavior;

/**
 Explictly end Push Notificatiopn tagging now.
 @note Has no affect if push notification tagging was inactive.
 If you implement @a pushNoteDisassociated, and notification tagging was active, 
 that message is sent to you. subsequently rece
*/
- (void)resetPushNoteTag;

// Utility Methods

/**
 Query the version.
 @returns The current version number in n.n.n format.
*/
- (NSString *)version;

/**
 Force an immediate update in status for all @a Reachability objects.
 Ignored in the first minute of app launch.
*/
- (void)forceStatusUpdate;

/**
 Access the Horizon Recommendation Service (same as Sailthru's online Recommend service).
 
 @note This message attempts to contact Sailthru regardless of the current @a Reachability state,
 and thus if the network is unavailable you will surely get a failed response.

 @param tags Restrict the recommendations to the provided array of interest tags, or @a nil for no restriction.
 @param count The number of desired recommendations. The parameter is clamped to: 1 <= count <= 100
 @return @a YES if you have implemented the appropriate delegate method.
 The recommendations are returned in a delegate message.
*/
- (BOOL)recommend:(NSArray *)tags count:(NSUInteger)count;

/**
 Path to the Documents directory, to save user important files that cannot be recreated.
 @returns The path as provided by the @a sharedApplication abject
*/
+ (NSString *)applicationDocumentsDirectory;

/**
 Path to the Application Support directory, to save app created files.
 @returns The path as provided by the @a sharedApplication abject.
 @note The directory is created if it hasn't been already.
*/
+ (NSString *)applicationAppSupportDirectory;

/** 
 Convenience method to mark a file or directory located anywhere in the @a Documents folder
 to insure it's not backed up by @a iCloud.
*/
+ (BOOL)markDoNotBackUp:(NSString *)path;

@end
