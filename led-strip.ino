#include <FastLED.h>
#include <SoftwareSerial.h>


// RX is digital pin 10 (GREEN connected to TX of user port)
// TX is digital pin 11 (BLUE connected to RX of user port)
SoftwareSerial c64Serial(10, 11); // RX, TX

// Constants
#define NUM_LEDS 8
#define DATA_PIN A0


// Define the array of leds
CRGB leds[NUM_LEDS];

// Our switch variable
int LIGHTS_ON=false;

// Char to hold byte
char THIS_CHAR=0;

// Delay
long previousMillis = 0;        // will store last time LED was updated
long interval = 500;            // interval at which to blink (milliseconds)



void setup() { 
  
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB order


    // Open serial communications and wait for port to open:
    Serial.begin(1200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.println("ATTEMPTING TO CONNECT TO C64 ...");
    
    // set the data rate for the SoftwareSerial port
    c64Serial.begin(1200);
    c64Serial.println("READY.");
}

void flash()
{

  static bool sw=true;

  
  if(sw)
    {  
      // Turn the LED on, then pause
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Red;
      leds[4] = CRGB::Blue;
      leds[5] = CRGB::Blue;
      leds[6] = CRGB::Blue;
      leds[7] = CRGB::Blue;
      FastLED.setBrightness(4);
      FastLED.show();
    }
    else
    {
      // Now switch
      leds[0] = CRGB::Blue;
      leds[1] = CRGB::Blue;
      leds[2] = CRGB::Blue;
      leds[3] = CRGB::Blue;
      leds[4] = CRGB::Red;
      leds[5] = CRGB::Red;
      leds[6] = CRGB::Red;
      leds[7] = CRGB::Red;
      FastLED.show();
      delay(500);
    }

    sw=!sw;
      
}


void loop() { 


  // IF THE C64 HAS DATA THEN PRINT IT HERE
  if (c64Serial.available()) {
    THIS_CHAR=c64Serial.read();
    if(THIS_CHAR=='1') 
    {
      LIGHTS_ON=true;
    }
    else
    {
      LIGHTS_ON=false;
    }
    Serial.write(THIS_CHAR);
    
  }

  // SEND DATA *TO* C64 ..
  if (Serial.available()) {
    c64Serial.write(Serial.read());
  }

  if(LIGHTS_ON)  
  {  


      unsigned long currentMillis = millis();
 
      if(currentMillis - previousMillis > interval) {
        // save the last time you blinked the LED 
        previousMillis = currentMillis;   

        // flash the LEDs
        flash();

      }


  } 
  else
  {
    FastLED.setBrightness(0);
    FastLED.show();
  }
}
