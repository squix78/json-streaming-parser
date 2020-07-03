# HTTPS Stream Parser
An example whereby we connect to a HTTPS JSON feed (web server) directly and use the Arduino HTTPClient class to send the received data directly to the parser as a 'Stream' interface.

Fast, efficient and doesn't require the JSON to be saved to memory as a String and then parsed character by character.

The results in this example are placed into a custom map structure: http://www.cplusplus.com/reference/map/map/ 