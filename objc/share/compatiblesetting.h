//
//  compatiblesetting.h
//  talker
//
//  Created by Shirley on 2015/9/25.
//  Copyright © 2015年 Shirley. All rights reserved.
//

#ifndef compatiblesetting_h
#define compatiblesetting_h

#ifdef _XCODE
    #define ARC_BEGIN @autoreleasepool{
    #define ARC_END }
#else
    #define ARC_BEGIN NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    #define ARC_END [pool drain];
#endif


#endif /* compatiblesetting_h */
