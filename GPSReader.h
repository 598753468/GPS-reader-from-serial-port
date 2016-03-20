#ifndef __GPSReader_H__
#define __GPSReader_H__
#include"serial.h"
#include"pthread.h"
#include<string>
#include <stdlib.h>
#include<unistd.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
///
/// \brief Do not use this function directly
/// \param args
/// \return
///
void*StartGPSReadThread(void *args);
class GPSReader
{
public:
    GPSReader();
    bool Init(string port, int baud);
    void stop();
    ///
    /// \brief GPSReadThread, Do not use it directly.
    ///
    void GPSReadThread();
    int Hour();
    int Minute();
    double Second();
    double Latitude();
    double Longitude();
    //bool IsValid();
    double HorizontalAccuracy();
    double AntennaHeight();
    double GroundHeight();
private:
    Serial serial;
    unsigned char checkSum;
    int hour,minute;
    double second;
    double latitude,longitude,horizontalAccuracy,antennaHeight,groundHeight;
    bool isReading,timeToExit;//isValid;
    pthread_t readThreadID;
    int Check(string str);
    int CommaPosition(int index,string str);
};

#endif
