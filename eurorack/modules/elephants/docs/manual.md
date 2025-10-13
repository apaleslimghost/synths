---
title: Using your Elephants
permalink: /elephants/manual
---

## Panel overview

![the Elephants panel, with: a large potentiometer dial at the bottom, labelled "1"; a jack socket above that, labelled "2"; an LED next to the socket, labelled "3"; four smaller potentiometer dials above those, collectively labelled "4"; and four more jack sockets at the top, collectively labelled "5"](./assets/panel.png)

<big>

1. Root voltage attenuverter
2. Voltage input (normalised to `+10V`)
3. Root voltage indicator LED
4. Output voltage attenuverters/indicator LEDs
5. Voltage outputs

</big>

## Module architecture

![a diagram showing an input sine wave, and the large dial from the panel; the dial is at the 5 o'clock position, and an identical sine wave is shown as the output](./assets/diagram-1.png)

![a diagram showing an input sine wave, and the large dial from the panel; the dial is at the 10 o'clock position, and an output sine wave is shown that's half the amplitude, and inverted](./assets/diagram-2.png)

![a diagram showing an input sine wave, and the large dial from the panel; the dial is at the 12 o'clock position, and a flat line is shown as the output](./assets/diagram-2.png)

The root attenuverter scales and inverts the input voltage from `-1×` at fully counter-clockwise to `1×` at fully clockwise. If nothing is patched into the input voltage, it's normalled to `+10V`, so the root attenuverter goes from `-10V` to `+10V`. The bipolar LED next to the attenuverter indicates the current root voltage, with red indicating positive voltage and blue indicating negative. When the attenuverter is at 12 o'clock, the root voltage is `0V`.

![a diagram showing an input sine wave, the large dial from the panel, and two smaller dials; the large dial is at the 5 o'clock position, the first smaller dial is at 5 o'clock, and the second smaller dial is at 10 o'clock; an output sine wive is shown next to each smaller dial, which is identical to the input for the first dial, and half the amplitude and inverted for the second dial](./assets/diagram-4.png)

![a diagram showing an input sine wave, the large dial from the panel, and two smaller dials; the large dial is at the 10 o'clock position, the first smaller dial is at 5 o'clock, and the second smaller dial is at 10 o'clock; an output sine wive is shown next to each smaller dial, which is half the amplitude and inverted for the first dial, and half the amplitude again and the original phase for the second dial](./assets/diagram-5.png)

![a diagram showing an input sine wave, the large dial from the panel, and two smaller dials; the large dial is at the 12 o'clock position, the first smaller dial is at 5 o'clock, and the second smaller dial is at 10 o'clock; an flat line is shown as the output next to each smaller dial](./assets/diagram-6.png)

This root voltage is then scaled and inverted from `-1×` to `1×` by four other independent attenuverter channels. The attenuverter knobs are lit to indicate that channel's voltage with red indicating positive voltage and blue indicating negative.

The jacks at the the top of the module output each channel's voltage. The top-left attenuverter outputs its voltage to the top-left jack, and so on.

> ⚠️ **Warning**: do not plug a patch cable into the output jacks that's connected to a voltage or audio source; this could damage the LEDs.
