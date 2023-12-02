const int cathodePins[] = {3, 2, 13};
const int anodePins[] = {12, 11, 10, 9, 8, 7, 6, 5, 4};

bool debug = true;
int wait = 100;

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
}

void loop() {
  VerticalColumns();
  // HorizontalColumns();
  // BottomLayer();
  CycleZLayers();
  CycleYLayers();
  CycleXLayers();
  HorizontalColumns();
}

void CycleZLayers(){
  activateLayer(0);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(0);

  delay(wait);

  activateLayer(1);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(1);

  delay(wait);

  activateLayer(2);
  for (int column=0; column<9; column++){
    activateColumn(column);
  }
  delay(wait);
  deactivateLayer(2);

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

void CycleYLayers(){
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



