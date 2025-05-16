const int pectoralPin = A0;
const int backPin = A1;

const int threshold = 900;           // Adjust as needed can very depending on electrode placement
const unsigned long cooldown = 500; // milliseconds

unsigned long lastPectoralTime = 0;
unsigned long lastBackTime = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int pectoralVal = analogRead(pectoralPin);
  int backVal = analogRead(backPin);
  unsigned long currentTime = millis();

  // Detect pectoral spike
  if (pectoralVal > threshold && currentTime - lastPectoralTime > cooldown) {
    Serial.println("SWIPE_R_TO_L");
    lastPectoralTime = currentTime;
  }

  // Detect back spike
  if (backVal > threshold && currentTime - lastBackTime > cooldown) {
    Serial.println("SWIPE_L_TO_R");
    lastBackTime = currentTime;
  }




  delay(100); // Mess with the delay more for proper dectection
}
