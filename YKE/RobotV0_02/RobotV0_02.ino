#include "common.h"
#include "logger.h"

#include "shell.h"
#include "motor.h"
#include "ultrasonic.h"

/****************************************************************/
/* MAIN */
/****************************************************************/

Device devices[5];

Ultrasonic sonic;
Motor motors[4];

void setup() {
  log_init();

  logline("---- Initialize ----");

  shell_configure();

  ultrasonic_configure(&sonic, DEVICE_TYPE_ULTRASONIC+0, 1,2);

  //Front Left
  motor_configure(&(motors[0]), DEVICE_TYPE_MOTOR+0, 0, MOTOR_POSITION_L ,0, 7, 6);
  //Front Right
  motor_configure(&(motors[1]), DEVICE_TYPE_MOTOR+1, 0, MOTOR_POSITION_R,0, 3, 2);
  //Back Left
  motor_configure(&(motors[2]), DEVICE_TYPE_MOTOR+2,  0, MOTOR_POSITION_L, 0, 9, 8);
  //Back Right
  motor_configure(&(motors[3]), DEVICE_TYPE_MOTOR+3,  0, MOTOR_POSITION_R, 0, 5, 4);

  device_configure(&(devices[0]), DEVICE_TYPE_ULTRASONIC,0, &sonic, "ultrason");
  device_configure(&(devices[1]), DEVICE_TYPE_MOTOR,1, &(motors[0]), "moteur avant-gauche");
  device_configure(&(devices[2]), DEVICE_TYPE_MOTOR,2, &(motors[1]), "moteur avant-droite");
  device_configure(&(devices[3]), DEVICE_TYPE_MOTOR,3, &(motors[2]), "moteur arrière-gauche");
  device_configure(&(devices[4]), DEVICE_TYPE_MOTOR,4, &(motors[3]), "moteur arrière-droite");

  logline("---- Initialize OK ----");
}

void loop() {
  shell_launch();
}


















