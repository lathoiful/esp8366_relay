#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "IOT";
const char* password = "1234567890";
const char* serverName = "http://smkssyaum.my.id:8080/iotlampu/get_status.php?api=json";

const int relayPins[4] = {D1, D2, D3, D4};
const unsigned long updateInterval = 5000;
unsigned long lastUpdate = 0;

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
  } else {
    Serial.println("\nFailed to connect WiFi!");
  }

  client.setInsecure();
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate >= updateInterval) {
    lastUpdate = now;
    if (WiFi.status() != WL_CONNECTED) {
      reconnectWiFi();
    }
    fetchAndUpdate();
  }
}

void reconnectWiFi() {
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("\nReconnected!");
  else
    Serial.println("\nReconnect failed!");
}

void fetchAndUpdate() {
  HTTPClient http;
  http.begin(client, serverName);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      digitalWrite(relayPins[0], doc["lampu1"] == "ON" ? HIGH : LOW);
      digitalWrite(relayPins[1], doc["lampu2"] == "ON" ? HIGH : LOW);
      digitalWrite(relayPins[2], doc["lampu3"] == "ON" ? HIGH : LOW);
      digitalWrite(relayPins[3], doc["lampu4"] == "ON" ? HIGH : LOW);
    }
  } else {
    Serial.println(httpCode);
  }

  http.end();
}
