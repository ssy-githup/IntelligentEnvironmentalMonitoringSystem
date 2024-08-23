#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int digitalPin = 17; // Rain sensor DO pin
const int ledPin = 13;
const int buzzerPin = 14; // Define buzzer pin

boolean Dstate = 0;

Adafruit_BMP085 bmp;

const char* ssid = "SSY";
const char* password = "123456789";
const char* serverName = "http://192.168.137.91:8080/data/data";

WebServer server(80); // Create WebServer object, listening on port 80

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(digitalPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output mode
  Serial.begin(9600);
  dht.begin();

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print ESP32 IP address

  // Set up Web server routes
  server.on("/", HTTP_GET, []() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude();
    float avgTemp = (temperature + bmp.readTemperature()) / 2.0;

    // Read the digital signal from the rain sensor
    boolean rainDetected = digitalRead(digitalPin) == LOW; // LOW indicates rain detected

    String html = "<html><body>";
    html += "<h1>Environmental Data</h1>";
    html += "<p>Humidity: " + String(humidity) + " %</p>";
    html += "<p>Temperature: " + String(temperature) + " C</p>";
    html += "<p>Pressure: " + String(pressure) + " Pa</p>";
    html += "<p>Altitude: " + String(altitude) + " m</p>";
    html += "<p>Average Temperature: " + String(avgTemp) + " C</p>";
    html += "<p>Rain Detected: " + String(rainDetected ? "Yes" : "No") + "</p>"; // Display if rain is detected
    html += "</body></html>";

    server.send(200, "text/html", html);
  });

  server.begin(); // Start the Web server
}

void loop() {
  Dstate = digitalRead(digitalPin);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();
  float avgTemp = (temperature + bmp.readTemperature()) / 2.0;

  // Read the digital signal from the rain sensor
  boolean rainDetected = digitalRead(digitalPin) == LOW; // LOW indicates rain detected

  // Add condition to activate the buzzer
  if (humidity > 28.00 && temperature > 28.0 && pressure > 100058.00 && altitude > 20 && avgTemp > 25.0) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    Serial.println("turn on the buzzerPin..........................");
  } else {
    digitalWrite(buzzerPin, LOW);  // Deactivate buzzer
    Serial.println("turn off the buzzerPin..........................");
  }

  if (Dstate == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "humidity=" + String(humidity) + "&temperature=" + String(temperature) +
                      "&pressure=" + String(pressure) + "&altitude=" + String(altitude) +
                      "&avgTemp=" + String(avgTemp) + "&rainDetected=" + String(rainDetected ? "Yes" : "No"); // Add rain sensor data

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  server.handleClient(); // Handle Web server requests

  delay(1000);
}
