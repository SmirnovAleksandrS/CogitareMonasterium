#ifndef _RF24_CONNECT_
#define _RF24_CONNECT_

#include <SPI.h>
#include <RF24.h>
#include <string>

#include "Sensors_interface.h"
#include "RF24_settings.h"

bool startRf24(RF24* radio);

class RF24Senosr : public Sensor{
public:
    RF24Senosr();
    bool callback(char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* inter);
protected:
    // Interface* Inter;
    static RF24* Radio;
};

#endif