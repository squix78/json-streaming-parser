#ifndef http_json_stream_H
#define http_json_stream_H

#include "Print.h"
#include "Stream.h"
#include <Arduino.h>
#include "JsonStreamingParser2.h"

class ArudinoStreamParser: public Stream, public JsonStreamingParser  {
public:
    size_t write(const uint8_t *buffer, size_t size) override;
    size_t write(uint8_t data) override;

    bool parseString(String &data);

    int available() override;
    int read() override;
    int peek() override;
    void flush() override;
};


#endif
