#include "GPSReader.h"
GPSReader::GPSReader()
{
    isReading=false;
}

bool GPSReader::Init(string port, int baud)
{
    bool ret= serial.Open((char*)port.c_str(),baud,8,NO,1);
    if(ret)
    {
        pthread_create(&readThreadID,NULL,&StartGPSReadThread,this);
    }
    return ret;
}

void GPSReader::stop()
{
    timeToExit=true;
    serial.Close();
}

int GPSReader::Hour()
{
    return hour;
}

int GPSReader::Minute()
{
    return minute;
}

double GPSReader::Second()
{
    return second;
}

double GPSReader::Latitude()
{
    return latitude;
}

double GPSReader::Longitude()
{
    return longitude;
}

double GPSReader::HorizontalAccuracy()
{
    return horizontalAccuracy;
}

double GPSReader::AntennaHeight()
{
    return antennaHeight;
}

double GPSReader::GroundHeight()
{
    return groundHeight;
}

void GPSReader::GPSReadThread()
{
    if(isReading)
    {
        return;
    }
    else
    {
        isReading=true;
        string message="";
        size_t start,end;
        char* buffer;
        while(!timeToExit)
        {
            int size=serial.Read(buffer);
            if(size>0)
            {
                //cout<<buffer<<endl;
                message=string(buffer);
                //message=buffer;
                bool quit=false;
                while(!quit)
                {
                    start=message.find("$GPGGA");
                    if(start!=-1)
                    {
                        message=message.substr(start);
                        end=message.find("*");
                        if((message.length()>=end+3)&&(end!=-1))
                        {
                            int check=strtol(message.substr(end+1,2).c_str(),NULL,16);
                            int che=Check(message.substr(1,end-1));
                            if(check==che)
                            {
                                int comma=0;
                                comma=message.find(",",comma+1); //comma behind $GPGGA,
                                hour=atoi(message.substr(comma+1,2).c_str());
                                minute=atoi(message.substr(comma+3,2).c_str());
                                second=atof(message.substr(comma+5,6).c_str());
                                comma=message.find(",",comma+1);//comma behind      121252.000,
                                double deg=atof(message.substr(comma+1,2).c_str());
                                double min=atof(message.substr(comma+3,7).c_str());
                                latitude=deg+min/60.0;
                                comma=message.find(",",comma+1);//comma behind          3937.3032,

                                comma=message.find(",",comma+1);//comma behind              N,
                                deg=atof(message.substr(comma+1,3).c_str());
                                min=atof(message.substr(comma+4,7).c_str());
                                longitude=deg+min/60.0;
                                comma=message.find(",",comma+1);//comma behind                  11611.6046,

                                comma=message.find(",",comma+1);//comma behind                      E,

                                comma=message.find(",",comma+1);//comma behind                          1,

                                comma=message.find(",",comma+1);//comma behind                              05,
                                horizontalAccuracy=atoi(message.substr(comma+1,4).c_str());
                                comma=message.find(",",comma+1);//comma behind                                  2.0,
                                antennaHeight=atof(message.substr(comma+1,6).c_str());
                                comma=message.find(",",comma+1);//comma behind                                      45.9,

                                comma=message.find(",",comma+1);//comma behind                                          M,
                                groundHeight=atof(message.substr(comma+1,6).c_str());
                                comma=message.find(",",comma+1);//comma behind                                              -5.7,

                                comma=message.find(",",comma+1);//comma behind                                                  M,

                                comma=message.find(",",comma+1);//comma behind
                            }
                            message=message.substr(end+2);
                        }
                        else
                        {
                            quit=true;
                        }
                    }
                    else
                    {
                        quit=true;
                    }
                }
            }

            usleep(20000);
        }
    }
}

int GPSReader::Check(string str)
{
    const char* strChar=str.c_str();
    int result;
    for(int j=0;j<str.length();j++)
    {
        result=result^(*(strChar+j));
    }
    return result;
}

int GPSReader::CommaPosition(int index,string str)
{

}

void*StartGPSReadThread(void *args)
{
    GPSReader *reader=(GPSReader*)args;
    reader->GPSReadThread();
}
