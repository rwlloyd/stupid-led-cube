/*
LED Cube pattern generator

rwlloyd. Lincoln. Dec 2023.
*/
const int cathodePins[] = {3, 2, 13};
const int anodePins[] = {12, 11, 10, 9, 8, 7, 6, 5, 4};

const int lednum = 3;
const int numLayers = lednum;           //Layers are Rows (cathodes)
const int numColumns = lednum*lednum;   // Columns are Anodes
bool debug = true;
int wait = 100; // this is the timing base for all animations except flashing the LEDs

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(cathodePins[i], OUTPUT);
    digitalWrite(cathodePins[i], LOW);
  }

  for (int i = 0; i < 9; i++) {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[i], LOW);
  }
  ActivateAll();
  delay(wait*2);
  ClearAll();
}

void loop() {

  // RandomLEDs();
  // VerticalColumns();
  // HorizontalColumns();
  // // BottomLayer();
  // CycleZLayers();
  // CycleYLayers(); // this is good
  // CycleXLayers();
  // HorizontalColumns();
  // for (int i=0; i<27; i++){
  //   RandomLEDs();
  // }
  breathe();
  
}

void breathe(){ // a visual aid to box breathing
    wait = 10; // set the wait for random to be 10ms
  //hold
// delay(3000);
  for (int i=0; i<400; i++){
    RandomLEDs();
  }
  ClearAll();
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  // Breathe in
  activateLayer(0);
  delay(1250); //2
  activateLayer(1);
  delay(1250); // 3
  activateLayer(2);
  delay(1500); //4

 // hold
 //  delay(3000);
  ClearAll();
  for (int i=0; i<400; i++){
    RandomLEDs();
  }
  ActivateAll();
  delay(1250);
 //breathe out
  deactivateLayer(2);
  delay(1250); //2
  deactivateLayer(1);
  delay(1250);
  deactivateLayer(0);
  delay(1250);
}

void RandomLEDs(){
  int randCol = round(random(0,9));
  int randRow = round(random(0,3));
  activateColumn(randCol);
  activateLayer(randRow);
  delay(wait);
  deactivateColumn(randCol);
  deactivateLayer(randRow);
}

void CycleZLayers(){ // Works as intended
  activateLayer(2);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(2);

  delay(wait);

  activateLayer(1);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(1);

  delay(wait);

  activateLayer(0);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(0);

  delay(wait);
  
  // for (int layer=0; layer< 3; layer++){
  //   activateLayer(layer);
  //   for (int row = 0; row < 9; row++){
  //     activateColumn(row);
  //   }
  //   delay(wait);
  //   for (int row = 0; row < 9; row++){
  //     deactivateColumn(row);
  //   }
  //   deactivateLayer(layer);
  //   delay(wait);
  // }
}

void CycleYLayers(){ // Works as intended
  // we need all the layers
  for (int layer=0; layer< 3; layer++){
    activateLayer(layer);
  }
  // first columns on
  for (int row = 0; row < 3; row++){
      activateColumn(row);
  }
  delay(wait);
  // first columns off
  for (int row = 0; row < 3; row++){
      deactivateColumn(row);
  }
  delay(wait);
  // change the columns
  for (int row = 3; row < 6; row++){
      activateColumn(row);
  }
  delay(wait);
  for (int row = 3; row < 6; row++){
      deactivateColumn(row);
  }
  delay(wait);
    // change the columns again
  for (int row = 6; row < 9; row++){
      activateColumn(row);
  }
  delay(wait);
  for (int row = 6; row < 9; row++){
      deactivateColumn(row);
  }
  delay(wait);
  // we need to turn all the layers off
  for (int layer=0; layer< 3; layer++){
    deactivateLayer(layer);
  }
  delay(wait);
}

void CycleXLayers(){
  // define arrays for the sets of anode pins we want to activate
  int front[]={0, 3, 6};
  int middle[]={1, 4, 7};
  int back[]={2, 5, 8};
  // turn on all the layers
  for (int layer=0; layer<3; layer++){
    activateLayer(layer);
  }
  //Activate the 'front' columuns
  for (int column=0; column < 3; column++){
    activateColumn(front[column]);
  }
  delay(wait);
  // deactivate the front columns
  for (int column=0; column < 3; column++){
    deactivateColumn(front[column]);
  }
  delay(wait);
  // then activate the middle etc...
  for (int column=0; column < 3; column++){
    activateColumn(middle[column]);
  }
  delay(wait);
  for (int column=0; column < 3; column++){
    deactivateColumn(middle[column]);
  }
  delay(wait);
  // finally the 'back'
  for (int column=0; column < 3; column++){
    activateColumn(back[column]);
  }
  delay(wait);
  for (int column=0; column < 3; column++){
    deactivateColumn(back[column]);
  }
  delay(wait);
  // turn off all the layers
  for (int layer=0; layer<3; layer++){
    activateLayer(layer);
  }
  delay(wait);
}

void BottomLayer(){
  activateLayer(0);
  for (int row = 0; row < 9; row++){
    activateColumn(row);
  }
  delay(wait);
  for (int row = 0; row < 9; row++){
    deactivateColumn(row);
  }
}

void HorizontalColumns(){
  // light each layer at a time
  for (int layer = 0; layer < 3; layer++){
    activateLayer(layer);
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 9; col++) {
        lightLED(row, col);
        delay(wait);  // Adjust delay as needed
      }
    }
    deactivateLayer(layer);
  }
}

void VerticalColumns(){
   // loop through each led in vertical columns
  for (int layer = 0; layer < 3; layer++) {
    activateLayer(layer);
    delay(wait);  // Adjust delay as needed
    for (int col = 0; col < 9; col++) {
      for (int row = 0; row < 3; row++) {
        lightLED(row, col);
        delay(wait);  // Adjust delay as needed
      }
    }
    deactivateLayer(layer);
  }
}

void activateColumn(int column){
  digitalWrite(anodePins[column], HIGH);
}

void deactivateColumn(int column){
  digitalWrite(anodePins[column], LOW);
}

void activateLayer(int layer) {
  digitalWrite(cathodePins[layer], HIGH);
}

void deactivateLayer(int layer) {
  digitalWrite(cathodePins[layer], LOW);
}

void ActivateAll(){
  for(int layer=0; layer<numLayers; layer++){
    activateLayer(layer);
  }
  for (int col=0; col<numColumns; col++){
    activateColumn(col);
  }
}

void ClearAll(){
  for(int layer=0; layer<numLayers; layer++){
    deactivateLayer(layer);
  }
  for (int col=0; col<numColumns; col++){
    deactivateColumn(col);
  }
}

void lightLED(int row, int col) {
  int anodeIndex = col;      // Anodes are connected to pins 12 to 4
  int cathodeIndex = row;     // Cathodes are connected to pins 3, 2, 13
  if (debug){
      Serial.print("Row: ");
      Serial.println(row);
      Serial.print("Col: ");
      Serial.println(col);
      Serial.print("Anode Index: ");
      Serial.println(anodeIndex);
      Serial.print("Cathode Index: ");
      Serial.println(cathodeIndex);
  }
  digitalWrite(anodePins[anodeIndex], HIGH);
  delay(1);  // Adjust delay as needed
  digitalWrite(cathodePins[cathodeIndex], HIGH);

  delay(10);  // Adjust delay as needed

  digitalWrite(cathodePins[cathodeIndex], LOW);
  digitalWrite(anodePins[anodeIndex], LOW);
}



