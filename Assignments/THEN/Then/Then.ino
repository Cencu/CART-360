

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#define RXPIN 2
#define TXPIN 3

SoftwareSerial GPSSerial(RXPIN, TXPIN);

TinyGPS gps;
long lat, lon;
unsigned long fix_age, time, date, speed, course;
unsigned long chars;
unsigned short sentences, failed_checksum;
int GPS_flag=0;
//int year;
//byte month, day, hour, minute, second, hundredths;

int DEG;
int MIN1;
int MIN2;
// Include the ESP8266 AT library:
#include <SparkFunESP8266WiFi.h>

#define BME_SCK A5
//#define BME_MISO 12
#define BME_MOSI A4
//#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)//change this accordingly

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

//////////////////////////////
// WiFi Network Definitions //
//////////////////////////////
const char mySSID[] = "VIDEOTRON8010";
const char myPSK[] = "VTYFFR4MUVVH3";

/////////////////////
// HTTP HEADER
/////////////////////
const String serverLink = "http://carttest351.000webhostapp.com"; // i.e. microsoft.com
const String endpoint = "/leafletTest/addlocationdb.php";
/* HTTP HEADER AND REQUEST TYPE = {PUT, GET, POST, DELETE} */
String httpHeader = "POST " + endpoint + " HTTP/1.1\n" +
                    "Host: " + serverLink + "\n" +
                    "Connection: close\n" +
                    "Content-Type: application/x-www-form-urlencoded\n";



const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";


// Create a client, and initiate a connection
ESP8266Client client;
// server object used towards the end of the demo.
// (This is only global because it's called in both setup()
// and loop()).
ESP8266Server server = ESP8266Server(80);


void setup() {
  Serial.begin(9600);
  pinMode(TXPIN, OUTPUT);
  pinMode(RXPIN, INPUT);
 
  bool status;

  status = esp8266.begin();
  if (status <= 0)
  {
    Serial.println(F("Unable to communicate with shield. Looping"));
    while (1) ;
  }
 int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
    }
  }
  // Get our assigned IP address and print it:
  Serial.print(("My IP address is: "));
  Serial.println(esp8266.localIP());

  delayTime = 5000;

  Serial.println();

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // To turn the shield on, and verify communication
  // always begin a sketch by calling cell.begin().

}


void loop() {
  
  
  if (Serial.available())
  {
    //  Make sure we haven't posted recently
    // getReq();
    //delay(5000);
    post();
    Serial.println("posted");
    //delay(10000);
    //serverDemo();
    // Then clear the serial buffer:
    while (Serial.available())
      Serial.read();
  }
  delay(delayTime);

 // printValues();
//   If a character has been received over serial:
   GPSSerial.begin(9600);
  GPS_flag = 1; // a flag to control GPS communication
  if (Serial.available()&&GPS_flag==1)
  {

    int c = Serial.read();                   // Read the GPS data
    if (gps.encode(c))                        // Check the GPS data
    {
      // process new gps info here
      gps.get_position(&lat, &lon, &fix_age);
      GPS_flag=0;
    }
  Serial.println(lat,lon);
  }
  GPSSerial.end();

}

void post()
{

  if (client.connect(serverLink, 80) <= 0)
  {
    Serial.println(F("Failed to connect to serverl."));
    return;
  }
  Serial.println(F("Connected."));

  // Set up post parameters - your sensor readings that you want to POST:
  // EX URL: your_top_level_domain/endpoint/process.php
  String params;
 // "$" + params += "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyBbCxEsdcXzR884-ABo1cp58ZfNDnhX8nE";
  params += "$tempe " + String(bme.readTemperature()) + "&";
 // params += "locations" + String(bme.readPressure() / 100.0F) + "&";
  params += "$keywords" + String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "&";
 // params += "tTravel" + String(bme.readHumidity()) + "&";
  params += "$lOrD" + String("light")+"&";
  params += "$geolocations " + String(lat,lon);

  Serial.println(("Attempting to Post!"));
  client.print(httpHeader);
  client.print("Content-Length: "); client.println(params.length());
  client.println();
  client.print(params);

  // available() will return the number of characters
  // currently in the receive buffer.
  while (client.available())
    Serial.write(client.read()); // read() gets the FIFO char
    // connected() is a boolean return value - 1 if the
    // connection is active, 0 if it's closed.
    if (client.connected())
      client.stop(); // stop() closes a TCP connection.
    }

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

//  Serial.print("Pressure = ");
//
//  Serial.print(bme.readPressure() / 100.0F);
//  Serial.println(" hPa");
//
//  Serial.print("Approx. Altitude = ");
//  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//  Serial.println(" m");
//
//  Serial.print("Humidity = ");
//  Serial.print(bme.readHumidity());
//  Serial.println(" %");

  Serial.println();
}
