#include "MQTT_interface.h"

bool initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_ssid, WIFI_passwd);

  #ifdef WriteLog_Serial
    Serial.print("Connecting to WiFi:");
  #endif

  uint8_t trys = 0;
  bool connection = false;

  while ((!connection)&&(trys < WIFI_tryConnect)) {
    connection = WiFi.status() == WL_CONNECTED;
    delay(WIFI_delayBetwenConect);
    trys ++;
    #ifdef WriteLog_Serial
      Serial.print('.');
    #endif
  }
  #ifdef WriteLog_Serial
  Serial.println();
  if (connection){
    Serial.println("Has connection. My IP is:");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Something wrong. Conection lost.");
  }
  #endif
  return connection;
}

bool startMQTT(PubSubClient* client){ //create PubSub connect
  #ifdef WriteLog_Serial
    Serial.begin(SerialSpeed);
  #endif

  if (initWiFi()){
    Serial.println("Start connect MQTT");
    client->setKeepAlive(20000);
    client->setServer(MQTT_serverId, MQTT_port); 
    client->setCallback(MQTTInterface::MQTTcallback);

    uint8_t trys = 0;
    bool ifConnect = false;

    #ifdef WriteLog_Serial
      Serial.print("Try connect:");
    #endif

    while ((trys < MQTT_tryConect)&&(!ifConnect)){
      ifConnect = client->connect(MQTT_clientId, MQTT_login, MQTT_passwd);
      delay(MQTT_delayBetwenConect);
      trys ++;
      #ifdef WriteLog_Serial
        Serial.print('.');
      #endif
    }
    // client->publish("esp32/output", "2");

    #ifdef WriteLog_Serial
    Serial.println();
    if (!client->connected()){
      Serial.println("Something wrong. Conection lost.");
    } else {
      Serial.println("Has conection!");
    }
    #endif

    return ifConnect;
  }
  return false;
}