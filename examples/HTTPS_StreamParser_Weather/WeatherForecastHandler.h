#pragma once

#include "JsonHandler.h"
#include <map>
#include <forward_list>
#include <string>
#include <stdexcept>  
#include <TimeLib.h> 

char fullPath[200] = "";
char valueBuffer[50] = "";

/*
 * This structure is used within the WeatherForecastHandler implementation.
 * It stores the values from the JSON we care about. Everything else 
 * is discarded.
 */
struct Forecast
{
    time_t  datetime;
    int     temp;
    int     humidity;
    char    summary[16];
};

// Example: LIST - Store a list of all forecasts
std::forward_list<Forecast> myForecasts;
std::forward_list<Forecast>::iterator myForecasts_it;

// Example: MAP  - Store a map of stuff we only care about that the parser sees.
std::map<std::string, float>mymap = {
    { "list[0].dt",             0},
    { "list[0].main.temp",      0},
    { "list[0].main.temp_min",  0},
    { "list[0].main.temp_max",  0}       
};
std::map<std::string, float>::iterator it;


// Virtual Handler class implementation
class WeatherForecastHandler: public JsonHandler
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

      start Object
      Current key is: dt
      start Object
      Current key is: temp
      Current key is: temp_min
      Current key is: temp_max
      Current key is: pressure
      Current key is: sea_level
      Current key is: grnd_level
      Current key is: humidity
      Current key is: temp_kf
      end Object
      start Object
      Current key is: id
      Current key is: main
      Current key is: description
      Current key is: icon
      end Object
      
      
     */
     
      private:
        Forecast forecast   = { 0 };
        bool in_forecast    = false;
       
      public:

      /* Process the value provided at a specific JSON path / element 
       * This forms the core operation of the Handler.
       */
      void value(ElementPath path, ElementValue value) 
      {
            
          memset(fullPath, 0 , sizeof(fullPath));          
          path.toString(fullPath);
          
          const char* currentKey = path.getKey();
          //Serial.print("Current key is: "); Serial.println(currentKey);
          
          /*
          // Uncomment this to see the paths.
          
          Serial.print(fullPath); Serial.print("': ");
          Serial.println(value.toString(valueBuffer));
          */
                
          // Map Example 1: Based on path string
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
              
            // Tradition State-Machine based parser
            if(strcmp(currentKey, "dt") == 0) {
              forecast.datetime = (time_t) value.getInt(); 
            }
            else if (strcmp(currentKey, "humidity") == 0) {
              forecast.humidity = value.getInt();
            }
            else if (strcmp(currentKey, "temp") == 0) {
              forecast.temp = value.getInt();
            }    
            else if (strcmp(currentKey, "main") == 0) {
              strncpy(forecast.summary, value.getString(), sizeof(forecast.summary));
            } 
            else if (strcmp(currentKey, "icon") == 0) { // We're at the end from our perspective.
              
              myForecasts.push_front (forecast);
              //Serial.println("Inserted forecast...");
       
            } // end state machine logic
                          
          } 
          // Array item.
          /*
          else {
            int currentIndex = path.getIndex();
            if(currentIndex == 0) {
              //TODO: use the value.
            } else if(currentIndex < 5) {
              //TODO: use the value.
            }
            // else ... 
          }
          */
          
      } // end value

      // Reverse the list so it's most recent to most far away forecast
      void endDocument() { 
        myForecasts.reverse(); 
      }	  

      //
      // Functions we don't care about.
      void startDocument() { }      
      void startObject(ElementPath path) { // Start of object '{'
        // Serial.println("start Object");
      }               
      void endObject(ElementPath path) {  // End of a forecast object '}'
        // Serial.println("end Object");             
      }             
      void startArray(ElementPath path) {}
      void endArray(ElementPath path) {}
      void whitespace(char c) {}

};