#include <Sensor_potentiometr.h>

Sensor_potentiometr::Sensor_potentiometr(){}

Sensor_potentiometr::Sensor_potentiometr(unsigned int PIN, const char* topic){
    port = PIN;
    voltage = 0;
    top = new char[strlen(topic) + 1];
    memcpy(top, topic, strlen(topic)+1);
    time = millis();
}


Sensor_potentiometr::~Sensor_potentiometr(){
    delete[] top;
}

bool Sensor_potentiometr::callback (char* topic, byte* message, unsigned int length){
    return true;
}

void Sensor_potentiometr::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_potentiometr::iteration(){
    if (inte->loop()){
        bool flag = true;
        int16_t volt = analogRead(port);

        #ifdef WriteLog_Serial
            // Serial.print("Voltage: ");
            // Serial.print(volt);
            // Serial.println(" parrots");
        #endif
        if (millis() - time > 1000){
            if ( abs(voltage - volt) >= 600 ){
                char bufer[6];  //т.к максимум 4096
                sprintf(bufer, "%i", volt);
                flag = inte->send(top, bufer);
                voltage = volt;
                time = millis();
            }
        }
        return flag;
    }
    return false;
}