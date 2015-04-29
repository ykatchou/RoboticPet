#ifndef HYDROMETRIC_H
#define HYDROMETRIC_H

#include "common.h"

//#define DEBUG

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
  uint iTemperature;
  uint iHydrometry;
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
  hydro->iTemperature = 0.0;
  hydro->iHydrometry = 0.0;

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
    sprintf(logbuffer, "Hydrometric [%i] : Start ERROR : Capteur non present en %i",hydro->iId, hydro->iPinData);
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

uint hydrometric_convert(byte* aBuffer, int iStartIndex, int iCount, int iDebug){
  uint bOut=0;
  int iIndex;
  char logbuffer[20];

#ifdef DEBUG
    log("Convert : ");
#endif

  //Big endian.
  if(iCount>=0 && iStartIndex>=0){
    iIndex=iStartIndex;
    while(iIndex < iStartIndex + iCount){

      bOut = bOut<<1;
      bOut= bOut + aBuffer[iIndex];

#ifdef DEBUG
      sprintf(logbuffer, "%i",aBuffer[iIndex]);
      log(logbuffer);
#endif

      iIndex++;
    }
  }
  //Little endian
  else if(iCount<0 && iStartIndex>=0){
    iIndex=iStartIndex - iCount;
    while(iIndex > iStartIndex){

      bOut = bOut<<1;
      bOut= bOut + aBuffer[iIndex];

#ifdef DEBUG
        sprintf(logbuffer, "%i",aBuffer[iIndex]);
        log(logbuffer);
#endif
      iIndex--;
    }
  }


#ifdef DEBUG
    sprintf(logbuffer, " => %i",bOut);
    logline(logbuffer);
#endif

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
    // ===========> Il semble y avoir une erreur dans la DOC !! 1 >60us et 0 <40us !!!
    //Fin = 50us LOW
    //TOTAL : 40bit of data (4mS)
    //Data = 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check-sum.
    if(duration >= 15 && duration < 35){
      aBitBuffer[iRawBufferIndex] = 0;
    }
    else if(duration >60 && duration < 80){
      aBitBuffer[iRawBufferIndex] = 1;
    }
    else{     
      aBitBuffer[iRawBufferIndex] =0;
      iResult=0;
      sprintf(logbuffer, "Hydrometric [%i] : Duration Error (%i)",hydro->iId,duration);
      logline(logbuffer);
    }
    iRawBufferIndex++;
  }

  if(iResult == 1){ 
    
#ifdef DEBUG
    int i;
    for(i=0; i<BUFFERSIZE;i++){
      sprintf(logbuffer, "%i",aBitBuffer[i]);
      log(logbuffer);
      if((i+1)%4==0 && i>0){
        log(" ");
      }
      if((i+1)%8==0 && i>0){        
        logline("");      
      }
    }
#endif

    hydro->iHydrometry=hydrometric_convert(aBitBuffer,0,8,1);
    hydro->iTemperature=hydrometric_convert(aBitBuffer,16,8,1); 

    //hydro->iHydrometry = map(hydro->iHydrometry, 0,255, 20,90);
    //hydro->iTemperature = map(hydro->iTemperature, 0,255, 0,50);

    hydro->iMeasureIsOK=1;
  }
  else{
    hydro->iHydrometry=0;
    hydro->iTemperature=0;
    hydro->iMeasureIsOK=0;
  }

  if(hydro->iMeasureIsOK == 1){
    sprintf(logbuffer, "Hydrometric [%i] : OK : Temperature : %i, Hydrometry  : %i",hydro->iId ,hydro->iTemperature, hydro->iHydrometry);
    logline(logbuffer);  
  }
  else{
    sprintf(logbuffer, "Hydrometric [%i] : NOK : Mesured failed",hydro->iId);
    logline(logbuffer);  
  }

  return iResult;
}

//Retourne 1 si la mesure est OK, 0 sinon.
int hydrometric_IsMesureOk(Hydrometric* hydro){
  return hydro->iMeasureIsOK;
}

//Retourne la temperature (x10) en celsius si la mesure est OK, sinon -1.
int hydrometric_GetTemperature(Hydrometric* hydro){
  int iOut = -1;
  if(hydro->iMeasureIsOK == 1)
  {
    iOut = hydro->iTemperature;
  }

  return iOut;
}

//Retourne l'hydrometrie (en %) si la mesure est OK, sinon -1.
int hydrometric_GetHydrometry(Hydrometric* hydro){
  int iOut = -1;
  if(hydro->iMeasureIsOK == 1)
  {
    iOut = hydro->iHydrometry;
  }

  return iOut;
}

#endif




































