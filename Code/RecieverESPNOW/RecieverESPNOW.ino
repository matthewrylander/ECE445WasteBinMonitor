  // Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include "Nextion.h"

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
 
// Create a structured object
struct_message myData;
NexText t0 = NexText(0,1,"t1");
NexProgressBar can1progressbar = NexProgressBar(0,1,"j0");
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  myData.c = 40 - myData.c+4;// 4 inches away is 100% full. 50 inches is the size of the bin
  if(myData.c < 0){
    myData.c = 0;
  }
  myData.c = myData.c * 2.5;
  if(myData.c > 100){
    myData.c = 100;
  }
  char buffer[7] = "error";
  itoa(myData.c,buffer,10); //(integer, yourBuffer, base)
  strcat(buffer,"%");
  t0.setText(buffer);
  can1progressbar.setValue(int(round(myData.c)));
}
 
void setup() {

  nexInit();
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    // Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  t0.setText("Hi!");
}
 
void loop() {
 
}