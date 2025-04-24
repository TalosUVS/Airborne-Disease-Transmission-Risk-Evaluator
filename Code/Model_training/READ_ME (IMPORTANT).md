# Flu Risk Prediction Model (Jupyter Notebook)

This folder contains the training notebook for the **flu risk classification model** used in the microcontroller-based risk detection system.

## 📓 File Overview

- `model.ipynb`: Trains a decision tree classifier that predicts the likelihood of flu transmission in an indoor space based on environmental and room factors.

## 📊 Inputs to the Model

- **Temperature** (°C)
- **Humidity** (%)
- **CO₂ Level** (ppm)
- **Number of People** in the room
- **Room Size** (m²)

## 🧠 Output

- Predicted **flu risk level**:
  - `0` → Low Risk
  - `1` → High Risk

## 🛠️ Model Training

The notebook uses:
- `pandas` for data handling
- `scikit-learn` for model training (`DecisionTreeClassifier`)
- `joblib` or manual export to convert the trained tree into a C-style structure for use on microcontrollers

## 💾 Export (EverywhereML Library)

After training, the decision tree is translated into a `.h` file (`riskClassifier.h`) for use directly in the microcontroller project.

## 🔁 Integration

This model is used in the ESP32 firmware to perform real-time flu risk prediction based on sensor inputs and user-provided room data.

---

📦 Part of the **Flu Risk Detection System** project.
