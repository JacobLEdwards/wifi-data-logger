#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT_U.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11

const int vReadPin = A0;
int sensorValue = 0;

DHT_Unified dht(DHTPIN, DHTTYPE);

const char* ssid = "--";
const char* password = "--";

void setup() {
 
  Serial.begin(115200);                            //Serial connection
  WiFi.begin(ssid, password);   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }

  // Initialise Sensor
  Serial.println("Initialising Sensor.");
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delay(2000);
}
 
void loop() {
 // Check WiFi
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    // Setup JSON payload.
    StaticJsonDocument<100> testDocument;


    // Get Data.
    // Temp.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      testDocument["Temp"] = "ERROR";
    }
    else {
      testDocument["Temp"] = event.temperature;
    }

    // Humidity
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      testDocument["Humi"] = "ERROR";
    }
    else {
      testDocument["Humi"] = event.relative_humidity;
    }

    // Battery Voltage.
    sensorValue = analogRead(vReadPin);
    sensorValue = map(sensorValue, 200, 400, 0, 100);
    testDocument["Batt"] = sensorValue;
    
    // Serialize JSON.
    char buffer[100];
    serializeJson(testDocument, buffer);
    Serial.println(buffer);

    // Setup Request
    HTTPClient http;
 
    http.begin("192.168.1.140", 8080);
    http.addHeader("Content-Type", "application/json");

    // Send Request
    int httpCode = http.POST(buffer);
    String payload = http.getString();
 
    Serial.println(httpCode);
    Serial.println(payload);
 
    http.end();
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  ESP.deepSleep(10e6);  //Send a request every 1 minute
 
}
