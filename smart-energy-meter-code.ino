#define BLYNK_TEMPLATE_ID "TMPL3HrwpUd8t"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "jEEJiDpKcYscQ-251u6Vo4ToWPcTdRK5"
#include <TimeLib.h>
#include <LiquidCrystal.h>
#include "EmonLib.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SD.h>

EnergyMonitor emon;
File myFile;
unsigned long lastmillis = millis();
unsigned long previousMillis = 0;
const long interval = 3600000; // 1 hour in milliseconds

#define vCalibration 83.3
#define currCalibration 0.50

BlynkTimer timer;

char auth[] = "jEEJiDpKcYscQ-251u6Vo4ToWPcTdRK5";
char ssid[] = "jaseem";
char pass[] = "passwordilla";

LiquidCrystal lcd(13, 12, 14, 27, 26, 25); // Set your LCD pins

float kWh = 0;
float value;
int led1=29;

void myTimerEvent() {
  emon.calcVI(20, 2000);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  yield();
  value=analogRead(25);

  // Display data on Serial Monitor
  Serial.print("Vrms: ");
  Serial.print(emon.Vrms, 2);
  Serial.print("V");
  Serial.print("\tIrms: ");
  Serial.print(emon.Irms, 4);
  Serial.print("A");
  Serial.print("\tPower: ");
  Serial.print(emon.apparentPower, 4);
  Serial.print("W");
  Serial.print("\tkWh: ");
  Serial.print(kWh, 5);
  Serial.println("kWh");

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.print(emon.Vrms, 2);
  lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("Irms:");
  lcd.print(emon.Irms, 4);
  lcd.print("A");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Power:");
  lcd.print(emon.apparentPower, 4);
  lcd.print("W");
  lcd.setCursor(0, 1);
  lcd.print("kWh:");
  lcd.print(kWh, 4);
  lcd.print("W");
  delay(2500);

  lastmillis = millis();

  // Update Blynk app with sensor data
  Blynk.virtualWrite(V0, emon.Vrms);
  Blynk.virtualWrite(V1, emon.Irms);
  Blynk.virtualWrite(V2, emon.apparentPower);
  Blynk.virtualWrite(V3, kWh);
  Blynk.virtualWrite(V4, value);
  Blynk.virtualWrite(V5, led1);

  // Update data to SD card every hour
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();

  

    // Create folder for the year
    String yearFolder = String(year());
    if (!SD.exists(yearFolder)) {
      SD.mkdir(yearFolder);
    }

    // Create folder for the month inside the year folder
    String monthFolder = yearFolder + "/" + String(month());
    if (!SD.exists(monthFolder)) {
      SD.mkdir(monthFolder);
    }

    // Create file for today's date inside the month folder
    String dayFileName = monthFolder + "/" + String(day()) + ".txt";
    myFile = SD.open(dayFileName, FILE_WRITE);
    if (myFile) {
     
      myFile.print("Voltage: ");
      myFile.println(emon.Vrms);
      myFile.print("Current: ");
      myFile.println(emon.Irms);
      myFile.print("Power: ");
      myFile.println(emon.apparentPower);
      myFile.print("kWh: ");
      myFile.println(kWh);
      myFile.close();
      Serial.println("Data updated in file.");
    } else {
      Serial.println("Error opening file for updating");
    }
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  lcd.begin(16, 2); // Initialize LCD with your configuration

  emon.voltage(35, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
  emon.current(34, currCalibration);    // Current: input pin, calibration.

  timer.setInterval(5000L, myTimerEvent);
  lcd.setCursor(3, 0);
  lcd.print("IoT Energy");
  lcd.setCursor(5, 1);
  lcd.print("Meter");
  delay(3000);
  lcd.clear();

  // Initialize the SD card
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed");
    return;
  }

  // Open the file for writing initially (optional)
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("Initial data.");
    myFile.close();
    Serial.println("Data written to file.");
  } else {
    Serial.println("Error opening file for writing");
  }
}

void loop() {
  Blynk.run();
  timer.run();
}