#pragma once

#include "JsonHandler.h"
#include <map>
#include <string>
#include <stdexcept>  

char fullPath[200] = "";
char valueBuffer[50] = "";

/*
 * This structure is used within the ExampleHandler implementation.
 * It stores the values from the JSON we care about. Everything else 
 * is discarded.
 */
std::map<std::string, float>mymap = {
    { "list[0].dt",             0},
    { "list[0].main.temp",      0},
    { "list[0].main.temp_min",  0},
    { "list[0].main.temp_max",  0}       
};

std::map<std::string, float>::iterator it;


// Virtual Handler class implementation
class ExampleHandler: public JsonHandler
{
  
    /* Open weather maps returns something like:
     *  
      cod': "200"
      message': 0.003200
      cnt': 36
      list[0].dt': 1487246336
      list[0].main.temp': 286.670013
      list[0].main.temp_min': 281.556000
      list[0].main.temp_max': 286.670013
      list[0].main.pressure': 972.729980
      list[0].main.sea_level': 1046.459961
      list[0].main.grnd_level': 972.729980
      list[0].main.humidity': 75
      list[0].main.temp_kf': 5.110000
      list[0].weather[0].id': 800
      list[0].weather[0].main': "Clear"
      
     */
     
       
      public:

      /* Process the value provided at a specific JSON path / element 
       * This forms the core operation of the Handler.
       */
      void value(ElementPath path, ElementValue value) 
      {
          memset(fullPath, 0 , sizeof(fullPath));
          
          path.toString(fullPath);
          /*
          // Uncomment this to see the paths.
          
          Serial.print(fullPath); Serial.print("': ");
          Serial.println(value.toString(valueBuffer));
          */
          const char* currentKey = path.getKey();
        
          it = mymap.find((std::string) fullPath);
          if (it != mymap.end())
          {
            Serial.print("-> Found a key we care about: ");
            Serial.print(fullPath);
            Serial.print(" = ");
            Serial.println(value.toString(valueBuffer));

            // Store this in the map
            it->second = value.getFloat();
          }
           
          
          // Object entry?
          if(currentKey[0] != '\0') {
            if(strcmp(currentKey, "temp") == 0) {
              //TODO: use the value.
            } else if(strcmp(currentKey, "pressure") == 0) {
              //TODO: use the value.
            }
            // else ... 
          } 
          // Array item.
          else {
            int currentIndex = path.getIndex();
            if(currentIndex == 0) {
              //TODO: use the value.
            } else if(currentIndex < 5) {
              //TODO: use the value.
            }
            // else ... 
          }
      }

      
      // End document
      void startDocument() { }
      void startArray(ElementPath path) {}
      void startObject(ElementPath path) { }
      void endArray(ElementPath path) {}
      void endObject(ElementPath path) {}
      void endDocument() {}
      void whitespace(char c) {}

};