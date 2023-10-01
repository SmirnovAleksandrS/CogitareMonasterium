#include "RF24_sensor.h"


bool startRf24(RF24* radio){
    bool ans = false;
    ans = radio->begin();
    if(ans){
        radio->setDataRate(RF24_DataRate); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
        radio->setPALevel(RF24_PaLevel); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
        radio->setPayloadSize(32);
        // radio->setAutoAck(false);       // автоответ
        uint8_t address[][6] = { "1Node", "2Node" };
        radio->openReadingPipe(1, address[1]);
        radio->openWritingPipe(address[0]);
        radio->startListening();
    }
    return ans;          
}

////////////////////////////блок для RF24Sensor//////////////////////////////// 

void RF24Senosr::setInterface(Interface* Inter){
    inte = Inter;
}

RF24Senosr::RF24Senosr(){}

bool RF24Senosr::callback(char* topic, byte* message, unsigned int length){
    //byte массив по-факту массив char, т.к. ничего другого запихать туда нельзя.
    //шаг первый, распарсим что это за данные, строка или число, т.к. число в строковом виде занимает больше места
    char type_message = 'i';
    for(int i = 0; i < length; i ++){
        if (!(('0' <= message[i] && message[i] <= '9') || (message[i] == '.')) && type_message){
            type_message = 's';
        }else if(message[i] == '.'){
            type_message = 'f';
        }
    }
    //шаг второй парсим строку нужным методом
    bool correctLen = true;
    byte data[32];
    memcpy(data, topic, strlen(topic)+1);
    data[strlen(topic)+1] = type_message;
    char* message_str = reinterpret_cast<char*>(message);
    int64_t data_int=0;
    float data_float;
    switch (type_message){
        case 'i':
            data_int = atoi(message_str);
            if(sizeof(data_int) + strlen(topic) < 32)
                memcpy(data+strlen(topic)+2, &data_int, sizeof(data_int));
            else
                correctLen = false;
            break;
        case 's':
            if(strlen(message_str) + strlen(topic) < 31)
                memcpy(data+strlen(topic)+2, message_str, strlen(message_str)+1);
            else
                correctLen = false;
            break;
        case 'f':
            data_float = atof(message_str);
            if(sizeof(data_float) + strlen(topic) < 32)
                memcpy(data+strlen(topic)+2, &data_float, sizeof(data_float));
            else
                correctLen = false;
            break;
    }

    #ifdef WriteLog_Serial
        for (int i = 0; i < 32; i ++){
            if (data[i] == '\0'){
                Serial.print("$");
            }else 
                Serial.print((char)data[i]);
        }
        Serial.println();
    #endif

    //шаг третий проверяем подходит ли длинна, если да то отправляем
    if (correctLen){
        Radio->stopListening();
        Radio->write(&data, 32);
        Radio->startListening();
        return true;
    }
    return false;
}

bool RF24Senosr::iteration(){
    if (inte->loop()){
        bool sendRes = false;
        if(Radio->isChipConnected()){
            // Serial.println("ChipOk");
            if(Radio->available()){
                #ifdef WriteLog_Serial
                    Serial.print("New data! Receved packet: ");
                #endif

                byte data[32];
                Radio->read(data, 32);

                #ifdef WriteLog_Serial
                    for (int i = 0; i < 32; i ++){
                        if (data[i] == '\0'){
                            Serial.print("$");
                        }else 
                            Serial.print((char)data[i]);
                    }
                    Serial.println();
                #endif

                int topicLn = 0;
                //отпарсиваем название топика
                for (int i = 0;i < 32; i ++){
                    if(data[i] == '\0'){
                        topicLn = i;
                        break;
                    }
                }

                char* topicName = new char [topicLn+1];
                for (int i = 0; i < topicLn; i ++){
                    topicName[i] = (char)data[i];
                }

                topicName[topicLn] = '\0';
                //отпарсиваем тип переданных данных
                char type = (char)data[topicLn+1];

                #ifdef WriteLog_Serial
                    Serial.print("Recognuze: ln: ");
                    Serial.print(topicLn);
                    Serial.print(" Type: ");
                    Serial.print(type);
                    Serial.print(" Topic name: ");
                    Serial.print(topicName);
                #endif
                
                int64_t value_int;
                char* value_char = new char [30 - topicLn];
                float value_float;
                //в зависимости от типа данных обрабатываем
                switch (type)
                {
                case 'i':   //передали интовое число
                    memcpy(&value_int, data +topicLn + 2, sizeof(int));
                    #ifdef WriteLog_Serial
                        Serial.print("Data: ");
                        Serial.print(value_float);
                        Serial.println(" Try send to server: ");
                    #endif
                    sendRes = inte->send(topicName, const_cast<char*>((std::to_string(value_int)).c_str()));
                    break;
                case 's':   //передали строку
                    memcpy(value_char, data + topicLn + 2, 30 - topicLn);
                    #ifdef WriteLog_Serial
                        Serial.print("Data: ");
                        Serial.print(value_float);
                        Serial.println(" Try send to server: ");
                    #endif
                    sendRes = inte->send(topicName, value_char);
                    break;
                case 'f':   //передали float
                    
                    memcpy(&value_float, data +topicLn + 2, sizeof(value_float));
                    #ifdef WriteLog_Serial
                        Serial.print("Data: ");
                        Serial.print(value_float);
                        Serial.println(" Try send to server: ");
                    #endif
                    sendRes = inte->send(topicName, const_cast<char*>((std::to_string(value_float)).c_str()));
                    
                    break;
                case 'b':    //передали команду подписаться на топик
                    #ifdef WriteLog_Serial
                        Serial.println(" Try subscribe: ");
                    #endif
                    sendRes = inte->subscribe(topicName);
                    break;
                }
            }
        }
        return sendRes;
    }
    return false;
}