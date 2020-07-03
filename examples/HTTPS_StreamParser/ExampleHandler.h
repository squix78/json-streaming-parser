#pragma once

#include "JsonHandler.h"

class ExampleHandler: public JsonHandler {

  public:
    virtual void startDocument();

    virtual void startArray(ElementPath path);

    virtual void startObject(ElementPath path);

    virtual void endArray(ElementPath path);

    virtual void endObject(ElementPath path);

    virtual void endDocument();

    virtual void value(ElementPath path, ElementValue value);
  
    virtual void whitespace(char c);
};
