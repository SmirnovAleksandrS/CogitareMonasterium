#include <Sensor_DHT11.h>

Sensor_DHT11::Sensor_DHT11(){

}


Sensor_DHT11::Sensor_DHT11(DHT_Unified* sens, const char* temp_topic, const char* humid_topic){
    dht = sens;
    dht->begin();
    // запись переданных названий топиков в класс
    humid_top = new char[strlen(humid_topic) + 1];
    memcpy(humid_top, humid_topic, strlen(humid_topic) + 1);
    temp_top = new char[strlen(temp_topic) + 1];
    memcpy(temp_top, temp_topic, strlen(temp_topic) + 1);
}

void Sensor_DHT11::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_DHT11::callback (char* topic, byte* message, unsigned int length){
    return true;
}

bool Sensor_DHT11::iteration(){
    // условие на время (датчик нельзя опрашивать чаще 5 секунд)
    if (inte->loop() && (millis() - time > 5000)){
        bool flag_t = true, flag_h = true;
        sensors_event_t event;
        int bufer_i = 0;
        char bufer_s[32];

        //чтение температуры
        dht->temperature().getEvent(&event);
        if (isnan(event.temperature)) {
            #ifdef WriteLog_SerialRF24
                Serial.println("Error reading temperature!");
            #endif
            flag_t = false;
        } else {
            #ifdef WriteLog_SerialRF24
                Serial.print("Temperature: ");
                Serial.print(event.temperature);
                Serial.println("C");
            #endif
            // отправка температуры
            bufer_i = (int)event.temperature;
            sprintf(bufer_s, "%i", bufer_i);
            flag_t = inte->send(temp_top, bufer_s);
        }
        delay(10);
        //чтение влажности
        dht->humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            #ifdef WriteLog_SerialRF24
                Serial.println("Error reading humidity!");
            #endif 
            flag_h = false;       
        } else {
            // отправка влажности
            #ifdef WriteLog_SerialRF24
                Serial.print("Humidity: ");
                Serial.print(event.relative_humidity);
                Serial.println("%");
            #endif

            bufer_i = (int)event.relative_humidity;
            sprintf(bufer_s, "%i", bufer_i);
            flag_h = inte->send(humid_top, bufer_s);
        }
        
        time = millis();
        return (flag_t && flag_h);
    }
    return false;
}