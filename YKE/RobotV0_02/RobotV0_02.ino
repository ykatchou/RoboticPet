#include "common.h"
#include "logger.h"

#include "shell.h"
#include "motor.h"
#include "ultrasonic.h"

/****************************************************************/
/* MAIN */
/****************************************************************/

Ultrasonic sonic;
Motor motors[4];

void setup() {
  log_init();

  ultrasonic_configure(&sonic, 0x0020, 1,2);

  logline("---- Initialize ----");
  //Front Left
  motor_configure(&(motors[0]), 0x0010, 0, MOTOR_POSITION_L ,0, 7, 6);
  //Front Right
  motor_configure(&(motors[1]), 0x0011, 0, MOTOR_POSITION_R,0, 3, 2);
  //Back Left
  motor_configure(&(motors[2]), 0x0012,  0, MOTOR_POSITION_L, 0, 9, 8);
  //Back Right
  motor_configure(&(motors[3]), 0x0013,  0, MOTOR_POSITION_R, 0, 5, 4);
}


void loop() {  
}
















