#include "common.h"
#include "logger.h"

#include "shell.h"

#include "motor.h"

#include "ultrasonic.h"
#include "laser.h"

/****************************************************************/
/* MAIN */
/****************************************************************/

Device devices[10];
Motor motors[4];
Ultrasonic sonic;
Laser laser;

long last_ite_timestamp = 0;
long last_switch = 0;

void setup() {
  log_init();
  logline("---- Initialize ----");
  last_ite_timestamp = millis();

  // shell_configure();

  ultrasonic_configure(&sonic, DEVICE_TYPE_ULTRASONIC + 0, 11, 12);
  laser_configure(&laser, DEVICE_TYPE_LASER + 0, 13);

  // Front Left
  motor_configure(&(motors[0]), DEVICE_TYPE_MOTOR + 0, 0, MOTOR_POSITION_L, 0, 7, 6);
  // Front Right
  motor_configure(&(motors[1]), DEVICE_TYPE_MOTOR + 1, 0, MOTOR_POSITION_R, 0, 3, 2);
  // Back Left
  motor_configure(&(motors[2]), DEVICE_TYPE_MOTOR + 2, 0, MOTOR_POSITION_L, 0, 9, 8);
  // Back Right
  motor_configure(&(motors[3]), DEVICE_TYPE_MOTOR + 3, 0, MOTOR_POSITION_R, 0, 5, 4);

  device_configure(&(devices[0]), DEVICE_TYPE_ULTRASONIC, 0, &sonic, "ultrason");
  device_configure(&(devices[1]), DEVICE_TYPE_LASER, 0, &laser, "laser");
  device_configure(&(devices[2]), DEVICE_TYPE_MOTOR, 1, &(motors[0]), "moteur avant-gauche");
  device_configure(&(devices[3]), DEVICE_TYPE_MOTOR, 2, &(motors[1]), "moteur avant-droite");
  device_configure(&(devices[4]), DEVICE_TYPE_MOTOR, 3, &(motors[2]), "moteur arrière-gauche");
  device_configure(&(devices[5]), DEVICE_TYPE_MOTOR, 4, &(motors[3]), "moteur arrière-droite");

  logline("---- Initialize OK ----");

  delay(10000);
}

void loop() {
  long current_timestamp = millis();
  long duration = current_timestamp - last_ite_timestamp;
  last_ite_timestamp = last_ite_timestamp;


  float last_mesured_distance = ultrasonic_measure(&sonic);
  if (last_mesured_distance < 30) {
    motor_rotateMany(motors, 4, -60);
  } else {
    motor_moveMany(motors, 4, 100, MOTOR_DIRECTION_FWD);
  }

  if (last_switch + 1000 < current_timestamp) {
    last_switch = current_timestamp;
    laser_toggle(&laser, laser.iIsActive == 0);

    logline("Timer: ", current_timestamp);
    logline("Laser: ", laser.iIsActive);
    logline("Ultrasonic: ", last_mesured_distance);
  }

  //Force 100ms per loop
  const long LOOP_DURATION = 150;
  current_timestamp = millis();
  if (current_timestamp - last_ite_timestamp < LOOP_DURATION) {
    delay(LOOP_DURATION - (current_timestamp - last_ite_timestamp));
  }
}

// void shell_launch()
// {
//   char c = shell_read();
//   // logline("Command: %c", c);
//   switch (c)
//   {
//   case 'U':
//     motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_FWD);
//     break;
//   case 'D':
//     motor_moveMany(motors, 4, 1000, MOTOR_DIRECTION_REV);
//     break;
//   case 'L':
//     motor_rotateMany(motors, 4, -90);
//     break;
//   case 'R':
//     motor_rotateMany(motors, 4, 90);
//     break;
//   case 'S':
//   default:
//     motor_stop(motors, true);
//     break;
//   }
//   if (timer % 1000000 == 0)
//   {
//     logline("Timer: ", timer);
//     laser_toggle(&laser, laser.iIsActive == 0);
//     logline("Laser: ", laser.iIsActive);
//     logline("Ultrasonic: ", ultrasonic_measure(&sonic));
//   }
// }
