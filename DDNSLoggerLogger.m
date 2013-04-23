//
//  DDNSLoggerLogger.m
//  Created by Peter Steinberger on 26.10.10.
//

#import "DDNSLoggerLogger.h"

// NSLogger is needed: http://github.com/fpillet/NSLogger
#import "LoggerClient.h"

@implementation DDNSLoggerLogger

static DDNSLoggerLogger *sharedInstance;

// The logger instance we use
static Logger *_DDNSLogger_logger = nil;

/**
 * The runtime sends initialize to each class in a program exactly one time just before the class,
 * or any class that inherits from it, is sent its first message from within the program. (Thus the
 * method may never be invoked if the class is not used.) The runtime sends the initialize message to
 * classes in a thread-safe manner. Superclasses receive this message before their subclasses.
 *
 * This method may also be called directly (assumably by accident), hence the safety mechanism.
 **/
+ (void)initialize
{
	static BOOL initialized = NO;
	if (!initialized)
	{
		initialized = YES;

		sharedInstance = [[DDNSLoggerLogger alloc] init];
	}
}

+ (DDNSLoggerLogger *)sharedInstance
{
	return sharedInstance;
}

- (id)init
{
	if (sharedInstance != nil)
	{
		return nil;
	}

	if ((self = [super init]))
	{
    // create and remember the logger instance
    _DDNSLogger_logger = LoggerInit();

    // configure the logger
    LoggerSetOptions(_DDNSLogger_logger, kLoggerOption_BufferLogsUntilConnection | kLoggerOption_BrowseBonjour | kLoggerOption_BrowseOnlyLocalDomain );
    LoggerStart(_DDNSLogger_logger);
	}
	return self;
}

- (void)logMessage:(DDLogMessage *)logMessage
{
	NSString *logMsg = logMessage->logMsg;
    NSString *newLogMsg;
    NSString *theClass;
    
	if (formatter)
	{
        // formatting is supported but not encouraged!
		logMsg = [formatter formatLogMessage:logMessage];
    }

    if (logMsg) {
        NSString *nsloggerLogTag;
        
        switch (logMessage->logFlag) {
                // NSLogger log levels start a 0, the bigger the number,
                // the more specific / detailed the trace is meant to be
            case LOG_FLAG_ERROR: nsloggerLogTag = @"❰ Error ❱"; break;
            case LOG_FLAG_REPORT: nsloggerLogTag = @"❰ Report ❱"; break;
            case LOG_FLAG_FUNC: nsloggerLogTag = @"❰ Function ❱";
                theClass = [NSString stringWithFormat:@"%@ %@", [@"" stringByPaddingToLength:30 - logMessage.fileName.length withString: @" " startingAtIndex:0], logMessage.fileName];
                newLogMsg = [NSString stringWithFormat:@"%@ ★ %@", theClass, logMessage.methodName];
                break;
            case LOG_FLAG_LOG: nsloggerLogTag = @"❰ Log ❱"; break;
            case LOG_FLAG_VIEW: nsloggerLogTag = @"❰ View ❱"; break;
            case LOG_FLAG_DATA: nsloggerLogTag = @"❰ Data ❱"; break;
            case LOG_FLAG_ACTION: nsloggerLogTag = @"❰ Action ❱"; break;
            default: nsloggerLogTag = @"❰ Default ❱"; break;
        }
        
        int nsloggerLogLevel;
        switch (logMessage->logLevel) {
                // NSLogger log levels start a 0, the bigger the number,
                // the more specific / detailed the trace is meant to be
            case LOG_LEVEL_ERROR: nsloggerLogLevel = 0; break;
            case LOG_LEVEL_REPORT: nsloggerLogLevel = 1; break;
            case LOG_LEVEL_FUNC: nsloggerLogLevel = 2; break;
            case LOG_LEVEL_LOG: nsloggerLogLevel = 3; break;
            default: nsloggerLogLevel = 4; break;
        }
        
        if (newLogMsg) {
            LogMessageF(logMessage->file, logMessage->lineNumber, logMessage->function, nsloggerLogTag,
                        nsloggerLogLevel, @"%@", newLogMsg);
        } else {
            LogMessageF(logMessage->file, logMessage->lineNumber, logMessage->function, nsloggerLogTag,
                        nsloggerLogLevel, @"%@", logMsg);
        }
    }
}

- (NSString *)loggerName
{
	return @"cocoa.lumberjack.NSLogger";
}

@end
