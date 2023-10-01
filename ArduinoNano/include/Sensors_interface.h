#ifndef _SENSORS_INTERFACE_
#define _SENSORS_INTERFACE_

#include <Arduino.h>
#include "Interface.h"

class Sensor{
public:
    Sensor() {};
    virtual bool iteration();   //опрос датчика, функция будет крутиться в main, переодически вызываясь
    virtual bool callback(char* topic, byte* message, unsigned int length);
    virtual void setInterface(Interface* Inter);
protected:
    // bool (*callback) (char* topic, byte* message, unsigned int length); //указатель на callback
    Interface* inte;    //указатель на интерфейс
    // const char* name;   //??название датчика
};

#endif