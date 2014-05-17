#define uint unsigned int
#define ulong unsigned long

#include "logger.h"
#include "motor.h"

/**
 * Permet de configurer en une ligne un moteur.
 */
void configure(Motor* motor, int id, int isactive, int pinenable, int pinfwd, int pinrev){
  motor->iId = id;
  motor->iIsActive = isactive;
  motor->iPinEnable = pinenable;
  motor->iPinFwd = pinfwd;
  motor->iPinRev = pinrev;
}

/**
 * Arrête un moteur.
 */
void stop (Motor* motor, boolean bStayActive){
  digitalWrite(motor->iPinFwd, LOW);
  digitalWrite(motor->iPinRev, LOW);

  if(bStayActive){
    digitalWrite(motor->iPinEnable, HIGH);
  }
  else{
    digitalWrite(motor->iPinEnable, LOW);
    motor->iIsActive=0;
  }
  delayMicroseconds(2);
}

/**
 * Active simplement un moteur (pas de verif !)
 */
void toggle_motor(Motor* motor, int idirection, boolean force_init){
  if(force_init){
    digitalWrite(motor->iPinFwd, LOW);
    digitalWrite(motor->iPinRev, LOW);
  }

  //FWD
  if(idirection ==1){
    digitalWrite(motor->iPinFwd, HIGH);
  }
  //REV
  else if(idirection ==2){    
    digitalWrite(motor->iPinRev, HIGH);
  }
}

/**
 * Initialise un moteur.
 */
void init_motor(Motor* motor){
  pinMode(motor->iPinEnable, OUTPUT);
  pinMode(motor->iPinFwd, OUTPUT);
  pinMode(motor->iPinRev, OUTPUT);
  motor->iIsActive = 0;

  stop(motor, false);
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void moveOne(Motor* motor, ulong idelayms, int idirection)
{
  if(motor->iIsActive=true){
    stop(motor,true);
  }

  toggle_motor(motor, idirection, true);

  delay(idelayms);
  logline("fin move");
  stop(motor, true);
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void moveMany(Motor motorArray[], int motorArrayLength, ulong idelayms, int idirection)
{
  int i=0;

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    if(pmotor->iIsActive=true){
      stop(pmotor,true);
    }
  }

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    toggle_motor(pmotor, idirection, true);
  }

  delay(idelayms);
  logline("fin move many motor");

  for(i=0; i<motorArrayLength; i++){
    Motor* pmotor = &(motorArray[i]);
    stop(pmotor,true);
  }
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void rotateMany(Motor motorArray[],int motorLenghtTotal,int motorLEFT[], int motorLengthLEFT,int motorRIGHT[], int motorLengthRIGHT, int iAngle)
{
  int i=0;

  //CALCUL !
  //vitesse angulaire en ms/0°
  int angularspeed = 10;  
  int idelayms = 0;
  int DirectionL=MOTOR_FWD;
  int DirectionR=MOTOR_REV;

  if(iAngle<0){
    DirectionL=MOTOR_REV;
    DirectionR=MOTOR_FWD;
  }
  idelayms = abs(int(angularspeed * iAngle));
  char buffer[80];
  sprintf(buffer, "Turn angle %i, timing %i ms", iAngle, idelayms);
  logline(buffer);  

  //STOP ALL
  for(i=0; i<motorLenghtTotal; i++){
    Motor* pmotor = &(motorArray[i]);
    if(pmotor->iIsActive=true){
      stop(pmotor,true);
    }
  }

  if(idelayms<100){
    logline("No turn (not enough angle)");
  }
  else{

    //TURN!!!
    for(i=0; i<motorLengthLEFT; i++){
      Motor* pmotor = &(motorArray[ motorLEFT[i] ]);
      toggle_motor(pmotor, DirectionL,true);
    }
    for(i=0; i<motorLengthRIGHT; i++){
      Motor* pmotor = &(motorArray[ motorRIGHT[i] ]);
      toggle_motor(pmotor, DirectionR,true);
    }
    //END TURN!!!
    delay(idelayms);
    logline("fin turn motor");


    //STOP ALL
    for(i=0; i<motorLenghtTotal; i++){
      Motor* pmotor = &(motorArray[i]);
      stop(pmotor,true);
    }
  }
}

/**********************************************************************************/


Motor motors[4];

void setup() {
  logline("---- Initialize ----");
  Motor* Front_L= &(motors[0]);
  Motor* Front_R= &(motors[1]);
  Motor* Back_L= &(motors[2]);
  Motor* Back_R= &(motors[3]);

  configure(Front_L, 0x0010, 0, 0, 7, 6);
  configure(Front_R, 0x0011, 0, 0, 3, 2);
  configure(Back_L, 0x0012, 0, 0, 9, 8);
  configure(Back_R, 0x0013, 0, 0, 5, 4);

  init_motor(Front_L);
  init_motor(Front_R);
  init_motor(Back_L);
  init_motor(Back_R);

  if(DEBUG_ON){
    // initialize serial communication:
    Serial.begin(9600);
  }

  delay(2500);

  //moveOne(Front_L,300, MOTOR_FWD);
  //moveOne(Front_R,300, MOTOR_FWD);
  //moveOne(Back_L,300, MOTOR_FWD);
  //moveOne(Back_R,300, MOTOR_FWD);

  //moveMany(motors, 4, 2000, MOTOR_FWD);

  int motorsLindex[2]={
    0,2          };
  int motorsRindex[2]={
    1,3          };

  rotateMany(motors, 4, motorsLindex,2, motorsRindex, 2,90);
  //  delay(1000);
  rotateMany(motors, 4, motorsLindex,2, motorsRindex, 2,-90);

  logline("---- Initialize OK ----");
}

void loop()
{
  // stop();
}














































