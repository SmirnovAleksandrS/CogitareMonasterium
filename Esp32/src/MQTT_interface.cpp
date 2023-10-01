#include <MQTT_interface.h>

MQTTInterface::MQTTInterface(const char* Name){
    name = Name;
}

MQTTInterface::MQTTInterface(const char* Name, typeSensor sens){
    name = Name;
    this->setCallback(sens);
}

void MQTTInterface::setCallback(typeSensor sens){
    My_sensor = sens;
}

bool MQTTInterface::isConnect(){
    return PSClient->connected();
}

bool MQTTInterface::loop(){
    if (PSClient->connected()){
        return PSClient->loop();
    } else {
        PSClient->connect(MQTT_clientId, MQTT_login, MQTT_passwd);
        return PSClient->loop();
    }
    return false;   
}

void MQTTInterface::MQTTcallback(char* topic, byte* message, unsigned int length){
    #ifdef WriteLog_Serial
        Serial.print("message from topic: ");
        Serial.println(topic);
    #endif 
    auto it = std::find(subscribedTopics.begin(), subscribedTopics.end(), topic);     //ищем topic среди подписок
    uint8_t index = std::distance(subscribedTopics.begin(), it); //находим индекс топика
    
    // надо бы переделать этот говнокод.....
    uint8_t ind = 0;
    for (const auto& row : subscribs) {
        if (ind == index){
            for (auto& elem : row) {
                elem->callback(topic, message, length);
            }
        }
        ind ++;
    }
}

bool MQTTInterface::send(const char* topic, const char* data){
    //создаем и очищаем кусок памяти для написания адреса
    char* addres;
    uint8_t allLen = strlen(topic) + strlen(name) + 3 + strlen(RoomName);
    addres = new char [allLen];
    
    //пишем адрес
    strcpy(addres, RoomName);
    strcat(addres, "/");
    strcat(addres, name);
    strcat(addres, "/");
    strcat(addres, topic);

    //отправляем данные
    bool answer = false;
    answer = PSClient->publish(addres, data);

    #ifdef WriteLog_Serial
        Serial.print("Send data to: ");
        Serial.print(addres);
        Serial.print(" Result: ");
        Serial.println(answer);
    #endif

    //очищаем память и завершаем функцию
    delete [] addres;
    return answer;
}

bool MQTTInterface::subscribe(const char* topic){
    bool answer = false;
    answer = PSClient->subscribe(topic);    //пробуем подписаться на топик
    if (answer){    //если получилось, то записываем это в массивы
        auto it = std::find(subscribedTopics.begin(), subscribedTopics.end(), topic);     //ищем topic среди подписок

        if (it != subscribedTopics.end()){    //нашелся топик
            uint8_t index = std::distance(subscribedTopics.begin(), it); //находим индекс топика
            auto sbStart = subscribs.begin();   //получаем итератор на первый топик в двухмерно массиве
            std::advance(sbStart, index);   //переходим на нужный топик
            bool hasTopic = std::find((*sbStart).begin(), (*sbStart).end(), My_sensor) != (*sbStart).end();
            if(!hasTopic){
                auto it_elem = sbStart->before_begin(); //получаем итератор на первого подписчика
                std::advance(it_elem, std::distance(sbStart->begin(), sbStart->end())); //переходим на последнего подписчика
                sbStart->insert_after(it_elem, My_sensor);  //добавление нового подписчика
            }
        }else{  //не нашел топик
            subscribedTopics.push_front(topic);
            std::forward_list<typeSensor> new_row = {My_sensor};
            subscribs.push_front(new_row);
        }
        
    }

    #ifdef WriteLog_Serial
    for (const auto& row : subscribs) {
        for (const auto& elem : row) {
            Serial.print("f");
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.print("Answer from server: ");
    Serial.println(answer);
    #endif

    return answer;
}