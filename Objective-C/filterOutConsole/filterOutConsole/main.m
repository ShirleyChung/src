//
//  main.m
//  filterOutConsole
//
//  Created by Shirley on 2015/9/29.
//  Copyright © 2015年 Shirley. All rights reserved.
//



#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        FILE * fp = fopen(argv[1], "rw");
        
        if (fp)
        {
        }
        NSLog(@"Hello, World!");
    }
    return 0;
}
