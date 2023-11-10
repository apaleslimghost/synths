const {GPIO} = require('gpio')

const LED_PINS = [8, 9, 10, 11, 12, 13, 14, 15]

const leds = LED_PINS.map(pin => new GPIO(pin, OUTPUT))

let led = 0

setInterval(() => {
	const nextLed = (led + 1) % leds.length
	leds[led].low()
	leds[nextLed].high()
	led = nextLed
}, 1000)
