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
  
  //0 : N/A, 1 : Left, 2 : Right
  int iPosition;
} 
Motor;

const int MOTOR_DIRECTION_FWD=1;
const int MOTOR_DIRECTION_REV=2;

const int MOTOR_POSITION_NONE=0;
const int MOTOR_POSITION_L=1;
const int MOTOR_POSITION_R=2;

#endif

