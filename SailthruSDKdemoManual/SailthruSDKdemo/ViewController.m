//
//  ViewController.m
//  SailthruSDKdemo
//
//  Copyright (c) 2013 Sailthru, Inc. All rights reserved.
//

#import "ViewController.h"

//#import <CoreLocation/CoreLocation.h>	// if you want to send location information to Sailthru

#import "SailthruSDK.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)buttonAction:(id)sender
{
	NSString *name = [((UIButton *)sender).titleLabel.text copy];
	
	STEvent *e;
	if([sender tag]) {
		e = [STEvent eventWithURL:@"http://www.apple.com/store" location:CLLocationCoordinate2DMake(40.7142, 74.0064)];
	} else {
		e = [STEvent eventWithTags:@[name, @"Red", @"Hat"]];
	}
	[e send];
}

@end
