#include "Sensor_LED.h"

Sensor_LED::Sensor_LED(Interface* inter ,uint8_t pin){
    PIN = pin;
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, 1);
    delay(100);
    digitalWrite(PIN, 0);
    inte = inter;
}

bool Sensor_LED::iteration(){
    inte->loop();
    return true;
}

bool Sensor_LED::callback(char* topic, byte* message, unsigned int length){
    #ifdef WriteLog_Serial
        Serial.println("has message to some LED");
    #endif
    if (message[0] == '0'){
        digitalWrite(PIN, 0);
    } else {
        digitalWrite(PIN, 1);
    }
    return true;
}

void Sensor_LED::setInterface(Interface* Inter){
    inte = Inter;
}

Sensor_LED::Sensor_LED(uint8_t pin){
    PIN = pin;
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, 1);
    delay(100);
    digitalWrite(PIN, 0);
}