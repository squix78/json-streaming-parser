#include "ArduinoStreamParser.h"

bool ArudinoStreamParser::parseString(String &data)
{
	for (int i = 0; i < data.length(); i++)
	{
		parse(data[i]);
	}

	return true;
}

size_t ArudinoStreamParser::write(const uint8_t *data, size_t size) {
	
    return 0;
}

size_t ArudinoStreamParser::write(uint8_t data) {
		
	return -1;
}

int ArudinoStreamParser::available() {
    return -1;
}

int ArudinoStreamParser::read() {
    return -1;
}

int ArudinoStreamParser::peek() {
    return -1;
}

void ArudinoStreamParser::flush() {
}

