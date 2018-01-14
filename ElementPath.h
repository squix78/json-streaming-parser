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

/*
 * Unified element selector.
 * Represents the handle associated to an element within either
 * an object (key) or an array (index). 
 */
class ElementSelector {
  public:
    int index;
    char key[20];
    
    bool isObject();
    void moveNext();
    void reset();
    void set(int index);
    void set(char* key);
    void toString(char* buffer);
};

/*
 * Hierarchical path to currently parsed element.
 * It eases element filtering, keeping track of the current node
 * position.  
 */
class ElementPath {
  private:
    ElementSelector* currentSelector;
    ElementSelector selectors[20];

  public:
    int count = 0;
    
    ElementSelector* get(int index);
    int getCurrentIndex();
    char* getCurrentKey();
    ElementSelector* peek();
    void pop();
    ElementSelector push();
    void toString(char* buffer);
};
