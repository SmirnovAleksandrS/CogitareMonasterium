#ifndef _RF24_CONNECT_
#define _RF24_CONNECT_

#include <SPI.h>
#include <RF24.h>
#include <Interface.h>
#include "RF24_settings.h"
#include "string.h"
#include "Sensors_interface.h"

#define typeSensor Sensor*

bool startRf24(RF24* radio);

class RF24Interface : public Interface{
public:
    RF24Interface();
    RF24Interface(typeSensor Sens);
    bool send(const char* topic, const char* data);
    bool send(const char* topic, const int64_t data);
    bool send(const char* topic, const float data);
    bool subscribe(const char* topic);
    bool loop();
protected:
    typeSensor My_Sensor;
    static RF24* Radio;
    static String* subscribedTopics;
    static typeSensor subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];
};

#endif