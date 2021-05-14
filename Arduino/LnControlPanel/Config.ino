// restore the configuration from EEPROM
void readConfigFromEEPROM() {

  int currentAddress = 0;
  for(int i = 0; i < IOPINS; i++) {

    EEPROM.get(currentAddress, pinInfo[i]);
    currentAddress += sizeof(PinInfo);
  }

  Serial.println(F("Configuration read from EEPROM"));
}

// save the configuration to EEPROM
void saveConfigToEEPROM() {

  int currentAddress = 0;
  for(int i = 0; i < IOPINS; i++) {

    EEPROM.put(currentAddress, pinInfo[i]);
    currentAddress += sizeof(PinInfo);
  }

  Serial.println(F("Configuration saved to EEPROM"));
}

// reset the configuration to default values
void resetConfiguration() {

  for(int i = 0; i < IOPINS / 2; i++) {
    
    pinInfo[i].dccAddress = i + 1;
    pinInfo[IOPINS / 2 + i].dccAddress = i + 1;
    pinInfo[i].isInput = true;
    pinInfo[IOPINS / 2 + i].isInput = false;
    pinInfo[i].deviceType = DEV_TURNOUT;
    pinInfo[IOPINS / 2 + i].deviceType = DEV_TURNOUT;
  }
  Serial.println(F("Configuration reset to default values"));  
}

// print the current configuration
void printConfiguration() {

  Serial.println("Current configuration:");
  Serial.println();

  for(int i = 0; i < IOPINS; i++) {

    Serial.print("I/O "); Serial.print(i + 1); Serial.print("\t");
    Serial.print("Addr: "); Serial.print(pinInfo[i].dccAddress); Serial.print("  ");
    Serial.print("Type: "); pinInfo[i].isInput ? Serial.print("INPUT") : Serial.print("OUTPUT"); Serial.print("  ");
    Serial.print("Device: "); 
    if(pinInfo[i].deviceType == DEV_TURNOUT) Serial.print("TURNOUT");
    else if(pinInfo[i].deviceType == DEV_SENSOR) Serial.print("SENSOR"); 
    else Serial.print("MSENSOR");
    Serial.print("  ");
    if(pinInfo[i].deviceType == DEV_TURNOUT) { Serial.print("Direction: "); isPinStraight[i] ? Serial.print("STRAIGHT") : Serial.print("DIVERGING"); Serial.print("\n"); } 
    else { Serial.print("State: "); isPinStraight[i] ? Serial.print("OFF") : Serial.print("ON"); Serial.print("\n"); }
  }
}
