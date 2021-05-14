/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/
//PINTER CODE

#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN1 2 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN1 6 // Arduino receive   GREEN WIRE   labeled TX on printer

#define TX_PIN2 8 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN2 9 // Arduino receive   GREEN WIRE   labeled TX on printer

#define TX_PIN3 10 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN3 12 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial1(RX_PIN1, TX_PIN1); // Declare SoftwareSerial obj first
SoftwareSerial mySerial2(RX_PIN2, TX_PIN2); // Declare SoftwareSerial obj first
SoftwareSerial mySerial3(RX_PIN3, TX_PIN3); // Declare SoftwareSerial obj first


Adafruit_Thermal printer1(&mySerial1);     // Pass addr to printer constructor
Adafruit_Thermal printer2(&mySerial2);     // Pass addr to printer constructor
Adafruit_Thermal printer3(&mySerial3);     // Pass addr to printer constructor


// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

//ENCODER CODE

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

int16_t oldEncPos, encPos;
uint8_t buttonState;

#define pinA A2
#define pinB A1
#define pinSw A0 //switch
#define STEPS 4

int letternumb;
ClickEncoder encoder(pinA, pinB, pinSw, STEPS);

int alpha[] = {" ","a", "b", "c", "d", "e","f","g","h","i",
"j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"," "}; //29

String letters[] = {" ","a", "b", "c", "d", "e","f","g","h","i",
"j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"," "};//26
int letterselect = 0;

String typemessage[] = {""};
int message[25];
int numLetters = 25;
int inputNum = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3); //Download the latest Adafruit Library in order to use this constructor

int contrast=55;

void setup() {

//PRINTER CODE

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial1.begin(9600);  // Initialize SoftwareSerial
    mySerial2.begin(9600);  // Initialize SoftwareSerial
        mySerial3.begin(9600);  // Initialize SoftwareSerial

//String Code


         printer1.begin();        // Init printer (same regardless of serial type)
         printer2.begin();        // Init printer (same regardless of serial type)
         printer3.begin();        // Init printer (same regardless of serial type)

         
    for (int i = 0; i < 12; i++){
      //Serial.println(parsedStrings[i]);//  should have the 5 data strings parsed out

        printer1.justify('C');
  printer1.boldOn();
  printer1.setSize('L');        // Set type size, accepts 'S', 'M', 'L'

// Sleep for 3 seconds

//delay(10000);

  }

  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer1.begin();        // Init printer (same regardless of serial type)
  printer2.begin();        // Init printer (same regardless of serial type)
  printer3.begin();        // Init printer (same regardless of serial type)

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.

  // Test inverse on & off
        //printer1.println(F("Hello! I am printer 1"));
        //printer1.println(F("I am working well :)"));
//
//        printer2.println(F("Hello! I am printer 2"));
//        printer2.println(F("I think im working well 2 :)"));
//
//        printer2.feed(2);
//
//        printer3.println(F("Hello! I am printer 3"));
//        printer3.println(F("Save the best for last :3"));
//
//        printer3.feed(2);



  printer1.sleep();      // Tell printer to sleep
    printer2.sleep();      // Tell printer to sleep
    printer3.sleep();      // Tell printer to sleep

  delay(3000L);         // Sleep for 3 seconds
  printer1.wake();       // MUST wake() before printing again, even if reset
  printer1.setDefault(); // Restore printer to defaults
  printer2.wake();       // MUST wake() before printing again, even if reset
  printer2.setDefault(); // Restore printer to defaults
  printer3.wake();       // MUST wake() before printing again, even if reset
  printer3.setDefault(); // Restore printer to defaults



 //ENCODER CODE
 
 pinMode(7,OUTPUT);
  turnBacklightOn();

  display.begin();      
  display.clearDisplay(); 
  setContrast();  

  Serial.begin(9600);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

  encoder.setAccelerationEnabled(true);

  Serial.print("Acceleration is ");
  Serial.println((encoder.getAccelerationEnabled()) ? "enabled" : "disabled");

  oldEncPos = -1;

  
}

void loop() {
encPos += encoder.getValue();

  if (encPos > oldEncPos) {
    letterselect++;
        Serial.println("UPPP");

  }

    if (encPos < oldEncPos) {
    letterselect--;
            Serial.println("DOWN");

  }

    if(letterselect > 26){
    letterselect = 0;
  }

    if(letterselect < 0){
    letterselect = 26;
  }
  if (encPos != oldEncPos) {
    oldEncPos = encPos;
    Serial.print("Encoder Value: ");
    Serial.println(encPos);
Serial.print("Letter: ");
    Serial.println(letters[letterselect]);
    //Serial.println(letterselect);

}

        if(buttonState != 0 && buttonState == 5){
      message[inputNum] = letterselect;
      //letterselect = 0;
      inputNum = inputNum + 1;
      Serial.print("PRESSED LOOK: ");
      for (int i = 0; i < 4; i = i+1){
    Serial.println(message[i]); }
    

}

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.print("what do u fear??????????????");
    //display.drawFastHLine(0,10,83,BLACK);

        //display.display();


//   letters[letterselect] = letterShow;
    display.setTextSize(1);
    //display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(30, 10);
   // display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 20);
          for (int i = 0; i < inputNum; i = i+1){
    display.print(letters[message[i]]);
}
    display.setTextSize(2);
    display.setCursor(35, 30);
    display.print(letters[letterselect]);
    display.setTextSize(2);
    display.display();


if(buttonState != 0 && buttonState == 6){
  
      for (int i = 0; i < inputNum; i = i+1){
    Serial.print(letters[message[i]]); }
    Serial.println("");

         printer1.begin();        // Init printer (same regardless of serial type)
         printer2.begin();        // Init printer (same regardless of serial type)
         printer3.begin(); 

        printer1.justify('C');
  printer1.boldOn();
  printer1.setSize('L');        // Set type size, accepts 'S', 'M', 'L'

         for (int i = 0; i < inputNum; i = i+1){
       printer1.print(letters[message[i]]);
         }
                 printer1.println(F("."));

        
          delay(2000L);   
printer2.upsideDownOn();
printer2.print(F("I am afraid of "));
         for (int i = 0; i < inputNum; i = i+1){
          printer2.print(letters[message[i]]);
         }
        printer2.println(F(""));

          delay(2000L);   

printer3.println(F("Here, I feel safe from "));
         for (int i = 0; i < inputNum; i = i+1){
        printer3.print(letters[message[i]]);
         }
        printer3.println(F("."));
        
         for (int i = 0; i < inputNum; i = i+1){
message[i]= 0;
         }
         inputNum = 0;
         
        
          delay(2000L);   
// Sleep for 3 seconds    
    
    
    
    Serial.println("");

    
}

if(buttonState != 0 && buttonState == 4){
           message[inputNum]= 0;
                      inputNum = inputNum - 1;


}

  buttonState = encoder.getButton();

  if (buttonState != 0) {
    Serial.print("Button: "); Serial.println(buttonState);
    switch (buttonState) {
      case ClickEncoder::Open:          //0
        break;

      case ClickEncoder::Closed:        //1
        break;

      case ClickEncoder::Pressed:       //2
        break;

      case ClickEncoder::Held:          //3
        break;

      case ClickEncoder::Released:      //4
        break;

      case ClickEncoder::Clicked:       //5
        break;

      case ClickEncoder::DoubleClicked: //6
        break;
    }
  }
}

void timerIsr() {
  encoder.service();
}
  void turnBacklightOn()
  {
    digitalWrite(7,HIGH);
  }
    void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }
