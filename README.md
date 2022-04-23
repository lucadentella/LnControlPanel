# LnControlPanel
![](https://github.com/lucadentella/LnControlPanel/raw/main/images/board-modules.jpg)

![](https://github.com/lucadentella/LnControlPanel/raw/main/images/board-chips.jpg)

## Description

LnControlPanel is an opensource board to create Loconet control panels.

![](https://img.shields.io/badge/license-CC--BY--NC--SA-green)

## What's new :tada:

- 23/04/2022, new board version, with MCP23017 chips instead of CJMCU modules
- 05/03/2022, new firmware (2.0) with support for new Adafruit libraries

## Features :trophy:

 - **32** independent channels:
   - each channel can be configured as **input** (to *control*) or as **output** (to *monitor)*
   - each channel can control/monitor a **turnout** or a **sensor**
   - each channel can have its own **address**
 - Two Loconet connectors for **cascade** connection
 - Based on **Arduino** framework and opensource libraries
 - Configurable using a simple **menu** via **serial** connection

## Tutorials :video_camera:
 - [LnControlPanel on Youtube (ENG)](https://youtu.be/r6l4IHOCdZg)
 - [LnControlPanel su Youtube (ITA)](https://youtu.be/eZ9PHgq4dks)

## Resources :open_file_folder:
 - [Eagle files - board with CJMCU modules](https://github.com/lucadentella/LnControlPanel/tree/main/Eagle/Modules) (schematic / PCB)
 - [Eagle files - board with MCP23017 chips](https://github.com/lucadentella/LnControlPanel/tree/main/Eagle/Chips) (schematic / PCB) 
 - [Arduino firmware](https://github.com/lucadentella/LnControlPanel/tree/main/Arduino)

## Documentation :notebook:
 - [Schematic - board with CJMCU modules](https://github.com/lucadentella/LnControlPanel/tree/main/Documentation/Schematics-modules.pdf) (PDF)
 - [Schematic - board with MCP23017 chips](https://github.com/lucadentella/LnControlPanel/tree/main/Documentation/Schematics-chips.pdf) (PDF)
 - [Part list](https://github.com/lucadentella/LnControlPanel/tree/main/Documentation/PARTLIST.md)
 - [How to configure the channels](https://github.com/lucadentella/LnControlPanel/tree/main/Documentation/CONFIGURATION.md)
 - [How to connect buttons/LEDs](https://github.com/lucadentella/LnControlPanel/tree/main/Documentation/CONNECTIONS.md) 

## Requirements :heavy_check_mark:
 - [mrrwa Loconet Library](https://github.com/mrrwa/LocoNet)
 - [Adafruit MCP23017 Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)

*The libraries above can be installed via the* [Library Manager](https://www.arduino.cc/en/guide/libraries)
