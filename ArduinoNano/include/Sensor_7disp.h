#ifndef _7DISP_
#define _7DISP_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <TM1637.h>
#include <math.h>

class Sensor_7disp : public Sensor{
public:
    Sensor_7disp();
    Sensor_7disp(TM1637* disp, unsigned int port, uint8_t clk, uint8_t dio, uint8_t bright);
    Sensor_7disp(Interface* interf, TM1637* disp, unsigned int port, uint8_t clk, uint8_t dio, uint8_t bright);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
protected:
    uint64_t time;
    uint8_t clk;                       // Указываем вывод CLK
    uint8_t dio;                      // Указываем вывод DIO
    uint8_t bright;
    TM1637* disp;          // Устанавливаем яркость дисплея от 0 до 7
    int8_t numtab[4] = {0,1,2,3};
};


#endif