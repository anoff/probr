# Probr device configuration

## Part List

> List of available devices

Microcontrollers
- 6x WeMos D1
- 4x ESP32
- 4x ESP8266

Sensors
- 6x AM2302 (T+H, = DHT22 breakout)
- 4x DHT22 (T+H)
- 10x KY-018 (photo resistor)
- 2x CCS811 (eCO2, VOC)
- 2x BME280 (T+H, P)
- 2x BME680 (T+H, P, VOC)

> T(emperature), H(umidity), P(ressure), V(olative)O(rganic)C(ompound) (= bad gas), L(ight)

## Rooms and mount locations

| Room | Mount location | Height | Sensors required |
|--|--|--|--|
| Office | behind monitor | 1.5m | T, H, L, VOC |
| Bedroom#1 | behind headrest | 1.5m | T, H, L, VOC |
| Bedroom#2 | on mattress level | 0.5m | T, H, L, VOC |
| Bedroom#3 | far corner | 1.5m | T, H, L |
| Living | behind TV | 0.5m | T, H, L, VOC |
| Kitchen | above vent | 2.0m | T, H, L |
| Entrance | near stairs | 2.0m | T, H, L |

## Board Configurations

### Debug Board

> Plug in everything via breadboard to test if sensors work

ESP32
- AM2302: D36
- KY-018: D35
- CCS811
- BME680
- BME280

ESP8266 (Huzzah Feather) D666505
- AM2302: 14 `gpio14 1216`
- KY-018: A0 / 17
- CCS811
- BME680
- BME280

### Probr1 (2x)

> TH, L, VOC

WeMos D1
- AM2302: D8
- KY-018: A0
- CCS811: SCL:D1, SDA:D2

### Probr2 (2x)

> TH, L, THP, VOC

WeMos D1
- AM2302: D8
- KY-018: A0
- BME680: SCL:D3, SDA:D4, CS:3V3, SDO:GND

### Probr3 (2x)

> TH, L, THP

WeMos D1
- AM2302
- KY-018
- BME280: SCL:D5, SDA:D6, !CS:3V3, SDO:GND

### Probr4 (2x)

