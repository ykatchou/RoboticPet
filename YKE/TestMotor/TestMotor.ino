#define uint unsigned int
#define ulong unsigned long


const int pinENABLE = 4;
const int pinFWD = 5;
const int pinREV = 6;

const int MOTOR_FWD=1;
const int MOTOR_REV=2;

const int DEBUG_ON=1;

int bIsActive;

void init_motor(){
  pinMode(pinENABLE, OUTPUT);
  pinMode(pinFWD, OUTPUT);
  pinMode(pinREV, OUTPUT);

  bIsActive = 0;
}

/**
 * Initialise le device.
 */
void start(){
  digitalWrite(pinFWD, LOW);
  digitalWrite(pinREV, LOW);
  digitalWrite(pinENABLE, HIGH);
  bIsActive=1;
  delayMicroseconds(2);
}

void log(char* str){
  if(DEBUG_ON){
    Serial.println(str);
  }
}

/**
 * idelayms : nombre de MILLI secondes dans un sens
 * value : si 1 : FWD, si 2 : REV
 */
void move(ulong idelayms, int pivalue)
{
  if(bIsActive==0){
    start();
  }

  digitalWrite(pinFWD, LOW);
  digitalWrite(pinREV, LOW);

  //FWD
  if(pivalue ==1){
    digitalWrite(pinFWD, HIGH);
  }
  //REV
  else if(pivalue ==2){    
    digitalWrite(pinREV, HIGH);
  }

  delay(idelayms);
    log("fin move");
  stop();
}

void stop(){
  if(bIsActive!=0){
    digitalWrite(pinFWD, HIGH);
    digitalWrite(pinREV, HIGH);
    delayMicroseconds(2);
  }
  digitalWrite(pinFWD, LOW);
  digitalWrite(pinREV, LOW);
  digitalWrite(pinENABLE, LOW);
  delayMicroseconds(2);

  bIsActive=0;
}


void setup() {
  init_motor();

  if(DEBUG_ON){
    // initialize serial communication:
    Serial.begin(9600);
  }

  start(); 

  move(100, MOTOR_FWD);

}

void loop()
{
  // stop();
}



























