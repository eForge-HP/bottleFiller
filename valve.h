#ifndef VALVE_H
#define VALVE_H

#include <arduino.h>
#include "config.h"

class Valve{
  public:
    Valve(int8_t pin);
    void openValve();
    void closeValve();
    
  private:
    int8_t _pin;
    bool _state;
};


#endif /* ELECTRODE_H */
