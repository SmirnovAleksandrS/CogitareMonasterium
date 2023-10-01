#include <Sensor_oled.h>

Sensor_oled::Sensor_oled(){}

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oledd, const char* humid_topic, const char* temp_topic, const char* poten_topic){
    oled = oledd;
    temp = 0;
    humid = 0;
    poten = 0;
    // запись передданных названий топиков в класс
    humid_top = new char[strlen(humid_topic) + 1];
    memcpy(humid_top, humid_topic, strlen(humid_topic) + 1);
    temp_top = new char[strlen(temp_topic) + 1];
    memcpy(temp_top, temp_topic, strlen(temp_topic) + 1);
    poten_top = new char[strlen(poten_topic) + 1];
    memcpy(poten_top, poten_topic, strlen(poten_topic) + 1);
}

bool Sensor_oled::init(){
    oled->init();
    oled->clear();
    // oled->invertDisplay(true);
    oled->setScale(2);
    oled->setCursorXY(0, 0);
    oled->print("Volt: ");
    oled->setCursorXY(0, 23);
    oled->print("Temp: ");
    oled->setCursorXY(0, 47);
    oled->print("Humid: ");
    oled->update();
}


void Sensor_oled::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled::callback (char* topic, byte* message, unsigned int length){
    char* temp_str = reinterpret_cast<char*>(message);
    // сравнение с записанными топиками, нахождение переданного и вывод на экран
    if (strcmp(topic, humid_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(80, 47);
        oled->println(temp_str);
        oled->update();
    }
    if (strcmp(topic, temp_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 23);
        oled->println(temp_str);
        oled->update();
    }
    if (strcmp(topic, poten_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 23);
        oled->println(temp_str);
        oled->update();
    }

    return true;
}

bool Sensor_oled::iteration(){
    return inte->loop();
}