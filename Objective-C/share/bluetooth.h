#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface BlueTooth:NSObject<CBCentralManagerDelegate>
{
	CBCentralManager *mCM;
}

-(id)init;

-(void)scanHRDev;

-(void)centralManagerDidUpdateState:(CBCentralManager*)cManager;

-(void)didDiscoverPeripheral:(CBCentralManager*)cManager;

@end

