# Connections

LnControlPanel has **32 independent** channels. Each channel can be connected to:
 - a **BUTTON** (if the channel is in INPUT mode)
 - one or two **LEDs** (if the channel is in OUTPUT mode)

See [Configuration](https://github.com/lucadentella/LnControlPanel/blob/main/CONFIGURATION.md) to learn how to configure channel properties. 
 
 ## INPUT - Button
In INPUT mode, a channel can **control** the status of a sensor or the position of a turnout.

Connect a button between **SIGNAL** and **GND**:
![](https://github.com/lucadentella/LnControlPanel/blob/main/images/con-btn.png?raw=true)
When the button is pressed, the status of the sensor or the position of the turnout is **switched**.

If the channel is configured as **MSENSOR** (*Momentary Sensor*), the sensor is set **ACTIVE** when the button is pressed and **INACTIVE** when released.

## OUTPUT - LEDs
In OUTPUT mode, a channel can **monitor** the status of a sensor or the position of a turnout.

If you connect the LED between **VCC** and **SIGNAL**, it will be ON if the sensor is **INACTIVE** or the turnout is **STRAIGHT**:
![](https://github.com/lucadentella/LnControlPanel/blob/main/images/con-ledvcc.png?raw=true)

If you connect the LED between **SIGNAL** and **GND**, it will be ON if the sensor is **ACTIVE** or the turnout is **DIVERGING**:
![](https://github.com/lucadentella/LnControlPanel/blob/main/images/con-ledgnd.png?raw=true)

If you connect **two LEDs** as follows, they will be **ON** based on the turnout position:
![](https://github.com/lucadentella/LnControlPanel/blob/main/images/con-twoleds.png?raw=true)
