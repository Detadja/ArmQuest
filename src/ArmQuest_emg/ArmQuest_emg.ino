#define EMG1 A0
#define EMG2 A1
#define EMG3 A2
#define EMG4 A3 

// Arduino Nano 33 BLE Rev3 MAC Address: 5B:86:37:1F:4E:7F

// FUNCTIONS & OUTSIDE VARIABLES
const int muscle[4]    = {EMG1, EMG2, EMG3, EMG4};
float     emg_val[4]   = {0, 0, 0, 0};
float     emg_norm[4]  = {0, 0, 0, 0};
const int emg_min[4] = {50, 40, 0, 0}; // Adjust as needed can very depending on electrode placement
const int emg_max[4] = {350, 600, 0, 0}; // Adjust as needed can very depending on electrode placement
float     emg_avg[4] = {0, 0, 0, 0};

static float angle        = 0.0;
static float emg_delta[2] = {0.0, 0.0};
int          count        = 0;


// INITIALIZATIONS
void setup() {
  Serial.begin(115200);
}


// MAIN
void loop() {
  emg_val[0] = analogRead(muscle[0]);
  emg_val[1] = analogRead(muscle[1]);
  // emg_val[2] = analogRead(muscle[2]);
  // emg_val[3] = analogRead(muscle[3]);

  if (count == 10)
  {
    // Average values (10 samples each)
    emg_avg[0] /= 10;
    emg_avg[1] /= 10;
    // emg_avg[2] /= 10;
    // emg_avg[3] /= 10;
    
    // // Clamp values
    // for (int i = 0; i < 4; i++)
    // {
    //   // Clamp values
    //   emg_val[i] = constrain(emg_val[i], emg_min[i], emg_max[i]);

    //   // Normalize
    //   emg_norm[i] = (float)(emg_val[i] - emg_min[i]) / (emg_max[i] - emg_min[i]);
    // }

    // // Compute signed balance: positive = front, negative = back
    // emg_delta[0] = emg_norm[0] - emg_norm[1];
    // // emg_delta[1] = emg_norm[2] - emg_norm[3];

    // // Map to angle:
    // // muscleDelta = -1 -> -45Deg (back contraction)
    // // MuscleDetla = 0 -> 0Deg (neutral)
    // // MuscleDelta = +1 -> 135Deg (front contraction)
    
    // (emg_delta[0] >= 0) ? angle = emg_delta[0] * 135 : emg_delta[0] * 45;
    // (emg_delta[1] >= 0) ? angle = emg_delta[1] * 135 : emg_delta[1] * 45;

    Serial.print(emg_avg[0]);
    Serial.print(',');
    Serial.println(emg_avg[1]);
    // Serial.print(',');
    // Serial.print(emg_avg[2]);
    // Serial.print(',');
    // Serial.print(emg_avg[3]);

    // Serial.println(emg_delta[0]);
    // Serial.print(',');
    // Serial.println(emg_delta[1]);

    count = 0;
    emg_avg[0] = 0;
    emg_avg[1] = 0;
  }
  else
  {
    emg_avg[0] += emg_val[0];
    emg_avg[1] += emg_val[1];
    // emg_avg[2] += emg_val[2];
    // emg_avg[3] += emg_val[3];
    count++;
  }

  // Serial.println(emg_val[0]);
  // Serial.print(',');
  // Serial.println(emg_val[1]);
  // Serial.print(',');
  // Serial.print(emg_val[2]);
  // Serial.print(',');
  // Serial.print(emg_val[3]);

  delay(5);

}
