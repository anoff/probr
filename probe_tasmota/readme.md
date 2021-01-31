# Running D1 probes with Tasmota

## 🔨 Installation

> 🚨 You might want to make sure to hardcode the port of your device instead of using the YOLO asterisk `*` version below

1. Install [esptool](https://github.com/espressif/esptool) (official espressif flashing tool) via `pip install esptool`
1. connect D1 chip via USB
1. test connection `esptool.py -p /dev/tty.usbserial* read_mac`, should print MAC address
1. grab latest release for [tasmota firmware](https://github.com/arendst/Tasmota/releases)
1. flash away using `esptool.py --port /dev/tty.usbserial* write_flash -fs 1MB -fm dout 0x0 tasmota.bin`
1. for ESP32 `esptool.py --chip esp32 --port /dev/tty.usbserial* --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dout --flash_freq 40m --flash_size detect 0x1000 bootloader_dout_40m.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 tasmota32-sensors.bin`

## Configuration

- `TelePeriod 30` set reporting interval to 30s
- MQTT server: 192.168.1.210, user: writer, password
- MQTT topic: `probr/floor:room_name:height/%hostname%/%prefix%(tele/cmnd/stat)/%ID%(SENSOR, STATE...)`
  - `FullTopic probr/1:office:0/%hostname%/%prefix%/`
- Module Configuration
  - AM2301: D4
  - ADC Light: D34
- `Timezone +9`
- `SetOption52 1`: enable timezone offset in timestamp

Backlog FullTopic probr/2:office:0/%hostname%/%prefix%/;Timezone +9;SetOption52 1;TelePeriod 30;Module 0;MqttHost 192.168.1.210;MqttUser writer;MqttPassword supersecret;MqttPort 1883;


8F71F9, bedroom
237F28 dining
3BADB7 living-AC
936C80 office

D4 - DHT22
D34 ADC Light
