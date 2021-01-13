#include <EEPROM.h>

String serial_in = "";
String command;
String attribute;
String value;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup");
  delay(100);
}

void loop() {
  if (Serial.available() > 0) {
    command = "";
    attribute = "";
    value = "";
    serial_in = Serial.readString();
    command = serial_in.substring(0, 3);
    int attribute_ix = serial_in.indexOf(' ', 4);
    Serial.print(attribute_ix);
    Serial.print(", ");
    Serial.println(serial_in.length());
    if (attribute_ix == -1) { // no value following attribute
      attribute = serial_in.substring(4, serial_in.length()-2);
    } else {
      attribute = serial_in.substring(4, attribute_ix);
      value = serial_in.substring(attribute_ix + 1, serial_in.length()-2);
    }
    if (attribute.length() < 1 || (attribute == "set" && value.length() < 1)) {
      Serial.println("ERROR: attribute/value not defined.");
      Serial.print("DEBUG: Received serial message: ");
      Serial.println(serial_in);
      Serial.println("");
      printHelp();
      return;
    }
    if (command == "get" || command == "set") {
      uint8_t EEPROM_addr = EEPROMlocation(attribute);
      if (EEPROM_addr == -1) {
        Serial.print("ERROR: Cannot find EEPROM address to access for attribute: ");
        Serial.println(attribute);
        return;
      }
      if (command == "get") {
        uint8_t v = EEPROM.read(0);
        Serial.print("read from PROM: ");
        Serial.println(v);
      } else if (command == "set") {
        uint8_t v = value.toInt();
        Serial.print("setting value: ");
        Serial.println(v);
        EEPROM.update(0, v);
      }
    } else {
      Serial.print("ERROR: Unexpected command: ");
      Serial.println(command);
      return;
    }
    Serial.print("attribute=value: ");
    Serial.print(attribute);
    Serial.print("=");
    Serial.println(value);
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