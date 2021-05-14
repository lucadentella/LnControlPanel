#include <LocoNet.h>
#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_MCP23017.h"

// LnControlPanel 1.2
// Momentary sensors

// Definitions
#define VERSION       "1.2"
#define IOPINS        32
#define CONFIGVALID   111
#define CMDLINESIZE   100
#define DEV_TURNOUT   0
#define DEV_SENSOR    1
#define DEV_MSENSOR   2

// Pins configuration
typedef struct {
  int dccAddress;
  bool isInput;
  int deviceType;
} PinInfo;

// Global variables
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
lnMsg *LnPacket;
PinInfo pinInfo[IOPINS];
bool isPinStraight[IOPINS];
bool wasPinDown[IOPINS];
char cmdline[CMDLINESIZE];
int cmdlinepos = 0;

void setup() {
  
  Serial.begin(115200);
  Serial.print("LnControlPanel v");
  Serial.println(VERSION);
  Serial.println();

  // check if the configuration in the EEPROM is valid
  if(EEPROM.read(EEPROM.length() - 1) == CONFIGVALID) readConfigFromEEPROM();
  else {
    Serial.println(F("Configuration in EEPROM is invalid"));
    resetConfiguration();
    saveConfigToEEPROM();
    EEPROM.update(EEPROM.length() - 1, CONFIGVALID);
  }

  // start with direction = straight for all the pins and all the buttons UP
  for(int i = 0; i < IOPINS; i++) {
    isPinStraight[i] = true;
    wasPinDown[i] = false;
  }

  LocoNet.init();
  Serial.println(F("LocoNet init complete"));

  mcp1.begin();
  mcp2.begin(1);
  Serial.println(F("MCP23017 library init complete"));
 
  for(int i = 0; i < IOPINS; i++) setPinDirection(i, pinInfo[i].isInput);
  for(int i = 0; i < IOPINS; i++) if(!pinInfo[i].isInput) writePinOutput(i, LOW);
  Serial.println(F("Pins configuration complete"));
  Serial.println();
}

void loop() {

  LnPacket = LocoNet.receive();
  if(LnPacket) LocoNet.processSwitchSensorMessage(LnPacket);

  checkInputs();

  if (Serial.available() > 0) {
    
    int inByte = Serial.read();
    Serial.write(inByte);

    if(inByte == '\n') {
      cmdline[cmdlinepos] = '\0';
      parseCmdLine();
    }
    else {   
      cmdline[cmdlinepos] = inByte;
      cmdlinepos++;
      if(cmdlinepos == CMDLINESIZE) cmdlinepos = 0;
    }
  }
}

void notifySwitchRequest(uint16_t Address, uint8_t Output, uint8_t Direction) {

  Serial.print("Received switch command - ");
  Serial.print("address: "); Serial.print(Address);
  Serial.print(", direction: "); if(Direction > 0) Serial.println("DIVERGING"); else Serial.println("STRAIGHT");

  for(int i = 0; i < IOPINS; i++) {
    if(pinInfo[i].dccAddress == Address && pinInfo[i].deviceType == DEV_TURNOUT) {
      isPinStraight[i] = (Direction == 0);
      if(!pinInfo[i].isInput) writePinOutput(i, Direction);
    }
  }
}

void notifySensor(uint16_t Address, uint8_t State) {

  Serial.print("Received sensor state - ");
  Serial.print("address: "); Serial.print(Address);
  Serial.print(", state: "); if(State > 0) Serial.println("ON"); else Serial.println("OFF");

  for(int i = 0; i < IOPINS; i++) {
    if(pinInfo[i].dccAddress == Address && (pinInfo[i].deviceType == DEV_SENSOR || pinInfo[i].deviceType == DEV_MSENSOR)) {
      isPinStraight[i] = (State == 0);
      if(!pinInfo[i].isInput) writePinOutput(i, State);
    }
  }
}

// set pin direction
void setPinDirection(uint8_t p, bool isInput) {

  if(!isInput) {
    if(p < 16) mcp1.pinMode(p, OUTPUT);
    else mcp2.pinMode(p - 16, OUTPUT);
  } else {
    if(p < 16) {
      mcp1.pinMode(p, INPUT);
      mcp1.pullUp(p, HIGH);
    }
    else {
      mcp2.pinMode(p - 16, INPUT);
      mcp2.pullUp(p - 16, HIGH);
    }
  }
}

// write output
void writePinOutput(uint8_t p, uint8_t d) {

  if(p < 16) mcp1.digitalWrite(p, d);
  else mcp2.digitalWrite(p - 16, d);
}

// check inputs
void checkInputs() {

  for(int i = 0; i < IOPINS / 2; i++) {

    if(pinInfo[i].isInput) {

      uint8_t buttonStatus;
      if(i < 16) buttonStatus = mcp1.digitalRead(i);
      else buttonStatus = mcp2.digitalRead(i - 16);

      // button pressed
      if(buttonStatus == 0 && !wasPinDown[i]) {
        wasPinDown[i] = true;
        if(pinInfo[i].deviceType == DEV_TURNOUT) {
          LocoNet.requestSwitch(pinInfo[i].dccAddress, 0, isPinStraight[i]);
          Serial.print("Sent switch command - ");
          Serial.print("address: "); Serial.print(pinInfo[i].dccAddress);
          Serial.print(", direction: "); if(isPinStraight[i] > 0) Serial.println("DIVERGING"); else Serial.println("STRAIGHT"); 
        } else {
          LocoNet.reportSensor(pinInfo[i].dccAddress, isPinStraight[i]);
          Serial.print("Sent sensor state - ");
          Serial.print("address: "); Serial.print(pinInfo[i].dccAddress);
          Serial.print(", state: "); Serial.println("ON");           
        }       
      } else if (buttonStatus != 0) {
        
        if(wasPinDown[i] && pinInfo[i].deviceType == DEV_MSENSOR) {
          LocoNet.reportSensor(pinInfo[i].dccAddress, 0);
          Serial.print("Sent sensor state - ");
          Serial.print("address: "); Serial.print(pinInfo[i].dccAddress);
          Serial.print(", state: "); Serial.println("OFF");            
        }
        wasPinDown[i] = false;
      }
    }
  }
}
