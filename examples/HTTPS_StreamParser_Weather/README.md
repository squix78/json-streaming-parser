# HTTP/HTTPS Open Weather Maps Stream Parser
An example whereby we connect to a HTTPS JSON service (Open Weather Maps) directly and use the Arduino HTTPClient class to send the received data directly to the parser as a 'Stream' interface.

Fast, efficient and doesn't require the JSON to be saved to memory as a String and then parsed character by character.

The weather forecast results extracted from the parsed JSON are placed into a custom C++ map and also forward_list for later printing to the Serial output. 
