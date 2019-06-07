#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <arduino.h>
#include "config.h"

class Electrode{
  public:
    Electrode(int8_t pin, int8_t minVal);
    bool get_sensingValue();
    
  private:
    int8_t _pin;
    int8_t _minVal;
};


#endif /* ELECTRODE_H */
