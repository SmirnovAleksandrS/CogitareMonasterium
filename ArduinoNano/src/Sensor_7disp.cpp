#include <Sensor_7disp.h>
// не заработалб сгорел видимо
Sensor_7disp::Sensor_7disp(){}

Sensor_7disp::Sensor_7disp(TM1637* disp, unsigned int port, uint8_t clk, uint8_t dio, uint8_t bright){
    this->disp = disp;
    this->clk = clk;
    this->dio = dio;
    this->bright = bright;
    this->time = millis();
    this->disp->init();
    this->disp->setBrightness(bright);
}

Sensor_7disp::Sensor_7disp(Interface* interf, TM1637* disp, unsigned int port, uint8_t clk, uint8_t dio, uint8_t bright){
    this->inte = interf;

    this->disp = disp;
    this->clk = clk;
    this->dio = dio;
    this->bright = bright;
    this->time = millis();
    this->disp->init();
    this->disp->setBrightness(bright);
}

void Sensor_7disp::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_7disp::iteration(){
    return inte->loop();
}

