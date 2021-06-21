#include <SoftwareSerial.h>

// RX is digital pin 10 (connect to TX of other device)
// TX is digital pin 11 (connect to RX of other device)

SoftwareSerial c64Serial(10, 11); // RX, TX

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(1200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("ATTEMPTING TO CONNECT TO C64 ...");

  // set the data rate for the SoftwareSerial port
  c64Serial.begin(1200);
  c64Serial.println("HELLO C64?");
}

void loop() { // run over and over

  // IF THE C64 HAS DATA THEN PRINT IT HERE
  if (c64Serial.available()) {
    Serial.write(c64Serial.read());
  }

  // SEND DATA *TO* C64 ..
  if (Serial.available()) {
    c64Serial.write(Serial.read());
  }
}
