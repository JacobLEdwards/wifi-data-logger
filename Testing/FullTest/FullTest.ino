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

 Serial.println("");
 Serial.println("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  // Initialise Sensor
  Serial.println("Initialising Sensor.");
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delay(2000);
  Serial.println("Startup Successful.");
}
 
void loop() {
 // Check WiFi
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    // Setup JSON payload.
    StaticJsonDocument<100> postDoc;

    // Get Data.
    // Temp.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      postDoc["Temp"] = "ERROR";
    }
    else {
      postDoc["Temp"] = event.temperature;
      Serial.println("Temperature Read Successful");
    }

    // Humidity
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      postDoc["Humi"] = "ERROR";
    }
    else {
      postDoc["Humi"] = event.relative_humidity;
      Serial.println("Humidity Read Successful");
    }

    // Battery Voltage.
    sensorValue = analogRead(vReadPin);
    sensorValue = map(sensorValue, 250, 500, 0, 100);
    postDoc["Batt"] = sensorValue;
    Serial.println("Battery Voltage Read Successful");
    // End Logging if battery voltage low.
    if (sensorValue < 10)
    {
      Serial.println("BATTERY LOW! Entering sleep mode.");
      ESP.deepSleep(0);
    }
    
    // Serialize JSON.
    char buffer[100];
    serializeJson(postDoc, buffer);
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
 
  ESP.deepSleep(3e8);  //Send a request every 5 mins.
 
}
