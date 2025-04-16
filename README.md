# Airborne Disease Transmission Risk Evaluator

## Overview

The **Airborne Disease Transmission Risk Evaluator** is a portable and cost-effective device designed to assess the risk of airborne disease transmission in indoor spaces. The system analyzes sensor data using Tiny Machine Learning (TinyML) to predict the likelihood of disease transmission based on environmental factors. This device operates offline and performs real-time predictions using a microcontroller, making it practical for use in various indoor environments without the need for an internet connection.

The project was developed by the **Talos Student Research Team** at the **University of West Attica**.

## Features

- **Real-time Risk Evaluation**: The device assesses the transmission risk of airborne diseases, such as influenza and COVID-19, based on environmental data.
- **Offline Operation**: It functions without requiring an internet connection, providing practical usage even in remote locations.
- **Low-cost and Portable**: The design emphasizes affordability and portability, making it suitable for various indoor environments like offices, classrooms, and other public spaces.
- **TinyML Integration**: The device uses Tiny Machine Learning (TinyML) models for on-device prediction, ensuring efficient and fast data processing with minimal power consumption.
- **Data Visualization**: The system provides real-time data and risk predictions through a dedicated webpage hosted by the device's built-in access point.
- **User Interface**: A small screen (optional) can be attached to the device to display the predicted risk level, allowing all individuals in the room to view it.

## How it Works

1. **Sensors**: The device collects the following environmental data using integrated sensors:
   - **Temperature**
   - **Humidity**
   - **Carbon Dioxide (CO₂)** – to monitor oxygen recycling in the room.

2. **External Inputs**: The system receives additional inputs from a website:
   - **Number of people in the room**
   - **Room size** (approximately)

3. **Machine Learning Model**: These inputs are processed by a classification model, which predicts the risk of airborne disease transmission based on the data provided. The model categorizes the risk into three levels:
   - **Low**
   - **Medium**
   - **High**

4. **Data Access**: The device creates a local **Wi-Fi access point**, enabling users to connect and view the data and risk prediction on a web page. No internet connection is required; only Wi-Fi protocol is necessary.

5. **Display**: Optionally, a small screen can be added to display the risk prediction in the room for everyone to see.

## Installation

### Hardware:
- Microcontroller (e.g., Arduino, ESP32)
- Sensors for temperature, humidity, and CO₂
- Optional: Small display (e.g., LCD) for local visualization

### Software:
- The device runs a local web server that serves the data and predictions. The user interface can be accessed through a web browser.
- The TinyML models are pre-trained and uploaded to the microcontroller.

### Step-by-step guide:
1. Connect the sensors to the microcontroller according to the wiring diagram provided.
2. Upload the code to the microcontroller.
3. Once powered on, the device will create a Wi-Fi access point. Connect to it using your smartphone, tablet, or computer.
4. Open the browser and navigate to the local IP address provided by the device to view the real-time data and risk prediction.

## Contributions

We welcome contributions to improve the system, whether it's through improving the machine learning models, adding new sensors, or enhancing the user interface. Feel free to fork this project and submit pull requests.

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
