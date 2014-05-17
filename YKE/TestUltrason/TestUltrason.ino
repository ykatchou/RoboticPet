#include "ultrasonic.h"

void setup() {
  ultrasonic_init();

  if(DEBUG_ON){
    // initialize serial communication:
    Serial.begin(9600);
  }
}

void loop()
{

  if(DEBUG_ON){
    Serial.print(ultrasonic_measure());
    Serial.print("cm");
    Serial.println();
  }

  delay(100);
}




