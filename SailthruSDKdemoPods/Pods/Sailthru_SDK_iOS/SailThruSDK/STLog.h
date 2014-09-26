//
//  STLog.h
//  Logger
//
//  Copyright (c) 2013-2014 Sailthru, Inc. All rights reserved.
//

// If you'd like to receive the log messages and deal with them yourself, make yourself the delegate
@protocol STLogging <NSObject>

- (void)logStMessage:(NSString *)msg;	// may arrive from any thread - dispatch to main queue if required.

@end

// Users can get more or less information as desired.

typedef enum {
	stError=-1,
	stInternal=0,
	stInformative,
	stWarning,
	stHard,
	stCatastrophic,
	stDisableLogging
} stLogType __attribute__((deprecated("Use 'STLogType' (Swift Friendly)")));

typedef NS_ENUM(NSInteger, STLogType) {
   STLogTypeError		= -1,
   STLogTypeInternal	= 0,
   STLogTypeInformative,
   STLogTypeWarning,
   STLogTypeHard,
   STLogTypeCatastrophic,
   STLogTypeDisableLogging
};


// Default is stCatastrophic. Returns the old value if the new one is within range, or stError otherwise.
STLogType stSetLogThreshold(STLogType t);

// A weak reference to logger is kept
void stSetLogger(id <STLogging> logger);
