# Flu Risk Sensor Module

This module contains the firmware for an microcontroller-based flu risk detection system. It runs a web server that displays environmental sensor data and allows users to submit room parameters to predict flu transmission risk.

## 📡 What It Does

- Starts a Wi-Fi Access Point (`RoomSensorAP`)
- Reads:
  - CO₂ levels via MQ135 sensor
  - Temperature and humidity via DHT11 sensor
- Serves a mobile-friendly web interface at the AP's IP address
- Accepts user input: number of people and room size
- Uses a local decision tree (`riskClassifier.h`) to predict flu risk

## 🧠 Prediction Model

Inputs:
- Temperature (°C)
- Humidity (%)
- CO₂ level (ppm)
- People count
- Room size (m²)

Output:
- Flu risk classification: **Low** or **High**

## 🔧 Files

- `FluRiskSensor.ino`: Main firmware for your microcontroller.
- `riskClassifier.h`: Decision tree logic for flu risk prediction

## 📲 How to Use

1. Upload the `.ino` sketch to your microcontroller.
2. Connect to the `RoomSensorAP` network (default password: `12345678`).
3. Open a browser and go to the IP shown in Serial Monitor (e.g., `192.168.4.1`).
4. View sensor data and submit room details for risk prediction.

---

⚠️ Make sure to calibrate the MQ135 in clean air on first run!
⚠️ Important! This code runs better on ESP32, Raspberry Pi Pico W/2W devices. You may need to change the code for other microcontrollers.
