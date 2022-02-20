# Probr device configuration

## Watch out

- D4 needs to be high, otherwise built-in LED will turn/stay on

## Part List

> List of available devices

Microcontrollers

* many WeMos D1 mini
* 3x D1 mini pro
* 1x ESP32CAM Devkit

Sensors

* 2x MH-Z19C (CO2)
* 7x AHT10 (T, H)
* 6x KY-05 IR Transmitter (IR)
* 6x BME680 (T, H, P, VOC)
* 3xPIR Sensor (Motion)
* 5xKY-018 (Light Sensor)
* 2xRasPi Cam
* 2xTouch Sensor
* 2xBME280 (T, H, P)

> T(emperature), H(umidity), P(ressure), V(olative)O(rganic)C(ompound) (= bad gas)

## Combinations

AC Controller

* KY-05 IR Transmitter
* AHT10

CO2

* MH-Z19C
* BME680



## Rooms and mount locations

| Room | Mount location | Height | Sensors required |
|--|--|--|--|
| Office | behind monitor | 1.5m | T, H, L, VOC |
| Bedroom#1 | behind headrest | 1.0m | T, H, L, VOC |
| Bedroom#2 | on mattress level | 0.5m | T, H, L, VOC |
| Bedroom#3 | far corner | 1.5m | T, H, L |
| Living | behind TV | 0.5m | T, H, L, VOC |
| Kitchen | above vent | 2.0m | T, H, L |
| Entrance | near stairs | 2.0m | T, H, L |

| Office | AC | 2.0m | IR, T |
| Bedroom | AC | 2.0m | IR, T |
| Child Room | AC | 2.0m | IR, T |
| Kitchen | AC | 2.0m | IR, T |
| Living Room#1 | AC | 2.0m | IR, T |
| Living Room#2 | AC | 2.0m | IR, T |
| Guest Room | AC | 2.0m | IR, T |



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


> TH, VOC

WeMos D1
- AM2302: D3
I2C D6/D7
- CCS811: SCL:D1, SDA:D2, WAK:GND

### v1
D0/GPIO16:
D1/GPIO5: SCL # component:608
D2/GPIO4: SDA # component:640
D3/GPIO0: AM2302 data # component:1216
D4/GPIO2: AM2302 VCC # Relay1:1 # 224
D5/GPIO14:
D6/GPIO12:
D7/GPIO13:
D8/GPIO15: I2C GND # Relay2:0 # 225 / CCS811 connected does not startup D1
3V3: I2C VCC
GND: AM2302 GND

D8 boot failure if pulled high
D3, D4, TX boot failure if pulled low

Backlog Ssid1 arawa;Password1 lauterschmutzigegeraete;module 18;
Backlog gpio0 1216; gpio2 224; gpio4 640; gpio5 608; gpio15 225;
Backlog power1 1; power2 0;
# autoset power1 every minute
rule1 on Time#Minute do backlog power1 1;power2 0 endon
rule1 1
rule1 4

> BME280 only
used in bathroom


### v2
D0/GPIO16:
D1/GPIO5: SCL # component:608
D2/GPIO4: SDA # component:640
D3/GPIO0: AM2302 data # component:1216
D4/GPIO2: AM2302 VCC # Relay1:1 # 224 (KY-018 VCC)
D5/GPIO14:
D6/GPIO12:
D7/GPIO13: I2C GND # Relay2:0 # 225
D8/GPIO15:
3V3: I2C VCC
GND: AM2302 GND (KY-018 GND)
(A0: KY-018 / Analog Light)

Backlog gpio0 1216; gpio2 224; gpio4 640; gpio5 608; gpio13 225;

### devices

v1

879827: BME280 (hardwired+, naked), http://192.168.1.27/      -> bathroom 1.25
8787DE: DHT22, http://192.168.1.28/                           -> guestroom
1B354B: DHT22, http://192.168.1.29/                           -> living TV
B00960: BME280 (incase), http://192.168.1.25/                 -> study

v2
8767C1: DHT22 (blue), BME280 http://192.168.1.26/             -> kitchen/dining
303054: DHT22, CCS811 http://192.168.1.21/                    -> bedroom headrest 0.7
AE7A22: DHT22, KY-018, BME680 http://192.168.1.24/     -> office
922905: DHT22, CCS811, http://192.168.1.30/                -> childroom
E52ABB: BME680 http://192.168.1.19/                           -> entrance 1.0


#### Offset Compensation

Temp 2020-02-22
Defined environment temperature as 21 °C, offset are:
879827 (BME280): +1.0
8787DE (DHT22): -2.4
1B354B (DHT22): -2.1
922905 (DHT22): +0.2 -> -0.5 after some observations
B00960 (BME280): -1.1
8767C1 (DHT22 blue-1.0, **BME280**+0.1): +0.1
303054 (DHT22): -1.0
E52ABB (BME680): -3.6
AE7A22 (DHT22-2.8, BME680): -2.5

Humidity 2020-02-22
Defined environment humidity as 40%, offset are:
879827 (BME280): -1.4
8787DE (DHT22): +1.5
1B354B (DHT22): 0
922905 (DHT22): -4.1
B00960 (BME280): +1.8
8767C1 (DHT22 blue-5.5, **BME280**-0.2): -0.2
303054 (DHT22): -2.0
E52ABB (BME680): +4.8
AE7A22 (DHT22+0.8, BME680): +0.7


Temperature Adjustments

2021-03-27
922905 (DHT22): changed from -0.5 to -3.0 (Childroom measures 21.8, is: ~18)

2021-03-28
922905 (DHT22): changed from -3.0 to (measures 20.3, is: ~19)
303054 (DHT22): changed from -1.0 to (bedroom measures 22.1, is ~19)
AE7A22: changed from .. (office measures 23.4, is ~21)

2021-03-29
AE7A22: changed from .. (office measures 22.5, is ~21)
2021-03-30
AE7A22: changed from .. (office measures 23.2, is ~23)