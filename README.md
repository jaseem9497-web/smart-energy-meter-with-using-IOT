# ⚡ IoT Energy Monitoring System (ESP32 + Blynk + SD Card + LCD)

This project measures voltage, current, power, and energy consumption (kWh) using an ESP32. Data is displayed on a 16×2 LCD, logged to an SD card every hour, and sent to the Blynk IoT app for remote monitoring.

## ✅ Features
- Real-time Vrms, Irms, power, and kWh measurement
- Live monitoring using Blynk
- Hourly SD card logging
- Automatic folder creation: /YEAR/MONTH/DAY.txt
- LCD display data rotation
- Based on EmonLib

## 🧰 Hardware Required
| Component | Quantity |
|---|:---:|
| ESP32 Development Board | 1 |
| SCT-013 Current Sensor | 1 |
| ZMPT101B Voltage Sensor | 1 |
| 16×2 LCD Display | 1 |
| SD Card Module + SD Card | 1 |
| Jumper Wires | — |

## 📌 Pin Connections

### LCD (16×2)
| LCD Pin | ESP32 GPIO |
|---|---|
| RS | 13 |
| EN | 12 |
| D4 | 14 |
| D5 | 27 |
| D6 | 26 |
| D7 | 25 |

### Sensors
| Sensor | ESP32 GPIO |
|---|---|
| Voltage Input | 35 |
| Current Input | 34 |

### SD Card Module
| SD Pin | ESP32 GPIO |
|---|---|
| CS | 10 |
| MOSI | 23 |
| MISO | 19 |
| SCK | 18 |
| VCC | 3.3V |
| GND | GND |

> If CS fails, try GPIO 5.

## 📦 Required Libraries
Install using Arduino Library Manager:
- Blynk
- EmonLib
- TimeLib
- LiquidCrystal
- SD
- WiFi
- WiFiClient
- BlynkSimpleEsp32

## 🔧 Setup Instructions
1. Open the `.ino` file in Arduino IDE
2. Select board: **ESP32 Dev Module**
3. Enter your Wi-Fi and Blynk credentials:
   ```cpp
   char auth[] = "YOUR_BLYNK_TOKEN";
   char ssid[] = "YOUR_WIFI_SSID";
   char pass[] = "YOUR_WIFI_PASSWORD";
