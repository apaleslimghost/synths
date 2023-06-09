#include <Trill.h>
#include <Adafruit_NeoPixel.h>

const unsigned int NUM_TOTAL_PADS = 30;
CustomSlider::WORD rawData[NUM_TOTAL_PADS];

Adafruit_NeoPixel leftPixels(2, D3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightPixels(9, D10, NEO_GRB + NEO_KHZ800);
Trill touchSensor;
uint8_t sliderPads[4] = {18,17,20,19};
CustomSlider slider;

void setup() {
	Serial.begin(115200);
	int ok = touchSensor.begin(Trill::TRILL_CRAFT);
	if(ok != 0) {
		Serial.printf("error %d initialising trill craft", ok);
	}

	slider.setup(sliderPads, 4);

	touchSensor.setMode(Trill::DIFF);
	touchSensor.setPrescaler(4);

	leftPixels.begin();
	leftPixels.clear();
	leftPixels.fill(leftPixels.Color(0xCC, 0x00, 0xFF));
	leftPixels.show();

	rightPixels.begin();
	rightPixels.clear();
	rightPixels.setPixelColor(5, rightPixels.Color(0x33, 0X33, 0xff));
	rightPixels.show();
}

void writeSliderLeds(int position) {
	if(position == -1) {
		rightPixels.clear();
		rightPixels.setPixelColor(5, rightPixels.Color(0x33, 0X33, 0xff));
	rightPixels.show();
		return;
	}

	float ledPosition = (6.0 * static_cast<float>(position)) / 384.0;
	int led = floor(ledPosition);
	float amountR = ledPosition - led;
	float amountL = 1.0 - amountR;

	Serial.println(ledPosition);
	Serial.println(led);
	Serial.println(amountL);
	Serial.println(amountR);

	rightPixels.clear();
	rightPixels.setPixelColor(led + 2, rightPixels.Color(0x33 * amountL, 0X33 * amountL, 0xff * amountL));
	rightPixels.setPixelColor(led + 3, rightPixels.Color(0x33 * amountR, 0X33 * amountR, 0xff * amountR));
	rightPixels.show();
}

void loop() {
	delay(100);
	touchSensor.requestRawData();

	unsigned n = 0;
	// read all the data from the device into a local buffer
	while(touchSensor.rawDataAvailable() > 0 && n < NUM_TOTAL_PADS) {
		rawData[n++] = touchSensor.rawDataRead();
	}

	slider.process(rawData);
	writeSliderLeds(slider.touchLocation(0));
}
