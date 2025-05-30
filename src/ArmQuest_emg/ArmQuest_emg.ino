#include <ArduinoBLE.h>

#define EMG1 A0 // A0
#define EMG2 15 // A1
#define EMG3 16 // A2
#define EMG4 17 // A3

// Arduino Nano 33 BLE Rev3 MAC Address: 5B:86:37:1F:4E:7F

// FUNCTIONS & OUTSIDE VARIABLES
const int muscle[4]    = {EMG1, EMG2, EMG3, EMG4};
float     emg_val[4]   = {0, 0, 0, 0};
const int threshold[4] = {900, 900, 0, 0}; // Adjust as needed can very depending on electrode placement

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
      // emg_val[1] = analogRead(muscle[1]);
      // emg_val[2] = analogRead(muscle[2]);
      // emg_val[3] = analogRead(muscle[3]);

      // (emg_val[0] > threshold[0]) ? Serial.println("Muscle 1 Activated!") : Serial.println("Muscle 1 NOT Activated!");
      // (emg_val[1] > threshold[1]) ? Serial.println("Muscle 2 Activated!") : Serial.println("Muscle 2 NOT Activated!");
      // (emg_val[2] > threshold[2]) ? Serial.println("Muscle 3 Activated!") : Serial.println("Muscle 3 NOT Activated!");
      // (emg_val[3] > threshold[3]) ? Serial.println("Muscle 4 Activated!") : Serial.println("Muscle 4 NOT Activated!");
      
      messageChar.writeValue(String(emg_val[0]));
      Serial.print("Destination Device Received: ");
      Serial.println(messageChar.value());
      
      // Serial.println(emg_val[0]);
      // Serial.print(',');
      // Serial.println(emg_val[1]);
      // Serial.print(',');
      // Serial.print(emg_val[2]);
      // Serial.print(',');
      // Serial.print(emg_val[3]);
      delay(10);
    }

    Serial.println("Disconnected.");
  }

}
