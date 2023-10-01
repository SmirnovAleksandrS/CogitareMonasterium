#include <Sensor_led_pwm.h>

Sensor_led_pwm::Sensor_led_pwm(){}

Sensor_led_pwm::Sensor_led_pwm(uint8_t PIN){
    port = PIN;
    // pinMode(port, OUTPUT);
    ledcSetup(LedChannel, Frequency, Resolution);                                    
    ledcAttachPin(port, LedChannel);
    

    ledcWrite(LedChannel, 253);
    delay(100);
    ledcWrite(LedChannel, 0);
    pwm = 255;
}

Sensor_led_pwm::Sensor_led_pwm(Interface* interf, uint8_t PIN){
    inte = interf;
    port = PIN;
    ledcSetup(LedChannel, Frequency, Resolution);

// подключаем ШИМ-канал к пину светодиода:                                         
    ledcAttachPin(port, LedChannel);
    ledcWrite(LedChannel, 253);
    delay(100);
    ledcWrite(LedChannel, 0);
    pwm = 255;
}

bool Sensor_led_pwm::callback (char* topic, byte* message, unsigned int length){
    Serial.println("Something to PWM LED");
    int64_t pwm_bufer;
    char* str_bufer = new char [6];
    str_bufer = reinterpret_cast<char*>(message);
    str_bufer[4] = '\0';
    
    pwm_bufer= atoi(str_bufer);
    int pwm_send = map(pwm_bufer, 0, 4090, 0, 255);

    Serial.println(str_bufer);
    Serial.println(pwm_send);
    // ledcWrite(port, pwm_send);
    pwm = pwm_send;
    return true;
}

void Sensor_led_pwm::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_led_pwm::iteration(){
    ledcWrite(LedChannel, pwm);
    return inte->loop();
}