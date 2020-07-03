#include "ExampleHandler.h"

// Function Implementation
void ExampleHandler::startDocument() {
  Serial.println("start document");
}

void ExampleHandler::startArray(ElementPath path) {
  Serial.println("start array. ");
}

void ExampleHandler::startObject(ElementPath path) {
  Serial.println("start object. ");
}

void ExampleHandler::value(ElementPath path, ElementValue value) {
  char fullPath[200] = "";
  path.toString(fullPath);
  Serial.print(fullPath);
  Serial.print("': ");
  char valueBuffer[50] = "";
  Serial.println(value.toString(valueBuffer));
  
  const char* currentKey = path.getKey();
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

void ExampleHandler::endArray(ElementPath path) {
  Serial.println("end array. ");
}

void ExampleHandler::endObject(ElementPath path) {
  Serial.println("end object. ");
}

void ExampleHandler::endDocument() {
  Serial.println("end document. ");
}

void ExampleHandler::whitespace(char c) {
  Serial.println("whitespace");
}
