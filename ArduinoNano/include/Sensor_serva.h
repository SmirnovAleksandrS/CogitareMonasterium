#ifndef _SERVA_
#define _SERVA_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <Servo.h>
#include <math.h>

class Sensor_serva : public Sensor{
public:
    Sensor_serva();
    Sensor_serva(Servo* sens, unsigned int port, const char* top);
    Sensor_serva(Interface* interf, Servo* sens, unsigned int port, const char* top);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
protected:
    Servo* serva;
    uint64_t time;
    uint8_t angle_position;
    char* top;
};


#endif