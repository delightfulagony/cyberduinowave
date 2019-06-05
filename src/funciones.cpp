#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIXEL, PIN); // (pixels, pin)

namespace vaporwave {
  uint32_t rosa = strip.Color(255,113,206);
  uint32_t azul = strip.Color(1,205,254);
  uint32_t verde = strip.Color(5,255,161);
  uint32_t morado = strip.Color(185,103,255);
  uint32_t amarillo = strip.Color(255,251,150);
  uint32_t colors[] = {rosa,azul,verde,morado,amarillo};
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

void basicLedCar(int xPin, uint32_t color, int& pixel) {
  if (analogRead(xPin)>1000) {
    strip.setPixelColor(pixel,0,0,0);
    pixel=(pixel+1)%NPIXEL;
    strip.setPixelColor(pixel, color);
  } else if (analogRead(xPin)<24) {
    strip.setPixelColor(pixel,0,0,0);
    pixel=pixel>0?pixel-1:29;
    strip.setPixelColor(pixel, color);
  } else {
    strip.setPixelColor(pixel, color);
  }
}
