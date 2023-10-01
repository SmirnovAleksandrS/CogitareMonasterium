#ifndef _OLED_
#define _OLED_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <GyverOLED.h>
#include <math.h>

class Sensor_oled : public Sensor{
public:
    Sensor_oled();
    Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oledd, const char* humid_topic, const char* temp_topic, const char* poten_topic);
    bool init();
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
protected:
    GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled; 
    char* humid_top;
    char* temp_top;
    char* poten_top;
    uint64_t humid;
    uint64_t temp;
    uint64_t poten;
};


#endif