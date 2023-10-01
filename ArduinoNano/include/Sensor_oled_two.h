#ifndef _OLED_TWO_
#define _OLED_TWO_

#include <Sensors_interface.h>
#include "OLED_I2C.h" 
#include <RF24_settings.h>
        //-> write to main

class Sensor_oled_two : public Sensor{
public:
    Sensor_oled_two();
    Sensor_oled_two(const char* humid_top, const char* temp_top, const char* poten_top);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    bool begin();
    void setInterface(Interface* interf);
protected:
    OLED oled = OLED(18, 19, 8);
    char* humid_topic;
    char* temp_topic;
    char* poten_topic;
    uint64_t humid;
    uint64_t temp;
    uint64_t poten;
};


#endif