//
//  STLog.h
//  Logger
//
//  Copyright (c) 2013-2014 Sailthru, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma clang assume_nonnull begin
#if ! __has_feature(nullability)
#define nullable
#define __nullable
#endif

// If you'd like to receive the log messages and deal with them yourself, make yourself the delegate
@protocol STLogging <NSObject>

- (void)logStMessage:(NSString *)msg;	// may arrive from any thread - dispatch to main queue if required.

@end

// Users can get more or less information as desired.

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
void stSetLogger(__nullable id <STLogging> logger);

#pragma clang assume_nonnull end
