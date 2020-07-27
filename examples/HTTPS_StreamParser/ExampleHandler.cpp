#include "ExampleHandler.h"

//#define HANDLER_DEBUG 1


/*
	// Parse a huge JSON test file with data like the following
	// Only do something when we find 'John'.
	[{
	  "id": 0,	
	  "first_name": "SvprRY8xno",
	  "last_name": "SvprRY8xno",
	  "email": "EkMZbRghxH@gmailz.com",
	  "gender": "Male",
	  "ip_address": "19.20.93.148" 
	},{
	  "id": 1,	
	  "first_name": "E0fugv6Vk4",
	  "last_name": "E0fugv6Vk4",
	  "email": "QWtUYuGod4@gmailz.com",
	  "gender": "Male",
	  "ip_address": "196.240.44.163" 
	}...
*/

// Function Implementation
void ExampleHandler::startDocument() {
#ifdef HANDLER_DEBUG	
  Serial.println("start document");
#endif  
}

void ExampleHandler::startArray(ElementPath path) {
#ifdef HANDLER_DEBUG	
  Serial.println("start array. ");
#endif  
}

void ExampleHandler::startObject(ElementPath path) {
#ifdef HANDLER_DEBUG	
  Serial.println("start object. ");
#endif  
}

void ExampleHandler::value(ElementPath path, ElementValue value) {
	
  char fullPath[200] = "";	
  path.toString(fullPath);
  
  char valueBuffer[50] = "";  
  value.toString(valueBuffer);
  
#ifdef HANDLER_DEBUG	
  Serial.print(fullPath);
  Serial.print(": ");
  Serial.println(valueBuffer);
#endif    
  
  const char* currentKey = path.getKey();
  
  // Object entry?
  if(currentKey[0] != '\0') {
	  
    if(strcmp(currentKey, "first_name") == 0) {		

   // Serial.println(value.getString());      
	
		if(strcmp(value.getString(), "John") == 0) {
			Serial.println("We found John!");
			in_json_object_of_interest = true;
		}			
      
    } else if(strcmp(currentKey, "pressure") == 0) {
      //TODO: use the value.
    }
	
  	if (in_json_object_of_interest)
  	{
  
  		Serial.print(fullPath);
  		Serial.print("': ");
  		Serial.println(valueBuffer);	
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

void ExampleHandler::endArray(ElementPath path) {
#ifdef HANDLER_DEBUG	
  Serial.println("end array. ");
#endif  
}

void ExampleHandler::endObject(ElementPath path) {
	
counter++; // Increase number of objects

if (counter % 500 == 0) { Serial.print(counter, DEC); Serial.println(" JSON objects parsed"); }

in_json_object_of_interest = false;
	
#ifdef HANDLER_DEBUG	
  Serial.println("end object. ");
#endif  
}

void ExampleHandler::endDocument() {
#ifdef HANDLER_DEBUG	
  Serial.println("end document. ");
#endif  
}

void ExampleHandler::whitespace(char c) {
#ifdef HANDLER_DEBUG	
  Serial.println("whitespace");
#endif  
}