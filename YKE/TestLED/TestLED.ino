
const int MAXROW = 8;
const int MAXCOL = 8;
const int MAXPIXEL = 64;

const int row[MAXROW] = {
  2,7,10,5,16,13,17,12 };

const int col[MAXCOL] = {
  6, 15, 14, 3, 11, 4, 8, 9};

int pict[8][8] = { 
  {
    0, 1, 1, 0, 0, 1, 1, 0          }
  ,
  {
    0, 1, 0, 1, 1, 0, 1, 0          }
  ,
  {
    1, 0, 0, 0, 0, 0, 0, 1          }
  ,
  {
    1, 0, 0, 0, 0, 0, 0, 1          }
  ,
  {
    1, 1, 0, 0, 0, 0, 1, 1          }
  ,
  {
    0, 0, 1, 0, 0, 1, 0, 0          }
  ,
  {
    0, 0, 0, 1, 1, 0, 0, 0          }
  ,
  {
    0, 0, 0, 1, 1, 0, 0, 0          }
};
int pictbis[8][8] = {   
  { 
    0, 0, 0, 0, 0, 0, 0, 0          }
  ,                                 
  { 
    0, 0, 1, 0, 0, 1, 0, 0          }
  ,                                 
  { 
    0, 1, 0, 1, 1, 0, 1, 0          }
  ,                                 
  { 
    0, 1, 0, 0, 0, 0, 1, 0          }
  ,                                 
  { 
    0, 1, 0, 0, 0, 0, 1, 0          }
  ,                                 
  { 
    0, 0, 1, 0, 0, 1, 0, 0          }
  ,                                 
  { 
    0, 0, 0, 1, 1, 0, 0, 0          }
  ,                                 
  { 
    0, 0, 0, 1, 1, 0, 0, 0          }
}; 

//INIT /////////////////////////////////////////
void init_pins(){
  for (int thisPin = 0; thisPin < MAXROW; thisPin++) {
    pinMode(row[thisPin], OUTPUT);  
    digitalWrite(row[thisPin], LOW);    
  }

  for (int thisPinY = 0; thisPinY < MAXCOL; thisPinY++) {
    pinMode(col[thisPinY], OUTPUT); 
    digitalWrite(col[thisPinY], LOW);  
  }
}

void init_pict(){
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      //pict[x][y] = LOW;
    }
  }

}

//METIER////////////////////////////////////////////////

void fullMatrixROW(){
  //1ere ligne
  digitalWrite(2, HIGH);
  //2eme ligne
  digitalWrite(7, HIGH);
  //3eme ligne
  digitalWrite(10, HIGH);
  //4eme ligne
  digitalWrite(5, HIGH);
  //5emeligne
  digitalWrite(16, HIGH);
  //6eme ligne
  digitalWrite(13, HIGH);
  //7eme ligne
  digitalWrite(17, HIGH);
  //8eme ligne
  digitalWrite(12, HIGH);
}

void fullMatrixCOL(){
  //1ere ligne
  digitalWrite(6, HIGH);
  //2eme ligne  
  digitalWrite(15, HIGH);
  //3eme ligne
  digitalWrite(14, HIGH);
  //4eme ligne
  digitalWrite(3, HIGH);
  //5eme ligne
  digitalWrite(11, HIGH);
  //6eme ligne
  digitalWrite(4, HIGH);
  //7eme ligne
  digitalWrite(8, HIGH);
  //8eme ligne
  digitalWrite(9, HIGH);
}

void clearMatrix(){
  for(int ix=0; ix<MAXROW;ix++){
    digitalWrite(row[ix], LOW);
  } 
  for(int iy=0; iy<MAXCOL;iy++){
    digitalWrite(col[iy], HIGH);
  }   
}

void showPixel(int p_ix, int p_iy, int iValue){
  int iOpposite = (iValue == HIGH) ? LOW : HIGH;

  for(int iRow=0; iRow<MAXROW; iRow++){
    if(iRow == p_ix){
      digitalWrite(row[iRow], iValue);           
    }
    else{
      digitalWrite(row[iRow], iOpposite); 
    }
  }

  for(int iCol=0; iCol<MAXCOL; iCol++){
    if(iCol == p_iy){
      digitalWrite(col[iCol], LOW);  
    }
    else{
      digitalWrite(col[iCol], HIGH);
    }
  }
}

//Draw a line using MAXCOL size array. (Use HIGH for Show a pixel)
void drawRow(int p_iRowIndex, int* p_aRowValues){
  digitalWrite(row[p_iRowIndex], HIGH);           

  for(int iCol=0; iCol<MAXCOL; iCol++){
    int iOpposite = (p_aRowValues[iCol] == HIGH) ? LOW : HIGH;
    digitalWrite(col[iCol], iOpposite);
  }
}

//Dessine l'image contenu dans la matrice 8x8 en paramètre. Ou 1 affiche un pixel.
void drawPict(){

  const int CYCLE=700;
  const int STEP = 1;
  const int CYCLE2=200;
  const int STEP2 = 1;

  int  iTps=0;
  while(iTps<CYCLE){

    for(int i=MAXROW-1;i>=0; i--){
      clearMatrix();
      drawRow(i,pict[i]); 
    }

    delay(STEP-1);
    iTps+=STEP;
  }

  iTps=0;
  while(iTps<CYCLE2){

    for(int i=MAXROW-1;i>=0; i--){
      drawRow(i,pictbis[i]); 
      clearMatrix();
    }

    delay(STEP2-1);
    iTps+=STEP2;
  }
}

//Promene un pixel sur tous les points de la matrice.
void testSnake(){
  for(int j=0; j<MAXROW; j++){
    for (int i=0; i<MAXCOL; i++){
      showPixel(j,i,HIGH);
      clearMatrix();
      delay(50);
    }
  } 
}

////////////////////////////////////
//MAIN /////////////////////////////
////////////////////////////////////

void setup() {
  init_pins();
  init_pict();
}

void loop() {
  drawPict();
}















