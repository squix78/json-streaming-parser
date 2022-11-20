/* 
 * An enhanced example where of the traditional JSON Stream Parser acts as a 'Streamable' interface
 * and takes the data directly from the WiFi receive buffers and begins parsing.
 *
 * The results we care about are then put into a stl::map for lookup based on key.
 * All results are placed into a forward_list for printing as well.
 *
 * Not totally memory efficient, but not the worst either.
 *
 * The use of SSL is by far the biggest consumer of memory, with over 20kB of SRAM consumed by this alone.
 */
#include <WiFi.h>
#include <WiFiClientSecure.h>  
#include <HTTPClient.h>  

#include "WeatherForecastHandler.h"                 // Custom JSON document handler
#include <ArduinoStreamParser.h>            // <==== THE JSON Streaming Parser - Arduino STREAM WRAPPER
#include <TimeLib.h>  						// Requires TimeLib: https://github.com/PaulStoffregen/Time

HTTPClient http; // Used for both SSl and non-SSL connections

void printHeapFreeToSerial()
{
   Serial.print("Heap free: ");
   Serial.println(String(ESP.getFreeHeap(), DEC));  
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
    
    WiFi.begin("<AP SSID>", "<PASSWORD>");
    
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

    std::unique_ptr<WiFiClientSecure>client(new WiFiClientSecure);
    client->setInsecure();

    printHeapFreeToSerial(); 

    // Open Weather Map JSON Streaming Parser
    ArudinoStreamParser parser;                   // <---------- Declare stream parser
    WeatherForecastHandler custom_handler;        // <---------- Declare stream handler
    
    parser.setHandler(&custom_handler); // <--------- Link to customer listener (parser to be honest)
    
    Serial.println("Setup JSON Streaming Parser.");
    printHeapFreeToSerial();    

    // Lets being
    http.begin(*client, "https://samples.openweathermap.org/data/2.5/forecast?q=London,us&appid=439d4b804bc8187953eb36d2a8c26a02");
   
    int httpCode = http.GET();
    if (httpCode > 0) 
    {    
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) 
      {
          Serial.print("Got payload response of length (-1 indicates chunked so size unknown): "); Serial.println(http.getSize(), DEC);

          Serial.println("Parsing JSON...");
          printHeapFreeToSerial();

          http.writeToStream(&parser); // <--------- Shoot the characters straight to the parser
      
          Serial.println("Completed Parsing.");
          printHeapFreeToSerial();   
        
      }
      
    } else {
       Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    Serial.println("Done.");    
    printHeapFreeToSerial();   
    
    Serial.println("----------------- PRINTING MAP VALUES -----------------");
    for (auto& x: mymap) {
            Serial.print(x.first.c_str()); Serial.print (" = " ); Serial.println(x.second);
    }  
	
   
}


void loop() {
  // put your main code here, to run repeatedly:

    Serial.println("----------------- PRINTING FORECAST LIST -----------------");
    for (auto& x: myForecasts) {

      // Note: Forecast datetime will need to be adjusted to make sense in your timezone
      int forecast_hour                  = hour(x.datetime);
      int forecast_day_of_week           = weekday(x.datetime);   // the weekday (Sunday is day 1) 
      int forecast_month                 = month(x.datetime);
      int forecast_day_of_month          = day(x.datetime);      // the day of month (first day of the month is 1, not 0 :-) )   

      char weekday_str[12] = { '\0' };
      strcpy(weekday_str, dayStr(forecast_day_of_week));    
	  
      Serial.printf_P("Forecast for %s %d %s @ %d:00: %s and %d degrees.\n", weekday_str, forecast_day_of_month, monthStr(forecast_month), hour(x.datetime), x.summary, x.temp/10);    
      
    }    

    delay(10000);

}