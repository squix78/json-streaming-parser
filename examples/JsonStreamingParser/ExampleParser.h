#pragma once

#include "JsonListener.h"

class ExampleListener: public JsonListener {

  public:
    virtual void startDocument();

    virtual void startArray(ElementPath path);

    virtual void startObject(ElementPath path);

    virtual void value(ElementPath path, char* value);
    
    virtual void value(ElementPath path, long value);
    
    virtual void value(ElementPath path, float value);
    
    virtual void value(ElementPath path, bool value);
    
    virtual void value(ElementPath path);

    virtual void endArray(ElementPath path);

    virtual void endObject(ElementPath path);

    virtual void endDocument();
  
    virtual void whitespace(char c);
};
