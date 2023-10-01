#ifndef _SENSOR_LED_PWM_
#define _SENSOR_LED_PWM_

#include "esp32-hal-ledc.h"
#include <Sensors_interface.h>
#include <RF24_settings.h>

#define Frequency 5000                                       
#define LedChannel 0
#define Resolution 8

class Sensor_led_pwm : public Sensor{
public:
    Sensor_led_pwm();
    Sensor_led_pwm(uint8_t port);
    Sensor_led_pwm(Interface* interf, uint8_t port);
    bool callback (char* topic, byte* message, unsigned int length);
    void setInterface(Interface* interf);

    bool iteration();
protected:
    int16_t pwm;
    uint8_t port;
};


#endif