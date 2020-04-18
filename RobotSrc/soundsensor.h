#ifndef SOUNDSENSOR_H
#define SOUNDSENSOR_H

#include "common.h"

/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos nécessaires à un capteur soundsensor.
 */
typedef struct{
  uint Id;
  int iIsActive;
  int iPinActivation;
  int iPinSensorValue;
} 
Soundsensor;

/***************************************************
 * Constantes
 ****************************************************/

/***************************************************
 * Fonctions
 ****************************************************/
void soundsensor_configure(Soundsensor* soundsensor, uint id, int pinactivation, int pinsensorvalue){
  soundsensor->Id = id;
  soundsensor->iPinActivation = pinactivation;
  soundsensor->iPinSensorValue = pinsensorvalue;

  pinMode(soundsensor->iPinSensorValue, OUTPUT);
  pinMode(soundsensor->iPinActivation, INPUT); 
  soundsensor->iIsActive = 1;
}

#endif




