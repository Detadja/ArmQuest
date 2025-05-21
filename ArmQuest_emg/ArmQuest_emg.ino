#define EMG1 14 // A0
#define EMG2 15 // A1
// #define EMG3 16 // A2
// #define EMG4 17 // A3

// FUNCTIONS & OUTSIDE VARIABLES
const int muscle[4]    = {EMG1, EMG2, EMG3, EMG4};
float     emg_val[4]   = {0, 0, 0, 0};
const int threshold[4] = {900, 900, 0, 0}; // Adjust as needed can very depending on electrode placement

// INITIALIZATIONS
void setup() {
  Serial.begin(115200);

}

// MAIN
void loop() {
  // put your main code here, to run repeatedly:
  emg_val[0] = analogRead(muscle[0]);
  emg_val[1] = analogRead(muscle[1]);
  // emg_val[2] = analogRead(muscle[2]);
  // emg_val[3] = analogRead(muscle[3]);

  (emg_val[0] > threshold[0]) ? Serial.print("Muscle 1 Activated!") : Serial.print("Muscle 1 NOT Activated!");
  (emg_val[1] > threshold[1]) ? Serial.print("Muscle 2 Activated!") : Serial.print("Muscle 2 NOT Activated!");
  // (emg_val[2] > threshold[2]) ? Serial.print("Muscle 3 Activated!") : Serial.print("Muscle 3 NOT Activated!");
  // (emg_val[3] > threshold[3]) ? Serial.print("Muscle 4 Activated!") : Serial.print("Muscle 4 NOT Activated!");

  Serial.print(emg_val[0]);
  Serial.print(',');
  Serial.println(emg_val[1]);
  // Serial.print(',');
  // Serial.print(emg_val[2]);
  // Serial.print(',');
  // Serial.print(emg_val[3]);
}
