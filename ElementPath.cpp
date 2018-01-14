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

bool ElementSelector::isObject() {
  return index < 0;
}

void ElementSelector::moveNext() {
  index++;
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

/*
 * Builds the string representation of this node position within 
 * its parent.
 */
void ElementSelector::toString(char* buffer) {
  if (index >= 0) {
    sprintf(buffer, "[%d]", index);
  } else {
    strcpy(buffer, key);
  }
}

ElementSelector* ElementPath::get(int index) {
  if(index >= count)
    return NULL;
    
  return &selectors[index];
}

int ElementPath::getCurrentIndex() {
  return peek()->index;
}

char* ElementPath::getCurrentKey() {
  return peek()->key;
}

ElementSelector* ElementPath::peek() {
  return currentSelector;
}

void ElementPath::pop() {
  if(count > 0) {
    count--;
    currentSelector = count > 0 ? &selectors[count - 1] : NULL;
  }
}

ElementSelector ElementPath::push() {
  (currentSelector = &selectors[count++])->reset();
}

/*
 * Builds the full path corresponding to the current node position.
 *
 * For example, "weather[0].id" corresponds to a 3-level hierarchy:
 * {
 *   "weather" : [
 *     {
 *       "id" : ..., <===== HERE IT IS
 *       ... : ...
 *     },
 *     { ... }
 *   ],
 *   ...
 * }
 */
void ElementPath::toString(char* buffer) {
  if (count <= 0)
    return;

  char elementBuffer[20];
  for(int index = 0; index < count; index++) {
    if(index > 0 && selectors[index].isObject()) {
      strcat(buffer, "."); 
    }
    selectors[index].toString(elementBuffer);
    strcat(buffer, elementBuffer);
  }
}
