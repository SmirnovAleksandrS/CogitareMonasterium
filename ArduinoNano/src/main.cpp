#include "Sensor_DHT11.h"
#include "RF24_interface.h"
#include "Sensor_LED.h"
#include "Sensor_oled.h"
#include "Sensor_potentiometr.h"
#include <GyverOLED.h>
// //////////////////////////Создаем интерфейс RF24//////////////////////////////

RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
String* RF24Interface::subscribedTopics = new String [RF24_MaxCountTopics];
typeSensor RF24Interface::subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];

// ////////////////////////Создаем сенсоры//////////////////////////////////

// //Создаем DHT
DHT_Unified dht_unif = DHT_Unified(2, DHT11);
Sensor_DHT11 dht11(&dht_unif, "temp", "humb");
RF24Interface rf24_inter_dht11 = RF24Interface(&dht11);

// //создаем LED
Sensor_LED LED = Sensor_LED(5);
RF24Interface LED_inter = RF24Interface(&LED);

// создаем oled
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled_lib;
Sensor_oled oled_class = Sensor_oled(&oled_lib, "room1/Nano/humb", "room1/Nano/temp", "room1/Pot/Resistance");
RF24Interface oled_inter = RF24Interface(&oled_class);


// ///////////////////////Основной код//////////////////////////////////////

void setup(){
  Serial.begin(9600);
  Serial.print(startRf24(&radio));

  // создание подписок на топики с температурой, вложностью и потенциометром
  oled_class.setInterface(&oled_inter);
  oled_inter.subscribe("room1/Pot/Resistance");
  oled_inter.subscribe("room1/Nano/temp");
  oled_inter.subscribe("room1/Nano/humb");

  // создание подписки на светодиод (+ передача указателя на интерфейсы)
  LED.setInterface(&LED_inter);
  LED_inter.subscribe("LED_nano");

  dht11.setInterface(&rf24_inter_dht11); 
}

void loop(){
  LED.iteration();
  oled_class.iteration();
  dht11.iteration();
}