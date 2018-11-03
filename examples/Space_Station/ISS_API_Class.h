// Header for Space Station class which supports the main sketch
#pragma once

#define SHOW_JSON  // Print the JSON to the serial monitor
#define PASSES 7   // Number of ISS passes to fetch

// Choose the WiFi library to load
#ifdef ESP8266
  #include <ESP8266WiFi.h> // Built in library for ESP8266
#else // ESP32
  #include <WiFi.h>        // Built in library for ESP32
#endif

#include <WiFiUdp.h>       // Built in library

#include "JsonStreamingParser.h"
#include "JsonListener.h"

// Structure to hold the parsed values
typedef struct ISS_pass {
  String    message;       // Message, usually "sucess"
  uint32_t  datetime = 0;  // Time of request, UTC unix time in seconds since Jan 01 1970
  uint16_t  passDuration[PASSES] = { 0 }; // Pass duration in seconds
  uint32_t  passRiseTime[PASSES] = { 0 }; // Time of pass, UTC unix time
} ISS_pass;

class SpaceStation: public JsonListener {

  public:

    void getPasses(String latitude, String longitude, ISS_pass* passData);

    // Start of Listener support functions

    void key(String key);

    void value(String value);

    void startDocument();

    void endDocument();

    void startObject();

    void endObject();

    void startArray();

    void endArray();

    void whitespace(char c);

    // End of Listener support functions

  private:

    bool     ended = true;  // Flag to indicate document has ended

    String   currentParent; // Current object e.g. "request"

    String   currentKey;    // Name key of the name:value pair e.g "temperature"

    uint16_t arrayIndex;    // Array index 0-N e.g. 4 for 5th pass, qualify with valuePath

    String   valuePath;     // object (i.e. sequential key) path (like a "file path")
                            // taken to the name:value pair in the form "/response"
                            // so values can be pulled from the correct array.
                            // Needed since different objects contain "data" arrays.

    ISS_pass *passData;     // pointer provided by sketch
};
