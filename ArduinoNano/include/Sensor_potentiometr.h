#ifndef _POTENTIOMETR_
#define _POTENTIOMETR_


#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <math.h>

class Sensor_potentiometr : public Sensor{
public:
    Sensor_potentiometr();
    Sensor_potentiometr(unsigned int port, const char* top);
    Sensor_potentiometr(Interface* interf, unsigned int port, const char* top);
    bool callback (char* topic, byte* message, unsigned int length);
    void setInterface(Interface* interf);

    bool iteration();
protected:
    uint64_t time;
    int16_t voltage;
    unsigned int port;
    char* top;
};


#endif 