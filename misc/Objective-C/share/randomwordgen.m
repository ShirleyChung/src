#import <Foundation/Foundation.h>
#import "randomwordgen.h"

@implementation RandomWordGenerator

@synthesize words;

-(id)init
{
	NSError *er = nil;
	NSString *allWords = [NSString stringWithContentsOfFile:@"/usr/share/dict/words"
					encoding:NSUTF8StringEncoding
					error:&er];

	self.words = [allWords componentsSeparatedByString:@"\n"];

	return self;
}

-(NSString*)randomWord
{
	if (! [self.words count] ) return @"no dict exist!";

	int randomIndex = rand() % [self.words count];
	return (NSString*)[words objectAtIndex:randomIndex];
}

-(NSString*)randomWords:(int)number
{
	NSString* sentense = @"";

	if (! [self.words count] ) return @"no dict exist!";

	while(number-->0)
	{
		int randomIndex = rand() % [self.words count];
		sentense = [NSString stringWithFormat:@"%@ %@", sentense, [words objectAtIndex:randomIndex]];	
	}	

	return sentense;
}

@end
