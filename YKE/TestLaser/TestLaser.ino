
const int PIN = 18;

//INIT /////////////////////////////////////////
void init_pins(){
  pinMode(PIN, OUTPUT);  
  digitalWrite(PIN, LOW);    
}

//METIER////////////////////////////////////////////////

void toggleLaser(int p_iLaserIsOn){
  digitalWrite(PIN, p_iLaserIsOn);
}

void test(){
  toggleLaser(LOW);
}

////////////////////////////////////
//MAIN /////////////////////////////
////////////////////////////////////

void setup() {
  init_pins();
}

void loop() {
  test();
}
















