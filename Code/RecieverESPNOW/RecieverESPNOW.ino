  // Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include "Nextion.h"

#define RXD2 17
#define TXD2 16

typedef struct data_packet {
    int canId;
    int percentFull;
    float temperature;
    float humidity;
} data_packet;
 
// Create a structured object
data_packet myData;
NexText can1percentage = NexText(0,1,"t1");
NexText can1temp = NexText(0,1,"t6");
NexText can1humid = NexText(0,1,"t10");
NexProgressBar can1progressbar = NexProgressBar(0,1,"j0");
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("ItemRecved");
  memcpy(&myData, incomingData, sizeof(myData));
  myData.percentFull = 40 - myData.percentFull+4;// 4 inches away is 100% full. 50 inches is the size of the bin
  if(myData.percentFull < 0){
    myData.percentFull = 0;
  }
  myData.percentFull = myData.percentFull * 2.5;
  if(myData.percentFull > 100){
    myData.percentFull = 100;
  }
  char buffer[7] = "error";
  itoa(myData.percentFull,buffer,10); //(integer, yourBuffer, base)
  strcat(buffer,"%");
  can1percentage.setText(buffer);
  can1progressbar.setValue(int(round(myData.percentFull)));
  // Temperature
  itoa(int(round(myData.temperature)),buffer,10); //(integer, yourBuffer, base)
  // strcat(buffer,char(176)+"F");
  can1temp.setText(buffer);
  // Humidity
  itoa(int(round(myData.temperature)),buffer,10); //(integer, yourBuffer, base)
  strcat(buffer,"%");
  can1humid.setText(buffer);


}
 
void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);    //Setting the Serial2 TX to Pin 9 for PCB (this is IO33/D33 on dev board)
  nexInit();
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  can1percentage.setText("...");
}
 
void loop() {
 
}