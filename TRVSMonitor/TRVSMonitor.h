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
 @note Can be used more than once
 */
@interface TRVSMonitor : NSObject

/// Creates an instance with expect signal count of 1
/**
 @returns an instance of TRVSMonitor
 */
+ (instancetype)monitor;

/// Creates an instance with expected signal count of 1
/**
 @returns an instance of TRVSMonitor
 */
- (instancetype)init;

/// Creates an instance with an expected signal count
/**
 @param expectedSignalCount the total amount of signals to be expected to be received
 @returns an instance of TRVSMonitor
 */
- (instancetype)initWithExpectedSignalCount:(NSInteger)expectedSignalCount;

/// Blocks the current thread until the expected amount of signals to be called
/**
 @returns YES when all signals have be received
 */
- (BOOL)wait;

/// Blocks the current thread until expected amount of signals is received or certain amount of time has passed
/**
 @param timeout an amount of time to wait in seconds

 @returns a boolean whether all signals were called
 */
- (BOOL)waitWithTimeout:(NSTimeInterval)timeout;

/// Blocks the current thread until the expected amount of signals is received
/**
 @param handler a block that wil be called repeatably and passes in a `TRVSMonitor`
 
 @returns a boolean whether all signals were called
 */
- (BOOL)waitWithSignalHandler:(TRVSMonitorHandler)handler;

/// Blocks the current thread until expected amount of signals is received or certain amount of time has passed
/**
 @param timeout an amount of time to wait in seconds
 @param handler a block that wil be called repeatably and passes in a `TRVSMonitor`
 
 @returns a boolean whether all signals were called
 */
- (BOOL)waitWithTimeout:(NSTimeInterval)timeout signalHandler:(TRVSMonitorHandler)handler;

/// Fires a signal
- (void)signal;
@end
