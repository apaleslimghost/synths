---
title: Using your Chordata
permalink: /chordata/manual
---

## Flashing firmware

Chordata uses the same microcontroller as the Raspberry Pi Pico, the RP2040, and anything that can be installed on the Pico will work on Chordata. It uses the [UF2](https://github.com/microsoft/uf2) bootloader flashed by default on the RP2040. Firmware is distributed as files with the `.uf2` extension. You can also flash runtimes such as [CircuitPython](https://circuitpython.org/) or [KalumaJS](https://kalumajs.org/).

Connect the Chordata to Eurorack power, then via a USB cable to a computer. Press the **boot** button. An external drive called `RPI-RP2` will appear. Drag the `.uf2` file you're flashing onto the external drive. After a couple of seconds, the drive will disconnect, and Chordata will restart, running the new firmware. It's safe to unplug the USB cable after it's restarted.

### Troubleshooting

 - **The Chordata must be connected to Eurorack power to turn on and flash. It doesn't draw any power from the USB port.**
 - macOS 13 "Ventura" [currently cannot flash UF2 firmware](https://www.raspberrypi.com/news/the-ventura-problem/) via the Finder. You'll get an error saying `The operation can’t be completed because an unexpected error occurred (error code 100093)`. You can flash the firmware by copying the `.uf2` file via the command line.

## Pinout
