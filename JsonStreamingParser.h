
#include <Arduino.h>
#include "JsonListener.h"

#define STATE_START_DOCUMENT     0
#define STATE_DONE               -1
#define STATE_IN_ARRAY           1
#define STATE_IN_OBJECT          2
#define STATE_END_KEY            3
#define STATE_AFTER_KEY          4  
#define STATE_IN_STRING          5
#define STATE_START_ESCAPE       6
#define STATE_UNICODE            7
#define STATE_IN_NUMBER          8
#define STATE_IN_TRUE            9
#define STATE_IN_FALSE           10
#define STATE_IN_NULL            11
#define STATE_AFTER_VALUE        12
#define STATE_UNICODE_SURROGATE  13

#define STACK_OBJECT             0
#define STACK_ARRAY              1
#define STACK_KEY                2
#define STACK_STRING             3

class JsonStreamingParser {
  private:
  
  
    int state;
    int stack[20];
    int stackPos = 0;
    JsonListener* myListener;
  
    boolean doEmitWhitespace = false;
    // fixed length buffer array to prepare for c code
    char buffer[512];
    int bufferPos = 0;
  
    char unicodeEscapeBuffer[128];
    int unicodeEscapeBufferPos = 0;
  
    char unicodeBuffer[128];
    int unicodeBufferPos = 0;
    
    int characterCounter = 0;
  
    int unicodeHighSurrogate = 0;
    //private JsonListener listener;

    void endString();

    void endArray();

    void startValue(char c);

    void startKey();

    void processEscapeCharacters(char c);

    boolean isDigit(char c);

    boolean isHexCharacter(char c);
    
    char convertCodepointToCharacter(int num);

    void endUnicodeCharacter(int codepoint);

    void startNumber(char c);

    void startString();

    void startObject();

    void startArray();

    void endNull();

    void endFalse();

    void endTrue();

    void endDocument();

    int convertDecimalBufferToInt(char myArray[], int length);

    void endNumber();

    void endUnicodeSurrogateInterstitial();

    boolean doesCharArrayContain(char myArray[], int length, char c);

    int getHexArrayAsDecimal(char hexArray[], int length);

    void processUnicodeCharacter(char c);

    void endObject();


    
  public:
    JsonStreamingParser();
    void parse(char c);
    void setListener(JsonListener* listener);
  
};

