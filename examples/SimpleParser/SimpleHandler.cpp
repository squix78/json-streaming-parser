#include "SimpleHandler.h"
#include "JsonHandler.h"

void SimpleHandler::startDocument() {
  Serial.println("start document");
}

void SimpleHandler::startArray(ElementPath path) {
  Serial.println("start array. ");
}

void SimpleHandler::startObject(ElementPath path) {
  Serial.println("start object. ");
}

void SimpleHandler::value(ElementPath path, ElementValue value) {
  char fullPath[200] = "";
  path.toString(fullPath);
  Serial.print(fullPath);
  Serial.print("': ");
  char valueBuffer[50] = "";
  Serial.println(value.toString(valueBuffer));
  
  const char* currentKey = path.getKey();
  // Object entry?
  if(currentKey[0] != '\0') {
    if(strcmp(currentKey, "mykey") == 0) {
      
      // CONTEXTUAL AWARE EXTRACTION OF JSON VALUES
      // Used later in getMyKeyString
      mykey_value = value.getInt();
      
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

void SimpleHandler::endArray(ElementPath path) {
  Serial.println("end array. ");
}

void SimpleHandler::endObject(ElementPath path) {
  Serial.println("end object. ");
}

void SimpleHandler::endDocument() {
  Serial.println("end document. ");
}

void SimpleHandler::whitespace(char c) {
  Serial.println("whitespace");
}