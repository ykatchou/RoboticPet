#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "common.h"

/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos nécessaires à un capteur ultrason.
 */
typedef struct{
  int iId;
  int iIsActive;
  int iPinTrigger;
  int iPinEcho;
} 
Ultrasonic;

/***************************************************
 * Constantes
 ****************************************************/

/***************************************************
 * Fonctions
 ****************************************************/
void ultrasonic_configure(Ultrasonic* sonic,int id, int pintrigger, int pinecho){
  sonic->iId = id;
  sonic->iPinTrigger = pintrigger;
  sonic->iPinEcho = pinecho;

  pinMode(sonic->iPinTrigger, OUTPUT);
  pinMode(sonic->iPinEcho, INPUT); 
  sonic->iIsActive = 1;
}

float ultrasonic_microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}

float ultrasonic_measure(Ultrasonic* sonic){
  long duration;
  float cm;

  digitalWrite(sonic->iPinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(sonic->iPinTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonic->iPinTrigger, LOW);

  //  // read the analog in value:
  //  int sensorValue = analogRead(pinEcho);            
  //  // map it to the range of the analog out:
  //  int outputValue = map(sensorValue, 0, 1023, 0, 255);  

  duration = pulseIn(sonic->iPinEcho, HIGH,50000);
  // convert the time into a distance
  cm = ultrasonic_microsecondsToCentimeters(duration);
  return cm;
}

#endif




