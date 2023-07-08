// CIRC 2023 GPS Beacon Code
// Used for providing real-time gps location of objects, such as the reactor and astronaut
// Torban Peterson torban@torban.ca

#include <Adafruit_GPS.h>  // GPS Functionality
#include <WiFi.h>          // WIFI Functionality
#include <WiFiClient.h>    // WIFI Functionality
#include <WiFiAP.h>        // WIFI Functionality

#define GPSSerial Serial2  // On ESP-32, Serial 2 is TX=GPIO17, RX= GPIO16
#define LED_BUILTIN 2      // Onboard LED
#define GPSTOSERIAL true   // Enables serial output of GPS to USB terminal every 2 seconds

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);


uint32_t timer = millis(); // General Purpose timer

const char *ssid = "Reactor";  // SSID Name
IPAddress local_IP(10, 10, 10, 1);
IPAddress gateway(10, 10, 10, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);     // Webserver

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("CIRC 2023 GPS Beacon");
  Serial.println("Version 0");
  Serial.println("https://github.com/canspacetech/CIRC-2023-Night-Task-HW-SW.git");

  Serial.println("Startup GPS Module");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);  // turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);     // 1 Hz update rate


  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  if (!WiFi.softAP(ssid)) {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  Serial.println("Start Webserver ");
  server.begin();
}

void loop() {                              // run over and over again
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // GPS Printout
            // Time - Line 1
            client.print("<br>Time: ");
            if (GPS.hour < 10) { client.print('0'); }
            client.print(GPS.hour, DEC);
            client.print(':');
            if (GPS.minute < 10) { client.print('0'); }
            client.print(GPS.minute, DEC);
            client.print(':');
            if (GPS.seconds < 10) { client.print('0'); }
            client.print(GPS.seconds, DEC);
            client.print('.');
            if (GPS.milliseconds < 10) {
              client.print("00");
            } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
              client.print("0");
            }
            client.println(GPS.milliseconds);

            // Date - Line 2
            client.print("<br>Date: ");
            client.print(GPS.day, DEC);
            client.print('/');
            client.print(GPS.month, DEC);
            client.print("/20");
            client.println(GPS.year, DEC);
            // If location recieved
            if (GPS.fix) {
              client.print("<br>Location: ");
              client.print(GPS.latitudeDegrees, 9);
              client.print(GPS.lat);
              client.print(", ");
              client.print(GPS.longitudeDegrees, 9);
              client.println(GPS.lon);
              client.print("<br>Speed (knots): ");
              client.println(GPS.speed);
              client.print("<br>Angle: ");
              client.println(GPS.angle);
              client.print("<br>Altitude: ");
              client.println(GPS.altitude);
              client.print("<br>Satellites: ");
              client.println((int)GPS.satellites);
            }


            // the content of the HTTP response follows the header:
            client.print("<br>Click <a href=\"/H\">here</a> to turn ON the LED Beacon.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED Beacon.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, HIGH);  // GET /L turns the LED on
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, LOW);  // GET /H turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }

  // read data from the GPS in the 'main loop'
  char c = GPS.read();

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived() flag to false
      return;                        // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 2 seconds or so, print out the current stats to Serial2

  if (GPSTOSERIAL) {
    if (millis() - timer > 2000) {
      timer = millis();  // reset the timer
      Serial.print("\nTime: ");
      if (GPS.hour < 10) { Serial.print('0'); }
      Serial.print(GPS.hour, DEC);
      Serial.print(':');
      if (GPS.minute < 10) { Serial.print('0'); }
      Serial.print(GPS.minute, DEC);
      Serial.print(':');
      if (GPS.seconds < 10) { Serial.print('0'); }
      Serial.print(GPS.seconds, DEC);
      Serial.print('.');
      if (GPS.milliseconds < 10) {
        Serial.print("00");
      } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
        Serial.print("0");
      }
      Serial.println(GPS.milliseconds);
      Serial.print("Date: ");
      Serial.print(GPS.day, DEC);
      Serial.print('/');
      Serial.print(GPS.month, DEC);
      Serial.print("/20");
      Serial.println(GPS.year, DEC);
      if (GPS.fix) {
        Serial.print("Location: ");
        Serial.print(GPS.latitudeDegrees, 9);
        Serial.print(GPS.lat);
        Serial.print(", ");
        Serial.print(GPS.longitudeDegrees, 9);
        Serial.println(GPS.lon);
        Serial.print("Speed (knots): ");
        Serial.println(GPS.speed);
        Serial.print("Angle: ");
        Serial.println(GPS.angle);
        Serial.print("Altitude: ");
        Serial.println(GPS.altitude);
        Serial.print("Satellites: ");
        Serial.println((int)GPS.satellites);
      }
    }
  }
}
