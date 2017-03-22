#import "bluetooth.h"

@implementation BlueTooth

-(id) init
{
	mCM = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
	[NSTimer scheduledTimerWithTimeInterval:2.0f target:self selector:@selector(scanPeripheral:nil) userInfo:nil repeats:NO];
	return self;
}

-(void)scanPeripheral:(NSArray*) uuidArray
{
	[mCM scanForPeripheralsWithServices:uuidArrau option:options];
}

-(void)scanHRDev
{
	NSLog(@"scan time out");
	NSArray* uuidArray = [NSArray arrayWithObjects:[CBUUID UUIDWithString:@"180D"], nil];
	[NSTimer scheduledTimerWithTimeInterval:2.0f target:self selector:@selector(scanTimeout:uuidArray) userInfo:nil repeats:NO];
}

-(void)centralManagerDidUpdateState:(CBCentralManager*)cManager
{
	NSMutableString* nsmstring = [NSMutableString stringWithString:@"UpdateStat:"];
	BOOL isWork = FALSE;
	switch(cManager.state)
	{
		case CNCentralManagerStatueUnknown:
			[nsmstring appendString:@"Unknown"];
			break;

		case CBCentralManagerStateUnsupported:
            		[nsmstring appendString:@"Unsupported\n"];
            		break;
	        case CBCentralManagerStateUnauthorized:
			[nsmstring appendString:@"Unauthorized\n"];
			break;
		case CBCentralManagerStateResetting:
			[nsmstring appendString:@"Resetting\n"];
			break;
		case CBCentralManagerStatePoweredOff:
			[nsmstring appendString:@"PoweredOff\n"];
			if (connectedPeripheral!=NULL){
				[CM cancelPeripheralConnection:connectedPeripheral];
			}
			break;
		case CBCentralManagerStatePoweredOn:
			[nsmstring appendString:@"PoweredOn\n"];
        		isWork=TRUE;
			break;
		default:
			[nsmstring appendString:@"none\n"]; 
			break;
	}
	NSLog(@"%@",nsmstring);
	[delegate didUpdateState:isWork message:nsmstring getStatus:cManager.state];
}

-(void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
	
}

@end
