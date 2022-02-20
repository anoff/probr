## esphome mqtt style

probr/2:study:0.3/tasmota_B00960-2400/tele/SENSOR {"Time":"2021-07-24T23:54:07+09:00","BME280":{"Temperature":28.2,"Humidity":47.0,"DewPoint":15.8,"Pressure":1007.6},"PressureUnit":"hPa","TempUnit":"C"}
probr/2:study:0.3/tasmota_B00960-2400/tele/STATE {"Time":"2021-07-24T23:51:07+09:00","Uptime":"149T00:49:42","UptimeSec":12876582,"Heap":22,"SleepMode":"Dynamic","Sleep":50,"LoadAvg":19,"MqttCount":43,"Wifi":{"AP":1,"SSId":"arawa","BSSId":"18:56:44:5E:12:F0","Channel":11,"RSSI":98,"Signal":-51,"LinkCount":8,"Downtime":"0T00:03:34"}}

homeassistant/sensor/attic_high/temperature_attic_high/config {"unit_of_measurement":"°C","name":"Temperature Attic High","state_topic":"attic_high/sensor/temperature_attic_high/state","availability_topic":"attic_high/status","unique_id":"ESPsensortemperature_attic_high","device":{"identifiers":"8caab51b354b","name":"attic_high","sw_version":"esphome v1.19.4 Jul 24 2021, 23:45:43","model":"PLATFORMIO_D1_MINI","manufacturer":"espressif"}}
attic_high/sensor/temperature_attic_high/state 30.5
homeassistant/sensor/attic_high/humidity_attic_high/config {"unit_of_measurement":"%","name":"Humidity Attic High","state_topic":"attic_high/sensor/humidity_attic_high/state","availability_topic":"attic_high/status","unique_id":"ESPsensorhumidity_attic_high","device":{"identifiers":"8caab51b354b","name":"attic_high","sw_version":"esphome v1.19.4 Jul 24 2021, 23:45:43","model":"PLATFORMIO_D1_MINI","manufacturer":"espressif"}}
attic_high/sensor/humidity_attic_high/state 46

attic_high/debug [D][dht:048]: Got Temperature=30.5°C Humidity=45.6%
attic_high/debug [D][sensor:117]: 'Temperature Attic High': Sending state 30.50000 °C with 1 decimals of accuracy
attic_high/sensor/temperature_attic_high/state 30.5
attic_high/debug [D][sensor:117]: 'Humidity Attic High': Sending state 45.60000 % with 0 decimals of accuracy
attic_high/sensor/humidity_attic_high/state 46


homeassistant/sensor/attic_low/temperature_aht10_attic_low/config {"unit_of_measurement":"°C","name":"Temperature (AHT10) Attic Low","state_topic":"attic_low/sensor/temperature_aht10_attic_low/state","availability_topic":"attic_low/status","unique_id":"ESPsensortemperature_aht10_attic_low","device":{"identifiers":"e8db849b7051","name":"attic_low","sw_version":"esphome v1.19.4 Jul 24 2021, 23:35:49","model":"PLATFORMIO_D1_MINI","manufacturer":"espressif"}}
homeassistant/sensor/attic_low/humidity_aht10_attic_low/config {"unit_of_measurement":"%","name":"Humidity (AHT10) Attic Low","state_topic":"attic_low/sensor/humidity_aht10_attic_low/state","availability_topic":"attic_low/status","unique_id":"ESPsensorhumidity_aht10_attic_low","device":{"identifiers":"e8db849b7051","name":"attic_low","sw_version":"esphome v1.19.4 Jul 24 2021, 23:35:49","model":"PLATFORMIO_D1_MINI","manufacturer":"espressif"}}
attic_low/debug [C][mqtt.sensor:028]:   State Topic: 'attic_low/sensor/humidity_aht10_attic_low/state'
attic_low/status online

probr/1:childroom:2/childroom/esphome/SENSOR [D][mhz19:057]: MHZ19 Received CO₂=771ppm Temperature=27°C Status=0x00
probr/1:childroom:2/childroom/esphome/SENSOR [D][sensor:117]: 'Miko CO2 Value': Sending state 771.00000 ppm with 0 decimals of accuracy
childroom/sensor/miko_co2_value/state 771
probr/1:childroom:2/childroom/esphome/SENSOR [D][sensor:117]: 'Miko Temperature (MH-Z19)': Sending state 27.00000 °C with 0 decimals of accuracy
childroom/sensor/miko_temperature_mh-z19/state 27
probr/1:childroom:2/childroom/esphome/SENSOR [D][aht10:074]: ATH10 Unrealistic humidity (0x0), retrying...
probr/1:childroom:2/childroom/esphome/SENSOR [D][aht10:067]: AHT10 is busy, waiting...
probr/1:childroom:2/childroom/esphome/SENSOR [D][sensor:117]: 'Miko Temperature': Sending state 25.81978 °C with 2 decimals of accuracy
childroom/sensor/miko_temperature/state 25.82
probr/1:childroom:2/childroom/esphome/SENSOR [D][sensor:117]: 'Miko Humidity': Sending state 67.30203 % with 2 decimals of accuracy
childroom/sensor/miko_humidity/state 67.30

## sensor calibration

### 2021-12-08

real -> sensor

office
10.4;16
13;19
16;20
17;23
19;27
20;25
22;29
44%;34%
45%;34.4%
48%;34%
48%;35.4%
48%;39.2%
51%;38.2%
60%;42.3%

living_ac
11.5;14
11.8;17
12.9;17
13.8;18
15.4;19
17;19
18;24
50%;40.1%
52%;35.9%
52%;45.4%
55%;42.8%
55%;43.9%

living_window
11;16
19;25
45%;35.5%

dining_ac
11;14
16;20
19;23
22;25
51%;35.8%

bedroom
10;11
10.8;12
11;11
12.5;14
12.5;14
14;16
15;16
19.1;21
8.9;10
9.0;8
38%;39.8%
40%;35.4%
43%;41.2%
44%;42.9%
45%;42.9%
47%;45%
49%;46.4%
58%;56.3%


miko
10.9;15
14;21
22;25
44%;32.5%

guestroom
9;12
11.5;15
15;18
46%;39.8%
55%;41.3%