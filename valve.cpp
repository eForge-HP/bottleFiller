#include "valve.h"

Valve::Valve(int8_t pin){
  this->_pin = pin;
  pinMode(_pin, OUTPUT);
  _state = CLOSED;
  digitalWrite(_pin, _state);
}


void Valve::openValve(){
  _state = OPEN;
  digitalWrite(_pin, _state);
}

void Valve::closeValve(){
  _state = CLOSED;
  digitalWrite(_pin, _state);
}
