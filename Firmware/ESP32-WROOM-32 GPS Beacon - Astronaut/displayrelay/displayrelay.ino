
#include <Wire.h>  // Include the Arduino SPI library

uint32_t timer_relay = millis();  // For monitoring and debouncing relay
uint32_t relay_counter = 0;
const byte s7sAddress = 0x71;

unsigned int counter = 9900;  // This variable will count up to 65k
char tempString[10];          // Will be used with sprintf to create strings

void setup() {
  Wire.begin();       // Initialize hardware I2C pins
  clearDisplayI2C();  // Clears display, resets cursor
  pinMode(9, INPUT);  //relay pin
  s7sSendStringI2C("2033");
}

void loop() {

  if (digitalRead(9) && millis() > (timer_relay + 5000)) {
    timer_relay = millis();  // Reset timer
    relay_counter++;         //increment relay counter
    if (relay_counter == 1) {
      s7sSendStringI2C("2572");  // hit 1
    } else if (relay_counter == 2) {
      s7sSendStringI2C("3999");  // hit 2
    } else if (relay_counter == 3) {
      s7sSendStringI2C("9001");  // hit 3
    } else if (relay_counter == 0) {
      s7sSendStringI2C("2033");
    } else{
      relay_counter = 0;
    }
  }
}

// This custom function works somewhat like a serial.print.
//  You can send it an array of chars (string) and it'll print
//  the first 4 characters in the array.
void s7sSendStringI2C(String toSend) {
  Wire.beginTransmission(s7sAddress);
  for (int i = 0; i < 4; i++) {
    Wire.write(toSend[i]);
  }
  Wire.endTransmission();
}

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void clearDisplayI2C() {
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x76);  // Clear display command
  Wire.endTransmission();
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightnessI2C(byte value) {
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x7A);   // Set brightness command byte
  Wire.write(value);  // brightness data byte
  Wire.endTransmission();
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimalsI2C(byte decimals) {
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x77);
  Wire.write(decimals);
  Wire.endTransmission();
}
