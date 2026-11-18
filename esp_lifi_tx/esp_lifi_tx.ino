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
  
  Serial.println("--- VLC Transmitter Ready ---");
  Serial.println("Type data below and press Enter to transmit...");
}

void loop() {
  // Forward bytes from PC Serial Monitor -> VLC Optical Link
  while (Serial.available() > 0) {
    char byte = Serial.read();
    Serial1.write(byte); // Sendover optical LED pin
  }
}