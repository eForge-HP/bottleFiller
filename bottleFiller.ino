////////////////////////////////////////////////////////////////////////////////////////////////////
/*  Project:        bottleFiller
 *  Author:         Hendrik P.
 *  Date:           2019-05-30
 *  Version:        0.1
 *  Add. Libs:      NONE
 *  License:        CC-BY-NC-SA
 *  
 *  Summary:                         
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include "electrode.h"
#include "light.h"
#include "valve.h"

Electrode electrode(ELECTRODEPIN, DETECTIONVALUE);

Valve beerValve(BEERVALVEPIN);
Valve co2Valve(CO2VALVEPIN);

Light electrodeLight(ELECTRODELEDPIN);
Light safetyClampLight(SAFTEYCLAMPLEDPIN);
Light safetyHousingLight(SAFTEYHOUSELEDPIN);
Light pressureSensorLight(PRESSURELEDPIN);
Light startLight(STARTSWITCHLEDPIN);
Light stopLight(STOPSWITCHLEDPIN);

long startTimeStamp = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  #if SERIALOUT
    Serial.begin(BAUDRATE);
    Serial.println("bottleFiller v0.1");
    Serial.println("by Hendrik P. \n");
  #endif

  pinMode(STARTSWITCHPIN, INPUT);
  pinMode(STOPSWITCHPIN, INPUT);
  pinMode(MODESWITCHPIN, INPUT);
  pinMode(BUTTONSWITCH, INPUT);

  pinMode(SAFTEYHOUSINGPIN, INPUT);
  pinMode(SAFTEYCLAMPPIN, INPUT);
  pinMode(PRESSURESENSORPIN, INPUT);

}

void loop() {
  if(digitalRead(STOPSWITCHPIN) == SAFETYSWACTIVE){
    // Safestate of the bottleFiller
    #if SERIALOUT
      Serial.println("Entered Safestate!");
    #endif
    while(digitalRead(MODESWITCHPIN) == SWITCHINACTIVE || digitalRead(BUTTONSWITCH) == SWITCHINACTIVE){
      stopLight.blinkLight(BLINKTIME);
      beerValve.closeValve();
      co2Valve.closeValve();
      safetyLights();
    }
    stopLight.turnOn();
    #if SERIALOUT
      Serial.println("Left Safestate.");
    #endif
    delay(500);
    
  }else if(digitalRead(SAFTEYHOUSINGPIN) == SAFETYSWACTIVE || digitalRead(SAFTEYCLAMPPIN) == SAFETYSWACTIVE){
    // Waitstate
    beerValve.closeValve();
    co2Valve.closeValve();
    safetyLights();
    stopLight.turnOn();
    
  }else{
    // RunState
    safetyLights();
    stopLight.turnOn();
    if(startCondition()){
      #if SERIALOUT
        Serial.println("Starting fill process.");
      #endif
      startTimeStamp = millis();
      while(fillClearance()){
        startLight.blinkLight(BLINKTIME);
        fillingProcess(startTimeStamp);
      }
      beerValve.closeValve();
      co2Valve.closeValve();
      #if SERIALOUT
        Serial.println("Ended fill process.");
      #endif
      startLight.turnOn();
    }
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////


void safetyLights(){
  if(digitalRead(SAFTEYHOUSINGPIN) ==  SAFETYSWACTIVE){
    safetyHousingLight.blinkLight(BLINKTIME);
  }else{
    safetyHousingLight.turnOn();
  }
  if(digitalRead(SAFTEYCLAMPPIN) ==  SAFETYSWACTIVE){
    safetyClampLight.blinkLight(BLINKTIME);
  }else{
    safetyClampLight.turnOn();
  }
  if(electrode.get_sensingValue()){
    electrodeLight.turnOn();
  }else{
    electrodeLight.turnOff();
  }
}


bool startCondition(){
  if(!digitalRead(STOPSWITCHPIN) || !digitalRead(SAFTEYHOUSINGPIN) || !digitalRead(SAFTEYCLAMPPIN)){
    return false;
  }
  if(digitalRead(STARTSWITCHPIN)){
    return true;
  }
  return false;
}

bool fillClearance(){
  if(!digitalRead(STOPSWITCHPIN) || !digitalRead(SAFTEYHOUSINGPIN) || !digitalRead(SAFTEYCLAMPPIN)){
    return false;
  }
  if(electrode.get_sensingValue()){
    electrodeLight.turnOn();
    return false;
  }
  return true;
}


void fillingProcess(long startTime){
  if(startTime + GASFILLTIME > millis()){
    beerValve.closeValve();
    co2Valve.openValve();
  }else{
    co2Valve.closeValve();
    beerValve.openValve();
  }
}
