#ifndef _POTENTIOMETR_
#define _POTENTIOMETR_

#include <Sensors_interface.h>
#include "MQTT_settings.h"
#include "esp32-hal-ledc.h"

class Sensor_potentiometr : public Sensor{
public:
    Sensor_potentiometr();
    Sensor_potentiometr(unsigned int PIN, const char* topic);
    ~Sensor_potentiometr();
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