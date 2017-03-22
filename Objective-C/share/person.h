#import <Foundation/Foundation.h>
#import "randomwordgen.h"

#include "compatiblesetting.h"

@interface Person:NSObject
{
@protected
	double salary;
	NSString* Name, *Address;
	NSMutableDictionary *memory;
	NSMutableDictionary *Environment;
	RandomWordGenerator *wordgen;
}

@property (nonatomic, retain) NSString* Name;
@property (nonatomic, retain) NSString* Address;
@property (retain) NSMutableDictionary *Environment;

-(void)sayHi;

-(NSString*)say;

-(void)whereRUfrom;

-(id)initWithName:(NSString*) name;

-(void)start;

-(void)interactWith:(NSMutableDictionary*)environment;

-(void)thinking;

-(void)remember:(NSString*) words;

@end
