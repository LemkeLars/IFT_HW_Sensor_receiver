#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX

int bluetoothData;
//float* data = 0;
bool nextData = false;
bool nextSize = false;
int i = 0;
int data[] = {0,0};

// Setup bluetooth interrupt
/* void bluetoothReceive() {
  if (bluetooth.available()) {
    bluetoothData = bluetooth.read();
    Serial.println(bluetoothData, HEX);
    
    int dataSize = 1;
    
    switch (bluetoothData) {
      case 0x01:
        Serial.println("Start signal received");
        delay(100);
        bluetooth.print('1');                      // Send start signal
        break;
      case 0x02:
        Serial.println("Size instruction received");
        nextSize = true;
        break;
      case 0x03:
        Serial.println("Data instruction received");
        nextData = true;
        break;
      default:
        if (nextSize) {
          Serial.println("Size received");
          dataSize = bluetoothData;
          delete[] data;                          // Free the previous data array if needed
          data = new float[dataSize];
          nextSize = false;
        } else if (nextData) {
          Serial.println("Data received");
          if (index < dataSize) {
            uint8_t receivedByte = bluetoothData;
            float receivedFloat;
            memcpy(&receivedFloat, &receivedByte, sizeof(float));
            data[index] = receivedFloat;
            // print data array
            Serial.print("Data: ");
            for (int i = 0; i < dataSize; i++) {
              Serial.print(data[i]);
              Serial.print(";");
            }
            index++;
          } else {
            index = 0;
            // Print data
            for (int i = 0; i < dataSize; i++) {
              Serial.println(data[i]);
            }
          }
          nextData = false;
        }
        break;
    }
  }
} */

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
