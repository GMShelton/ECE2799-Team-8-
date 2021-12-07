/*
  Name:    MultipleSequence.ino
  Created:  03/23/2020 12:45:23 AM
  Author: José Gabriel Companioni Benítez (https://github.com/elC0mpa)
  Description: Example to demostrate how to work with multiple sequences 
*/

#include <Arduino.h>
#include <EasyButton.h>

// Arduino pin where the button is connected to.
#define BUTTON_PIN 34
#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define BAUDRATE 115200

int ButtonPattern = 0;
int PressTime = 500; // Allows time for button pushes

void sequenceEllapsed()
{
  Serial.println("2 clicks");
  ButtonPattern++;
  delay(PressTime);
}

void otherSequence()
{
  Serial.println("3 clicks");
  ButtonPattern = 3;
  delay(PressTime);
}

void Sequence1 (){
  Serial.println("1 click");
  ButtonPattern++;
  delay(PressTime);
}
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

  button.onSequence(1, 2000, Sequence1);

  button.onSequence(2, 2000, sequenceEllapsed);

  button.onPressedFor(1000, otherSequence);


}

void loop()
{
  // Continuously read the status of the button.
  button.read();
  if (ButtonPattern == 1){
  Serial.println("Turn on LED Red");
  digitalWrite(LedBlue, HIGH);
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, HIGH);
  ButtonPattern = 0; 
  }
  if (ButtonPattern == 2){
  Serial.println("Turn on LED Blue");
  ButtonPattern = 0; 
  digitalWrite(LedBlue, LOW);
  digitalWrite(LedRed, HIGH);
  digitalWrite(LedGreen, HIGH);
  }
  if (ButtonPattern >= 3){
  Serial.println("Turn on LED Green");
  ButtonPattern = 0; 
  digitalWrite(LedBlue, HIGH);
  digitalWrite(LedRed, HIGH);
  digitalWrite(LedGreen, LOW);
}
}
