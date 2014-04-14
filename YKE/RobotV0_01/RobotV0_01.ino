/**********************************************************/
/*              INPUT MATCHING */
/**********************************************************/

#define DEBUG_ACTIVE 1

#define LASER_ACTIVE 0
#define LASER_PIN 5

#define ULTRASON_ACTIVE 1
#define ULTRASON_PIN_TRIGG 4
#define ULTRASON_PIN_ECHO 14

/*
AVANT :
 const int row[MAXROW] = {2,7,10,5,16,13,17,12 };
 const int col[MAXCOL] = {6, 15, 14, 3, 11, 4, 8, 9}; 
 */

#define MATRIX_ACTIVE 1
#define MATRIX_MAXROW 8
#define MATRIX_MAXCOL 8
#define MATRIX_PIN_ROW1 6
#define MATRIX_PIN_ROW2 8
#define MATRIX_PIN_ROW3 11
#define MATRIX_PIN_ROW4 7
#define MATRIX_PIN_ROW5 10
#define MATRIX_PIN_ROW6 13
#define MATRIX_PIN_ROW7 9
#define MATRIX_PIN_ROW8 12

/****************************************************************/
/* VARIABLES */
/****************************************************************/
int matrixRow[8]={
  MATRIX_PIN_ROW1,MATRIX_PIN_ROW2,MATRIX_PIN_ROW3,MATRIX_PIN_ROW4,MATRIX_PIN_ROW5,MATRIX_PIN_ROW6,MATRIX_PIN_ROW7,MATRIX_PIN_ROW8};

int iLaser_Timer=0;
int iLaser_State=LOW;

/****************************************************************/
/* INIT */
/****************************************************************/
void init_debug(){
 if(DEBUG_ACTIVE){
    Serial.begin(9600);
 }
}

void init_laser(){
  if(LASER_ACTIVE){
    iLaser_Timer=0;
    iLaser_State = LOW;
    pinMode(LASER_PIN, OUTPUT);  
  }
}

void init_ultrason(){
  if(ULTRASON_ACTIVE){
    pinMode(ULTRASON_PIN_TRIGG, OUTPUT);  
    pinMode(ULTRASON_PIN_ECHO, INPUT);  
  }
}


void init_matrix(){
  if(MATRIX_ACTIVE){
    for (int thisPin = 0; thisPin < MATRIX_MAXROW; thisPin++) {
      pinMode(matrixRow[thisPin], OUTPUT);  
      digitalWrite(matrixRow[thisPin], LOW);    
    }
  }
}

/****************************************************************/
/* LASER METHOD */
/****************************************************************/
void laser_toggle(int p_iLaserIsOn){
  if(LASER_ACTIVE){
    digitalWrite(LASER_PIN, p_iLaserIsOn);
  }
}

/****************************************************************/
/* ULTRASON METHOD */
/****************************************************************/
float ultrason_ms_to_cm(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}

float ultrason_measure(){
  long duration;
  float cm;

  if(ULTRASON_ACTIVE){
    digitalWrite(ULTRASON_PIN_TRIGG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASON_PIN_TRIGG, HIGH);
    delayMicroseconds(5);
    digitalWrite(ULTRASON_PIN_TRIGG, LOW);
    duration = pulseIn(ULTRASON_PIN_ECHO, HIGH,20000);
    // convert the time into a distance
    cm = ultrason_ms_to_cm(duration);
  }
  return cm;
}

/****************************************************************/
/* MATRIX METHOD */
/****************************************************************/
//Draw a line using MAXCOL size array. (Use HIGH for Show a pixel)
void matrix_drawRow(int p_iRowIndex, int p_iState){
  if(MATRIX_ACTIVE){
    digitalWrite(matrixRow[p_iRowIndex], p_iState);           
  }
}

void matrix_drawLevel(int p_iLevel){
  int iState=HIGH;
  if(MATRIX_ACTIVE){
    for(int i=0; i<MATRIX_MAXROW; i++){
      if(i>=p_iLevel){
        iState=LOW;
      }
      matrix_drawRow(i, iState);
    }
  }
}

/****************************************************************/
/* MAIN */
/****************************************************************/

void setup() {
  init_debug();
  init_laser();
  init_ultrason();
  init_matrix();
}


void loop() {
  float cm=0.0;
  int matrixLevel=0;
  
  cm = ultrason_measure();

  if(cm<10.0){
    matrixLevel=0;
  }
  if(cm>10.0 && cm<20.0){
    matrixLevel=1;
  }
  if(cm>20.0 && cm<30.0){
    matrixLevel=2;
  }
  if(cm>30.0 && cm<40.0){
    matrixLevel=3;
  }
  if(cm>40.0 && cm<50.0){
    matrixLevel=4;
  }
  if(cm>50.0 && cm<60.0){
    matrixLevel=5;
  }
  if(cm>60.0 && cm<80.0){
    matrixLevel=6;
  }
  if(cm>80.0 && cm<100.0){
    matrixLevel=7;
  }
  if(cm>100.0){
    matrixLevel=8;
  }
  matrix_drawLevel(matrixLevel);

  //LASER
  if(iLaser_Timer>20){
    iLaser_State = (iLaser_State==HIGH)?LOW:HIGH;
    laser_toggle(iLaser_State);
    iLaser_Timer=0; 
  }
  iLaser_Timer++;
  
  delay(100);
  
  if(DEBUG_ACTIVE){
    Serial.print(cm);
    Serial.print(" cm, ");
    Serial.print(matrixLevel);
    Serial.print(" level.");
    Serial.println();
  }

  
}













