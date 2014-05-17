#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

/**
 * Definit les infos nécessaires à un moteur.
 */
typedef struct{
  int iId;
  int iIsActive;
  int iPinEnable;
  int iPinFwd;
  int iPinRev;
} 
Motor;

int MOTOR_FWD=1;
int MOTOR_REV=2;

#endif

