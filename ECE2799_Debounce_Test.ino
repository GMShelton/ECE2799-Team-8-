
const int buttonPin = 2;    
const int ledPin = 13;      
#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define ButtonInput 34

int ledState = HIGH;         
int buttonState = HIGH;             
int lastButtonState = LOW;   

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    
unsigned long PatterenDelay = 500;
int CurrentPattern = 0;
unsigned long PatternTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ButtonInput, INPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen,OUTPUT);
  digitalWrite(LedBlue, HIGH); 
  digitalWrite(LedRed, HIGH);
  digitalWrite(LedGreen, HIGH);
  digitalWrite(ButtonInput, LOW);
}

void loop() {
  //delay(1000);
  int reading = digitalRead(ButtonInput);
  Serial.println(reading);
  //Serial.println(digitalRead(lastButtonState));
  if (reading == lastButtonState) {
    lastDebounceTime = millis();
    Serial.println("First IF");
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    CurrentPattern ++;
    Serial.println(CurrentPattern);
    Serial.println("Second IF");
    PatternTime = millis();
     if (PatternTime > PatterenDelay) {
      if (reading != buttonState) {
      buttonState = reading;
      Serial.println("Third IF");
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.println("Fourth IF");
        if (CurrentPattern == 1){
          Serial.println("Fifth IF");
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
        if (CurrentPattern >= 2){
          Serial.println("Sixth IF");
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
      
     }
      }
   
  }

  // set the LED:
  //digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
}
