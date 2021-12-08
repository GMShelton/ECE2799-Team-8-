/*
  Name:    MultipleSequence.ino
  Created:  03/23/2020 12:45:23 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to work with multiple sequences 
*/

#include <Arduino.h>
#include <EasyButton.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 34
#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define BAUDRATE 115200

int ButtonPattern = 0;
int PressTime = 500; // Allows time for button pushes
int status = WL_IDLE_STATUS;



// Instance of the button.
EasyButton button(BUTTON_PIN,35,false,false); //Name(Button_pin,Debounce_Delay,pull_up_enable,invert_logic)

void setup()
{
  pinMode(LedBlue, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen,OUTPUT);
  digitalWrite(LedBlue, HIGH); 
  digitalWrite(LedRed, HIGH);
  digitalWrite(LedGreen, HIGH);
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton multiple onSequence example <<<");

  // Initialize the button.
  button.begin();

  button.onSequence(3, 2000, hi);

  button.onSequence(2, 2000, leave);

  button.onPressedFor(1000, emergency);


}

void loop()
{
  // Continuously read the status of the button.
  button.read();
}

void sendSignal(char* ssid, char* password, String func){
  WiFiClient client;
  //connect to access point
  Serial.println("trying to connect to access point");
  
  while(WiFi.begin(ssid) != WL_CONNECTED) {
      Serial.print("wifi connection in progress");
      delay(5000);
  }  
  delay(5);
  const uint16_t port = 80;
  const char * host = "192.168.4.1"; // ip or dns
  
  // Use WiFiClient class to create TCP connections
  
  Serial.println(func);
  
  //Check's if the client is connected and delays if it cannot connect
  while(!client.connect(host, port)) {
      delay(5000);
      Serial.println("trying to connect");
  }
  String output = "GET /" + func;
  client.println(output);
  Serial.print("request sent");
}

void emergency(){
  sendSignal("yourAP", "yourPassword", "EMERGENCY");
}

void hi(){
  sendSignal("yourAP", "yourPassword", "HI");
}
void leave(){
  sendSignal("yourAP", "yourPassword", "LEAVE");
  
}
