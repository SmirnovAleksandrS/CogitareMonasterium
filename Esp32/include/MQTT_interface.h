#ifndef _MQTT_INTERFACE_
#define _MQTT_INTERFACE_

#include <Interface.h>
#include <forward_list>
#include <PubSubClient.h>
#include <WiFi.h>
#include <MQTT_settings.h>
#include "Sensors_interface.h"

#define typeSensor Sensor*

class MQTTInterface : public Interface{
  public:
    MQTTInterface();
    MQTTInterface(const char* Name);
    MQTTInterface(const char* Name, typeSensor sens);

    bool send(const char* topic, const char* data);   //отправка сообщений
    // bool send(const char* topic, int32_t data); 
    bool subscribe(const char* topic);                //подписка на топик
    bool loop();
    bool isConnect();
    void setCallback(typeSensor sens);
    static void MQTTcallback(char* topic, byte* message, unsigned int length);

  protected:
    typeSensor My_sensor;
    static WiFiClient WFClient;
    static PubSubClient* PSClient;
    static std::forward_list<std::string> subscribedTopics; 
    static std::forward_list<std::forward_list<typeSensor>> subscribs;
};


bool startMQTT(PubSubClient* client);   // функция запуска всех интерфейсов, подключение к Wi-Fi и MQTT серверу

#endif