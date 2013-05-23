# NSLogger-CocoaLumberjack-connector #

This is a bridge for the projects

* http://github.com/robbiehanson/CocoaLumberjack
(A general purpose superfast logging framework)

and

* http://github.com/fpillet/NSLogger
(send logs to a client app via network)


Just add this code to the logger initializer in your app delegate:

`[DDLog addLogger:[DDNSLoggerLogger sharedInstance]];`


# Tricks & Tips #

To find the beginning of any Objective-C function, just run the following regex (since Xcode doesn't support multiline regexes, you'll have to use something that does, e.g. Sublime Text):

    ((^(\+[ ]?\(|-[ ]?\()[a-z0-9_ \*]*\)[a-z0-9_:\(\) \*<>\t\n\r]*)(\{))
    
...and the following could then be used to insert a log statement into every single function:

    
    \1
        PCLogFunc(@"◀ BEG ▶");

This ends up being a quick way to help visualize what's going on in someone else's code.


*...more to come...*