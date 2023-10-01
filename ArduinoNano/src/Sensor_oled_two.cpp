#include <Sensor_oled_two.h>
// класс, написанный н аэтой библиотеке не заработал
extern uint8_t TinyFont[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

Sensor_oled_two::Sensor_oled_two(){}

Sensor_oled_two::Sensor_oled_two(const char* humid_top, const char* temp_top, const char* poten_top){
    memcpy(humid_topic, humid_top, strlen(humid_top)+1);
    memcpy(temp_topic, temp_top, strlen(temp_top)+1);
    memcpy(poten_topic, poten_top, strlen(poten_top)+1);
    // Serial.begin(9600);
    // Serial.print(1);
    // Serial.print(oled.begin());
    // Serial.print('2');
    // oled.setFont(TinyFont);
    // Serial.print('3');
    // oled.print("Aaaaaaaaaaaaaaaaaaa", RIGHT, 10);
    // Serial.print('4');

    // oled.print("Humudity: ", LEFT, 5);
    // // oled.setCursorXY(0, 26);
    // oled.print("Tempature: ", LEFT, 26);
    // // oled->setCursorXY(0, 47);
    // oled.print("Voltage: ", LEFT, 47);
    // oled.update();
}

bool Sensor_oled_two::begin(){
    bool ans = oled.begin();
    oled.setFont(TinyFont);
    oled.print("Aaaaaaaaaaaaaaaaaaa", RIGHT, 10);
    oled.update();
    return ans;
}

void Sensor_oled_two::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled_two::callback (char* topic, byte* message, unsigned int length){
    int64_t dat_int;
    memcpy(&dat_int, message, sizeof(int64_t));
    char bufer[32];
    sprintf(bufer, "%i", dat_int);
    if (strcmp(topic, humid_topic) == 0){
        
    } else if (strcmp(topic, temp_topic) == 0){
        
    } else if (strcmp(topic, poten_topic) == 0){
        
    }

    return true;
}

bool Sensor_oled_two::iteration(){
    oled.print("1", LEFT, 20);
    oled.update();
    return inte->loop();
    // return true;
}