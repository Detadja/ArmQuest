#define EMG1 14 // A0
#define EMG2 15 // A1
#define EMG3 16 // A2
#define EMG4 17 // A3

// FUNCTIONS & OUTSIDE VARIABLES
const int muscle[4] = {EMG1, EMG2, EMG3, EMG4};
float emg_val[4] = {0, 0, 0, 0};

// INITIALIZATIONS
void setup() {
  Serial.begin(9600);

}

// MAIN
void loop() {
  // put your main code here, to run repeatedly:
  emg_val[0] = analogRead(muscle[0]);
  emg_val[0] = analogRead(muscle[0]);
  emg_val[0] = analogRead(muscle[0]);
  emg_val[0] = analogRead(muscle[0]);

  Serial.print(emg_val[0]);
  Serial.print(',');
  Serial.print(emg_val[1]);
  Serial.print(',');
  Serial.print(emg_val[2]);
  Serial.print(',');
  Serial.print(emg_val[3]);
}
