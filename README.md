# JSON Streaming Parser 2
Arduino library for parsing potentially huge json streams on devices with scarce memory. 

## Don't use this library anymore. ArduinoJson is far more functional now, and supports streaming as well.

This library is a fork of squix78's json-streaming-parser, which itself is a port of Salsify's PHP based json streaming parser (https://github.com/salsify/jsonstreamingparser).

Furthermore, this fork implements significant improvements by [stechio](https://github.com/stechio/json-streaming-parser) departing from squix78's original library to introduce:
 * Explicit element path tracking (ElementPath class): object keys and array indices are managed in a robust, unified manner and exposed in each and every event (users are relieved the pain to jury-rig their own custom event-filtering mechanism)
 * String flattening: adhering to common best practises, cumbersome instances of std::string have been replaced by plain C-style char arrays.
 * Strongly-typed values: untypified (string) value event method has been replaced by a strongly-typed one corresponding to actual serialization types.
 
Finally, a couple of useful real life examples have been provided to get you started. 

## How to install

Until the library becomes available in the Arduino IDE library manager you'll have to do a bit more work by hand.
1) Download this library: https://github.com/mrfaptastic/json-streaming-parser2/archive/master.zip
2) Rename master.zip to json-streaming-parser2.zip
3) Open the zip file in the Arduino IDE from menu Sketch > Include Library > Add ZIP Library...

## How to use

This is a streaming parser, which means that you feed a stream of chars into the parser and you take out from that stream whatever you are interested in. In order to do that you will create a subclass of JsonHandler class and implement methods which will be notified in case of certain events in the feed occure. Available events are:

 * startDocument()
 * endDocument()
 * startArray(ElementPath path)
 * endArray(ElementPath path)
 * startObject(ElementPath path)
 * endObject(ElementPath path)
 * value(ElementPath path, ElementValue value)

In your implementation of these methods you will have to write problem specific code to find the parts of the document that you are interested in. Please see the example to understand what that means. In the example the ExampleHandler implements the event methods declared in the JsonHandler interface and prints to the serial console when they are called.


## Why yet another JSON parser?

When working with small (connected) devices you might quickly get to the point where you need to process potentially huge JSON object received from a REST interface.
All libraries for processing JSON objects on the Arduino platform had some deficiencies which led me to create one on my own.
Not really being an expert in writing parsers I miserably failed the first time. 

This is the second attempt and I took Salsify's PHP based parser and ported it to C++. 
This library has been tested on the Arduino/ESP8266 target platform but should work in theory on all platforms available for the Arduino environment

## Why a streaming parser?

Generally speaking when parsing data you have two options to make sense of this data: 
you either create a document object model (DOM) which contains the whole information of that document and lets you retrieve the
nodes with random access. A DOM parser needs the whole document to start parsing and only lets you access the data
after it has finished the process.
The other option you have when parsing a document is to process it char by char (or byte by byte) while it becomes
available to your client code. Compared to the DOM parser this has two advantages: a) you can react
the data as soon as meaningful parts are available and b) you can drop information as soon as the parser has processed
it. This reduces the memory consumption a lot, especially if you retrieve huge documents when only being interested
by a small subset of it. But this efficiency comes at a price: your code will have to do more "magic" than with a
DOM parser, the business logic becomes part of the parser.

## License

This code is available under the MIT license, which basically means that you can use, modify the distribute the code as long as you give credits to Squix78 and Salsify and add a reference to this repository.

## Credits

squix78 for the original Arduino implementation: https://github.com/squix78/json-streaming-parser

Stechio for enhancements: https://github.com/stechio/json-streaming-parser
