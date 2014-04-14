const int pinTrigg = 4;
const int pinEcho = 14;

const int pinLaser=3;

const int DEBUG_ON=1;

void init_sound(){
  pinMode(pinTrigg, OUTPUT);
  pinMode(pinEcho, INPUT);  
}

float microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}

float measure(){
  long duration;
  float cm;
    
  digitalWrite(pinTrigg, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigg, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrigg, LOW);

  //  // read the analog in value:
  //  int sensorValue = analogRead(pinEcho);            
  //  // map it to the range of the analog out:
  //  int outputValue = map(sensorValue, 0, 1023, 0, 255);  

  duration = pulseIn(pinEcho, HIGH,50000);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  return cm;
}



void setup() {
  init_sound();

  pinMode(pinLaser, OUTPUT);
  digitalWrite(pinLaser, HIGH);

  if(DEBUG_ON){
    // initialize serial communication:
    Serial.begin(9600);
  }
}

void loop()
{

  if(DEBUG_ON){
    Serial.print(measure());
    Serial.print("cm");
    Serial.println();
  }

  delay(100);
}




