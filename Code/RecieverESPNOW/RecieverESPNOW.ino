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
    int CO2Concentration;
} data_packet;
 
// Create a structured object
data_packet myData;
NexText can1percentage = NexText(0,1,"t1");
NexText can2percentage = NexText(0,1,"t0");
NexGauge can1AQ = NexGauge(0,1,"z1");
NexGauge can2AQ = NexGauge(0,1,"z0");
NexText can1temp = NexText(0,1,"t6");
NexText can2temp = NexText(0,1,"t7");
NexText can1humid = NexText(0,1,"t10");
NexText can2humid = NexText(0,1,"t11");
NexProgressBar can1progressbar = NexProgressBar(0,1,"j0");
NexProgressBar can2progressbar = NexProgressBar(0,1,"j1");

int AQ1_Baseline;
int AQ2_Baseline;
int AQ1_Avg;
int AQ2_Avg;
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("ItemRecved");
  memcpy(&myData, incomingData, sizeof(myData));


  //Can 1
  if(myData.canId == 1){
    int heightofCan1 = 26; //40 inches is the size of the bin
    myData.percentFull = heightofCan1 - myData.percentFull;// 4 inches away is 100% full.
    if(myData.percentFull < 0){
      myData.percentFull = 0;  
    }
    myData.percentFull = myData.percentFull * 100/heightofCan1;
    if(myData.percentFull > 100){
      myData.percentFull = 100;
    }
    char buffer[7] = "error";
    itoa(myData.percentFull,buffer,10); //(integer, yourBuffer, base)
    strcat(buffer,"%");
    can1percentage.setText(buffer);
    can1progressbar.setValue(int(round(myData.percentFull)));
    if(int(round(myData.percentFull)) > 89){
      can1progressbar.Set_font_color_pco(61700);
    }else{
      can1progressbar.Set_font_color_pco(26282);
    }

    // Temperature
    if(myData.temperature < 150){
      itoa(int(round(myData.temperature)),buffer,10); //(integer, yourBuffer, base)
      // strcat(buffer,char(176)+"F");
      can1temp.setText(buffer);
      // Humidity
      itoa(int(round(myData.humidity)),buffer,10); //(integer, yourBuffer, base)
      strcat(buffer,"%");
      can1humid.setText(buffer);
    }else{
      can1temp.setText("--");
      can1humid.setText("--");
    }
    // Air Quality
    if(AQ1_Baseline == -1){
      AQ1_Baseline = AQ1_Avg/5;
    }
    if(AQ1_Baseline < 0){
      AQ1_Baseline++;
      if(AQ1_Baseline >= -5){
        AQ1_Avg += myData.CO2Concentration;
      }
    }else{
      if(myData.CO2Concentration < AQ1_Baseline){
        myData.CO2Concentration = AQ1_Baseline;
      }else if(myData.CO2Concentration > AQ1_Baseline+400){
        myData.CO2Concentration = AQ1_Baseline+400;
      }
      myData.CO2Concentration = (myData.CO2Concentration - AQ1_Baseline)*225/400;
      can1AQ.setValue(int(round(myData.CO2Concentration)));
    }
  }
  if(myData.canId == 2){
    int heightofCan2 = 23; //40 inches is the size of the bin
    
    myData.percentFull = heightofCan2 - myData.percentFull;// 4 inches away is 100% full. 50 inches is the size of the bin
    
    if(myData.percentFull < 0){
      myData.percentFull = 0;
    }
    myData.percentFull = myData.percentFull * 100/heightofCan2;
    if(myData.percentFull > 100){
      myData.percentFull = 100;
    }
    char buffer[7] = "error";
    itoa(myData.percentFull,buffer,10); //(integer, yourBuffer, base)
    strcat(buffer,"%");
    can2percentage.setText(buffer);
    can2progressbar.setValue(int(round(myData.percentFull)));
    if(int(round(myData.percentFull)) > 89){
      can2progressbar.Set_font_color_pco(61700);
    }else{
      can2progressbar.Set_font_color_pco(26282);
    }

    // Temperature
    if(myData.temperature < 150){
      itoa(int(round(myData.temperature)),buffer,10); //(integer, yourBuffer, base)
      // strcat(buffer,char(176)+"F");
      can2temp.setText(buffer);
      // Humidity
      itoa(int(round(myData.humidity)),buffer,10); //(integer, yourBuffer, base)
      strcat(buffer,"%");
      can2humid.setText(buffer);
    }else{
      can2temp.setText("--");
      can2humid.setText("--");
    }
    // Air Quality
    if(AQ2_Baseline == -1){
      AQ2_Baseline = AQ2_Avg/5;
    }
    if(AQ2_Baseline < 0){
      AQ2_Baseline++;
      if(AQ2_Baseline >= -5){
        AQ2_Avg += myData.CO2Concentration;
      }
    }else{
      if(myData.CO2Concentration < AQ2_Baseline){
        myData.CO2Concentration = AQ2_Baseline;
      }else if(myData.CO2Concentration > AQ2_Baseline+400){
        myData.CO2Concentration = AQ2_Baseline+400;
      }
      myData.CO2Concentration = (myData.CO2Concentration - AQ2_Baseline)*225/400;
      can2AQ.setValue(int(round(myData.CO2Concentration)));
    }
  }

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
  delay(1000);
  can1percentage.setText("...");

  AQ1_Baseline = -10;
  AQ2_Baseline = -10;
  AQ1_Avg = 1;
  AQ2_Avg = 1;

  can1temp.setText("--");
  can1humid.setText("--");
  can2temp.setText("--");
  can2humid.setText("--");
  can1percentage.setText("--");
  can2percentage.setText("--");
}
 
void loop() {
 
}