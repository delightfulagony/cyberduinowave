#include <Adafruit_NeoPixel.h>

#define NPIXEL 30
#define LEDPIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIXEL, LEDPIN); // (pixels, pin)

const int soundPin = A0;

namespace vaporwave {
  uint32_t rosa = strip.Color(0,255,159);
  uint32_t azul = strip.Color(0,184,255);
  uint32_t verde = strip.Color(0,30,255);
  uint32_t morado = strip.Color(189,0,255);
  uint32_t amarillo = strip.Color(214,0,255);
  uint32_t colors[] = {rosa,azul,verde,morado,amarillo};
}

struct cascade {
  int pixel = 0;
  bool running = false;
  uint32_t color;
} cascades[NPIXEL];

void colorCascade(int &pixelIndex, bool &running, uint32_t color) {
  if (pixelIndex>=strip.numPixels()) {
    running = false;
    pixelIndex = 0;
  }
  strip.setPixelColor(pixelIndex,color);
  pixelIndex++;
}

void newCascade(int &number, uint32_t color) {
  if (number>=NPIXEL) {
    number = 0;
  }
  cascades[number].pixel = 0;
  cascades[number].running = true;
  cascades[number].color = color;
  number++;
}

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(250); // 250 Full brightness
  strip.show();             // All pixels off
}

int value;
bool unlock = true;

int contador=0;
int mediaProgreso=0;
int mediaUmbral=60;

int colorIndex=0;
int nCascadas=0;

void loop() {
  value = analogRead(soundPin);

  for (unsigned int i=0; i<NPIXEL; i++) {
    if (cascades[i].running)
      colorCascade(cascades[i].pixel,cascades[i].running,cascades[i].color);
  }

  if (contador < 50) {
    mediaProgreso += value;
    contador++;
  } else {
    contador = 0;
    mediaUmbral = (mediaProgreso/50);
    mediaProgreso = 0;
  }

  Serial.println(value);
  Serial.println(mediaUmbral);

  if (value < mediaUmbral)
    unlock = true;

  if (value > mediaUmbral and unlock) {
    colorIndex = (colorIndex<4)?(colorIndex+1):0;
    newCascade(nCascadas, vaporwave::colors[colorIndex]);
    unlock = false;
  }
  strip.setPixelColor(0,0,0,0);
  strip.show();
  //delay(20);
}
