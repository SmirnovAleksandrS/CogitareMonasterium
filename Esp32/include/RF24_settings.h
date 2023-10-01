#ifndef _RF24_SETTINS_
#define _RF24_SETTINS_

// #define RF24_CE 4
// #define RF24_CS 5

#define RF24_PaLevel RF24_PA_MAX    //мощность передатчика
#define RF24_pipe 0x7878787878      //аддрес используемой трубы
#define RF24_DataRate RF24_1MBPS    //скорость передача
#define RF24_Channel 0x6f   //канал

#define RF24_pipe_read  "Node2"
#define RF24_pipe_write "Node1"


#define WriteLog_Serial

#endif