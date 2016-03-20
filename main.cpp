#include <stdio.h>
//#include "serial.h"
#include"GPSReader.h"
#include<iostream>
#include<pthread.h>
using namespace std;
// Create serial port
//Serial serial;

int main(int argc, char** argv)
{
    GPSReader gps;
    gps.Init("/dev/ttyUSB0",57600);
    int i=0;
    usleep(3000000);
    while(i<20)
    {
        cout<<gps.Latitude()<<","<<gps.Longitude()<<","<<gps.AntennaHeight()<<endl;
        usleep(1000000);
        i++;
    }
    gps.stop();
//	char buffer[256] = {0};
//	int i, length = 0;
	
//	// Open serial port ("COM3", "/dev/ttyUSB0")
//    serial.Open("COM3", 9600, 8, NO, 1);
	
//	while(1)
//	{
//		// Wait character
//		length = serial.Read(buffer);
		
//		if(length)
//		{
//			for(i = 0; i < length; i++)
//			{
//				printf("%.2X ", buffer[i]);
//				//printf("%c", buffer[i]);
//			}
			
//			printf("\n");
			
//			// Send data
//			serial.Write(buffer, length);
//		}
//	}
	
//	// Close serial port
//	serial.Close();
	
	return 0;
}
