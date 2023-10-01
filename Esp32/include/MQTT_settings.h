#ifndef _MQTT_SETTINGS_
#define _MQTT_SETTINGS_

/////////////////////////////////////////////////////////////////////////////

#define RoomName "room1"

#define WIFI_ssid "*************"
#define WIFI_passwd "***********"
#define WIFI_tryConnect 10
#define WIFI_delayBetwenConect 100

#define MQTT_clientId "ESP32TestClient"
#define MQTT_serverId "192.168.1.35"
#define MQTT_login "TestClient"
#define MQTT_passwd "TestClient"
#define MQTT_port 1883
#define MQTT_tryConect 10
#define MQTT_delayBetwenConect 100

#define WriteLog_Serial //при наличии заставляет выводить в сериал свои действия
#define SerialSpeed 115200

/////////////////////////////////////////////////////////////////////////////

#endif