#ifndef _SENSOR_LED_
#define _SENSOR_LED_

#include "Sensors_interface.h"
#include "RF24_settings.h"

class Sensor_LED : public Sensor{
public:
    Sensor_LED(uint8_t pin);
    Sensor_LED(Interface* inter ,uint8_t pin);
    bool iteration();
    bool callback (char* topic, byte* message, unsigned int length);
    void setInterface(Interface* Inter);
    
protected:
    uint8_t PIN;
    // Interface* Inter; прописан в родительском классе
};

#endif