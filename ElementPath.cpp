/**The MIT License (MIT)

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
*/

#include <Arduino.h>
#include "ElementPath.h"

int ElementSelector::getIndex() {
  return index;
}
    
const char* ElementSelector::getKey() {
  return key;
}

bool ElementSelector::isObject() {
  return index < 0;
}

void ElementSelector::reset() {
  index = -1;
  key[0] = '\0';
}

void ElementSelector::set(int index) {
  this->index = index;
  this->key[0] = '\0';
}

void ElementSelector::set(char* key) {
  strcpy(this->key, key);
  this->index = -1;
}

void ElementSelector::step() {
  index++;
}

void ElementSelector::toString(char* buffer) {
  if (index >= 0) {
    sprintf(buffer, "%s[%d]", buffer, index);
  } else {
    strcat(buffer, key);
  }
}

ElementSelector* ElementPath::get(int index) {
  if (index >= count
      || (index < 0 && (index += count - 1) < 0))
    return NULL;

  return &selectors[index];
}

int ElementPath::getCount() {
  return count;
}

ElementSelector* ElementPath::getCurrent() {
  return current;
}

int ElementPath::getIndex() {
  return getIndex(current);
}

int ElementPath::getIndex(int index) {
  return getIndex(get(index));
}

int ElementPath::getIndex(ElementSelector* selector) {
  return selector != NULL ? selector->index : -1;
}

const char* ElementPath::getKey() {
  return current != NULL ? current->key : "\0";
}

const char* ElementPath::getKey(int index) {
  return getKey(get(index));
}

const char* ElementPath::getKey(ElementSelector* selector) {
  return selector != NULL ? selector->key : "\0";
}

ElementSelector* ElementPath::getParent() {
  return get(-1);
}

void ElementPath::pop() {
  if(count > 0) {
    current = --count > 0 ? &selectors[count - 1] : NULL;
  }
}

void ElementPath::push() {
  (current = &selectors[count++])->reset();
}

void ElementPath::toString(char* buffer) {
  if (count <= 0)
    return;

  for(int index = 0; index < count; index++) {
    if(index > 0 && selectors[index].isObject()) {
      strcat(buffer, "."); 
    }
    selectors[index].toString(buffer);
  }
}
