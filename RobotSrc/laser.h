#ifndef LASER_H
#define LASER_H

#include "common.h"

/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos nécessaires à un capteur laser.
 */
typedef struct{
  uint Id;
  int iIsActive;
  int iPinTrigger;
} 
Laser;

/***************************************************
 * Constantes
 ****************************************************/

/***************************************************
 * Fonctions
 ****************************************************/
void laser_configure(Laser* laser, int pintrigger){
  laser->Id = id;
  laser->iPinTrigger = pintrigger;
  pinMode(laser->iPinTrigger, OUTPUT);
  laser->iIsActive = 1;
}

/**
 * Active ou désactive le laser.
 * @param laser le laser à activer ou désactiver.
 * @param targetValue la valeur cible de l'activation du laser.
 * @return true si le laser a été activé ou désactivé, false sinon.
 */
bool laser_toggle(Laser* laser, bool targetValue){
  if(laser->iIsActive != targetValue){
    laser->iIsActive = targetValue;

    if(laser->iIsActive){
      digitalWrite(laser->iPinTrigger, HIGH);
    }else{
      digitalWrite(laser->iPinTrigger, LOW);
    }

    return true;
  }
  return false;
}

#endif

