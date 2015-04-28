#ifndef HYDROMETRIC_H
#define HYDROMETRIC_H

#include "common.h"

/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos n�cessaires � un capteur hydrometric (DHT11 Sensor 140C03).
 */
typedef struct{
  int iId;
  int iIsActive;
  int iPinData;
  
  int iMeasureIsOK;
  float fTemperature;
  float fHydrometry;
} 
Hydrometric;

/***************************************************
 * Constantes
 ****************************************************/

/***************************************************
 * Fonctions
 ****************************************************/
void hydrometric_configure(Hydrometric* hydro,int id, int pindata){
  hydro->iId = id;
  hydro->iPinData = pindata;
  
  hydro->iMeasureIsOK = 0;
  hydro->fTemperature = 0.0;
  hydro->fHydrometry = 0.0;
  
  pinMode(hydro->iPinData, INPUT); 
  hydro->iIsActive = 1;

}

//Retourne 1 si la mesure est OK, 0 sinon.
int hydrometric_measure(Hydrometric* hydro){
  int iResult=0;
  
  //envoyer LOW pendant au moins 18ms puis HIGH pendant 40us
  //Puis reception  LOW 80us puis HIGH 80us
  //Data : 50us LOW puis
  //  1 = HIGH durant 27us
  //  0 = HIGH durant 70us
  //Fin = 50us LOW
  //TOTAL : 40bit of data (4mS)
  //Data = 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check-sum.
  

  // read the analog in value:
//  int sensorValue = analogRead(hydro->iPinData);            
  
  // map it to the range of the analog out:
//  float fPercentageValue = sensorValue / 1024;

  char buffer[80];
  if(iResult == 1){
    sprintf(buffer, "Hydrometric [%i] : Temperature : %d, Hydrometry  : %d",hydro->iId ,hydro->fTemperature, hydro->fHydrometry);
  }else{
    sprintf(buffer, "Hydrometric [%i] : Mesured failed",hydro->iId ,hydro->fTemperature, hydro->fHydrometry);
  }
  logline(buffer);  
 
  return iResult;
}

#endif

