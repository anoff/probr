#include <EEPROM.h>

String serial_in = "";

#define ROOM_MAX_LENGTH 16
#define DEBUG_SERIAL_CONFIG true

void printHelp();
int EEPROMlocation(String attribute);
bool writeCharArrayToEEPROM(char *value, char address, char length);
bool readCharArrayFromEEPROM(char *outArray, char address, char length);

uint8_t id;
float height;
uint8_t floor;
char room[16];

void setup() {
  Serial.println("Starting setup");
  Serial.begin(115200);
  delay(100);
  Serial.println("Reading config from EEPROM..");
  id = EEPROM.read(EEPROMlocation("id"));
  floor = EEPROM.read(EEPROMlocation("floor"));
  height = EEPROM.read(EEPROMlocation("height"));
  height /= 10;
  readCharArrayFromEEPROM(room, EEPROMlocation("room"), 16);
  Serial.println("Configuration:");
  Serial.print("id=");
  Serial.print(id);
  Serial.print(", height=");
  Serial.print(height);
  Serial.print(", floor=");
  Serial.print(floor);
  Serial.print(", room=");
  Serial.print(room);
}

void loop() {
  if (Serial.available() > 0) {
    serial_in = Serial.readString();
    parseSerial(serial_in);
  }  
}

void printHelp() {
  Serial.println("Probe configuration");
  Serial.println("Usage: <command> <attribute> <value>");
  Serial.println("  Valid values:");
  Serial.println("  <command>: set, get");
  Serial.println("  <attribute>: id, height, floor, room");
  Serial.println("  <value>: id(0-255), height(0.0-5.0),floor(0-5), room(15 chars)");
}

int EEPROMlocation(String attribute) {
  if (attribute == "id") {
    return 0; // size 1 byte
  } else if (attribute == "height") {
    return 1; // size 1 byte
  } else if (attribute == "floor") {
    return 2; // size 1 byte
  } else if (attribute == "room") {
    return 8; // size 16 byte (15 chars + \0)
  } else {
    return -1;
  }
}

bool writeCharArrayToEEPROM(char *value, char address, char length) {
  uint8_t i = 0;
  char t;
  while (i < ROOM_MAX_LENGTH) {
    t = value[i];
    EEPROM.update(address + i, t);
    if (t == '\0') {
      break;
    }
    i++;
  }
  EEPROM.update(address + ROOM_MAX_LENGTH, '\0'); // make sure that last character always terminates char array
  return true;
}

bool readCharArrayFromEEPROM(char *outArray, char address, char length) {
  char t;
  uint8_t i = 0;
  while (i < length) {
    t = EEPROM.read(address + i);
    outArray[i] = t;
    if (t == '\0') {
      break;
    }
    i++;
  }
  return true;
}

bool parseSerial(String serial_in) {
  String command = "";
  String attribute = "";
  String value = "";
  command = serial_in.substring(0, 3);
  int attribute_ix = serial_in.indexOf(' ', 4);
  if (attribute_ix == -1) { // no value following attribute
    attribute = serial_in.substring(4, serial_in.length()-2);
  } else {
    attribute = serial_in.substring(4, attribute_ix);
    value = serial_in.substring(attribute_ix + 1, serial_in.length()-2);
  }
  if (DEBUG_SERIAL_CONFIG) {
    Serial.print("DEBUG: Parsed message: ");
    Serial.print(command);
    Serial.print(" ");
    Serial.print(attribute);
    Serial.print("=");
    Serial.println(value);
  }
  if (command == "help") {
    printHelp();
    return true;
  }
  if (attribute.length() < 1 || (command == "set" && value.length() < 1)) {
    Serial.println("ERROR: attribute/value not defined.");
    Serial.print("DEBUG: Received serial message: ");
    Serial.println(serial_in);
    Serial.println("");
    printHelp();
    return false;
  }
  if (command == "get" || command == "set") {
    uint8_t EEPROM_addr = EEPROMlocation(attribute);
    if (EEPROM_addr == -1) {
      Serial.print("ERROR: Cannot find EEPROM address to access for attribute: ");
      Serial.println(attribute);
      return false;
    }
    if (command == "get") {
      DEBUG_SERIAL_CONFIG && Serial.print("read from PROM: ");
      if (attribute == "id" || attribute == "height" || attribute == "floor") {
        uint8_t v = EEPROM.read(EEPROM_addr);
        if (attribute == "height") {
          float height = v;
          height /= 10;
          DEBUG_SERIAL_CONFIG && Serial.println(height);
        } else {
          DEBUG_SERIAL_CONFIG && Serial.println(v);
        }
      } else if (attribute == "room") {
        char room[16];
        readCharArrayFromEEPROM(room, EEPROM_addr, ROOM_MAX_LENGTH);
        DEBUG_SERIAL_CONFIG && Serial.println(room);
      } else {
        Serial.print("ERROR: Unknown attribute: ");
        Serial.println(attribute);
        return false;
      }
    } else if (command == "set") {
      DEBUG_SERIAL_CONFIG && Serial.print("setting value: ");
      if (attribute == "id" || attribute == "height" || attribute == "floor") {
        uint8_t v = value.toInt();
        if (attribute == "height") {
          float height = value.toFloat();
          height *= 10;
          v = (uint8_t)height;
        }
        DEBUG_SERIAL_CONFIG && Serial.println(v);
        EEPROM.update(EEPROM_addr, v);
      } else if (attribute == "room") {
        char room[ROOM_MAX_LENGTH];
        value.toCharArray(room, ROOM_MAX_LENGTH);
        writeCharArrayToEEPROM(room, EEPROM_addr, ROOM_MAX_LENGTH);
        DEBUG_SERIAL_CONFIG && Serial.println(room);
      } else {
        Serial.print("ERROR: Unknown attribute: ");
        Serial.println(attribute);
        return false;
      }
    }
  } else {
    Serial.print("ERROR: Unexpected command: ");
    Serial.println(command);
    return false;
  }
  return true;
}