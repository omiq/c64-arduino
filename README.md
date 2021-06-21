# c64-arduino
C64 to Arduino interfacing examples

```
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
```

```
10 rem 1200,8n1
20 print "{clear}{white}"
30 open2,2,4,chr$(8)+chr$(0):rem open the serial from user port
40 get#2,s$:rem get from serial to prime the pump
100 rem main loop
110 rem ---------
200 get k$:rem get from c64 keyboard
220 if k$<>""then print#2,k$;:rem send keypress to serial
230 get#2,s$:rem get byte from serial
240 print s$;k$;:rem print these bytes
245 if (peek(673)and1)then 245:rem wait until all chars transmitted
900 goto 110
1000 close 2:end
```
