#include <Sensor_led_pwm.h>

// работает, не использовался на демонстрации
Sensor_led_pwm::Sensor_led_pwm(){}

Sensor_led_pwm::Sensor_led_pwm(uint8_t port){

    this->time = millis();
    this->port = port;
    pinMode(port, OUTPUT);
    analogWrite(port, 254);
    delay(100);
    analogWrite(port, 0);
    this->pwm = 100;
}

Sensor_led_pwm::Sensor_led_pwm(Interface* interf, uint8_t port){
    this->inte = interf;

    this->time = millis();
    this->port = port;
    pinMode(port, OUTPUT);
    analogWrite(port, 254);
    delay(100);
    analogWrite(port, 0);
    this->pwm = 100;
}

bool Sensor_led_pwm::callback (char* topic, byte* message, unsigned int length){
    int64_t pwm;
    memcpy(&pwm, message, sizeof(int64_t));
    if (pwm > 100){
        pwm = 100;
    }
    if (pwm < 0){
        pwm = 0;
    }
    int pwm_send = map(pwm, 0, 100, 0, 255);
    analogWrite(port, pwm_send);
    return true;
}

void Sensor_led_pwm::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_led_pwm::iteration(){
    // if ( inte->loop() ){
    //     if (millis() - time > 5){
    //         #ifdef WriteLog_SerialRF24
    //             Serial.print("pwm: ");
    //             Serial.print(pwm);
    //             Serial.println("percent");
    //         #endif
    //     }
    // }
    return true;
}