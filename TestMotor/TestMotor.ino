#include "common.h"
#include "logger.h"
#include "motor.h"

Motor motors[4];

void setup() {

  delay(1000);
  logline("---- Initialize ----");
  Motor* Front_L= &(motors[0]);
  Motor* Front_R= &(motors[1]);
  Motor* Back_L= &(motors[2]);
  Motor* Back_R= &(motors[3]);

  motor_configure(Front_L, 0x0010, 0, MOTOR_POSITION_L ,0, 7, 6);
  motor_configure(Front_R, 0x0011, 0, MOTOR_POSITION_R,0, 3, 2);
  motor_configure(Back_L, 0x0012,  0, MOTOR_POSITION_L, 0, 9, 8);
  motor_configure(Back_R, 0x0013,  0, MOTOR_POSITION_R, 0, 5, 4);

  motor_init(Front_L);
  motor_init(Front_R);
  motor_init(Back_L);
  motor_init(Back_R);

  log_init();

  delay(3000);
  logline("---- Initialize OK ----");
  logline("Wait for GO (g): ");
}


void loop()
{
  byte input= Serial.read();
  if(input == 'g'){
    logline("Go !");

    //moveOne(Front_L,300, MOTOR_DIRECTION_FWD);
    //moveOne(Front_R,300, MOTOR_DIRECTION_FWD);
    //moveOne(Back_L,300, MOTOR_DIRECTION_FWD);
    //moveOne(Back_R,300, MOTOR_DIRECTION_FWD);

    //moveMany(motors, 4, 2000, MOTOR_DIRECTION_FWD);

    int motorsLindex[2]={
      0,2                        };
    int motorsRindex[2]={
      1,3                        };

    motor_rotateMany(motors, 4, 90);
    delay(100);
    motor_rotateMany(motors, 4, -90);
    delay(100);

    logline("done.");
  }
  else{
    delay(1000);
  }
}



















































