#ifndef DISPLAY_DOUBLE8BITLED_H
#define DISPLAY_DOUBLE8BITLED_H

#include "common.h"

#include <Adafruit_LEDBackpack.h>


/***************************************************
 * Structures
 ****************************************************/

/**
 * Definit les infos nécessaires à un capteur ultrason.
 */
typedef struct{
  uint Id;
  int iIsActive;
  int iPinDIO;
  int iPinRCLK;
  int iPinSCLK;
} 
Double8bitled;

/***************************************************
 * Constantes
 ****************************************************/
// array to activate particular digit on the 8x7segment module
// it is the common anode of 7 segment
const byte anode[8] = { 0b10000000,  //digit 1 from right
                    0b01000000,  //digit 2 from right
                    0b00100000,  //digit 3 from right
                    0b00010000,  //digit 4 from right
                    0b00001000,  //digit 5 from right
                    0b00000100,  //digit 6 from right
                    0b00000010,  //digit 7 from right
                    0b00000001   //digit 8 from right                                         
                    };
 
//array for decimal number, it is the cathode.
//logic low will activate the particular segment
const byte cathode[12] = {0b11000000,  // 0
                    0b11111001,  // 1
                    0b10100100,  // 2
                    0b10110000,  // 3
                    0b10011001,  // 4
                    0b10010010,  // 5
                    0b10000010,  // 6
                    0b11111000,  // 7
                    0b10000000,  // 8
                    0b10010000,  // 9  
                    0b01111111,  //dot                  
                    0b11111111   //blank
                    };


/***************************************************
 * Fonctions
 ****************************************************/
void double8bitled_configure(Double8bitled* displayled, uint id, int pindio, int pinrclk, int pinsclk){
  displayled->Id = id;
  displayled->iPinDIO = pindio;
  displayled->iPinRCLK = pinrclk;
  displayled->iPinSCLK = pinsclk;

  pinMode(displayled->iPinDIO, OUTPUT);
  pinMode(displayled->iPinRCLK, OUTPUT);
  pinMode(displayled->iPinSCLK, OUTPUT);

  digitalWrite(displayled->iPinDIO, LOW);
  digitalWrite(displayled->iPinRCLK, LOW);
  digitalWrite(displayled->iPinSCLK, LOW);
  
  displayled->iIsActive = 1;
}


void double8bitled_test(Double8bitled* displayled){
}

#endif




