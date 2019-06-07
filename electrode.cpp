#include "electrode.h"

Electrode::Electrode(int8_t pin, int8_t minVal){
  this->_pin = pin;
  this->_minVal = minVal;
  pinMode(_pin, INPUT);
}


bool Electrode::get_sensingValue(){
  if(analogRead(_pin) >= _minVal){
    return true;
  }else{
    return false;
  }
}
