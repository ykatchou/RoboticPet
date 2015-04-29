#ifndef HYDROMETRIC_H
#define HYDROMETRIC_H

#include "common.h"

/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos nécessaires à un capteur hydrometric (DHT11 Sensor 140C03).
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
#define BUFFERSIZE 34

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

  char logbuffer[80];

  //On envoie la commande START au capteur :
  //envoyer LOW pendant au moins 18ms puis HIGH pendant 40us
  pinMode(hydro->iPinData, OUTPUT); 
  digitalWrite(hydro->iPinData, LOW);
  delay(20);
  digitalWrite(hydro->iPinData, HIGH);
  delayMicroseconds(40);
  digitalWrite(hydro->iPinData, LOW);

  //On regarde si le capteur à bien reçu le start : 
  pinMode(hydro->iPinData, INPUT); 
  int iRawBufferIndex=0;
  char aRawBuffer[BUFFERSIZE];
  int aDurationBuffer[BUFFERSIZE];

  //Puis reception  LOW 80us puis HIGH 80us
  int iStart=  pulseIn(hydro->iPinData, HIGH);
  if(iStart>60){
    sprintf(logbuffer, "Hydrometric [%i] : Start OK",hydro->iId);
    logline(logbuffer);
    iResult=1;
  }
  else{
    sprintf(logbuffer, "Hydrometric [%i] : Start ERROR : Capteur non présent ?",hydro->iId);
    logline(logbuffer);
    iResult=0;
  }

  //Data : Pour chaque bit de données : 50us LOW puis
  //  1 = HIGH durant 27us
  //  0 = HIGH durant 70us
  //Fin = 50us LOW
  //TOTAL : 40bit of data (4mS)
  //Data = 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check-sum.

  //Pour des questions de performances, on fait d'abord un dump du signal.
  iRawBufferIndex=0;
  while(iRawBufferIndex<BUFFERSIZE){
    int duration = pulseIn(hydro->iPinData, HIGH,200); 
    aDurationBuffer[iRawBufferIndex] = duration;
    iRawBufferIndex++;
  }

  //Analyse du signal :
  iRawBufferIndex=0;
  while(iRawBufferIndex<BUFFERSIZE && iResult==1){

    int duration = aDurationBuffer[iRawBufferIndex];

    if(duration > 1 && duration < 40){
      aRawBuffer[iRawBufferIndex] = 1;
    }
    else if(duration >50 && duration < 90){
      aRawBuffer[iRawBufferIndex] = 0;
    }
    else{
      aRawBuffer[iRawBufferIndex] = -1;
      iResult=0;
    }

    sprintf(logbuffer, "Hydrometric [%i] : Buffer[%i] : %i",hydro->iId ,iRawBufferIndex, aRawBuffer[iRawBufferIndex]);
    logline(logbuffer);

    iRawBufferIndex++;
  }

  if(iResult == 1){ 
    for(iRawBufferIndex=0;iRawBufferIndex<BUFFERSIZE;iRawBufferIndex++){
      sprintf(logbuffer, "Hydrometric [%i] : RawBuffer[%i] : %i",hydro->iId ,iRawBufferIndex, aRawBuffer[iRawBufferIndex]);
      //logline(logbuffer);  
    }
    sprintf(logbuffer, "Hydrometric [%i] : Temperature : %d, Hydrometry  : %d",hydro->iId ,hydro->fTemperature, hydro->fHydrometry);
  }
  else{
    sprintf(logbuffer, "Hydrometric [%i] : Mesured failed",hydro->iId ,hydro->fTemperature, hydro->fHydrometry);
  }
  logline(logbuffer);  

  return iResult;
}

#endif










