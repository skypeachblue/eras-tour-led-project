# The Eras Tour - LED Project

My goal here was to create an LED strip which will light up in sync with the Pixmob LED bracelets, controlled by the IR senders inside the stadium.
Additionally, all received signals are logged to a file (using SPIFFS).

Unfortunately, I did not get the chance to actually try it out (Vienna...).

https://github.com/user-attachments/assets/0c64cc5e-7798-41e2-ad05-a8513c5199d3


The IR commands in this project are based on the [pixmob-ir-reverse-engineering](https://github.com/danielweidman/pixmob-ir-reverse-engineering) project,
including the file in [this issue](https://github.com/danielweidman/pixmob-ir-reverse-engineering/issues/13).

`receiver/effects.h` contains all signals (as uint64) which I've found the Eras Tour Bracelet to respond to.

<div align="center">
<img src="img/on.jpeg" width="200" height="200" /> <img src="img/off.jpeg" width="200" height="200" />
<img src="img/close-up1.jpeg" width="200" height="200" /> <img src="img/close-up2.jpeg" width="200" height="200" />
</div>

## Hardware
* 1x [Seeed Studio XIAO ESP32C3](https://www.mouser.de/ProductDetail/Seeed-Studio/113991054?qs=3Rah4i%252BhyCHVBerMrpzCkw%3D%3D)
* 1x [Vishay TSOP4436 IR Receiver](https://www.mouser.de/ProductDetail/Vishay-Semiconductors/TSOP4436?qs=9Cg39qEKpi4wCNZSvf6qEw%3D%3D)
* 1x [Adafruit Mini Skinny NeoPixel RGB LED Strip](https://www.mouser.de/ProductDetail/Adafruit/2953?qs=ivJcBTDythWo3KcYUoUS1A%3D%3D) (1m)
* 2x [LIR2032H 3.7V 70mAh Coin Cell](https://amzn.eu/d/3eSunD8)
* 2x [Coin Cell Holder](https://amzn.eu/d/a9WcBUC)

Two LIR2032H cells (in parallel) are connected to the battery connector on the back side.  

8 Neopixel LEDs draw about 55mA when set to RGB(45, 45, 45), so the 140mAh from the coin cells should last
for about 2.5h. Since the LEDs won't be on the entire time and will be set to colors
other than white most of the time, I'm hoping that this setup should last through the entire 3.5h
long Eras Tour show. Of course, a better power supply would make things easier but I wanted everything
to be as small as possible.

<div align="center">
<img src="https://files.seeedstudio.com/wiki/XIAO_WiFi/front-label-3.png" height="250" /> <img src="https://files.seeedstudio.com/wiki/XIAO_WiFi/back-label-6.png" height="250" />
</div>

The LED strip is connected directly to `BAT+`, `D7` and `GND`.

The IR receiver is connected directly to `3V3`, `D10` and `GND`.

<div align="center">
<img src="https://files.seeedstudio.com/wiki/XIAO_WiFi/pin_map-2.png" width="500" />
</div>
Source: https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/


## Dependencies
* Arduino IDE 2.3.2 (Important, older versions do not work properly with the ESP32 Boards in my experience)
* ESP32 Boards Package 2.0.17
* [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) 1.12.3
* [Arduino-IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) 4.4.0


## Usage
In order to use SPIFFS, the partition scheme should be set to `Default 4MB with spiffs`
and the SPIFFS partition has to be formatted first. Running `File->Examples->SPIFFS->SPIFFS_Test`
once should do the trick.

`receiver.ino` receives infrared signals and also saves them to the SPIFFS partition.
Every time `setup()` is executed, a new file is created: 0.txt, 1.txt, and so on.  

`read_spiffs.ino` prints the content from all files on the SPIFFS partition.
