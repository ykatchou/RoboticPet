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
#define BUFFERSIZE 40

/***************************************************
 * Fonctions
 ****************************************************/
void hydrometric_configure(Hydrometric* hydro,int id, int pindata){
  hydro->iId = id;
  hydro->iPinData = pindata;

  hydro->iMeasureIsOK = 0;
  hydro->fTemperature = 0.0;
  hydro->fHydrometry = 0.0;

  hydro->iIsActive = 1;
}

int hydrometric_dumpsignal(Hydrometric* hydro, byte* aRawBuffer){
  int iResult=0;
  char logbuffer[80];
  int  iRawBufferIndex=0;

  //On envoie la commande START au capteur :
  //envoyer LOW pendant au moins 18ms puis HIGH pendant 40us
  pinMode(hydro->iPinData, OUTPUT); 
  digitalWrite(hydro->iPinData, LOW);
  delay(50);
  digitalWrite(hydro->iPinData, HIGH);
  delayMicroseconds(40);
  digitalWrite(hydro->iPinData, LOW);

  //On regarde si le capteur à bien reçu le start : 
  pinMode(hydro->iPinData, INPUT); 

  //Puis reception  LOW 80us puis HIGH 80us
  int iStart=  pulseIn(hydro->iPinData, HIGH);
  if(iStart>=60 && iStart <= 100){
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
  while(iRawBufferIndex<BUFFERSIZE && iResult==1){
    int duration;
    aRawBuffer[iRawBufferIndex] = pulseIn(hydro->iPinData, HIGH,200);
    iRawBufferIndex++;
  }

  return iResult;
}

byte hydrometric_convert(byte* aBuffer, int iStartIndex, int iCount){
  byte bOut=0;
  int iIndex=iStartIndex;

  char logbuffer[80];

  if(iCount>=0){
    while(iIndex<iStartIndex + iCount){
      bOut = bOut<<1;
      bOut= bOut + aBuffer[iIndex];
      iIndex++;
    }
  }
  else{
    while(iIndex>iStartIndex + iCount){
      bOut = bOut<<1;
      bOut= bOut + aBuffer[iIndex];
      iIndex--;
    }
  }
  return bOut;
}

//Retourne 1 si la mesure est OK, 0 sinon.
int hydrometric_measure(Hydrometric* hydro){
  int iResult=0;
  char logbuffer[80];

  int iRawBufferIndex=0;
  byte aRawBuffer[BUFFERSIZE];
  byte aBitBuffer[BUFFERSIZE];

  //Retrieve the signal.
  iResult = hydrometric_dumpsignal(hydro, aRawBuffer);

  //Analyse du signal :
  iRawBufferIndex=0;
  while(iRawBufferIndex<BUFFERSIZE && iResult==1){
    int duration = aRawBuffer[iRawBufferIndex];

    //Rappel :
    //Data : Pour chaque bit de données : 50us LOW puis
    //  1 = HIGH durant 27us
    //  0 = HIGH durant 70us
    //Fin = 50us LOW
    //TOTAL : 40bit of data (4mS)
    //Data = 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check-sum.
    if(duration > 15 && duration < 35){
      aBitBuffer[iRawBufferIndex] = 1;
    }
    else if(duration >60 && duration < 80){
      aBitBuffer[iRawBufferIndex] = 0;
    }
    else{     
      aBitBuffer[iRawBufferIndex] =0;
      iResult=0;
      sprintf(logbuffer, "Hydrometric [%i] : Duration Error (%i)",hydro->iId,duration);
      logline(logbuffer);
    }
    iRawBufferIndex++;
  }

  hydro->iMeasureIsOK = iResult;

  if(iResult == 1){ 
    //for(iRawBufferIndex=0;iRawBufferIndex<BUFFERSIZE;iRawBufferIndex++){
    //  sprintf(logbuffer, "Hydrometric [%i] : Buffer[%i] : %i",hydro->iId ,iRawBufferIndex, aBitBuffer[iRawBufferIndex]);
    //  logline(logbuffer);  
    //}

    hydro->fHydrometry=hydrometric_convert(aBitBuffer,0,8);
    hydro->fTemperature=hydrometric_convert(aBitBuffer,16,8);   

    hydro->fTemperature = map(hydro->fTemperature, 0,255, 0,50) / 10.0;
    hydro->fHydrometry = map(hydro->fHydrometry, 0,255, 20,90) / 10.0;

    sprintf(logbuffer, "Hydrometric [%i] : Temperature : %i, Hydrometry  : %i",hydro->iId ,hydro->fTemperature, hydro->fHydrometry);
  }
  else{
    sprintf(logbuffer, "Hydrometric [%i] : Mesured failed",hydro->iId);
  }
  logline(logbuffer);  

  return iResult;
}

int hydrometric_MesureOk(Hydrometric* hydro){
  return hydro->iMeasureIsOK;
}

float hydrometric_Temperature(Hydrometric* hydro){
  float fOut = -1;
  if(hydro->iMeasureIsOK == 1)
  {
    fOut = hydro->fTemperature;
  }
  
  return fOut;
}

float hydrometric_Hydrometry(Hydrometric* hydro){
  float fOut = -1;
  if(hydro->iMeasureIsOK == 1)
  {
    fOut = hydro->fHydrometry;
  }
  
  return fOut;
}

#endif





















