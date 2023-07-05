#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SPI.h>
#include <SD.h>

#define SensorAnount 2

SoftwareSerial bluetooth(2, 3); // RX, TX
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int chipSelect = 10;           // chip select pin for the SD card reader

int bluetoothData;
bool nextData = false;
bool nextSize = false;
int i = 0;
int data[] = {0,0,0,0};
int displayData[] = {0,0,0,0};
String SensorName[] = {"Temp", "TDS", "pH", "level"};
String SensorUnit[] = {"C", "ppm", "", "cm"};
int SensorIndex = 0;
int SensorIndex2 = 1;
const unsigned long interval = 5000; // 5 seconds
unsigned long previousMillis = 0;

void displayNext() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(SensorName[SensorIndex] + ": ");
  lcd.setCursor(8,0);
  lcd.print(displayData[SensorIndex] + SensorUnit[SensorIndex]);
  lcd.setCursor(0,1);
  lcd.print(SensorName[SensorIndex2] + ": ");
  lcd.setCursor(8,1);
  lcd.print(displayData[SensorIndex2] + SensorUnit[SensorIndex2]);
  SensorIndex++;
  SensorIndex2++;
  if(SensorIndex > SensorAnount) SensorIndex = 0; 
  if(SensorIndex2 > SensorAnount) SensorIndex2 = 0; 
}

void saveData(int data[]) {
  // open log.txt and add data to it:
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println();
    for (int i = 0; i < SensorAnount; i++) {
      dataFile.print(data[i]);
      if(i < SensorAnount - 1) dataFile.print(",");
    }
    dataFile.close();
    // print to the serial port too:
    for (int i = 0; i < SensorAnount; i++) {
      Serial.print(data[i]);
      if(i < SensorAnount - 1) Serial.print(",");
    }
    Serial.println();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void receive() {
  /* if(!bluetooth.available()) return;
  bluetoothData = bluetooth.read();
  if(i >= SensorAnount) i = 0;
  data[i] = bluetoothData;
  i++; */
  // when none of the data is 0, save the data
  if(data[0] != 0 && data[1] != 0 && data[2] != 0 && data[3] != 0) {
    saveData(data);
    // copy data to displayData
    for (int i = 0; i < SensorAnount; i++) {
      displayData[i] = data[i];
    }
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
  }
}

void setup() {
  // Setup
  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.init();                      // initialize the lcd 
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Hello, world!");
  Serial.println("Hello, world!");
  delay(1000);
  lcd.clear();
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    lcd.print("Card failed");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  lcd.print("card init");
  // create log file named "datalog.csv" and write header (sensor names) to it if it doesn't exist:
  File dataFile = SD.open("datalog.csv");
  if (!dataFile) {
    Serial.println("datalog.csv doesn't exist, creating it");
    // create header row:
    dataFile = SD.open("datalog.csv", FILE_WRITE);
    for (int i = 0; i < SensorAnount; i++) {
      dataFile.print(SensorName[i]);
      // write comma if not last item
      if(i < SensorAnount - 1) dataFile.print(",");
    }
  } else {
    Serial.println("datalog.csv exists");
  }
  dataFile.close();
  // Attach interrupt to receive data from bluetooth
  attachInterrupt(digitalPinToInterrupt(2), receive, FALLING);         // Attach interrupt to receive data from bluetooth
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Reset the previousMillis
    displayNext();
  }

  if(data[0] != 0 && data[1] != 0 && data[2] != 0 && data[3] != 0) {
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
    Serial.println(data[3]);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
  }
}
