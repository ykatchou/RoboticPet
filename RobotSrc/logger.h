#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

int DEBUG_ON=1;

void log_init(){
  if(DEBUG_ON){
    // initialize serial communication:
    Serial.begin(9600);
  }
}

/**
 * Fonction permettant de logger une chaîne de caractère (sans retour chariot !).
 */
void log(char* str){
  if(DEBUG_ON){
    Serial.print(str);
  }
}

/**
 * Fonction permettant de logger une chaîne de caractère avec retour chariot.
 */
void logline(char* str){
  if(DEBUG_ON){
    Serial.println(str);
  }
}

#endif

