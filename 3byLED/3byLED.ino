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



