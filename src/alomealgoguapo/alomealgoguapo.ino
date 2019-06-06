#include <Adafruit_NeoPixel.h>

#define NPIXEL 30
#define LEDPIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIXEL, LEDPIN); // (pixels, pin)

const int soundPin = A0;

namespace vaporwave {
  uint32_t rosa = strip.Color(255,113,206);
  uint32_t azul = strip.Color(1,205,254);
  uint32_t verde = strip.Color(5,255,161);
  uint32_t morado = strip.Color(185,103,255);
  uint32_t amarillo = strip.Color(255,251,150);
  uint32_t colors[] = {rosa,azul,verde,morado,amarillo};
}
/*
class colorCascade() {
  int pixelIndex=0;

  colorCascade(uint32_t color) {
    
  }
}
*/

int colorIndex=0;
int pixelIndex=0;
int contador=0;
int mediaProgreso=0;
int mediaUmbral=60;

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(50); // 250 Full brightness
  strip.show();             // All pixels off
}

int value;
bool unlock = true;

void loop() {
  //alternateColorCascade();
  
  value = analogRead(soundPin);

  if (contador < 10) {
    mediaProgreso += value;
    contador++;
  } else {
    contador = 0;
    mediaUmbral = (mediaProgreso/10);
    mediaProgreso = 0;
  }

  Serial.println(value);
  Serial.println(mediaUmbral);

  if (value < mediaUmbral)
    unlock = true;

  if (value > mediaUmbral and unlock) {
    colorIndex = (colorIndex<4)?(colorIndex+1):0;
    strip.fill(vaporwave::colors[colorIndex]);
    unlock = false;
  }
    
  strip.show();
  delay(5);
}

void alternateColorCascade() {
  if (pixelIndex>=strip.numPixels() or pixelIndex==0) {
    colorIndex = (colorIndex<4)?(colorIndex+1):0;
    pixelIndex = 0;
  }
  strip.setPixelColor(pixelIndex,vaporwave::colors[colorIndex]);
  pixelIndex++;
}
