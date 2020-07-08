/* 
 * Example of the traditional JSON Stream Parser done character by character with
 * the use of a character array or Arduino string which consumes memory proportional
 * to the length of the string.
 */ 
#include "JsonStreamingParser2.h" 
#include "JsonHandler.h"
#include "SimpleHandler.h"

JsonStreamingParser parser;
SimpleHandler handler;

void setup() {
  Serial.begin(115200);
  Serial.println(String(ESP.getFreeHeap()));

  // Set the custom handler
  parser.setHandler(&handler);
  
  // put your setup code here, to run once:
  char json[] = "{\"mykey\":100, \"b\":{\"c\":\"d\"}}";
  
  for (int i = 0; i < sizeof(json); i++) {
    parser.parse(json[i]); // <-- Parse character by character
  }

  Serial.println("--------------------------------");
  Serial.println(handler.getMyKeyString());
  Serial.println("--------------------------------");

  
  Serial.println(String(ESP.getFreeHeap()));
}

void loop() {
  // put your main code here, to run repeatedly:

}
