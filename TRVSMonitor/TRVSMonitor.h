//
//  TRVSMonitor.h
//
//  Created by Travis Jeffery on 10/11/13.
//  Copyright (c) 2013 Travis Jeffery. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TRVSMonitor;

typedef void (^TRVSMonitorHandler)(TRVSMonitor *monitor);

/// A synchronization construct with the ability to wait until signalled that a condition has been met.
/**
 Can be used more than once
 */
@interface TRVSMonitor : NSObject

/**
 Creates an instance of TRVSMonitor with `init`
 
 @see init
 @see initWithExpectedSignalCount:
 */
+ (instancetype)monitor;

/**
 Calls `initWithExpectedSignalCount:` with `expectedSignalCount` being 1
 
 @see monitor
 @see initWithExpectedSignalCount:
 */
- (instancetype)init;

/// Creates an instance with a given number of signal counts.
/**
 
 @param expectedSignalCount the amount of `signal` calls it will `wait` for
 
 @see monitor
 @see init
 @see wait
 @see waitWithTimeout:
 @see waitWithSignalHandler:
 @see waitWithTimeout:signalHandler:
 @see signal
 */
- (instancetype)initWithExpectedSignalCount:(NSInteger)expectedSignalCount;

/// Waits for all expected amount of signals to be called
/**
 @returns a boolean whether all signals were called

 @see signal
 @see waitWithTimeout:
 @see waitWithSignalHandler:
 @see waitWithTimeout:signalHandler:
 */
- (BOOL)wait;

/// Waits for all expected amount of signals to be called or will timeout
/**
 @param timeout an amount of time to wait in seconds

 @returns a boolean whether all signals were called
 
 @see signal
 @see wait
 @see waitWithSignalHandler:
 @see waitWithTimeout:signalHandler:
 */
- (BOOL)waitWithTimeout:(NSTimeInterval)timeout;

/// Waits for all expected amount of signals to be called
/**
 @param handler a block that wil be called repeatably and passes in a `TRVSMonitor`
 
 @returns a boolean whether all signals were called
 
 @see signal
 @see wait
 @see waitWithTimeout:
 @see waitWithTimeout:signalHandler:
 */
- (BOOL)waitWithSignalHandler:(TRVSMonitorHandler)handler;

/// Waits for all expected amount of signals to be called or will timeout
/**
 @param timeout an amount of time to wait in seconds
 @param handler a block that wil be called repeatably and passes in a `TRVSMonitor`
 
 @returns a boolean whether all signals were called
 
 @see signal
 @see wait
 @see waitWithTimeout:
 @see waitWithSignalHandler:
 */
- (BOOL)waitWithTimeout:(NSTimeInterval)timeout signalHandler:(TRVSMonitorHandler)handler;

/// Reduces the count of remaining signals
/**
 @see initWithExpectedSignalCount:
 @see wait
 @see waitWithTimeout:
 @see waitWithSignalHandler:
 @see waitWithTimeout:signalHandler:
 */
- (void)signal;
@end
