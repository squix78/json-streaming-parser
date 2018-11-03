// This is an example sketch for the JsonStreamingParser library:
// https://github.com/squix78/json-streaming-parser

// It is compatible with the ESP8266 and ESP32, but could be adapted for other processors
// Created by Bodmer 3/11/18

// It connects to a website, requests a list of International Space Station passes that might
// be visible, decodes (parses) the returned JSON message and prints the results to the
// serial monitor window.

// The sketch uses WiFi to connect to your router and sends a GET request to this
// website which responds with pass times and duration:
// http://open-notify.org/Open-Notify-API/ISS-Pass-Times/
// This site is convenient for use in an example becuase you do not need to setup an
// account and the API requests per day is not limited. The website also outputs quite a
// simple JSON message with line feeds etc, so it prints nicely.

// Click the following link to fetch an example JSON message and see it in a browser:
// http://api.open-notify.org/iss-pass.json?lat=27.9881&lon=86.9250

// An alternative ISS pass time API website is here is you wish to adapt the sketch:
// https://wheretheiss.at/w/developer

// To support the example a C++ class is used, this could be in a library of it's own but
// it is attached in the ISS_API_Class tabs of this sketch.

// Request every 5 minutes for demonstration only, ISS pass times are not updated often
const int UPDATE_INTERVAL_SECS = 5 * 60UL; // 5 minutes

// >>>>>>>>>>>>  Change to suit your WiFi router  <<<<<<<<<<<< NOTE
#define WIFI_SSID "Your_SSID"
#define SSID_PASSWORD "Your_password"

// >>>>>>>>>>>>  Change to your location  <<<<<<<<<<<< NOTE
// Set the latitude and longitude to at least 4 decimal places, website server bug means it
// will not accept 0.0000 but 0.0001 is OK, try 0.0000 to show error handling!
//const String latitude =  "27.9881"; // 90.0000 to -90.0000 negative for Southern hemisphere
//const String longitude = "86.9250"; // 180.000 to -180.000 negative for West
const String latitude =  "0.0000001"; // near Null Island
const String longitude = "0.0000001"; //

#include <TimeLib.h> // https://github.com/PaulStoffregen/Time/blob/master/TimeLib.h

// Choose the WiFi library to load
#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else // ESP32
  #include <WiFi.h>
#endif

#include <WiFiUdp.h>

#include "ISS_API_Class.h" // Local sketch functions

SpaceStation api;          // Create an instance of this sketches support class

WiFiUDP udp;               // A UDP instance to send and receive packets

ISS_pass *pass_data;       // Pointer to struct that will contain decoded values

uint32_t nextUpdate = 0;   // Time of next update request

/***************************************************************************************
**                                        Setup
***************************************************************************************/
void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, SSID_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();

  unsigned int localPort = 2390; // local port to listen to for UDP packets

  udp.begin(localPort);

  nextUpdate = millis();  // Set so next update happens immediately
}

/***************************************************************************************
**                                        Loop
***************************************************************************************/
void loop() {

  // Check if it is time for an update
  if (millis() >= nextUpdate)
  {
    // Set next update time
    nextUpdate = millis() + 1000UL * UPDATE_INTERVAL_SECS;

    // Connect to server and fetch ISS pass time
    getPassTimes(latitude, longitude);
  }

}

/***************************************************************************************
**  Get the International Space Station pass times
***************************************************************************************/
void getPassTimes(String latitude, String longitude)
{
  // Create a new struct to contain the decoded values
  pass_data = new ISS_pass;

  uint32_t dt = millis(); // Time how long it takes out of interest only

  // Request passes from website API, provide location and pointer to struct
  api.getPasses(latitude, longitude, pass_data);

  Serial.print("\nJSON response parsed in ");
  Serial.print(millis()-dt);
  Serial.println(" ms\n");

  // Print pass details while struct still exists
  printPasses(pass_data);

  // Delete the struct to recover the memory used
  delete pass_data;
}

/***************************************************************************************
**  Retrieve data from struct and print to serial monitor
***************************************************************************************/
void printPasses(ISS_pass* pass_data)
{
  Serial.print("Message   = "); Serial.println(pass_data->message);
  Serial.print("Date      = "); Serial.println(strDate(pass_data->datetime));
  Serial.println();

  for (int i = 0; i < PASSES; i++ )
  {
    Serial.print("Pass      = "); Serial.println( i+1 );
    Serial.print("Duration  = "); Serial.print(pass_data->passDuration[i]); Serial.println( " s" );
    Serial.print("Rise time = "); Serial.println(strDate(pass_data->passRiseTime[i]));
  }
}

/***************************************************************************************
**  Convert unix time to a local date + time string "Oct 16 17:18", ends with newline
***************************************************************************************/
String strDate(time_t utc)
{
  setTime(utc);      // Set system clock to utc time (not time zone compensated)

  String localDate = "";

  localDate += monthShortStr(month(utc));
  localDate += " ";
  localDate += day(utc);
  localDate += " " + strTime(utc);

  return localDate;
}

/***************************************************************************************
**             Convert unix time to a "local time" time string "12:34"
***************************************************************************************/
String strTime(time_t unixTime)
{
  String localTime = "";

  if (hour(unixTime) < 10) localTime += "0";
  localTime += hour(unixTime);
  localTime += ":";
  if (minute(unixTime) < 10) localTime += "0";
  localTime += minute(unixTime);

  return localTime;
}
