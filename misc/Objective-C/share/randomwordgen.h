#import <Foundation/Foundation.h>

@interface RandomWordGenerator:NSObject
{
@protected
	NSArray* words;
}

@property (nonatomic, retain) NSArray* words;

-(id)init;

-(NSString*)randomWord;

-(NSString*)randomWords:(int)number;

@end
