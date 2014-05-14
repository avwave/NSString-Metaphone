//
//  NSString+Metaphone.m
//  Metaphone
//
//  Created by Ray Arvin Rimorin on 5/14/14.
//  Copyright (c) 2014 avwave. All rights reserved.
//

#import "NSString+Metaphone.h"
#import "ShortDoubleMetaphone.h"

@implementation NSString (Metaphone)

- (NSString *)metaphone {
    return [NSString doGetMetaphoneFromString:self alternate:NO];
	
}

- (NSString *)alternateMetaphone {
    return [NSString doGetMetaphoneFromString:self alternate:YES];
}

+ (NSString *)doGetMetaphoneFromString:(NSString *)sourceString alternate:(bool)isAlternate {
    DoubleMetaphone<15> metaphoneValue([sourceString cStringUsingEncoding:NSASCIIStringEncoding]);
	
	NSString *metaphoneKey;
	
    if (isAlternate) {
        if (metaphoneValue.getAlternateKey()) {
            metaphoneKey = [NSString stringWithUTF8String: metaphoneValue.getAlternateKey()];
        }
    }
    else {
        metaphoneKey = [NSString stringWithUTF8String: metaphoneValue.getPrimaryKey()];
    }
    
    return metaphoneKey;
}
@end
