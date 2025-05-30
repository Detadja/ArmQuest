#include <ArduinoBLE.h>

// Arduino Nano 33 BLE Rev3 Address: 5B:86:37:1F:4E:7F
// DENISE DEVICE MAC ADDRESS: E4:70:B8:5E:74:22

// Create a BLE service and a characteristic
BLEService simpleService("180C"); // Custom service UUID
BLEStringCharacteristic messageChar("2A56", BLERead | BLEWrite, 50); // Custom characteristic

void setup() {
  Serial.begin(9600);
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

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to: ");
    Serial.println(central.address());

    while (central.connected()) {
      // You can check or modify BLE behavior here
      // if (messageChar.written()) {
      //   String value = messageChar.value();
      //   Serial.print("Received: ");
      //   Serial.println(value);
      // }
      String msg = "Arduino Nano Messaging ON!";
      messageChar.writeValue(msg);
      Serial.print("PC received: ");
      Serial.println(messageChar.value());
    }

    Serial.println("Disconnected.");
  }
}
