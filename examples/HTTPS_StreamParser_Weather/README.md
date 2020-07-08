# HTTP/HTTPS Open Weather Maps Stream Parser
An example whereby we connect to a HTTPS JSON service (Open Weather Maps) directly and use the Arduino HTTPClient class to send the received data directly to the parser as a 'Stream' interface.

Fast, efficient and doesn't require the JSON to be saved to memory as a String and then parsed character by character.

The weather forecast results extracted from the parsed JSON are placed into a custom C++ map and also forward_list for printing to the Serial output. For example: 


```
Starting.........
Heap free: 48456
Stack free: 2048
Connecting.....
Connected, IP address: 192.168.43.197
Heap free: 48456
Stack free: 2048
SSL fingerprint set.
Heap free: 42040
Stack free: 2048
Setup JSON Streaming Parser.
Heap free: 42040
Stack free: 2048
Making HTTPS Connection.
Heap free: 41912
Stack free: 2048
[HTTP] GET... code: 200
Heap free: 20784
Stack free: 576
Got payload response of length: -1
Parsing JSON...
Heap free: 20784
Stack free: 576
-> Found a key we care about: list[0].dt = 1487246336
-> Found a key we care about: list[0].main.temp = 286.670013
-> Found a key we care about: list[0].main.temp_min = 281.556000
-> Found a key we care about: list[0].main.temp_max = 286.670013
Completed Parsing.
Heap free: 19120
Stack free: 576
Done.
Heap free: 19120
Stack free: 576
----------------- PRINTING MAP VALUES -----------------
list[0].dt = 1487246336.00
list[0].main.temp = 286.67
list[0].main.temp_max = 286.67
list[0].main.temp_min = 281.56
----------------- PRINTING FORECAST LIST -----------------
Forecast for Thursday 16 February @ 11:00: Clear and 28 degrees.
Forecast for Thursday 16 February @ 15:00: Clear and 28 degrees.
Forecast for Thursday 16 February @ 17:00: Clear and 27 degrees.
Forecast for Thursday 16 February @ 21:00: Clear and 27 degrees.
Forecast for Friday 17 February @ 0:00: Clouds and 27 degrees.
Forecast for Friday 17 February @ 2:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 6:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 8:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 12:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 15:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 17:00: Rain and 27 degrees.
Forecast for Friday 17 February @ 21:00: Rain and 27 degrees.
Forecast for Saturday 18 February @ 0:00: Rain and 27 degrees.
Forecast for Saturday 18 February @ 2:00: Rain and 27 degrees.
Forecast for Saturday 18 February @ 6:00: Rain and 27 degrees.
Forecast for Saturday 18 February @ 8:00: Rain and 27 degrees.
Forecast for Saturday 18 February @ 11:00: Clear and 27 degrees.
Forecast for Saturday 18 February @ 15:00: Clear and 27 degrees.
Forecast for Saturday 18 February @ 17:00: Clear and 27 degrees.
Forecast for Saturday 18 February @ 21:00: Clear and 27 degrees.
Forecast for Sunday 19 February @ 0:00: Clear and 26 degrees.
Forecast for Sunday 19 February @ 2:00: Clear and 26 degrees.
Forecast for Sunday 19 February @ 6:00: Clear and 26 degrees.
Forecast for Sunday 19 February @ 8:00: Clear and 27 degrees.
Forecast for Sunday 19 February @ 12:00: Clear and 27 degrees.
Forecast for Sunday 19 February @ 15:00: Clear and 27 degrees.
Forecast for Sunday 19 February @ 17:00: Clear and 27 degrees.
Forecast for Sunday 19 February @ 21:00: Clear and 26 degrees.
Forecast for Monday 20 February @ 0:00: Clear and 26 degrees.
Forecast for Monday 20 February @ 2:00: Clear and 26 degrees.
Forecast for Monday 20 February @ 6:00: Clear and 26 degrees.
Forecast for Monday 20 February @ 8:00: Clear and 27 degrees.
Forecast for Monday 20 February @ 11:00: Clear and 27 degrees.
Forecast for Monday 20 February @ 15:00: Clear and 27 degrees.
Forecast for Monday 20 February @ 17:00: Clouds and 27 degrees.
Forecast for Monday 20 February @ 21:00: Clouds and 27 degrees.
```
