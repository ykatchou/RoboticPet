#include "common.h"
#include "logger.h"

#include "shell.h"

#include "motor.h"

#include "ultrasonic.h"
#include "hydrometric.h"
#include "soundsensor.h"
//#include "display_double8bitled.h"

/****************************************************************/
/* MAIN */
/****************************************************************/

Device devices[10];

//Hydrometric hydro;
//Ultrasonic sonic;
Motor motors[4];
//Double8bitled displayled;

void setup() {
  log_init();
  logline("---- Initialize ----");

  shell_configure();

//  ultrasonic_configure(&sonic, DEVICE_TYPE_ULTRASONIC+0, 1,2);
//  hydrometric_configure(&hydro,DEVICE_TYPE_HYDROMETRIC+0,20);

 //Front Left
 motor_configure(&(motors[0]), DEVICE_TYPE_MOTOR+0, 0, MOTOR_POSITION_L ,0, 7, 6);
 //Front Right
 motor_configure(&(motors[1]), DEVICE_TYPE_MOTOR+1, 0, MOTOR_POSITION_R,0, 3, 2);
 //Back Left
 motor_configure(&(motors[2]), DEVICE_TYPE_MOTOR+2,  0, MOTOR_POSITION_L, 0, 9, 8);
 //Back Right
 motor_configure(&(motors[3]), DEVICE_TYPE_MOTOR+3,  0, MOTOR_POSITION_R, 0, 5, 4);

 //device_configure(&(devices[0]), DEVICE_TYPE_ULTRASONIC,0, &sonic, "ultrason");
 //device_configure(&(devices[1]), DEVICE_TYPE_HYDROMETRIC,0, &hydro, "hydrométrie et température");
 device_configure(&(devices[2]), DEVICE_TYPE_MOTOR,1, &(motors[0]), "moteur avant-gauche");
 device_configure(&(devices[3]), DEVICE_TYPE_MOTOR,2, &(motors[1]), "moteur avant-droite");
 device_configure(&(devices[4]), DEVICE_TYPE_MOTOR,3, &(motors[2]), "moteur arrière-gauche");
 device_configure(&(devices[5]), DEVICE_TYPE_MOTOR,4, &(motors[3]), "moteur arrière-droite");
 //device_configure(&(devices[0]), DEVICE_TYPE_DISPLAY_DOUBLELED, 1, &displayled, "Double led display");

  logline("---- Initialize OK ----");

  delay(3000);
}

void loop() {

  //shell_launch();
  //scenario_light();

  scenario();
  
  //double8bitled_test(&)
}


void shell_launch(){

  char c = shell_read();
  switch(c){
    case 'U':
      motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_FWD);
      break;
    case 'D':
      motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_REV);
      break;
    case 'L':
      motor_rotateMany(motors, 4, -90);
      break;
    case 'R':
      motor_rotateMany(motors, 4, 90);
      break;
    case 'S':
    default:
      motor_stop(motors, true);
      break;
  }

}



void scenario_light(){

  for(int i=0; i<10; i++){
    motor_moveMany(motors, 4, 200, MOTOR_DIRECTION_FWD);
  }

  delay(1000);
}

void scenario(){

  for(int i=0; i<10; i++){
    motor_moveMany(motors, 4, 200, MOTOR_DIRECTION_FWD);
  }

  delay(1000);
  
  for(int i=0; i<10; i++){
    motor_moveMany(motors, 4, 200, MOTOR_DIRECTION_FWD);
  }
  
  //LEFT
  motor_rotateMany(motors, 4, -90);
  motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_FWD);

  //RIGHT
  motor_rotateMany(motors, 4, 90);
  motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_FWD);

  motor_rotateMany(motors, 4, 180);
  motor_moveMany(motors, 4, 3000, MOTOR_DIRECTION_FWD);
  
  motor_rotateMany(motors, 4, -90);
  motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_FWD);

}
