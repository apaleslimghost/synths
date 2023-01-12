---
title: Using your Chordata
permalink: /chordata/manual
---

## Flashing firmware

Chordata uses the same microcontroller as the Raspberry Pi Pico, the RP2040, and anything that can be installed on the Pico will work on Chordata. It uses the [UF2](https://github.com/microsoft/uf2) bootloader flashed by default on the RP2040. Firmware is distributed as files with the `.uf2` extension. You can also flash runtimes such as [CircuitPython](https://circuitpython.org/) or [KalumaJS](https://kalumajs.org/).

Connect the Chordata to Eurorack power, then via a USB cable to a computer. Press the **boot** button. An external drive called `RPI-RP2` will appear. Drag the `.uf2` file you're flashing onto the external drive. After a couple of seconds, the drive will disconnect, and Chordata will restart, running the new firmware. It's safe to unplug the USB cable after it's restarted.

### Troubleshooting

 - **The Chordata must be connected to Eurorack power to turn on and flash. It doesn't draw any power from the USB port.**
 - macOS "Ventura" 13.0 [cannot flash UF2 firmware](https://www.raspberrypi.com/news/the-ventura-problem/) via the Finder. You'll get an error saying `The operation can’t be completed because an unexpected error occurred (error code 100093)`. Upgrade to macOS 13.1, or flash the firmware by copying the `.uf2` file via the command line.

## Pinout

- Pins 1-16 and 21-34 are the standard RP2040 GPIO pins.
- Pins 18, 19, and 35 are connected to GND.
- Pins 17 and 20 are connected directly to the +12V and -12V rails of the Eurorack power connector. This power is filtered by a 10μF tantalum capacitor on each rail.
- Pin 36 is connected to the output of the 3.3V LDO regulator used to power the RP2040. Although the regulator is rated for 1A maximum current, the thermal design of Chordata means a maximum current of around 150mA before the regulator reaches its maximum allowed temperature. To allow plenty of headroom for the RP2040 to function normally, you should only draw a **maximum of 100mA** from the 3.3V pin. This is safe for use in digital logic, but if you have any devices that require 3.3V at a higher current than this, include your own voltage regulator.
- The USB port is connected only to the RP2040 USB D+ and D- pins. USB VBus and ground aren't connected to anything, and the USB data pins aren't broken out to the header. If you want to connect a USB port to a front panel, use a panel mount USB Type-C extension cable.
