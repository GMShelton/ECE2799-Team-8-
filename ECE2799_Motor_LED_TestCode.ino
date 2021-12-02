#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define ButtonInput 34
#define Button 6

int ButtonState = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(Motor,OUTPUT);
pinMode(LedRed, OUTPUT);
pinMode(LedBlue, OUTPUT);
pinMode(LedGreen, OUTPUT);
pinMode(ButtonInput,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: Ayo new comment
  ButtonState = digitalRead(ButtonInput);
  if (ButtonState == HIGH) {
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
  }
  else {
    digitalWrite(Motor,LOW);
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedBlue,HIGH);
    digitalWrite(LedGreen,LOW);
  }

}
