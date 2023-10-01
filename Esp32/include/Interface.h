#ifndef _INTERFACE_
#define _INTERFACE_

// #include <MQTT_settings.h>

class Interface{
  public:
    virtual bool send(const char* topic, const char* data) = 0;
    // virtual bool send(const char* topic, const int64_t data) = 0;
    // virtual bool send(const char* topic, const float data) = 0;
    virtual bool subscribe(const char* topic) = 0;
    virtual bool loop() = 0;

  protected:
    // bool hasChange;
    const char* name;     //название датчика
};

#endif