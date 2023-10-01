#ifndef _SENSOR_LED_PWM_
#define _SENSOR_LED_PWM_

#include <Sensors_interface.h>
#include <RF24_settings.h>

class Sensor_led_pwm : public Sensor{
public:
    Sensor_led_pwm();
    Sensor_led_pwm(uint8_t port);
    Sensor_led_pwm(Interface* interf, uint8_t port);
    bool callback (char* topic, byte* message, unsigned int length);
    void setInterface(Interface* interf);

    bool iteration();
protected:
    uint64_t time;
    int16_t pwm;
    uint8_t port;
};


#endif