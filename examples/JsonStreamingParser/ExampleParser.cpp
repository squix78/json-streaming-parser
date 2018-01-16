#include "ExampleParser.h"
#include "JsonListener.h"

void ExampleListener::startDocument() {
  Serial.println("start document");
}

void ExampleListener::startArray(ElementPath path) {
  Serial.println("start array. ");
}

void ExampleListener::startObject(ElementPath path) {
  Serial.println("start object. ");
}

void ExampleListener::value(ElementPath path, char* value) {
}

void ExampleListener::value(ElementPath path, long value) {
}

void ExampleListener::value(ElementPath path, float value) {
  char fullPath[200] = "";
  path.toString(fullPath);
  Serial.print(fullPath);
  Serial.print(" float value: ");
  Serial.println(value);
  
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

void ExampleListener::value(ElementPath path, bool value) {
}

void ExampleListener::value(ElementPath path) {
  Serial.println("value: null");
}

void ExampleListener::endArray(ElementPath path) {
  Serial.println("end array. ");
}

void ExampleListener::endObject(ElementPath path) {
  Serial.println("end object. ");
}

void ExampleListener::endDocument() {
  Serial.println("end document. ");
}

void ExampleListener::whitespace(char c) {
  Serial.println("whitespace");
}