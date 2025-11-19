#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// API Key
String apiKey = "bc579c10e1e48fa276fe5634722bfcfc";

// Cities available (User can select)
String cities[] = {"Hyderabad", "Mumbai", "Delhi", "Chennai", "Bangalore"};
int cityIndex = 0; // Change this value 0-4 to pick city

// Firebase RTDB
String firebaseURL = "https://iot-weather-monitoring-s-918d2-default-rtdb.firebaseio.com/weather_data.json?auth=CFNF7F3MrmATXQAGK3fHDJNvl78o8crRHM1eGrma";

void setup() {
  Serial.begin(115200);

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");

  Serial.println("Available Cities:");
  for (int i = 0; i < 5; i++) {
    Serial.println(String(i) + " -> " + cities[i]);
  }

  Serial.println("Currently Selected City: " + cities[cityIndex]);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String city = cities[cityIndex];

    // Weather API URL
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city +
                 "&appid=" + apiKey + "&units=metric";

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Weather API Data: ");
      Serial.println(payload);

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      float temperature = doc["main"]["temp"];
      float humidity = doc["main"]["humidity"];
      float pressure = doc["main"]["pressure"];
      float windSpeed = doc["wind"]["speed"];

      HTTPClient firebase;
      firebase.begin(firebaseURL);

      DynamicJsonDocument sendData(256);
      sendData["city"] = city;
      sendData["temperature"] = temperature;
      sendData["humidity"] = humidity;
      sendData["pressure"] = pressure;
      sendData["windSpeed"] = windSpeed;
      sendData["timestamp"] = millis() / 1000;

      String jsonOut;
      serializeJson(sendData, jsonOut);

      firebase.PATCH(jsonOut);
      Serial.print("Uploaded to Firebase: ");
      Serial.println(jsonOut);

      firebase.end();
    }
    http.end();
  }

  delay(10000);
}
