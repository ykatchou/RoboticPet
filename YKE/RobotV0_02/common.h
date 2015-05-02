#ifndef COMMON_H
#define COMMON_H

#include "Arduino.h"

#define uint unsigned int
#define ulong unsigned long
#define bool boolean

/***************************************************
 * Constantes
 ****************************************************/
const uint DEVICE_TYPE_MOTOR = 0x0010;
const uint DEVICE_TYPE_ULTRASONIC = 0x0020;
const uint DEVICE_TYPE_HYDROMETRIC = 0x0030;


/***************************************************
 * Structures
 ****************************************************/
typedef struct{
  uint Id;
  uint uiType;
  void* pDevice;
  char* strName;
} 
Device;


/***************************************************
 * Fonctions
 ****************************************************/

Device* device_configure(Device* device, uint id,uint type, void* pdevice, char* deviceName){
  device->Id = id;
  device->uiType = type;
  device->pDevice = pdevice;
  device->strName = deviceName;

  return device;
}

uint device_rawid(Device* device){
  uint o_id=0xFFFF;
  
  //if(device!=null && device.pDevice !=null){
    o_id= *(device->pDevice+);
  //}
  
  return o_id;
}

#endif



