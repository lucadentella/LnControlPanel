# LnControlPanel
![](https://github.com/lucadentella/LnControlPanel/raw/main/images/board.jpg)

## Description

LnControlPanel is an opensource board to create Loconet control panels.

![GitHub](https://img.shields.io/github/license/lucadentella/LnControlPanel)

## Features

 - **32** independent channels:
   - each channel can be configured as **input** (to *control*) or as **output** (to *monitor)*
   - each channel can control/monitor a **turnout** or a **sensor**
   - each channel can have its own **address**
 - Two Loconet connectors for **cascade** connection
 - Based on **Arduino** framework and opensource libraries
 - Configurable using a simple **menu** via **serial** connection
 
## Documentation
 - [Part list](https://github.com/lucadentella/LnControlPanel/blob/main/PARTLIST.md)
 - [How to configure the channels](https://github.com/lucadentella/LnControlPanel/blob/main/CONFIGURATION.md)
 - [How to connect buttons/LEDs](https://github.com/lucadentella/LnControlPanel/blob/main/CONNECTIONS.md) 

## Requirements
 - [mrrwa Loconet Library](https://github.com/mrrwa/LocoNet)
 - [Adafruit MCP23017 Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)
