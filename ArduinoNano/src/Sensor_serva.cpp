#include <Sensor_serva.h>
// сгорела, зараза...
Sensor_serva::Sensor_serva(){}

Sensor_serva::Sensor_serva(Servo* sens, unsigned int port, const char* top){
    serva = sens;
    this->time = millis();
    this->angle_position = serva->read();
    serva->attach(port);
    this->top = new char[strlen(top) + 1];
    for (unsigned int  i=0; i < strlen(top); i++){
        this->top[i] = top[i];
    }
}

Sensor_serva::Sensor_serva(Interface* interf, Servo* sens, unsigned int port, const char* top){
    this->inte = interf;

    serva = sens;
    this->time = millis();
    this->angle_position = serva->read();
    serva->attach(port);
    this->top = new char[strlen(top) + 1];
    for (unsigned int i=0; i < strlen(top); i++){
        this->top[i] = top[i];
    }
}

void Sensor_serva::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_serva::callback (char* topic, byte* message, unsigned int length){
    int64_t angle;
    memcpy(&angle, message, sizeof(int64_t));
    // проверка на тупого юзера
    if (angle > 180){
        angle = 180;
    }
    if (angle < 0){
        angle = 0;
    }
    if ( abs(angle_position - angle) >= 1 ){
        serva->write(angle);
        angle_position = angle;
    }
    return true;
}

bool Sensor_serva::iteration(){
    bool flag = true;
    if ( inte->loop() ){
        if (millis() - time > 5){
            uint8_t angle = serva->read();
            #ifdef WriteLog_SerialRF24
                Serial.print("angle: ");
                Serial.print(angle);
                Serial.println("grad");
            #endif
            flag = inte->send(top, (int64_t)angle);
        }
    }
    return flag;
}