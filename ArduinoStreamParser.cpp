#include "ArduinoStreamParser.h"


size_t ArudinoStreamParser::write(const uint8_t *data, size_t size) {
	
	// Trick the Stream Class into thinking it's writing to memory
	//Serial.println("ArudinoStreamParser::write(data, size)");
	
	uint8_t char_val = 0x00;
	
    if(size && data) 
	{
		for (size_t idx=0; idx<size; idx++)
		{
			char_val = *(data + idx);
			parse(char_val);
		}
		
            return size;
        
		
       // DEBUGV(":ArudinoStreamParser: OOM (%d->%d)\n", size);        
    }
	
    return 0;
}

size_t ArudinoStreamParser::write(uint8_t data) {
	
	//Serial.println("ArudinoStreamParser::write(char)");

	// Catch the write of the byte/char from the arduino library.
	parse(data);
	
	return 1;
}

int ArudinoStreamParser::available() {
    return 1;
}

int ArudinoStreamParser::read() {
    return -1;
}

int ArudinoStreamParser::peek() {
    return -1;
}

void ArudinoStreamParser::flush() {
}

