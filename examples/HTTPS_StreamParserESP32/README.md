# HTTP/HTTPS Stream Parser - ESP32 Example

An enhanced example whereby we connect to a HTTPS JSON feed (web server) directly and use the Arduino HTTPClient class to send the received data directly to the parser as a 'Stream' interface.

* This sketch connects to a webserver and starts streaming a LARGE json file... so the speed of parsing is dependant on your Arduino device CPU and the speed of your WiFi internet.
* The size of the JSON file could be unlimited - but the time taken to parse will also increase.
 
Fast, efficient and doesn't require the JSON to be saved to memory as a String and then parsed character by character.
