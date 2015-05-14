#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

const int Ultrasonic_PinTrigg = 4;
const int Ultrasonic_pinEcho = 14;
const int DEBUG_ON=1;


void ultrasonic_init(){
  pinMode(Ultrasonic_PinTrigg, OUTPUT);
  pinMode(Ultrasonic_pinEcho, INPUT);  
}

float ultrasonic_microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}

float ultrasonic_measure(){
  long duration;
  float cm;
    
  digitalWrite(Ultrasonic_PinTrigg, LOW);
  delayMicroseconds(2);
  digitalWrite(Ultrasonic_PinTrigg, HIGH);
  delayMicroseconds(5);
  digitalWrite(Ultrasonic_PinTrigg, LOW);

  //  // read the analog in value:
  //  int sensorValue = analogRead(pinEcho);            
  //  // map it to the range of the analog out:
  //  int outputValue = map(sensorValue, 0, 1023, 0, 255);  

  duration = pulseIn(Ultrasonic_pinEcho, HIGH,50000);
  // convert the time into a distance
  cm = ultrasonic_microsecondsToCentimeters(duration);

  return cm;
}

#endif

