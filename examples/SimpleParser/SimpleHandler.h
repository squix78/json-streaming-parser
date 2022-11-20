#pragma once

#include "JsonHandler.h"

class SimpleHandler: public JsonHandler {

  private:
    int mykey_value = 0;

  public:
    virtual void startDocument();

    virtual void startArray(ElementPath path);

    virtual void startObject(ElementPath path);

    virtual void endArray(ElementPath path);

    virtual void endObject(ElementPath path);

    virtual void endDocument();

    virtual void value(ElementPath path, ElementValue value);
  
    virtual void whitespace(char c);

    // our custom function to extract something back from the json when parsed
    inline String getMyKeyString()
    {
      return String("The value of myKey was: " + String(mykey_value));
    }
};