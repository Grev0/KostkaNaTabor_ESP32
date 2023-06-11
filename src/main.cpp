/*
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>



int a = 1;


#include <Adafruit_NeoPixel.h>
#define PIN 2
#define LED_COUNT 30
#define BRIGHTNESS 50


Adafruit_NeoPixel pixels(30, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(921600);
  pixels.begin();
}

void loop(){
  pixels.clear();
  Serial.printf("Second %i\n", a);

  for(int i=0; i<30; i++) { // For each pixel...

    pixels.setPixelColor((i - 1), 0, 0, 0);
    pixels.setPixelColor(i, 20, 50, 2);
    pixels.show();
    delay(25);
  }

  for(int i=31; i>1; i--) { // For each pixel...
    pixels.setPixelColor((i + 1), 0, 0, 0);
    pixels.setPixelColor(i, 20, 50, 2);
    pixels.show();
    delay(25);
  }
}

///////////////////////////////////////////////////////////////////////////
*/


/*
#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>

const char* ssid = "ESP32";
const char* password = "heslo";

String header;

IPAddress subnet(255, 255, 0, 0);

void setup(){
    Serial.begin(115200);

    
// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    Serial.print("Connecting to ");
    Serial.println(ssid);


    while(WiFi.status() != WL_CONNECTED){
        Serial.println(local_IP);
        Serial.print('\n');
        Serial.print(".");
        Serial.print('\n');
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("\nLocal ESP32 IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("\n");
}

void loop(){

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("Tlacitko01") >= 0) {
              Serial.println("Tlacitko01");
            } else if (header.indexOf("Tlacitko02") >= 0) {
              Serial.println("Tlacitko02");
            } else if (header.indexOf("Tlacitko03") >= 0) {
              Serial.println("Tlacitko03");
            } else if (header.indexOf("Tlacitko04") >= 0) {
              Serial.println("Tlacitko04");
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Tlacitko01</p>");
            // If the output26State is off, it displays the ON button       
            if (true) {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Tlacitko02</p>");
            // If the output27State is off, it displays the ON button       
            if (false) {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
*/


#include <Arduino.h>
#include <WiFi.h>

#include "Arduino.h"	
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"

//#ifndef wificlient_h
#define wificlient_h

const char *ssid = "Access";
const char *passphrase = "heslo";
/*
int channel = 1;
int ssid_hidden = 0;
int max_connection = 2;
*/


//IPAddress address(100, 20, 3, 255);
//IP = WiFi.localIP(100, 20, 3, 255);

unsigned long previousMillis = 0;
int interval = 500;
String CLIENT_NAME = "SENSOR1";
WiFiClient client;
// IP Address of the server
IPAddress server(192, 168, 4, 1);
String ServerMessage;
//IPAddress localIP(192, 168, 4, 1);
//IPAddress IP = ;

String Server;

void setup()
{
  WiFi.config(192,168,4,1);

  Serial.begin(115200);
  
  Serial.println("Connecting");

  

  //IPAddress IP = WiFi.begin(ssid, passphrase);
  //WiFi.softAP(WIFI_AP);
  
  WiFi.config(192,168,4,1);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("\n");
    Serial.print(WiFi.status());

    Serial.print("\n");
    
   // Serial.print("\n\nAP IP address: ");
   // Serial.println(WiFi.config());

    Serial.print("IP local: ");
    Serial.println(WiFi.localIP());

    Serial.print("password: ");
    Serial.print(passphrase);

    Serial.print("\nssid: ");
    Serial.print(ssid);
    delay(500);
    
  }
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    Serial.println("Attemting to connect");
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("wifi status connected");
      client.connect(ssid, 80);
      while (client.connected())
      {
        Serial.println("client connected");
        String data = client.readStringUntil('\r');
        if (data != "\0")
        {
          Serial.print("Received data from Server:");
          Serial.println(data);
          int Index = data.indexOf(':');
          String CLIENT = data.substring(0, Index);
          String ACTION = data.substring(Index + 1);
          if (CLIENT == CLIENT_NAME)
          {
            if (ACTION == "TEMPERATURE?")
            {
              client.println("ACK:10");
              Serial.println("This is Client: ACK10 was sent to server");
            }
          }
          else if (CLIENT == "OUTPUT1")
          {
            if (ACTION == "ON" || ACTION == "OFF")
            {
              Serial.println("This is Client: server is sending output1 On or Off command");
            }
          }
          client.flush();
          data = "\0";
        }
      }
    }
    previousMillis = millis();
  }
}
