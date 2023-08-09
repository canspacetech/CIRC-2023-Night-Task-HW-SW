
const int test_button = 19;
const int start_button = 18;
#include <Adafruit_NeoPixel.h>
#define LED_PIN 21
#define LED_COUNT 6
#define GOOD_ROD 1429
#define BAD_ROD 783
int continue_test = false;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  pinMode(test_button, INPUT);
  pinMode(start_button, INPUT);

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

// the loop routine runs over and over again forever:
void loop() {
  int dock_alpha = analogRead(36);
  int dock_beta = analogRead(39);
  int dock_gamma = analogRead(34);

  if (dock_alpha > GOOD_ROD || dock_alpha < BAD_ROD) {
    strip.setPixelColor(3, 0, 255, 0);
  } else {
    strip.setPixelColor(3, 255, 0, 0);
  }

  if (dock_beta > GOOD_ROD || dock_beta < BAD_ROD) {
    strip.setPixelColor(4, 0, 255, 0);
  } else {
    strip.setPixelColor(4, 255, 0, 0);
  }

  if (dock_gamma > GOOD_ROD || dock_gamma < BAD_ROD) {
    strip.setPixelColor(5, 0, 255, 0);
  } else {
    strip.setPixelColor(5, 255, 0, 0);
  }


  if (!digitalRead(test_button) || continue_test) {
    continue_test = true;  // keeps running the test

    Serial.print("ALPHA VALUE = ");
    Serial.println(dock_alpha);
    if (dock_alpha < BAD_ROD) {  //bug in hardware with hall upside down so bad rod is actually good rod
      strip.setPixelColor(2, 0, 255, 0);
    } else {
      strip.setPixelColor(2, 255, 0, 0);
    }

    Serial.print("BETA VALUE = ");
    Serial.println(dock_beta);
    if (dock_beta > GOOD_ROD) {
      strip.setPixelColor(1, 0, 255, 0);
    } else {
      strip.setPixelColor(1, 255, 0, 0);
    }

    Serial.print("GAMMA VALUE = ");
    Serial.println(dock_gamma);
    if (dock_gamma < BAD_ROD) {  //bug in hardware with hall upside down so bad rod is actually good rod
      strip.setPixelColor(0, 0, 255, 0);
    } else {
      strip.setPixelColor(0, 255, 0, 0);
    }
  }

  if (!digitalRead(start_button)) {
    if (dock_alpha < BAD_ROD && dock_beta > GOOD_ROD && dock_gamma < BAD_ROD) { //bug in hardware with hall upside down so bad rod is actually good rod
      colorWipe(strip.Color(  255, 255,   0), 50); // Yellow
      strip.show();
      delay(60000);
      ESP.restart();
    } else {
      colorWipe(strip.Color(255,   0,   0), 50); // Red
      strip.show();
      delay(5000);
      ESP.restart();
    }
  }
  strip.show();
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}