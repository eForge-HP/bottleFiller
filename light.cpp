#include "light.h"

Light::Light(int8_t pin){
  this->_pin = pin;
  pinMode(_pin, OUTPUT);
}


void Light::turnOn(){
  _powerState = true;
  digitalWrite(_pin, _powerState);
}


void Light::turnOff(){
  _powerState = false;
  digitalWrite(_pin, _powerState);
}


void Light::toggleLight(){
  _powerState != _powerState;
  digitalWrite(_pin, _powerState);
}


void Light::changeState(bool powerState){
  _powerState = powerState;
  digitalWrite(_pin, _powerState);
}


void Light::blinkLight(long blinkTime){
  if(millis()/blinkTime%2){
    _powerState = true;
  }else{
    _powerState = false;
  }
  digitalWrite(_pin, _powerState);
}


bool Light::get_powerState(){
  return _powerState;
}
