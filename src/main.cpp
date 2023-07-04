#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX

int bluetoothData;
//float* data = 0;
bool nextData = false;
bool nextSize = false;
int i = 0;
int data[] = {0,0};


void receive() {
  if(!bluetooth.available()) return;
  bluetoothData = bluetooth.read();
  if(i >= 2) i = 0;
  data[i] = bluetoothData;
  i++;
}

void setup() {
  // Setup
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("Start");
  attachInterrupt(digitalPinToInterrupt(2), receive, FALLING);         // Attach interrupt to receive data from bluetooth

}

void loop() {
  if(data[0] != 0 && data[1] != 0) {
    Serial.println(data[0]);
    Serial.println(data[1]);
    data[0] = 0;
    data[1] = 0;
  }
}
