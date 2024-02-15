//Bop-It!
//ON/OFF switch as well as LED indicating that system is ON is handled solely by hardware - No pin assignments needed
#include <LiquidCrystal_I2C.h> //Include the LCD display library
#include <Wire.h>
//***STILL NEED TO INSTALL THE ABOVE TWO LIBRARIES
//Reserve analog pins for LCD display: SDA = A4, SCL = A5

LiquidCrystal_I2C lcdOne(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //Initialize LCD object - May need to change address depending on LCD
//Use LCD to display: Initial screen, current score during game, "Game Over!" screen w/ end score (Blinking)
void setup() {
  //Put your setup code here, to run once:
  //LCD set-up:
  lcdOne.begin(16, 2); //Number of rows and columns on LCD screen
  //lcdOne.noCursor(); //Hides the cursor - Not necessary
  lcdOne.print("Press Button for New Game");

  //Digital inputs:
  pinMode(0, INPUT); //"New Game" button
  pinMode(1, INPUT);  //Microphone input
  pinMode(2, INPUT); //Green button input ("Play-It!")
  pinMode(3, INPUT); //Red button input ("Play-It!")
  pinMode(4, INPUT); //Yellow button input ("Play-It!")
  
  //Analog inputs:
  pinMode(A1, INPUT); //Analog input for "Whammy-It!" - Potentiometer

  //Outputs:
  pinMode(5, OUTPUT); //Green button LED
  pinMode(6, OUTPUT) //Red button LED
  pinMode(7, OUTPUT) //Yellow button LED

  pinMode(8, OUTPUT) //Green LED indicating successful attempt
  pinMode(9, OUTPUT) //Red LED indicating unsuccessful attempt
  //Reserve 4 pins for Piezo speakers: One to be affected by the whammy bar, and three to play upon a key being pressed (Can be analog or digital)

  //***Need to find easiest way to implement audio commands
}

void loop() {
  //Put your main code here, to run repeatedly:

}
