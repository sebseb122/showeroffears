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

#include "Adafruit_Thermal.h"

#include "frame.h"


#include <LCD5110_Graph.h>
#include <dht.h>
dht DHT;
LCD5110 myGLCD(8,9,10,11,12);
#define DHT11_PIN 6

extern unsigned char SmallFont[];
extern unsigned char TinyFont[];
extern uint8_t arduino_logo[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {
pinMode(2,INPUT_PULLUP);
int buttonStatus = 0;
  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(9600);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin(200);        // Init printer (same regardless of serial type)

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.

  // Test inverse on & off
printer.justify('C');
printer.inverseOn();
printer.doubleHeightOn();
printer.println(F(" DOCENDO DISCIMUS "));
printer.inverseOff();
printer.doubleHeightOff();

    myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  randomSeed(analogRead(7));
    printer.println(F("Temperature and Humanity"));
    printer.println(F("Printer Project"));

        printer.println(F("by Sebastian DeMarino"));
  printer.feed(3);
  printer.justify('L');
    printer.underlineOn();
    printer.println(F("Components:"));
  printer.underlineOff();
  
      printer.println(F("- Arduino Uno"));
      printer.println(F("- LCD 84x48 - Nokia 5110"));
      printer.println(F("- Tiny Thermal Receipt Printer"));
      printer.println(F("- 4x AA Battery Holder"));
      printer.println(F("- Tactile Button switch (6mm)"));
      printer.println(F("- DHT22 Temp-Humidity Sensor"));
      printer.println(F("(to purchase components scan QR code)"));
  printer.feed(3);

    printer.underlineOn();
    printer.println(F("Hardware Setup:"));
  printer.underlineOff();
  
      printer.println(F("- First connect the data cable  of the Tiny Thermal Printer to  the Arduino, the data cable has 5 wires but only 3 need to be     connected:"));
      printer.println(F("   - Black = ground"));
      printer.println(F("   - Green = data IN, pin 6"));
      printer.println(F("   - Yellow = data OUT, pin 5"));
      printer.println(F("- Next connect the power cable  to your 4x AA Battery Holder"));
      printer.println(F("- Then lets connect the Nokia   5110 LCD:"));
      printer.println(F("   - 1 VCC = 3.3V"));
      printer.println(F("   - 2 GND = ground"));
      printer.println(F("   - 3 SCE = pin 12"));
      printer.println(F("   - 4 RST = pin 11"));
      printer.println(F("   - 5 D/C = pin 10"));
      printer.println(F("   - 6 DN(MOSI) = pin 9"));
      printer.println(F("   - 7 SCLK = pin 8"));
      printer.println(F("   - 8 LED = no pin"));
      printer.println(F("- Next lets connect the button, put the button in the middle of the breadboard and on the same  side of the breadboard:"));
      printer.println(F("   - Top = ground"));
      printer.println(F("   - Bottom = pin 2"));
      printer.println(F("- Finally lets connect the DHT22 with the 3 pins pointing right:"));
      printer.println(F("   - Top = ground"));
      printer.println(F("   - Mid = 5V"));
      printer.println(F("   - Bottom = pin 6"));
      printer.println(F("- All your hardware is setup!"));

  printer.feed(3);
    printer.underlineOn();
    printer.println(F("Software Setup:"));
    printer.underlineOff();

      printer.println(F("- Scan the QR code below for the Arduino code for this project"));
      printer.println(F("- This project requires you to  download the following libraries in the Library Manager:"));
      printer.println(F("   - Adafruit Thermal Printer      Library (for Printer)"));
      printer.println(F("   - DHT sensor library (for       DHT22)"));
      printer.println(F("   - LiquidCrystal (for Nokia      5110 LCD)"));
      printer.println(F("- Upload the TempPrint.ino to   your Arduino and you should be    ready to go!"));
      printer.println(F("- Explore the example code in   each library to help understand how each library works"));

   printer.feed(3);
    printer.underlineOn();
    printer.println(F("All files need for this project:"));
    printer.underlineOff();
    
printer.printBitmap(frame_width, frame_height, frame_data);

       printer.feed(3);
       printer.justify('C');

    printer.println(F("Good luck and Have Fun!"));
    
       printer.feed(3);

  printer.feed(2);
//
  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}

void loop() {

}
