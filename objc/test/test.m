#import <Foundation/Foundation.h>

#import "../share/person.h"
#import "../share/webreader.h"
#import "../share/stem.h"
#import "../share/bluetooth.h"

NSString* testLoad(NSString* file)
{
        NSError* err = nil;
        NSURL* url = [[NSURL alloc] initWithString:file];
        
        NSString* text = [[NSString alloc] initWithContentsOfURL:url
                encoding:NSUTF8StringEncoding error:&err];

	return (text)? text: [err localizedDescription];
}

void testSave(NSString* file, NSString* text)
{
	NSError* err = nil;
	[text writeToFile:file atomically:YES encoding:NSUTF8StringEncoding error:&err];
	
	if (err) NSLog(@"file: %@ write error:%@", file, [err localizedDescription]);
}

bool testReader()
{
	WebReader* wr = [[WebReader alloc] init];
	NSLog(@"web reader:%@", [wr randomGetAWord]);	
	return true;
}

void testPerson()
{
	NSMutableDictionary *env = [[NSMutableDictionary alloc] init];
	Person* p = [[Person alloc] initWithName:@"micky"];
	
	[p interactWith:env];

	RandomWordGenerator* rwg = [[RandomWordGenerator alloc] init];
	NSLog(@"random: %@, conut words:%d", [rwg randomWord], [rwg.words count]);
	testSave(@"test.txt", [rwg randomWord]);

	NSDateFormatter *df = [[NSDateFormatter alloc] init];
	[df setTimeZone:[NSTimeZone localTimeZone]]; 
	[df setDateFormat:@"yyyy-MM-dd HH:mm:ss"];

	int count = 10;
	while(count-- >0)
	{
		NSLog(@"[%@] world is waiting guys...:\n", [df stringFromDate:[NSDate date]]);
		[NSThread sleepForTimeInterval:10];
	}
}

int main(void)
{
NSAutoreleasePool *myPool = [[NSAutoreleasePool alloc] init];

        NSString* file = @"file:/home/shirley/hello.txt";
        NSLog(@"load:%@ = %@\n", file, testLoad(file));
	NSLog(@"test=%@\n", testLoad(@"123"));
	NSLog(@"from book author: %@\n", testLoad(@"http://www.appsmith.dk/chp12.txt"));

	testReader();
	testPerson();

[myPool drain];
	return 0;
}
