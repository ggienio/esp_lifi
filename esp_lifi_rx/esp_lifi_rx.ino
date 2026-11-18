#include "../config.h"

constexpr int SERIAL1_TX_PIN = 4;
constexpr int SERIAL1_RX_PIN = 5;

void setup() {
  // Initialize USB communication to PC
  Serial.begin(BAUD_RATE);
  
  // Initialize VLC Optical Link
  Serial1.begin(BAUD_RATE, SERIAL_8N1, SERIAL1_RX_PIN, SERIAL1_TX_PIN);

  while (!Serial)
  {
    delay(10);
  }

  Serial.println("--- VLC Receiver Ready ---");
  Serial.println("Awaiting incoming optical data...");
}

void loop() {
  // Forward bytes from VLC Optical Link -> PC Serial Monitor
  while (Serial1.available() > 0) {
    char byte = Serial1.read();
    Serial.write(byte); // Output to PC Serial Monitor
  }
}