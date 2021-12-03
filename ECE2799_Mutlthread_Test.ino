TaskHandle_t Task1;
TaskHandle_t Task2;

#define LedRed 4
#define LedBlue 0
#define LedGreen 2
#define Motor 33
#define ButtonInput 34
int ButtonState = 0;

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

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 

    // configure LED PWM functionalitites And I guess it goes to Core1???
  //ledcSetup(ledChannel, freq, resolution);
  //ledcAttachPin(ledPin, ledChannel); // attach the channel to the GPIO to be controlled

  pinMode(Motor,OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(ButtonInput,INPUT);
}

//Task1code: Blinks Red and Green other code will do motor and Blue
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen, LOW);
    delay(2000);
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    delay(3000);
  } 
}

//Task2code: When button is pushed run the motor, when not pushed turn blue
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    ButtonState = digitalRead(ButtonInput);
  if (ButtonState == HIGH) {
    digitalWrite(Motor,HIGH);
    digitalWrite(LedBlue,HIGH);
    delay(2000);

  }
  else {
    digitalWrite(Motor,LOW);
    digitalWrite(LedBlue,LOW);
    
  }
}
}

void loop() {
}
