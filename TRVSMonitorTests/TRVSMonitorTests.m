//
//  TRVSXCTestAsyncTests.m
//  TRVSXCTestAsyncTests
//
//  Created by Travis Jeffery on 10/11/13.
//  Copyright (c) 2013 Travis Jeffery. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "TRVSMonitor.h"

@interface TRVSMonitorTests : XCTestCase

@property (nonatomic, strong, readwrite) TRVSMonitor *monitor;

@end

@implementation TRVSMonitorTests

- (void)testExpectedSignalCount {
    self.monitor = [[TRVSMonitor alloc] initWithExpectedSignalCount:3];
    
    [self.monitor waitWithSignalHandler:^(TRVSMonitor *monitor) {
        [self signalAfterTimeInterval:.1];
        [self signalAfterTimeInterval:.1];
        [self signalAfterTimeInterval:.1];
    }];
    
    XCTAssert([self.monitor waitWithTimeout:1]);
}

- (void)testURLSessionTask {
    self.monitor = [[TRVSMonitor alloc] initWithExpectedSignalCount:1];
    [[[NSURLSession sharedSession] dataTaskWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"http://google.com"]] completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        [self.monitor signal];
    }] resume];

    XCTAssert([self.monitor wait]);
}

#pragma mark - Private

- (void)signalAfterTimeInterval:(NSTimeInterval)timeInterval {
    double delayInSeconds = timeInterval;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self.monitor signal];
    });
}

@end
