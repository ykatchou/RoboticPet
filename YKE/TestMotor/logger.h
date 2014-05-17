#ifndef LOGGER_H
#define LOGGER_H

#include "Arduino.h"

int DEBUG_ON=1;

void log(char* str){
  if(DEBUG_ON){
    Serial.print(str);
  }
}

void logline(char* str){
  if(DEBUG_ON){
    Serial.println(str);
  }
}

#endif
