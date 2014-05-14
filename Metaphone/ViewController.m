//
//  ViewController.m
//  Metaphone
//
//  Created by Ray Arvin Rimorin on 5/14/14.
//  Copyright (c) 2014 avwave. All rights reserved.
//

#import "ViewController.h"
#import "NSString+Metaphone.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSLog(@"%@ : meta=%@, altmeta=%@", @"Kalayaan", [@"Kalayaan" metaphone], [@"Kalayaan" alternateMetaphone]);
    
    NSLog(@"%@ : meta=%@, altmeta=%@", @"Calayaan", [@"Calayaan" metaphone], [@"Calayaan" alternateMetaphone]);
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
