#import "person.h"
#import <stdlib.h>

#define MAX_WORDS_SAYS 20

@implementation Person

@synthesize Name, Address, Environment;

-(id)init
{
	memory = [NSMutableDictionary dictionaryWithCapacity:10];
	wordgen = [[RandomWordGenerator alloc] init];
    return [super init];
}

-(id)initWithName:(NSString*) name{
	Name = name;
    return [self init];
}

-(void)whereRUfrom
{
	if (0 == [Address length])
		NSLog(@"I don't know...\n");
	else
		NSLog(@"I come from %@", Address);
}

-(void)sayHi
{
	NSLog(@"Hi!!! my name is %@", Name);
}

-(void)start
{
	NSThread* thread = [[NSThread alloc] initWithTarget:self selector:@selector(thinking) object:nil];

	[thread start];	
}

-(void)interactWith:(NSMutableDictionary*)environment
{
	NSThread* thread = [[NSThread alloc] initWithTarget:self selector:@selector(talking:) object:environment];

	[thread start];	
}

-(void)talking:(NSMutableDictionary*)environment
{
ARC_BEGIN
	time_t tm;
    srand((unsigned int)time(&tm));
    NSDateFormatter *df = [[NSDateFormatter alloc] init];
    [df setTimeZone: [NSTimeZone localTimeZone]];
    [df setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    
	while(1)
	{
		if (rand()%2)
		{
			NSString *whatisay = [self say];
			NSLog(@"I say: %@", whatisay);
			[environment setValue:whatisay forKey:[df stringFromDate:[NSDate date]]];
		}
		[NSThread sleepForTimeInterval:2];
	}
ARC_END
}

-(NSString*)say
{
	int words_to_say = rand() % MAX_WORDS_SAYS;
	return [wordgen randomWords: words_to_say];
}

-(void)thinking
{
ARC_BEGIN
	time_t tm;
    srand((unsigned int)time(&tm));
	while(1)
	{
		NSLog(@"I'm thinking...\n");
		if (rand()%2)
			NSLog(@"I say: %@", [self say]);
		[NSThread sleepForTimeInterval:2];
	}
ARC_END
}

-(void)remember:(NSString*) words
{
	NSNumber *num = [NSNumber numberWithInt:1];
	[memory setObject:num forKey:words];
}

@end
