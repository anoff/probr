#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif
#include <DHT.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "secrets.h" // load connection credentials

// // Adafruit Feather Huzzah
#define PIN_DHT_READ 15 // temp + humidity sensor
#define PIN_DHT_POWER 13

// LoLin nodeMCU3
// #define PIN_DHT_READ 4 // D2, temp + humidity sensor
// #define PIN_DHT_POWER 13 // D7


#define DHT_TYPE DHT22
#define SLEEP_S 30 // how many seconds to sleep between readings
#define DEVICE_ID "office"
#define MAX_READING_RETRIES 3 // maximum number of retries when getting NaN values from sensor

// Synchronize time with NTP servers and set timezone
// Accurate time is necessary for certificate validaton and writing in batches
// For the fastest time sync find NTP servers in your area: https://www.pool.ntp.org/zone/
//configTzTime("JST-9", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client_cloud(INFLUXDB_CLOUD_URL, INFLUXDB_CLOUD_ORG, INFLUXDB_CLOUD_BUCKET, INFLUXDB_CLOUD_TOKEN, InfluxDbCloud2CACert);
InfluxDBClient client_soto; // for local db
// Initialize DHT sensor
DHT dht(PIN_DHT_READ, DHT_TYPE);

void setup() {
  pinMode(PIN_DHT_POWER, OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting setup");
  delay(100);
  digitalWrite(PIN_DHT_POWER, HIGH);
  wifiConnect(WIFI_SSID, WIFI_KEY);
  delay(2000); // wait for DHT to power up?
  // read sensor values
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature(false);
  int count = 0;
  while (isnan(humidity) || isnan(temp)) {
    Serial.println("Error while reading sensor values, retrying");
    delay(2000);
    humidity = dht.readHumidity();
    temp = dht.readTemperature(false);
    count++;
    // force ESP into deepsleep so heartbeat gets out in case of permanent sensor damage
    if (count > MAX_READING_RETRIES) {
      shutdown();
    }
  }
  logSensorStatus(temp, humidity);


  Point pointDevice("node");
  // Set tags
  pointDevice.addTag("device", DEVICE_ID);
  pointDevice.addTag("SSID", WiFi.SSID());
  // Add data fields
  pointDevice.addField("temperature", temp);
  pointDevice.addField("humidity", humidity);
  pointDevice.addField("uptime", millis());
  Serial.println(client_cloud.writePoint(pointDevice));
  Serial.println("written to InfluxDB Cloud");

  client_soto.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DATABASE, INFLUXDB_USER, INFLUXDB_PASSWORD);
  Serial.println(client_soto.writePoint(pointDevice));
  Serial.println("written to InfluxDB soto");


  shutdown();
}

void loop() {
}

void shutdown() {
  digitalWrite(PIN_DHT_POWER, LOW);
  ESP.deepSleep(SLEEP_S * 1000000 - millis()*1000); // offset by the duration the program run (converted from ms to µs)
}

void logSensorStatus(float temp, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("");
}

// try to connect to given SSID and key, loop until successful
void wifiConnect(const char* ssid, const char* key) {
  WiFi.begin(ssid, key);
  Serial.print("Waiting for WiFi connection..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(".");
  Serial.print("Successfully connected to ");
  Serial.println(WiFi.SSID());
}