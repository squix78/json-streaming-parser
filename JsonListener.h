/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Contributors:
    Stefano Chizzolini

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch and https://github.com/squix78/json-streaming-parser
*/

#pragma once

#include <Arduino.h>
#include "ElementPath.h"
#include "ElementValue.h"

class JsonListener {
  private:

  public:

    virtual void endArray(ElementPath path) = 0;

    virtual void endDocument() = 0;

    virtual void endObject(ElementPath path) = 0;

    virtual void startArray(ElementPath path) = 0;
  
    virtual void startDocument() = 0;

    virtual void startObject(ElementPath path) = 0;

    virtual void value(ElementPath path, ElementValue value) = 0;
  
    virtual void whitespace(char c) = 0;
};