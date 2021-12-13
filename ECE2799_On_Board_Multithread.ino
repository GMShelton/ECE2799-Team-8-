//Change the Freq from 80 to 40. this is done in tools, by where the port is selected
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFiMulti.h>
#include <Arduino.h>
#include <EasyButton.h>

//Make another version of this and have 2 seperate servers. One code will run a server and connect tot the other and vise versa

#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define ButtonInput 34
#define BAUDRATE 115200
int ButtonState = 0;
int ButtonPattern = 0;
int PressTime = 500; // Allows time for button pushes
int status = WL_IDLE_STATUS;

EasyButton button(ButtonInput,35,false,false); //Name(Button_pin,Debounce_Delay,pull_up_enable,invert_logic)


#define LED_BUILTIN 2 

TaskHandle_t Task1;


WiFiServer server(80);
const char *ssid = "yourAP";
const char *password = "yourPassword";

//Adding PWM so the LEDs don't blow each other out
//const int freq = 5000;
//const int ledChannel = 0;
//const int resolution = 8;
//Setup for the mutlithread stuff
void setup() {
  Serial.begin(115200);
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 



  pinMode(Motor,OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(ButtonInput,INPUT);
  digitalWrite(LedRed, HIGH);
 digitalWrite(LedBlue,HIGH);
  digitalWrite(LedGreen,HIGH);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

  button.begin();

  button.onSequence(3, 2000, hi);

  button.onSequence(2, 2000, leave);

  button.onPressedFor(1000, emergency);

  Serial.println(">>> EasyButton multiple onSequence example <<<");
}

//Task1code: Blinks Red and Green other code will do motor and Blue
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
  button.read();
  vTaskDelay(10);
  } 
}



void loop() //Not used
{
 

   WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /EMERGENCY")) {
              digitalWrite(Motor,HIGH);
              digitalWrite(LedRed, LOW);
              digitalWrite(LedBlue,HIGH);
              digitalWrite(LedGreen,HIGH);
              delay(5000);             
              digitalWrite(LedRed,HIGH); 
              digitalWrite(Motor,LOW);
        }
        if (currentLine.endsWith("GET /LEAVE")) {
              digitalWrite(Motor,HIGH);
              digitalWrite(LedRed, HIGH);
              digitalWrite(LedBlue,LOW);
              digitalWrite(LedGreen,HIGH);
              delay(250);              
              digitalWrite(Motor,LOW);
              delay(250);
              digitalWrite(Motor,HIGH);
              delay(250);
              digitalWrite(Motor,LOW); 
              delay(750);
              digitalWrite(LedBlue,HIGH); 
        }
        if (currentLine.endsWith("GET /HI")) {
              digitalWrite(Motor,HIGH);
              digitalWrite(LedRed, HIGH);
              digitalWrite(LedBlue,HIGH);
              digitalWrite(LedGreen,LOW);
              delay(1000);
              digitalWrite(LedGreen,HIGH);  
              digitalWrite(Motor,LOW);            
        }
        if (currentLine.endsWith("GET /SILENT")){
          
          //int ButtonState = 0;
          
            // put your main code here, to run repeatedly: Ayo new comment
            //ButtonState = digitalRead(ButtonInput);
           
              digitalWrite(Motor,HIGH);
              digitalWrite(LedRed, LOW);
              digitalWrite(LedBlue,HIGH);
              digitalWrite(LedGreen,HIGH);
              delay(2000);
              digitalWrite(Motor,LOW);
              digitalWrite(LedRed, HIGH);
              digitalWrite(LedBlue,LOW);
              digitalWrite(LedGreen,HIGH);
              delay(2000);
              digitalWrite(Motor,LOW);
              digitalWrite(LedRed, HIGH);
              digitalWrite(LedBlue,HIGH);
              digitalWrite(LedGreen,LOW);
            

            
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
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
