
#include <WiFi.h>            // For ESP32 (for ESP8266, use: #include <ESP8266WiFi.h>)
#include <WebServer.h>       // For ESP32 (for ESP8266, use: #include <ESP8266WebServer.h>)
#include <MQUnifiedsensor.h>
#include <DHT.h>
#include "riskClassifier.h"  // Include the risk classifier model header

// ********** Sensor Definitions ********** //
// MQ135 definitions
#define placa "ESP Board"           // Name your board (used in the MQ sensor library)
#define Voltage_Resolution 5        // Voltage resolution of the board
#define MQ135_PIN 28                // Analog input connected to MQ135 (adjust if necessary)
#define type "MQ-135"               // Sensor type string
#define ADC_Bit_Resolution 10       // ADC resolution (for ESP boards, adjust if necessary)
#define RatioMQ135CleanAir 3.6      // RS/R0 ratio in clean air

// DHT11 definitions
#define DHTPIN 26                  // DHT11 sensor connected to pin 27
#define DHTTYPE DHT11               // Define sensor type as DHT11

// Instantiate sensors
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ135_PIN, type);
DHT dht(DHTPIN, DHTTYPE);

// Global sensor values (updated periodically)
float currentCO2 = 0;
float currentTemperature = 0;
float currentHumidity = 0;

// ********** WiFi and Server Definitions ********** //
const char* ssid = "RoomSensorAP";       // AP SSID
const char* password = "12345678";         // AP Password

WebServer server(80);                     // Create a web server on port 80

// Timing for sensor update (non-blocking)
unsigned long previousMillis = 0;
const long sensorInterval = 500;          // Update sensor readings every 500ms

// ********** Web Page Handlers ********** //

// Root page: display sensor values, the AP IP, and a form for input
// Root page: display sensor values, the AP IP, and a form for input
void handleRoot() {
  String ipAddress = WiFi.softAPIP().toString();
  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Flu Risk Sensor Data</title>";
  
  // Adding some basic styling for a more modern look
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f4f4f9; margin: 0; padding: 0; color: #333; }";
  html += "h1, h2 { color: #4CAF50; text-align: center; }";
  html += "p { font-size: 18px; text-align: center; }";
  html += "label { font-size: 18px; }";
  html += "input[type='number'] { padding: 8px; width: 50%; margin: 10px 0; border: 2px solid #4CAF50; border-radius: 4px; }";
  html += "input[type='submit'] { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer; }";
  html += "input[type='submit']:hover { background-color: #45a049; }";
  html += ".container { width: 80%; margin: auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 8px; }";
  html += ".sensor-data { display: flex; justify-content: space-around; margin-bottom: 20px; }";
  html += ".sensor-item { padding: 10px; background-color: #e3f2fd; border-radius: 8px; flex: 1; margin: 5px; text-align: center; }";
  html += ".sensor-item strong { display: block; font-size: 22px; margin-bottom: 8px; }";
  html += "footer { text-align: center; margin-top: 20px; font-size: 14px; color: #888; }";
  html += "</style>";

  // Body of the page
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Flu Risk Sensor Data</h1>";
  html += "<p><strong>Access Point IP:</strong> " + ipAddress + "</p>";

  // Displaying sensor data with a more stylish layout
  html += "<div class='sensor-data'>";
  html += "<div class='sensor-item'><strong>CO2 Level</strong>" + String(currentCO2) + " ppm</div>";
  html += "<div class='sensor-item'><strong>Temperature</strong>" + String(currentTemperature) + " &deg;C</div>";
  html += "<div class='sensor-item'><strong>Humidity</strong>" + String(currentHumidity) + " %</div>";
  html += "</div>";
  
  html += "<h2>Room Information</h2>";
  html += "<form method='get'>";
  html += "<label for='people'>Number of People:</label><br>";
  html += "<input type='number' id='people' name='people' required><br>";
  html += "<label for='room'>Room Size (sq. meters):</label><br>";
  html += "<input type='number' id='room' name='room' step='0.01' required><br>";
  html += "<div style='text-align:center; margin-top: 20px;'>";
  html += "<input type='submit' value='Submit' formaction='/submit'>";
  html += "<input type='submit' value='Predict Risk' formaction='/predict'>";
  html += "</div>";
  html += "</form>";

  html += "</div>";
  html += "<footer>Powered by Flu Risk Detection System | Stay Safe!</footer>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// Handle form submission: print sensor values along with user input to Serial
void handleSubmit() {
  String peopleStr = server.arg("people");
  String roomStr = server.arg("room");

  // Print sensor values and form values to Serial only when submit is pressed.
  Serial.println("----- Submission Received -----");
  Serial.print("CO2 Level: "); Serial.print(currentCO2); Serial.println(" ppm");
  Serial.print("Temperature: "); Serial.print(currentTemperature); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(currentHumidity); Serial.println(" %");
  Serial.print("Number of People: "); Serial.println(peopleStr);
  Serial.print("Room Size: "); Serial.println(roomStr);
  Serial.println("--------------------------------");

  String response = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Submission Received</title>";
  response += "<style>body { font-family: Arial, sans-serif; background-color: #f4f4f9; color: #333; text-align: center; }";
  response += "h1 { color: #4CAF50; } p { font-size: 18px; }</style></head><body>";
  response += "<h1>Submission Received</h1>";
  response += "<p>Number of People: " + peopleStr + "</p>";
  response += "<p>Room Size: " + roomStr + " sq. meters</p>";
  response += "<p><a href='/'>Return to main page</a></p>";
  response += "</body></html>";

  server.send(200, "text/html", response);
}

// New handler for flu risk prediction
void handlePredict() {
  String peopleStr = server.arg("people");
  String roomStr = server.arg("room");

  // Convert the input values to float
  float people = peopleStr.toFloat();
  float room = roomStr.toFloat();

  // Prepare the input vector for the prediction model:
  // Order: Temperature, Humidity, CO2, Number of People, Room Size
  float input[5] = { currentTemperature, currentHumidity, currentCO2, people, room };

  // Call the riskClassifier model to get prediction (0: Low, 1: Medium, 2: High)
  int prediction = riskClassifier.predict(input);

  String risk;
  if (prediction == 0) {
    risk = "Low";
  } else if (prediction == 1) {
    risk = "High";
  } else {
    risk = "Unknown";
  }

  // Build the HTML response for the prediction
  String response = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Flu Risk Prediction</title>";
  response += "<style>body { font-family: Arial, sans-serif; background-color: #f4f4f9; color: #333; text-align: center; }";
  response += "h1 { color: #4CAF50; } p { font-size: 18px; }</style></head><body>";
  response += "<h1>Flu Risk Prediction</h1>";
  response += "<p><strong>Predicted Flu Risk: </strong>" + risk + "</p>";
  response += "<p><a href='/'>Return to main page</a></p>";
  response += "</body></html>";

  server.send(200, "text/html", response);
}

// ********** Setup ********** //
void setup() {
  Serial.begin(115200);
  Serial.println("Starting sensor calibration and WiFi AP...");
  
  // Initialize DHT11 sensor
  dht.begin();
  
  // Configure MQ135 sensor model
  MQ135.setRegressionMethod(1);   // _PPM = a * ratio^b
  MQ135.init();
  
  // Calibrate MQ135 sensor in clean air
  Serial.print("Calibrating MQ135 please wait");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ135.update(); // Update sensor reading
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
    delay(100);  // Brief delay for calibration readings
  }
  MQ135.setR0(calcR0 / 10);
  Serial.println(" done!");
  
  if (isinf(calcR0)) {
    Serial.println("Warning: Connection issue, R0 is infinite. Please check your wiring and supply.");
    while (1);
  }
  if (calcR0 == 0) {
    Serial.println("Warning: Connection issue, R0 is zero. Please check your wiring and supply.");
    while (1);
  }
  
  // Start WiFi Access Point
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.on("/predict", handlePredict);   // New route for prediction
  
  server.begin();
  Serial.println("Web server started.");
  Serial.println("Access point is ready. Connect with your device and open the browser to see sensor data.");
}

// ********** Loop ********** //
void loop() {
  server.handleClient();  // Handle incoming client connections

  // Update sensor readings without printing to Serial continuously.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= sensorInterval) {
    previousMillis = currentMillis;
    
    // Update MQ135 reading for CO2 with offset
    MQ135.update();
    MQ135.setA(110.47);
    MQ135.setB(-2.862);
    currentCO2 = MQ135.readSensor() + 400;
    
    // Update DHT11 sensor readings
    currentTemperature = dht.readTemperature();
    currentHumidity = dht.readHumidity();
  }
}
