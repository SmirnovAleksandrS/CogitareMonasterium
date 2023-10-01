#ifndef _SENSOR_PWM_LED_
#define _SENSOR_PWM_LED_

#include "Sensors_interface.h"

class Sensor_PWM_LED : public Sensor{
public:
    Sensor_PWM_LED(Interface* inter ,uint8_t pin);
    bool iteration();
    static bool PWM_LED_Callback (char* topic, byte* message, unsigned int length);
protected:
    static uint8_t PIN;
    static uint8_t duty;
    // Interface* Inter; прописан в родительском классе
};

#endif