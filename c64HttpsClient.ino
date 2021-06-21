#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>


void setup() {
  Serial.begin(1200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("garretts", "aaaaaaaaaa");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void printChars(String in)
{
  in.toUpperCase();
  in.replace("<P>","\r");
  in.replace("</P>","\r");
  in.replace("&#8217;","'");
  in.replace("&#8220;","\"");
  in.replace("&#8211;","-");
  in.replace("[&HELLIP;]","\"");
  
  for (int n = 0; n < in.length(); n++)
  {
    Serial.write(in[n]);
    delay(100);
  }
}

void getPayload() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  https.useHTTP10(true);
  if (https.begin(*client, "https://retrogamecoders.com/wp-json/wp/v2/posts?_fields=excerpt,title&per_page=10")) 
  { 
    
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {

      // file found at server?
      if (httpCode == HTTP_CODE_OK) {

        // Parse response
        DynamicJsonDocument doc(4720);
        deserializeJson(doc, https.getStream());

        // Ensure the C64 is clear
        delay(100);        
        Serial.println("\n\r");
        Serial.println("\n\r");
        Serial.println("\n\r");

        // Now loop through article JSON     
        
        for(int n=0;n < 9;n++) {
          String title = (doc[n]["title"]["rendered"].as<String>());
   
          String excerpt = (doc[n]["excerpt"]["rendered"].as<String>());

          if (title != NULL && excerpt != NULL && title != "null" && excerpt != "null") 
          {

            // Headline
            Serial.print("[");
            printChars(title);
          
            // Excerpt
            Serial.print("]");
            printChars(excerpt);
            delay(500);
          }
        }
      }
    }

    https.end();
  }
}

void loop() {
  getPayload();
  delay(10000);
}
