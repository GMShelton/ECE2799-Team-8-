#include <ezButton.h>
#define button1 34
#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define BUTTON_DEBOUNCE_DELAY 20



ezButton button(34);

void setup() {
  // put your setup code here, to run once:
  button.setDebounceTime(50);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  button.loop();
  if(button.isPressed()){
    Serial.println("on");
    
  }
}
