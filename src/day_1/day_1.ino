#include <Adafruit_NeoPixel.h>

#define NPIXEL 30
#define PIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIXEL, PIN); // (pixels, pin)
const int SW_pin = 2; //Joystick Button
const int X_pin = 0; //Joystick X Axis
const int Y_pin = 1; //Joystick Y Axis
//int pixel = 0;
bool par = true;
//int s_pix = pixel;

namespace vaporwave {
  uint32_t rosa = strip.Color(255,113,206);
  uint32_t azul = strip.Color(1,205,254);
  uint32_t verde = strip.Color(5,255,161);
  uint32_t morado = strip.Color(185,103,255);
  uint32_t amarillo = strip.Color(255,251,150);
  uint32_t colors[] = {rosa,azul,verde,morado,amarillo};
}

int aPix=0;
int bPix=1;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  
  strip.begin();
  strip.setBrightness(250); // 250 Full brightness
  strip.show();             // All pixels off
}

void loop() {
  alternateColorCascade();

//  basicLedCar(X_pin,47,244,10,aPix);
//  basicLedCar(Y_pin,255,0,0,bPix);

  strip.show();
  delay(50);
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
void alternateColor() {
  if (analogRead(X_pin)>1000)
    par = true;
  else if (analogRead(X_pin)<24)
    par = false;
    
  for(int i = 0; i < NPIXEL;i++) {
    if(par) {
      if(i%2==0)
        strip.setPixelColor(i,255,113,206);
      else
        strip.setPixelColor(i,255,251,150);
    } else {
      if(i%2==0)
        strip.setPixelColor(i,255,251,150);
      else
        strip.setPixelColor(i,255,113,206);
    }
  }

  strip.show();
}

void alternateColorFull() {
  par = !par;
  for (int i=0;i<NPIXEL;i++) {
    if(par) {
      if(true)//i%4==0)
        strip.setPixelColor(i,vaporwave::verde);
      else
        strip.setPixelColor(i,vaporwave::morado);
    } else {
      if(true)//i%4==0)
        strip.setPixelColor(i,vaporwave::morado);
      else
        strip.setPixelColor(i,vaporwave::verde);
    }
  }
}

int colorIndex=0;
int pixelIndex=0;

void alternateColorCascade() {
  if (pixelIndex>=strip.numPixels()) {
    colorIndex = (colorIndex<4)?(colorIndex+1):0;
    pixelIndex = 0;
  }
  strip.setPixelColor(pixelIndex,vaporwave::colors[colorIndex]);
  pixelIndex++;
}
