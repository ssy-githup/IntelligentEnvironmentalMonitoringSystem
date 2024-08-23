# Environmental Data Monitoring System

## Introduction

This project utilizes an ESP32 microcontroller combined with several sensors to collect, monitor, and alarm environmental data. Through a WiFi connection, data can be displayed in real-time via a web server and sent to a specified server using an HTTP POST request.

## Hardware Requirements

- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- BMP180 Pressure Sensor
- Rain Sensor
- Buzzer
- LED

## Software Requirements

- Arduino IDE
- Adafruit BMP085 Library
- DHT Library

## Pin Configuration

- DHT11 connected to GPIO 4
- BMP180 connected to I2C pins
- Rain sensor digital output pin connected to GPIO 17
- Buzzer connected to GPIO 14
- LED connected to GPIO 13

## Features

1. **Environmental Data Collection**:
    - Collect environmental data including temperature, humidity, pressure, altitude, and average temperature.
    - Detect the status of the rain sensor to determine if it is raining.

2. **Web Server**:
    - Display real-time environmental data through a web server, including temperature, humidity, pressure, altitude, average temperature, and rain detection.

3. **Alarm Function**:
    - The buzzer will be activated when the humidity exceeds 28%, the temperature exceeds 28°C, the pressure exceeds 100058 Pa, the altitude exceeds 20 m, and the average temperature exceeds 25°C.

4. **Data Upload**:
    - Upload collected data to the specified server via an HTTP POST request.

## Usage

1. **Hardware Connection**:
    - Connect all sensors and peripherals according to the pin configuration.

2. **Code Configuration**:
    - Open the code file in the Arduino IDE and modify the following parameters:
      ```cpp
      const char* ssid = "SSY";
      const char* password = "123456789";
      const char* serverName = "http://192.168.137.91:8080/data/data";
      ```
      Replace the WiFi SSID, password, and server URL with actual information.

3. **Compile and Upload**:
    - Compile the code and upload it to the ESP32 development board.

4. **Run and Monitor**:
    - Use the serial monitor to view log outputs.
    - Enter the IP address of the ESP32 in a web browser to view real-time environmental data.

## Notes

- Ensure that all sensors are connected correctly and that the DHT11 and BMP180 libraries are properly installed.
- If the buzzer keeps alarming, check whether the alarm conditions are met or adjust the thresholds in the code.

## References

- [Arduino Official Website](https://www.arduino.cc/)
- [Adafruit BMP085 Library Documentation](https://github.com/adafruit/Adafruit-BMP085-Library)
- [DHT Library Documentation](https://github.com/adafruit/DHT-sensor-library)
