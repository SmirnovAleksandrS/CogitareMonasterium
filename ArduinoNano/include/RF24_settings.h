#ifndef _RF24_SETTINS_
#define _RF24_SETTINS_

// #define RF24_CE 4
// #define RF24_CS 5

#define RF24_PaLevel RF24_PA_MAX    //мощность передатчика
#define RF24_pipe 0x7878787878      //аддрес используемой трубы
#define RF24_DataRate RF24_1MBPS    //скорость передача
#define RF24_Channel 0x6f   //канал
#define WriteLog_SerialRF24

#define RF24_pipe_read  "Node1"
#define RF24_pipe_write "Node2"

#define RF24_MaxCountTopics 10
#define RF24_MaxCountSubscribers 10

#endif