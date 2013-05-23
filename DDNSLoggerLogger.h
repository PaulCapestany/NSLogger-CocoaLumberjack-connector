//
//  DDNSLoggerLogger.h
//  Created by Peter Steinberger on 26.10.10.
//

#import <Foundation/Foundation.h>
#import "DDLog.h"

@interface DDNSLoggerLogger : DDAbstractLogger <DDLogger>
{
}

// First undefine the default CocoaLumberjack stuff we don't want to use.

#undef LOG_FLAG_ERROR
#undef LOG_FLAG_WARN
#undef LOG_FLAG_INFO
#undef LOG_FLAG_VERBOSE

#undef LOG_LEVEL_ERROR
#undef LOG_LEVEL_WARN
#undef LOG_LEVEL_INFO
#undef LOG_LEVEL_VERBOSE

#undef LOG_ERROR
#undef LOG_WARN
#undef LOG_INFO
#undef LOG_VERBOSE

#undef DDLogError
#undef DDLogWarn
#undef DDLogInfo
#undef DDLogVerbose

#undef DDLogCError
#undef DDLogCWarn
#undef DDLogCInfo
#undef DDLogCVerbose

// ???: probably should have a different fix for this
#define LOG_FLAG_WARN    (1 << 9) // temp fix to prevent error from CocoaLumberjack RE: colors

// Now define everything how we want it

// *************************
// * LOG FLAGS (aka, Tags) *
// *************************
// TODO: keep improving the log flag vs. log level distinctions as the need arises
#define LOG_FLAG_ERROR   (1 << 0) // 0000000001
#define LOG_FLAG_REPORT  (1 << 1) // 0000000010
#define LOG_FLAG_FUNC    (1 << 2) // 0000000100
#define LOG_FLAG_LOG     (1 << 3) // 0000001000
//---------------------------------------------
#define LOG_FLAG_VIEW    (1 << 4) // 0000010000
#define LOG_FLAG_DATA    (1 << 5) // 0000100000
#define LOG_FLAG_ACTION  (1 << 6) // 0001000000
//---------------------------------------------

// **************
// * LOG LEVELS *
// **************
#define LOG_LEVEL_ERROR  (LOG_FLAG_ERROR)                                                       // 0000000001
#define LOG_LEVEL_REPORT (LOG_FLAG_REPORT | LOG_LEVEL_ERROR)                                    // 0000000011
#define LOG_LEVEL_FUNC   (LOG_FLAG_FUNC   | LOG_LEVEL_REPORT)                                   // 0000000111
#define LOG_LEVEL_LOG    (LOG_FLAG_LOG    | LOG_LEVEL_FUNC)                                     // 0000001111
#define LOG_FLAG_ALL     (LOG_FLAG_VIEW   | LOG_FLAG_DATA  | LOG_FLAG_ACTION | LOG_LEVEL_LOG)   // 1001111111
#define LOG_LEVEL_ALL    (LOG_FLAG_ALL)                                                         // 1001111111

#define LOG_ERROR        (ddLogLevel & LOG_FLAG_ERROR)
#define LOG_REPORT       (ddLogLevel & LOG_FLAG_REPORT)
#define LOG_FUNC         (ddLogLevel & LOG_FLAG_FUNC)
#define LOG_LOG          (ddLogLevel & LOG_FLAG_LOG)
//---------------------------------------------
#define LOG_VIEW         (ddLogLevel & LOG_FLAG_VIEW)
#define LOG_DATA         (ddLogLevel & LOG_FLAG_DATA)
#define LOG_ACTION       (ddLogLevel & LOG_FLAG_ACTION)
//---------------------------------------------
#define LOG_ALL          (ddLogLevel & LOG_FLAG_ALL)

#define PCLogError(frmt, ...)  SYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_ERROR,  0, frmt, ## __VA_ARGS__)
#define PCLogReport(frmt, ...) SYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_REPORT,  0, frmt, ## __VA_ARGS__)
#define PCLogFunc(frmt, ...)   ASYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_FUNC,   0, frmt, ## __VA_ARGS__)
#define PCLog(frmt, ...)       ASYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_LOG, 0, frmt, ## __VA_ARGS__)
#define PCLogView(frmt, ...)   ASYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_VIEW,   0, frmt, ## __VA_ARGS__)
#define PCLogData(frmt, ...)   ASYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_DATA,  0, frmt, ## __VA_ARGS__)
#define PCLogAction(frmt, ...) ASYNC_LOG_OBJC_MAYBE(ddLogLevel, LOG_FLAG_ACTION,  0, frmt, ## __VA_ARGS__)


+ (DDNSLoggerLogger *)sharedInstance;

// Inherited from DDAbstractLogger

// - (id <DDLogFormatter>)logFormatter;
// - (void)setLogFormatter:(id <DDLogFormatter>)formatter;

@end
