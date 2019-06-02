#include <Adafruit_NeoPixel.h>

#define NPIXEL 30
#define PIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIXEL, PIN); // (pixels, pin)
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
//int pixel = 0;
bool par;
//int s_pix = pixel;

int aPix=0;
int bPix=1;

struct color {
  int r;
  int g;
  int b;
};

typedef color Color;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  
  strip.begin();
  strip.setBrightness(10); // Full brightness
  strip.show();             // All pixels off
}

void loop() {
  basicLedCar(X_pin,47,244,10,aPix);
  basicLedCar(Y_pin,255,0,0,bPix);
  delay(20);
}

void rainbowRun() {
  for(int i=2;i<NPIXEL;i++) {
    strip.setPixelColor(i-2,0,0,255);
    strip.setPixelColor(i-1,0,255,0);
    strip.setPixelColor(i,255,0,0);
    delay(50);
    strip.show();
    strip.fill(0,0,0);
  }
}

void basicLedCar(int xPin, int r, int g, int b, int& pixel) {
  if (analogRead(xPin)>1000) {
    strip.setPixelColor(pixel,0,0,0);
    pixel=(pixel+1)%NPIXEL;
    strip.setPixelColor(pixel, r, g, b);
  } else if (analogRead(xPin)<24) {
    strip.setPixelColor(pixel,0,0,0);
    pixel=pixel>0?pixel-1:29;
    strip.setPixelColor(pixel, r, g, b);
  } else {
    strip.setPixelColor(pixel, r, g, b);
  }
  strip.show();
}
/*
void shot() {
  if (digitalRead(SW_pin)==LOW)
    s_pix = pixel+2;
    strip.setPixelColor(pixel+1,255,0,0);
    strip.show();
  if (s_pix>pixel) {
    strip.setPixelColor(s_pix-1,0,0,0);
    strip.setPixelColor(s_pix,255,0,0);
    strip.show();
    s_pix = s_pix>NPIXEL?s_pix++:pixel;
  }
}
*/
void stuff() {
  if (analogRead(X_pin)>1000)
    par = true;
  else if (analogRead(X_pin)<24)
    par = false;
    
  for(int i = 0; i < NPIXEL;i++) {
    if(par) {
      if(i%2==0)
        strip.setPixelColor(i,0,0,0);
      else
        strip.setPixelColor(i, 47, 244, 10);
    } else {
      if(i%2==0)
        strip.setPixelColor(i, 47, 244, 10);
      else
        strip.setPixelColor(i,0,0,0);
    }
  }

  strip.show();
}
