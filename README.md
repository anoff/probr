# probr 🏠🌡💦📊

> Playing with IoT sensors to learn about the climate in individual rooms and impact of weather

## Architecture

The system consists of the following components:

* Components
  * Microcontroller: placed in each room, collects local measurement and sends it to database
  * Raspberry Pi: hosting database and dashboard services
* Services
  * [InfluxDB](https://www.influxdata.com/products/influxdb/): timeseries database to keep data from sensors and weather report
  * [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/): Ingest plugin for InfluxDB to collect weather data and MQTT messages
  * [Mosquitto](https://mosquitto.org/): mqtt broker between microcontroller(sender) and telegraf(consumer)
  * [Grafana](https://grafana.com/): Dashboard for visualizing data
  * [traefik](https://traefik.io/): Get SSL certificates for grafana domain and route traffic for individual subdomains to correct docker services

![architecture of used stack](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.github.com/anoff/probr/master/docs/system.puml)

## Structure

* [**wifi_probe**](./nodes): code for microcontrollers
* [**services**](./services): configs for individual services
  * influxdb/init/: scripts to initialize influxdb databases & users

## Evolution

My setup has overgone several system changes, in chronological order:

- started with handwritten Arduino code (using InfluxDB lib) and InfluxCloud to measure temperature, humidity, TVOC
- migrated to locally hosted InfluxDB
- switched handwritten Arduino code to Tasmota firmware
- switched Tasmota firmware to ESPhome
- added Home Assistant Dashboard & Integrations
- added devices with IR remote control capability for Airconditioning

## Setup

### Database, Dashboard & Co

For setup of all used **services** see the `docker-compose` configuration at [anoff/docker-compose-influxdb-grafana](https://github.com/anoff/docker-compose-influxdb-grafana).
Required configuration is stored in the services folder.

### Debugging MQTT

MQTT is running via mosquitto, to see what's running over the broker:

```sh
docker run --rm -it eclipse-mosquitto sh
mosquitto_sub -h 192.168.1.210 -u USER -P PASSWORD -v -t 'probrv2/#'
```

mosquitto_sub -h 192.168.68.210 -u writer -P exert.ominous.THIEVE.snapback -v -t 'probrv2/#'
