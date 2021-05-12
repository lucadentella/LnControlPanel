# Configuration :gear:

LnControlPanel has **32 independent** channels; each channel can be configured in:

 - **OUTPUT** mode (the channel *monitors* an element of the layout)
 - **INPUT** mode (the channel *controls* an element of the layout)

The layout elements associated to each channel can be:
 - **Turnouts**
 - **Sensors**
 - **Momentary** Sensors (*only in* INPUT *mode*)

Each layout element is identified by its **address**.

To summarize, each channel has the following parameters:
|Direction|Device|Address|
|--|--|--|
|Input/Output|Turnout/Sensor/MSensor|*element address*

See [Connections](https://github.com/lucadentella/LnControlPanel/blob/main/Documentation/CONNECTIONS.md) to learn how to connect buttons/LEDs to the channels. 

## Serial console :electric_plug:
It is possible to configure LnControlPanel using a **serial terminal** (for example *Arduino Serial Monitor*).

Using an USB->Serial adapter, connect your computer to the board. 
Make sure that TX and RX pins are **reversed**.

![](https://github.com/lucadentella/LnControlPanel/raw/main/images/config-serial.png)

Open the terminal (**115200** baud, **8N1**, **NL** as line terminator).

![](https://github.com/lucadentella/LnControlPanel/raw/main/images/config-serial2.png)

The available commands (case sensitive!) are:

 - **INPUT** *ioPin*: set the ioPin as INPUT
 - **OUTPUT** *ioPin*: set the ioPin as OUTPUT
 - **TURNOUT** *ioPin*: set the ioPin as a TURNOUT
 - **SENSOR** *ioPin*: set the ioPin as a SENSOR
 - **MSENSOR** *ioPin*: set the ioPin as a MOMENTARY SENSOR
 - **ADDRESS** *ioPin* *address*: set the address for the ioPin
 - **STATUS**: print the current status
 - **RESET**: reset the configuration to factory
 - **HELP**: print the usage

![](https://github.com/lucadentella/LnControlPanel/raw/main/images/config-serial3.png)
