void printUsage() {

  Serial.println(F("Available commands:"));
  Serial.println(F("INPUT <ioPin>: set the ioPin as INPUT")); 
  Serial.println(F("OUTPUT <ioPin>: set the ioPin as OUTPUT"));
  Serial.println(F("TURNOUT <ioPin>: set the ioPin as a TURNOUT")); 
  Serial.println(F("SENSOR <ioPin>: set the ioPin as a SENSOR")); 
  Serial.println(F("MSENSOR <ioPin>: set the ioPin as a MOMENTARY SENSOR"));    
  Serial.println(F("ADDRESS <ioPin> <dccAddress>: set the dccAddress for the ioPin"));
  Serial.println(F("STATUS: print the current status"));
  Serial.println(F("RESET: reset the configuration to factory"));
  Serial.println(F("HELP: print this message"));
  Serial.println();
}

void parseCmdLine() {

  // empty line, print usage
  if(cmdlinepos == 0) {
    printUsage();
    return;
  }

  // get the command 
  char *command = strtok(cmdline, " ");

  // INPUT
  if(strcmp(command, "INPUT") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      pinInfo[ioPin - 1].isInput = true;
      setPinDirection(ioPin - 1, true);
      saveConfigToEEPROM();
    }    
  }

  // OUTPUT
  else if(strcmp(command, "OUTPUT") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      pinInfo[ioPin - 1].isInput = false;
      setPinDirection(ioPin - 1, false);
      saveConfigToEEPROM();
    }    
  }

  // TURNOUT
  else if(strcmp(command, "TURNOUT") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      pinInfo[ioPin - 1].deviceType = DEV_TURNOUT;
      saveConfigToEEPROM();
    }    
  }

  // SENSOR
  else if(strcmp(command, "SENSOR") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      pinInfo[ioPin - 1].deviceType = DEV_SENSOR;
      saveConfigToEEPROM();
    }    
  }

  // MSENSOR
  else if(strcmp(command, "MSENSOR") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      pinInfo[ioPin - 1].deviceType = DEV_MSENSOR;
      saveConfigToEEPROM();
    }    
  }

  // ADDRESS
  else if(strcmp(command, "ADDRESS") == 0) {

    int ioPin = atoi(strtok(NULL, " "));
    if(ioPin < 1 || ioPin > IOPINS) {
      Serial.print("Invalid ioPin: "); 
      Serial.println(ioPin);
      Serial.println();
    } else {
      int address = atoi(strtok(NULL, " "));
      if(address < 1 || address > 2048) {
        Serial.print("Invalid address: "); 
        Serial.println(address);
        Serial.println();        
      } else {
        pinInfo[ioPin - 1].dccAddress = address;
        saveConfigToEEPROM();
      }
    }    
  }

  // STATUS
  else if(strcmp(command, "STATUS") == 0) printConfiguration();

  // RESET
  else if(strcmp(command, "RESET") == 0) {
    
    resetConfiguration();
    saveConfigToEEPROM();
  }

  // HELP
  else if(strcmp(command, "HELP") == 0) printUsage();

  // Unknown
  else {
    Serial.print("Unknown command: '");
    Serial.print(command);
    Serial.println("'");
  }
  
  cmdlinepos = 0;
}
