//
//  STLog.h
//  Logger
//
//  Copyright (c) 2013 Sailthru, Inc.. All rights reserved.
//

// If you'd like to receive the log messages and deal with them yourself, make yourself the delegate
@protocol STLogging <NSObject>

- (void)logStMessage:(NSString *)msg;

@end

// Users can get more or less information as desired.
typedef enum { stError=-1, stInformative=1, stWarning, stHard, stCatastrophic, stDisableLogging } stLogType;

// Default is stCatastrophic. Returns the old value if the new one is within range, or stError otherwise.
stLogType stSetLogThreshold(stLogType t);

// A weak reference to logger is kept
void stSetLogger(id <STLogging> logger);
