//
//  STEvent.h
//  libSailthru
//
//  Copyright (c) 2013-2014 Sailthru, Inc. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

// NOTE: You need to have one tag, an event, or a url set on an Event for the SDK to send it.


/** 
 Unfortunately, Xcode will not process doxygen comments for class methods, so this note will have to suffice.
 
 Tags: each tag is processed by Sailthru:
 - the string is trimmed, that is leading and trailing white space is removed
 - all underscores, non-alphanumeric characters, and remaining whitespace get converted to dashes
 - all upper case characers are converted to lower case
 - if the result is a number, or starts with a number, it's discarded
 - finally, if the resultant string is longer than 32 characters, its truncated to that length
 
 More information on tags can be found here:
 http://getstarted.sailthru.com/documentation/products/horizon-data-collection/horizon-meta-tags
*/

@interface STEvent : NSObject

// Common factory methods.

// - an event with a list of interesting tags
+ (STEvent *)eventWithTags:(NSArray *)tags;	// Event with just tags
+ (STEvent *)eventWithTags:(NSArray *)tags location:(CLLocationCoordinate2D)location; // "tags" are required, URL optional

// - a typed event with optional URL and location.
// NOTE: URLs may get spidered to other users - they are not just local to the current user.
+ (STEvent *)eventWithURL:(NSString *)url; 
+ (STEvent *)eventWithURL:(NSString *)url location:(CLLocationCoordinate2D)location; // name is required, URL optional

/**
 Add one tag to an existing tag-style event
*/
- (BOOL)addTag:(NSString *)tag;		// returns NO if you try to add a tag to a URL style message
/**
 Add one or more tags to an existing tag-style event
*/
- (BOOL)addTags:(NSArray *)tags;	// returns NO if you try to add tags to a URL style message
/**
 Retrieve all tags currently contained in this event.
*/
- (NSArray *)tags;					// curious what other classes added?

/**
 Send the Event to Sailthru.
 @returns Only @a NO if there are no tags or a URL attached to the event. If @a NO, the event will not be sent.
 @note Queues the message for transmission, which happens sometime later.
*/
- (BOOL)send;

/*
 Descriptive information about this event.
*/
- (NSString *)description;			// you can log the current event using NSLog(@"Current Event: %@", stEvent);

@end

