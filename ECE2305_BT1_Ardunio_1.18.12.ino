//This code is on the Uno with the andriod black connector usb -> thuderbolt /Assorment of oddities
#include <SoftwareSerial.h>
//SoftwareSerial mySerial(11, 12); //Rx,Tx

#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback

//byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

void setup() {
   Serial.begin(9600);// Serial (Bluetooth) Communication
}

void loop() {

        // read the parameter byte
        param = Serial.read();
        switch (param)

        {
          case 1:
            // Android device requests the Arduino to send some data back to Android
            if (Serial)
            {
              Serial.write(1);
              Serial.write(2);
            }
            break;
           case 2:
           //Nuns
           Serial.println("Nuns of the Battlefield is a public artwork made in 1924"
           "located at the intersection of Rhode Island Avenue NW, M Street, and Connecticut Avenue NW, in Washington, D.C"
           "It is a tribute to the more than 600 nuns who nursed soldiers of both armies during the American Civil War") ;
           //Grant
           break;
           case 3:
           Serial.println(" A presidential memorial in Washington, D.C. honoring American Civil War general and 18th United States President Ulysses S. Grant"
           "It sits at the base of Capitol Hill,  below the west front of the United States Capitol"           
           "It is the second-largest equestrian statue in the United States and the fourth-largest in the world");
           break;
           //
           case 4:
           Serial.println("an equestrian statue of Winfield Scott Hancock, by Henry Jackson Ellicott" 
           " located at Pennsylvania Avenue and 7th Street, Northwest, Washington, D.C"
           " The statue is featured in the opening of the Netflix series House of Cards");
           break;
           case 5:
           //George
           Serial.println("also known as the Thomas Circle Monument, is an equestrian sculpture in Washington, D.C. that honors Civil War general George Henry Thomas"
           " George Henry Thomas was a Union general in the Civil War and a principal commander in the Western Theater"
           " The monument is located in the center of Thomas Circle");
           break;
           default: break; // do nothing
           
           
        
      }
  
  delay(READ_RATE); // wait 100ms for next reading
}
