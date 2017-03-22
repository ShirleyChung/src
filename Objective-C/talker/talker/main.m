//
//  main.m
//  talker
//
//  Created by Shirley on 2015/9/24.
//  Copyright © 2015年 Shirley. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../../share/person.h"

void testPersonTalks()
{
    Person *p = [[Person alloc] initWithName:@"Bob"];
    [p sayHi];
    NSLog(@"%@ says:%@", [p Name], [p say]);
    [p start];
}

int main(int argc, const char * argv[]) {
ARC_BEGIN
        
        testPersonTalks();
        
        NSDateFormatter *df = [[NSDateFormatter alloc] init];
        [df setTimeZone:[NSTimeZone localTimeZone]];
        [df setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
        while(true)
        {
            NSLog(@"It's %@", [df stringFromDate:[NSDate date]]);
            [NSThread sleepForTimeInterval:10];
        }
        
ARC_END
    return 0;
}
