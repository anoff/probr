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
    if (attribute_ix == -1) { // no value following attribute
      attribute = serial_in.substring(4, serial_in.length()-2);
    } else {
      attribute = serial_in.substring(4, attribute_ix);
      value = serial_in.substring(attribute_ix + 1, serial_in.length()-2);
    }
    Serial.print("DEBUG: Parsed message: ");
    Serial.print(command);
    Serial.print(" ");
    Serial.print(attribute);
    Serial.print("=");
    Serial.println(value);
    if (command == "help") {
      printHelp();
      return;
    }
    if (attribute.length() < 1 || (command == "set" && value.length() < 1)) {
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
        Serial.print("read from PROM: ");
        if (attribute == "id" || attribute == "height" || attribute == "floor") {
          uint8_t v = EEPROM.read(EEPROM_addr);
          if (attribute == "height") {
            float height = v;
            height /= 10;
            Serial.println(height);
          } else {
            Serial.println(v);
          }
        } else if (attribute == "room") {
          char room[16];
          char t;
          uint8_t i = 0;
          while (i < 17) {
            t = EEPROM.read(EEPROM_addr + i);
            room[i] = t;
            if (t == '\0') {
              break;
            }
            i++;
          }
          Serial.println(room);
        } else {
          Serial.print("ERROR: Unknown attribute: ");
          Serial.println(attribute);
          return;
        }
      } else if (command == "set") {
        Serial.print("setting value: ");
        if (attribute == "id" || attribute == "height" || attribute == "floor") {
          uint8_t v = value.toInt();
          if (attribute == "height") {
            float height = value.toFloat();
            height *= 10;
            v = (uint8_t)height;
          }
          Serial.println(v);
          EEPROM.update(EEPROM_addr, v);
        } else if (attribute == "room") {
          char room[16];
          char t;
          value.toCharArray(room, 16);
          uint8_t i = 0;
          while (i < 17) {
            t = room[i];
            EEPROM.update(EEPROM_addr + i, t);
            if (t == '\0') {
              break;
            }
            i++;
          }
          Serial.println(room);
        } else {
          Serial.print("ERROR: Unknown attribute: ");
          Serial.println(attribute);
          return;
        }
      }
    } else {
      Serial.print("ERROR: Unexpected command: ");
      Serial.println(command);
      return;
    }
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