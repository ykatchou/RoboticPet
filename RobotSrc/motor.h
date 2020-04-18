#ifndef MOTOR_H
#define MOTOR_H

#include "common.h"

/***************************************************
* Structures
****************************************************/

/**
 * Definit les infos nécessaires à un moteur.
 */
typedef struct{
  uint iId;
  int iIsActive;
  int iPinEnable;
  int iPinFwd;
  int iPinRev;
  
  //0 : N/A, 1 : Left, 2 : Right
  int iPosition;
} 
Motor;

/***************************************************
* Constantes
****************************************************/
const int MOTOR_DIRECTION_FWD=1;
const int MOTOR_DIRECTION_REV=2;

const int MOTOR_POSITION_NONE=0;
const int MOTOR_POSITION_L=1;
const int MOTOR_POSITION_R=2;


/***************************************************
* Fonctions
****************************************************/

/**
 * Arrête un moteur.
 */
void motor_stop (Motor* motor, boolean bStayActive){
  digitalWrite(motor->iPinFwd, LOW);
  digitalWrite(motor->iPinRev, LOW);

  if(bStayActive){
    digitalWrite(motor->iPinEnable, HIGH);
  }
  else{
    digitalWrite(motor->iPinEnable, LOW);
    motor->iIsActive=0;
  }
  delayMicroseconds(2);
}

/**
 * Permet de configurer en une ligne un moteur.
 */
void motor_configure(Motor* motor, uint id, int isactive, int position,int pinenable, int pinfwd, int pinrev){
  motor->iId = id;
  motor->iIsActive = isactive;
  motor->iPinEnable = pinenable;
  motor->iPinFwd = pinfwd;
  motor->iPinRev = pinrev;
  motor->iPosition = position;
  
  pinMode(motor->iPinEnable, OUTPUT);
  pinMode(motor->iPinFwd, OUTPUT);
  pinMode(motor->iPinRev, OUTPUT);
  motor->iIsActive = 0;

  motor_stop(motor, false);
}

/**
 * Active simplement un moteur (pas de verif !)
 */
void motor_toggle(Motor* motor, int idirection, boolean force_init){
  if(force_init){
    digitalWrite(motor->iPinFwd, LOW);
    digitalWrite(motor->iPinRev, LOW);
  }

  //FWD
  if(idirection ==1){
    digitalWrite(motor->iPinFwd, HIGH);
  }
  //REV
  else if(idirection ==2){    
    digitalWrite(motor->iPinRev, HIGH);
  }
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void motor_moveOne(Motor* motor, ulong idelayms, int idirection)
{
  if(motor->iIsActive=true){
    motor_stop(motor,true);
  }

  motor_toggle(motor, idirection, true);

  delay(idelayms);
  logline("fin move");
  motor_stop(motor, true);
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void motor_moveMany(Motor motorArray[], int motorArrayLength, ulong idelayms, int idirection)
{
  int i=0;

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    if(pmotor->iIsActive=true){
      motor_stop(pmotor,true);
    }
  }

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    motor_toggle(pmotor, idirection, true);
  }

  delay(idelayms);
  logline("fin move many motor");

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    motor_stop(pmotor,true);
  }
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 * If iAngle > 0, turn right else turn left.
 */
void motor_rotateMany(Motor motorArray[],int motorLenghtTotal, int iAngle)
{
  int i=0;

  //CALCUL !
  //vitesse angulaire en ms/0°
  int angularspeed = 10;  
  int idelayms = 0;
  int DirectionL=MOTOR_DIRECTION_FWD;
  int DirectionR=MOTOR_DIRECTION_REV;

  if(iAngle<0){
    DirectionL=MOTOR_DIRECTION_REV;
    DirectionR=MOTOR_DIRECTION_FWD;
  }
  idelayms = abs(int(angularspeed * iAngle));
  char buffer[80];
  sprintf(buffer, "Turn angle %i, timing %i ms", iAngle, idelayms);
  logline(buffer);  

  //STOP ALL
  for(i=0; i<motorLenghtTotal; i++){
    Motor* pmotor = &(motorArray[i]);
    if(pmotor->iIsActive=true){
      motor_stop(pmotor,true);
    }
  }

  if(idelayms<100){
    logline("No turn (not enough angle)");
  }
  else{

    //TURN!!!
    for(i=0; i<motorLenghtTotal; i++){
      Motor* pmotor = &(motorArray[i]);
      switch(pmotor->iPosition){
      case MOTOR_POSITION_L:
        motor_toggle(pmotor, DirectionL,true);
        break;
      case MOTOR_POSITION_R:
        motor_toggle(pmotor, DirectionR,true);
        break;
      default:
        break;
      }
    }

    //END TURN!!!
    delay(idelayms);
    logline("fin turn motor");


    //STOP ALL
    for(i=0; i<motorLenghtTotal; i++){
      Motor* pmotor = &(motorArray[i]);
      motor_stop(pmotor,true);
    }
  }
}

#endif

