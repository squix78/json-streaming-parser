// Space Station class functions which supports the main sketch

#include "ISS_API_Class.h" // Include the header with the function prototypes etc

/***************************************************************************************
**  Connect to website and get the International Space Station pass times
***************************************************************************************/
void SpaceStation::getPasses(String latitude, String longitude, ISS_pass* passData)
{
  this->passData = passData; // Make a copy of the pointer for this class

  JsonStreamingParser json;      // Create an instance of the parser
  json.setListener(this); // Pass pointer to "this" SpaceStation class to the listener
                          // so it can call the support functions in this class

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  // URL and port of the server
  const char*  host = "api.open-notify.org";
  const int httpPort = 80;

  // Connect as a client to the server
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Built up the GET request
  String url = "http://api.open-notify.org/iss-pass.json?lat=" + latitude + "&lon=" + longitude + "&n=" + PASSES;

  // Send GET request
  Serial.println("\nSending GET request to api.open-notify.org...\n");
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  // Local variables for time-out etc
  uint32_t timeout = millis();
  char c = 0;
  uint16_t ccount = 0;

  Serial.println("=====>   Header start   <=====");

  // Read the header that precedes the JSON, ends with \r\n
  while ( client.available() > 0 || client.connected())
  {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("=====>   Header end    <=====");
      break;
    }

    Serial.println(line); // Print the header to serial monitor for viewing

    // Check for timeout
    if ((millis() - timeout) > 5000UL)
    {
      Serial.println ("HTTP header timeout");
      client.stop();
      return;
    }
  }

  // The JSON message should now be in the buffer for reading

  // Read the JSON character by character and pass it to the JSON decoder
  // The decoder will call the SpaceStation class  during decoding, so we can
  // save the decoded values

  // Use OR since data may still be in the buffer when the client has disconnected!
  while ( client.available() > 0 || client.connected())
  {
    while(client.available() > 0)
    {
      c = client.read(); // Read a received character

      #ifdef SHOW_JSON   // Optionally show the message with a simple formatter
      Serial.print(c);
      #endif

      json.parse(c);     // Pass to the parser, parser will call listener support functions as needed

      // Check for timeout
      if ((millis() - timeout) > 8000UL)
      {
        Serial.println ("JSON parse client timeout");
        json.reset();
        client.stop();
        return;
      }
      yield();
    }
  }

  json.reset();

  client.stop();

}

/***************************************************************************************
**  JSON Decoder library calls this when a key has been read
***************************************************************************************/
void SpaceStation::key(String key) {
  currentKey = key;

  //Serial.print("key: ");
  //Serial.println(key);
}

/***************************************************************************************
**  JSON Decoder library calls this when a value has been read
***************************************************************************************/
void SpaceStation::value(String val) {

  // Test only:
  //Serial.print("\nvaluePath     :"); Serial.println(valuePath);
  //Serial.print("currentParent :"); Serial.println(currentParent);
  //Serial.print("currentKey    :"); Serial.println(currentKey);
  //Serial.print("arrayIndex    :"); Serial.println(arrayIndex);
  //Serial.print("Value    :"); Serial.println(val);

  if (currentParent == "")
  {
    if (currentKey == "message") passData->message = val;
    return;
  }

  else
  if (currentParent == "request")
  {
    if (currentKey == "datetime") passData->datetime = (uint32_t)val.toInt();
  }
  
  else
  if (valuePath == "/response")
  {
    if (currentKey == "duration") passData->passDuration[arrayIndex] = (uint16_t)val.toInt();
    else
    if (currentKey == "risetime") passData->passRiseTime[arrayIndex] = (uint32_t)val.toInt();
  }
}

/***************************************************************************************
**  JSON Decoder library calls this when a start of document decoded
***************************************************************************************/
void SpaceStation::startDocument() {
  currentParent = currentKey = "";
  arrayIndex = 0;
  ended = false;

  //Serial.println("\nstart document");
}

/***************************************************************************************
**  JSON Decoder library calls this when a end of document decoded
***************************************************************************************/
void SpaceStation::endDocument() {
  ended = true;

  //Serial.println("end document. ");
}

/***************************************************************************************
**  JSON Decoder library calls this when a start of object decoded
***************************************************************************************/
void SpaceStation::startObject() {
  currentParent = currentKey;

  //Serial.println("start object. ");
}

/***************************************************************************************
**  JSON Decoder library calls this when a end of object decoded
***************************************************************************************/
void SpaceStation::endObject() {
  currentParent = "";
  arrayIndex++;
  
  //Serial.println("end object. ");
}

/***************************************************************************************
**  JSON Decoder library calls this when an array of values has started
***************************************************************************************/
void SpaceStation::startArray() {
   arrayIndex  = 0;
   valuePath = currentParent + "/" + currentKey;

   //Serial.println("start array. ");
}

/***************************************************************************************
**  JSON Decoder library calls this when an array of values has ended
***************************************************************************************/
void SpaceStation::endArray() {
  valuePath = "";

  //Serial.println("end array. ");
}

/***************************************************************************************
**  JSON Decoder library calls this when a character is whitespace (not used here)
***************************************************************************************/
void SpaceStation::whitespace(char c) {

  //Serial.println("whitespace");
}
