#ifndef LIGHT_H
#define LIGHT_H

#include <arduino.h>
#include "config.h"

class Light{
  public:
    Light(int8_t pin);
    void turnOn();
    void turnOff();
    void toggleLight();
    void changeState(bool);
    void blinkLight(long);

    bool get_powerState();
    
  private:
    int8_t _pin;
    bool _powerState;
};



#endif /* LIGHT_H */
