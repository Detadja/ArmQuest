#include <ArduinoBLE.h>
#include <string.h>

#define EMG1 A0 // A0
#define EMG2 15 // A1
#define EMG3 16 // A2
#define EMG4 17 // A3

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

// Create a BLE service and a characteristic
BLEService simpleService("180C"); // Custom service UUID
BLEStringCharacteristic messageChar("2A56", BLERead | BLEWrite | BLENotify, 50); // Custom characteristic


// INITIALIZATIONS
void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  // Set the device name and local name
  BLE.setDeviceName("Nano33BLE");
  BLE.setLocalName("Nano33BLE");
  BLE.setAdvertisedService(simpleService);

  // Add characteristic to the service
  simpleService.addCharacteristic(messageChar);

  // Add service to BLE stack
  BLE.addService(simpleService);

  // Set initial value
  messageChar.writeValue("Hello!");

  // Start advertising
  BLE.advertise();
  Serial.println("BLE device is now advertising...");
}

// MAIN
void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to: ");
    Serial.println(central.address());

    while (central.connected()) {
      emg_val[0] = analogRead(muscle[0]);
      emg_val[1] = analogRead(muscle[1]);
      // emg_val[2] = analogRead(muscle[2]);
      // emg_val[3] = analogRead(muscle[3]);

      if (count == 10)
      { 
        // Clamp values
        for (int i = 0; i < 4; i++)
        {
          // Average values (10 samples each)
          emg_avg[i] /= 10;

          // Clamp values
          emg_avg[i] = constrain(emg_avg[i], emg_min[i], emg_max[i]);

          // Normalize
          emg_norm[i] = (float)(emg_avg[i] - emg_min[i]) / (emg_max[i] - emg_min[i]);
        }

        // Compute signed balance: positive = front, negative = back
        emg_delta[0] = emg_norm[0] - emg_norm[1];
        // emg_delta[1] = emg_norm[2] - emg_norm[3];

        // Map to angle:
        // muscleDelta = -1 -> -45Deg (back contraction)
        // MuscleDetla = 0 -> 0Deg (neutral)
        // MuscleDelta = +1 -> 135Deg (front contraction)
        // TODO: CHANGE ANGLE MAPPING FOR ELBOW JOINT        
        (emg_delta[0] >= 0) ? angle = emg_delta[0] * 135 : emg_delta[0] * 45;
        // (emg_delta[1] >= 0) ? angle = emg_delta[1] * 135 : emg_delta[1] * 45;
        
        // String msg = emg_delta[0] + "," + emg_delta[1];

        messageChar.writeValue(String(emg_delta[0]));
        Serial.print("Destination Device Received: ");
        Serial.println(messageChar.value());
        
        // Serial.println(emg_val[0]);
        // Serial.print(',');
        // Serial.println(emg_val[1]);
        // Serial.print(',');
        // Serial.print(emg_val[2]);
        // Serial.print(',');
        // Serial.print(emg_val[3]);

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

      // Serial.print(emg_avg[0]);
      // Serial.print(',');
      // Serial.print(emg_avg[1]);
      // Serial.print(',');
      // Serial.print(emg_avg[2]);
      // Serial.print(',');
      // Serial.print(emg_avg[3]);

      delay(10);
    }

    Serial.println("Disconnected.");
  }

}
