#include <Adafruit_NeoPixel.h>
#include <Trill.h>

const unsigned int NUM_TOTAL_PADS = 30;
CustomSlider::WORD rawData[NUM_TOTAL_PADS];

Adafruit_NeoPixel leftPixels(2, D3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightPixels(9, D10, NEO_GRB + NEO_KHZ800);
Trill touchSensor;
uint8_t sliderPads[4] = {18, 17, 20, 19};
CustomSlider slider;

void setup() {
  Serial.begin(115200);
  Serial.println("what in the fuck");

  while (int code = touchSensor.begin(Trill::TRILL_CRAFT)) {
    Serial.printf("error %d initialising trill craft, retrying", code);
    delay(100);
  }

  slider.setup(sliderPads, 4);

  touchSensor.setMode(Trill::DIFF);
  touchSensor.setPrescaler(4);

  leftPixels.begin();
  leftPixels.clear();
  leftPixels.fill(leftPixels.Color(0x00, 0xFF, 0x00));
  leftPixels.show();

  rightPixels.begin();
  rightPixels.clear();
  rightPixels.show();

  delay(1000);

  updateLogoLeds();

  rightPixels.setPixelColor(5, rightPixels.Color(0x33, 0X33, 0xff));
  rightPixels.show();
}

void writeSliderLeds(int position) {
  if (position == -1) {
    rightPixels.clear();
    rightPixels.setPixelColor(5, rightPixels.Color(0x33, 0X33, 0xff));
    rightPixels.show();
    return;
  }

  float ledPosition = (6.0 * static_cast<float>(position)) / 384.0;
  int led = floor(ledPosition);
  float amountR = ledPosition - led;
  float amountL = 1.0 - amountR;

  rightPixels.clear();
  rightPixels.setPixelColor(
      led + 2,
      rightPixels.Color(0x33 * amountL, 0X33 * amountL, 0xff * amountL));
  rightPixels.setPixelColor(
      led + 3,
      rightPixels.Color(0x33 * amountR, 0X33 * amountR, 0xff * amountR));
  rightPixels.show();
}

uint32_t logoLedColor(float pos) {
  int r = 0xff * (abs(pos - 0.5));
  int g = 0;
  int b = 0x77;

  return Adafruit_NeoPixel::Color(r, g, b);
}

void updateLogoLeds() {
  int time = millis();
  int a = time % 130000;
  int b = (time + 17500) % 70000;
  float aPos = static_cast<float>(a) / 130000.0;
  float bPos = static_cast<float>(b) / 70000.0;

  leftPixels.setPixelColor(0, logoLedColor(aPos));
  leftPixels.setPixelColor(1, logoLedColor(bPos));
  leftPixels.show();
}

void loop() {
  delay(50);
  updateLogoLeds();

  if (!touchSensor.requestRawData()) {
    Serial.println("couldn't read from trill");
    return setup();
  }

  unsigned n = 0;
  // read all the data from the device into a local buffer
  while (touchSensor.rawDataAvailable() > 0 && n < NUM_TOTAL_PADS) {
    rawData[n++] = touchSensor.rawDataRead();
    int data = rawData[n];
    if (data < 1000)
      Serial.print(0);
    if (data < 100)
      Serial.print(0);
    if (data < 10)
      Serial.print(0);
    Serial.print(data);
    Serial.print(" ");
  }

  slider.process(rawData);
  Serial.println("");
  writeSliderLeds(slider.touchLocation(0));
}
