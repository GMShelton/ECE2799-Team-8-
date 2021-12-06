
const int buttonPin = 2;    
const int ledPin = 13;      
#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define ButtonInput 34

int ledState = HIGH;         
int buttonState;             
int lastButtonState = LOW;   

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    
unsigned long PatterenDelay = 500;
int CurrentPattern = 0;
unsigned long PatternTime = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ButtonInput, INPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen,OUTPUT);
  digitalWrite(LedBlue, LOW); 
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
}

void loop() {
  int reading = digitalRead(ButtonInput);
  Serial.println("Press Optional");
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    CurrentPattern ++;
    Serial.println("Patten Calc");
    PatternTime = millis();
     if (PatternTime > PatterenDelay) {
      if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        if (CurrentPattern = 1){
        Serial.println("One push.");
        digitalWrite(LedBlue, LOW);
        digitalWrite(LedRed, HIGH);
        digitalWrite(LedGreen, HIGH);
        delay(1000);
        digitalWrite(LedBlue, HIGH);
        digitalWrite(LedRed, HIGH);
        digitalWrite(LedGreen, HIGH);
        CurrentPattern = 0;
      }
        if (CurrentPattern = 2){
          Serial.println("two push");
        digitalWrite(LedBlue, HIGH);
        digitalWrite(LedRed, HIGH);
        digitalWrite(LedGreen, LOW);
        delay(1000);
        digitalWrite(LedBlue, HIGH);
        digitalWrite(LedRed, HIGH);
        digitalWrite(LedGreen, HIGH);
        CurrentPattern = 0;
      }
      
      if (CurrentPattern = 3){
        Serial.println("3 push");
        digitalWrite(LedBlue, HIGH);
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, HIGH);
        delay(1000);
        digitalWrite(LedBlue, HIGH);
        digitalWrite(LedRed, HIGH);
        digitalWrite(LedGreen, HIGH);
        CurrentPattern = 0;
     }
     }
     } 
   
  }

  // set the LED:
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
}
