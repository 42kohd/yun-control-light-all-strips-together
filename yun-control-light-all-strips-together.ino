#include "Bridge.h"
#include "YunServer.h"
#include "YunClient.h"
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIXELS_PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second
int ledState = LOW; // the current state of the output pin
long previousMillis = 0; // will store last time LED was updated
int neoPixelToChange = 0; //track which neoPixel to change
int neoPixel_j = 0; //stores values for program cycles
int defaultBrightness = 255;
long delayMillis = 0; // will store the last time the

int currentLightScheme = 0;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;

int redRaw = 0;
int greenRaw = 0;
int blueRaw = 0;

int waitTime = 0;

int oldValue = 0;
int value = 0;

int currentCycles = 0;
int totalCycles = 0;

int redStartRaw = 0;
int redStartVal = 0;
int greenStartRaw = 0;
int greenStartVal = 0;
int blueStartRaw = 0;
int blueStartVal = 0;

int redEndRaw = 0;
int redEndVal = 0;
int greenEndRaw = 0;
int greenEndVal = 0;
int blueEndRaw = 0;
int blueEndVal = 0;


int redDif = 0;
int greenDif = 0;
int blueDif = 0;


int prevCommand = 0;


int R = 0;
int G = 0;
int B = 0;
int finCount = 15;
int foutCount = 15;
int Rset = 125;
int Gset = 125;
int Bset = 125;
int waitT = 0;



unsigned long currentMillis = millis();

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

void setup() {
  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // This initializes the NeoPixel library.
}

void loop() {

  // Get clients coming from server
  YunClient client = server.accept();
  if (client) {

    String command = client.readStringUntil('/');

    client.println(command);
    if (command == "light") {
      int programMode = client.parseInt();
      client.println(programMode);

      switch (programMode) {
        case 0:
          allColor(strip.Color(0, 0, 0)); //off
          break;
        case 1:
          softBlink(strip.Color(redVal, greenVal, blueVal), 255, 50); // blue
          break;
        case 2:
          // blink in pixels one at a time
          redRaw = client.parseInt();
          redVal = constrain(redRaw, 0, 255);
          greenRaw = client.parseInt();
          greenVal = constrain(greenRaw, 0, 255);
          blueRaw = client.parseInt();
          blueVal = constrain(blueRaw, 0, 255);

          waitTime = client.parseInt();

              client.stop();
              
              
          uint32_t c;
          uint32_t wait;

          if ( waitTime > 0 ) {
            wait = waitTime;
          } else {
            wait = 50;
          }

//          client.print("waitTime: " );
//          client.println(wait);

          c = strip.Color(redVal, greenVal, blueVal);
          neoPixelToChange = 0;
          while (neoPixelToChange <= NUMPIXELS) {
           YunClient client = server.accept();
            if (client) {
              break;
              client.stop();
            }
            currentMillis = millis();
            if (currentMillis - previousMillis > wait) {
              previousMillis = currentMillis;
              strip.setPixelColor(neoPixelToChange, c);
              strip.show();
              neoPixelToChange++;
            }
          }
          break;
        case 3:
          softBlink(strip.Color(0, 0, 255), defaultBrightness, 50); // blue
          break;
        case 4:
          //rainbow


          waitTime = client.parseInt();

          if ( waitTime > 0 ) {
            wait = waitTime;
          } else {
            wait = 50;
          }

          client.print("waitTime: " );
          client.println(wait);

          totalCycles = 5000;
          currentCycles = 0;
          while ( totalCycles > currentCycles ) {
            YunClient client = server.accept();
            if (client) {
              break;
              client.stop();
            }
            currentMillis = millis();
            if (currentMillis - previousMillis > wait) {
              previousMillis = currentMillis;
              uint16_t i;
              for (i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, Wheel((i + neoPixel_j) & 255));
              }
              strip.show();
              neoPixel_j = (neoPixel_j + 1) % 255; //increment j until all colors are used, then start over
            }
            currentCycles++;
          }
          break;
        case 5:
          rainbowCycle(10);
          break;
        case 6:
          redRaw = client.parseInt();
          redVal = constrain(redRaw, 0, 255);
          greenRaw = client.parseInt();
          greenVal = constrain(greenRaw, 0, 255);
          blueRaw = client.parseInt();
          blueVal = constrain(blueRaw, 0, 255);
          allColor(strip.Color(redVal, greenVal, blueVal));
          break;
        case 7:
















          //
          //      int R = 0;
          //      int G = 0;
          //      int B = 0;
          //Fade in
          while (1) { //using an inf loop to be more custom.
            //Protect the strand from higher then 255 values
            if (R > 255 || G > 255 || B > 255) {
              break;  //DO NOT DELETE OR ALTER THIS LINE.
            }
            //break the inf loop if the color is higher then what its set at.
            if (R > Rset + 1 && G > Gset + 1 && B > Bset + 1)  {
              //ReSet the RGB to set values.
              R = Rset;
              G = Gset;
              B = Bset;
              break;
            }
            //update the strip
            for (int i = 0; i < strip.numPixels(); i++) {
              strip.setPixelColor(i, strip.Color(R, G, B));
              strip.show();
              delay(0);
            }
            //increase by the set amount
            R = R + finCount;
            G = G + finCount;
            B = B + finCount;
            delay(waitT);
          }
          //Fade Out
          while (1) { //using an inf loop to be more custom.
            //Protect the strand from higher then 255 values
            if (R > 255 || G > 255 || B > 255) {
              break;  //DO NOT DELETE OR ALTER THIS LINE.
            }
            //break the inf loop if the color is off
            if (R < 0 && G < 0 && B < 0)  {
              //ReSet the RGB to 0 values.
              R = 0;
              G = 0;
              B = 0;
              break;
            }
            //update the strip
            for (int j = 0; j < strip.numPixels(); j++) {
              strip.setPixelColor(j, strip.Color(R, G, B));
              strip.show();
              delay(0);
            }
            //Decrease by the set amount
            R = R - foutCount;
            G = G - foutCount;
            B = B - foutCount;
            delay(waitT);
          }



















          break;
        case 8:
          allColor(strip.Color(redVal, greenVal, blueVal)); //off
          break;

        case 9:
          uint16_t r, g, b;

          wait = 100;
          totalCycles = 500;
          currentCycles = 0;

          redStartRaw = client.parseInt();
          redStartVal = constrain(redStartRaw, 0, 255);
          greenStartRaw = client.parseInt();
          greenStartVal = constrain(greenStartRaw, 0, 255);
          blueStartRaw = client.parseInt();
          blueStartVal = constrain(blueStartRaw, 0, 255);

          redEndRaw = client.parseInt();
          redEndVal = constrain(redEndRaw, 0, 255);
          greenEndRaw = client.parseInt();
          greenEndVal = constrain(greenEndRaw, 0, 255);
          blueEndRaw = client.parseInt();
          blueEndVal = constrain(blueEndRaw, 0, 255);

          allColor(strip.Color(redStartVal, greenStartVal, blueStartVal));
          strip.show();


          client.println("before while loop");

          while ( totalCycles > currentCycles ) {
            YunClient client = server.accept();
            if (client) {
              client.println("found client - stopping");
              break;
              client.stop();
            }

            currentMillis = millis();
            //          client.println(previousMillis);
            //          client.println(currentMillis);

            if (currentMillis - previousMillis > wait) {
              previousMillis = currentMillis;
              redDif = constrain(255 - redEndVal, 0, 255);
              greenDif = constrain(255 - greenEndVal, 0, 255);
              blueDif = constrain(255 - blueEndVal, 0, 255);


              int redNow = 0;
              int greenNow = 0;
              int blueNow = 0;
              //
              //              client.println(redDif);
              //              client.println(greenDif);
              //              client.println(blueDif);

              //              for (g = 0; g < greenDif; g++) {
              //                greenNow = greenStartVal + g;
              //              }
              //              for (b = 0; b < blueDif; b++) {
              //                blueNow = blueStartVal + b;
              //              }
              for (r = 0; r < redDif; r++) {
                redNow = redStartVal + r;
                allColor(strip.Color(constrain(redNow, 0, 255), constrain(greenNow, 0, 255), constrain(blueNow, 0, 255)));
                strip.show();

              }


              client.println(redNow);



              //
              //                    client.print("red: " );
              //                    client.println(redStartVal + r);


              //strip.show();
              currentCycles++;
            }


          }

          break;

        default:
          // if nothing else matches, do the default
          allColor(strip.Color(0, 0, 0)); //off
      }

    }

  }
  client.stop();
  delay(50);

}
//
//void process(YunClient client) {
//  // read the command
//  String command = client.readStringUntil('/');
//
//  // is "message" command?
//  if (command == "light") {
//    lightCommand(client);
//  }
//}
//
//void lightCommand(YunClient client) {
//
//
//  int programMode = client.parseInt();
//  int redRaw = client.parseInt();
//  int redVal = constrain(redRaw, 0, 255);
//  client.print("redval: " );
//  client.println(redVal);
//
//  int greenRaw = client.parseInt();
//  int greenVal = constrain(greenRaw, 0, 255);
//  client.print("greenval: " );
//  client.println(greenVal);
//
//  int blueRaw = client.parseInt();
//  int blueVal = constrain(blueRaw, 0, 255);
//  client.print("blueval: " );
//  client.println(blueVal);
//
//  // Send feedback to client
//  client.print("Command found is ");
//  client.println(programMode);
//
//      switch (programMode) {
//        case 0:
//          allColor(strip.Color(0, 0, 0)); //off
//          break;
//        case 1:
//          softBlink(strip.Color(redVal, greenVal, blueVal), 255, 50); // blue
//          break;
//        case 2:
//          colorWipeCycle(strip.Color(0, defaultBrightness, 0), 500); // green
//          break;
//        case 3:
//          softBlink(strip.Color(0, 0, 255), defaultBrightness, 50); // blue
//          break;
//        case 4:
//        // rainbow
//        currentCycles = wait;
//  while ( wait > currentCycles ) {
//
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > wait) {
//    // save the last time you changed a NeoPixel
//    previousMillis = currentMillis;
//
//    //change the colors of the pixels
//    uint16_t i;
//    for (i = 0; i < strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i + neoPixel_j) & 255));
//    }
//    strip.show();
//    neoPixel_j = (neoPixel_j + 1) % 255; //increment j until all colors are used, then start over
//  }
//  currentCycles++;
//
//  }
//
//
//
//
//
//          break;
//        case 5:
//          rainbowCycle(10);
//          break;
//        case 6:
//          client.println("in program 6");
//          client.println();
//          client.println(redVal);
//          client.println(greenVal);
//          client.println(blueVal);
//          client.println();
//          allColor(strip.Color(redVal, greenVal, blueVal)); //off
//          client.println("end program 6");
//          break;
//        case 7:
//          break;
//        case 8:
//          allColor(strip.Color(redVal, greenVal, blueVal)); //off
//          break;
//        default:
//          // if nothing else matches, do the default
//          allColor(strip.Color(0, 0, 0)); //off
//      }
//
//}

// Fill all the dots with one color
void allColor(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
} // note for a random color, use:
// allColor((unsigned long)random(0x01000000));



void blinkColor(uint32_t c, uint8_t wait) {
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis > wait) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      allColor(c);
    } else {
      ledState = LOW;
      allColor(strip.Color(0, 0, 0)); // off
    }
  }
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  unsigned long currentMillis = millis();
  //only do this if some of the pixels still need to be lit
  if (neoPixelToChange <= NUMPIXELS) {
    if (currentMillis - previousMillis > wait) {
      // save the last time you changed a NeoPixel
      previousMillis = currentMillis;
      //change a pixel
      strip.setPixelColor(neoPixelToChange, c);
      strip.show();
      neoPixelToChange++;
    }
  }
}



// Fill the dots one after the other with a color
void colorWipeCycle(uint32_t c, uint8_t wait) {
  unsigned long currentMillis = millis();
  //only do this if some of the pixels still need to be lit
  if (neoPixelToChange <= NUMPIXELS) {
    if (currentMillis - previousMillis > wait) {
      // save the last time you changed a NeoPixel
      previousMillis = currentMillis;
      //change a pixel
      strip.setPixelColor(neoPixelToChange, c);
      strip.show();
      neoPixelToChange++;
    }
  } else {
    // reset the cycle
    previousMillis = 0;
    neoPixelToChange = 0;
    allColor(strip.Color(0, 0, 0));
  }
}



void rainbow(uint8_t wait) {
  currentCycles = wait;
  while ( wait > currentCycles ) {

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > wait) {
      // save the last time you changed a NeoPixel
      previousMillis = currentMillis;

      //change the colors of the pixels
      uint16_t i;
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i + neoPixel_j) & 255));
      }
      strip.show();
      neoPixel_j = (neoPixel_j + 1) % 255; //increment j until all colors are used, then start over
    }
    currentCycles++;

  }


}





// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > wait) {
    // save the last time you changed a NeoPixel
    previousMillis = currentMillis;
    //change the colors of the pixels
    uint16_t i;
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + neoPixel_j) & 255));
    }
    strip.show();
    neoPixel_j = (neoPixel_j + 1) % 1279; // 5 cycles of all colors on wheel, then start over
  }
}


void softBlink(uint32_t c, uint8_t brightness, uint8_t wait) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > wait) {
    //set the color of all pixels
    allColor(c); // is there a way to set this only once per program ????????????????????
    // save the last time you changed a NeoPixel
    previousMillis = currentMillis;
    uint16_t i;
    int b = (neoPixel_j * brightness) / brightness;
    strip.setBrightness(b);
    strip.show();
    // sometime figure out how to get this to fade down too instead of just restarting //////////////////////
    neoPixel_j = (neoPixel_j + 1) % brightness;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

