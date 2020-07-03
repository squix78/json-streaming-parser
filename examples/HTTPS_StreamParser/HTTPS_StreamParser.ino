/* 
 * An enhanced example where of the traditional JSON Stream Parser acts as a 'Streamable' interface
 * and takes the data directly from the WiFi receive buffers and begins parsing.
 */
 
#define USE_HTTPS_MODE 1 // on the ESP8266 this is dangerous... https://www.esp8266.com/viewtopic.php?p=69937

#include <ESP8266WiFi.h>

  #ifdef USE_HTTPS_MODE
    #include <WiFiClientSecureBearSSL.h>  
  #else
    #include <WiFiClient.h>                      
  #endif


#include <ESP8266HTTPClient.h>  


//#include <JsonStreamingParser2.h>         // Note: This isn't used!
#include "ExampleHandler.h"                 // Custom JSON document handler
#include <ArduinoStreamParser.h>            // <==== THE JSON Streaming Parser - Arduino STREAM WRAPPER


// IF not HTTPS
#ifndef USE_HTTPS_MODE
  WiFiClient client;
#endif  

HTTPClient http; // Used for both SSl and non-SSL connections


void printHeapFreeToSerial()
{
   Serial.print("Heap free:");
   Serial.println(String(ESP.getFreeHeap(), DEC));
   Serial.print("Stack free:");
   Serial.println(String(ESP.getFreeContStack(), DEC));   
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    for (uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(500);
    }    
    
    Serial.println("Starting........."); printHeapFreeToSerial();
    
    WiFi.begin("XXXXX", "XXXXX");
    
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    printHeapFreeToSerial();

  #ifdef USE_HTTPS_MODE
    
      // Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
      const uint8_t fingerprint[20] = {0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3};
  
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint(fingerprint);    
      client->setInsecure();
      Serial.println("SSL fingerprint set.");
      printHeapFreeToSerial(); 
  #endif

    // Open Weather Map JSON Streaming Parser
    ArudinoStreamParser parser;
    ExampleHandler custom_handler;
    
    parser.setHandler(&custom_handler); // Link to customer listener (parser to be honest)
    
    Serial.println("Setup JSON Streaming Parser.");
    printHeapFreeToSerial();    

    // Lets being
   #ifdef USE_HTTPS_MODE
    http.begin(*client, "https://samples.openweathermap.org/data/2.5/forecast?q=London,us&appid=439d4b804bc8187953eb36d2a8c26a02");
   #else
    http.begin(client, "http://xxxxx");
   #endif
    
    
    // start connection and send HTTP header
    Serial.println("Making HTTPS Connection.");
    printHeapFreeToSerial(); 
        
    int httpCode = http.GET();
    if (httpCode > 0) 
    {    
      
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      printHeapFreeToSerial();    
      
      // file found at server
      if (httpCode == HTTP_CODE_OK) 
      {
          Serial.print("Got payload response of length: "); Serial.println(http.getSize(), DEC);

          Serial.println("Parsing JSON...");
          printHeapFreeToSerial();

          http.writeToStream(&parser); // Shoot it straight to the parser
      
          Serial.println("Completed Parsing.");
          printHeapFreeToSerial();   
        
      }
      
    } else {
       Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    Serial.println("Done.");    
    printHeapFreeToSerial();   
 
}


void loop() {
  // put your main code here, to run repeatedly:

}
