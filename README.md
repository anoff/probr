# probr 🏠🌡💦📊

> Playing with IoT sensors to learn about the climate in individual rooms and impact of weather

## Architecture

The system consists of the following components:
* Components
  * Microcontroller: placed in each room, collects local measurement and sends it to database
  * Raspberry Pi: hosting database and dashboard services
* Services
  * [InfluxDB](https://www.influxdata.com/products/influxdb/): timeseries database to keep data from sensors and weather report
  * [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/): Ingest plugin for InfluxDB to collect weather data
  * [Grafana](https://grafana.com/): Dashboard for visualizing data
  * [traefik](https://traefik.io/): Get SSL certificates for grafana domain and route traffic for individual subdomains to correct docker services

![architecture of used stack](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.github.com/anoff/probr/master/docs/system.puml)

## Structure

* [**wifi_probe**](./nodes): code for microcontrollers
* [**services**](./services): configs for individual services
  * influxdb/init/: scripts to initialize influxdb databases & users

## Setup

### Database, Dashboard & Co

For setup of all used **services** see the `docker-compose` configuration at [anoff/docker-compose-influxdb-grafana](https://github.com/anoff/docker-compose-influxdb-grafana).
Required configuration is stored in the services folder.