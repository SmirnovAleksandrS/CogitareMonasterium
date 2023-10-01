#include <Sensor_potentiometr.h>

Sensor_potentiometr::Sensor_potentiometr(){}

Sensor_potentiometr::Sensor_potentiometr(unsigned int port, const char* top){

    this->time = millis();
    this->port = port;
    this->voltage = 0;
    this->top = new char[strlen(top) + 1];
    for (unsigned int i=0; i < strlen(top); i++){
        this->top[i] = top[i];
    }
}

Sensor_potentiometr::Sensor_potentiometr(Interface* interf, unsigned int port, const char* top){
    this->inte = interf;

    this->time = millis();
    this->port = port;
    this->voltage = 0;
    this->top = new char[strlen(top) + 1];
    for (unsigned int i=0; i < strlen(top); i++){
        this->top[i] = top[i];
    }
}

bool Sensor_potentiometr::callback (char* topic, byte* message, unsigned int length){return true;}

void Sensor_potentiometr::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_potentiometr::iteration(){
    if ( inte->loop() ){
        if (millis() - time > 5){
            bool flag = true;
            int16_t volt = analogRead(port);
            #ifdef WriteLog_SerialRF24
                Serial.print("Voltage: ");
                Serial.print(volt);
                Serial.println("parrot");
            #endif
            // отправка
            if ( abs(voltage - volt) >= 5 ){
                flag = inte->send(top, (int64_t)volt);
            }
            voltage = volt;
            time = millis();
            return flag;
        }
    }
    return false;
}