# import rotaryio
import board
import neopixel
import rotaryio
import time
import usb_midi
import adafruit_midi
import storage

from digitalio import DigitalInOut, Direction, Pull
from adafruit_midi.control_change import ControlChange
from adafruit_midi.note_on import NoteOn
from adafruit_midi.note_off import NoteOff

pixel = neopixel.NeoPixel(board.D2, 1, brightness = 1.0, auto_write = True)

midi = adafruit_midi.MIDI(midi_out = usb_midi.ports[1], out_channel = 0)

encoders = [
    rotaryio.IncrementalEncoder(board.A1, board.A0, divisor = 1),
    rotaryio.IncrementalEncoder(board.D5, board.D4, divisor = 1),
    rotaryio.IncrementalEncoder(board.MOSI, board.MISO, divisor = 1),
    rotaryio.IncrementalEncoder(board.D7, board.D8, divisor = 1),
]

buttons = [
	DigitalInOut(board.A2),
	DigitalInOut(board.D3),
	DigitalInOut(board.D10),
	DigitalInOut(board.D9)
]

buttons[0].pull = Pull.UP
buttons[1].pull = Pull.UP
buttons[2].pull = Pull.UP
buttons[3].pull = Pull.UP

if buttons[0].value or buttons[1].value:
	storage.disable_usb_drive()

last_position = [0, 0, 0, 0]
last_buttons = [True, True, True, True]

def send_cc_twos_complement(cc, value):
	if value > 0:
		midi.send(ControlChange(cc, value))
	elif value < 0:
		midi.send(ControlChange(cc, 127 + value))

while True:
	pixel[0] = (
		127 * abs(((time.monotonic() % 30) / 30) - 0.5),
		0,
		196
	)

	send_cc_twos_complement(70, encoders[0].position - last_position[0])
	send_cc_twos_complement(71, encoders[1].position - last_position[1])
	send_cc_twos_complement(72, encoders[2].position - last_position[2])
	send_cc_twos_complement(73, encoders[3].position - last_position[3])

	if last_buttons[0] and not buttons[0].value:
		midi.send(NoteOn(60))
	elif not last_buttons[0] and buttons[0].value:
		midi.send(NoteOff(60))

	if last_buttons[1] and not buttons[1].value:
		midi.send(NoteOn(61))
	elif not last_buttons[1] and buttons[1].value:
		midi.send(NoteOff(61))

	if last_buttons[2] and not buttons[2].value:
		midi.send(NoteOn(62))
	elif not last_buttons[2] and buttons[2].value:
		midi.send(NoteOff(62))

	if last_buttons[3] and not buttons[3].value:
		midi.send(NoteOn(63))
	elif not last_buttons[3] and buttons[3].value:
		midi.send(NoteOff(63))

	last_position = [encoders[0].position, encoders[1].position, encoders[2].position, encoders[3].position]
	last_buttons = [buttons[0].value, buttons[1].value, buttons[2].value, buttons[3].value]
	time.sleep(0.1)
