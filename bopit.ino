#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUTTON_COUNT 3
#define BUTTON_PIN_START 12
#define GREEN_LED_PIN 13
#define RED_LED_PIN 14

LiquidCrystal_I2C lcdOne(0x27, 16, 2); // Initialize LCD object - Assuming 16x2 display
bool micState = false;
bool lcdOn = false; // Variable to track the state of the LCD
bool gameStarted = false;
int randomButton; // Variable to store the randomly selected button
unsigned long gameStartTime; // Variable to store the time when the game started
bool correctButtonPressed = false; // Flag to track if the correct button was pressed
bool game3States = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // Initialize random number generator with seed
  randomSeed(analogRead(0));
  
  // LCD setup
  lcdOne.init(); // Initialize the LCD with the I2C interface

  //Digital Inputs
  pinMode(0, INPUT_PULLUP); // OFF/ON button
  pinMode(1, INPUT_PULLUP); // "New Game" button

  //Success/failure LEDs
  pinMode(18, OUTPUT);//Success led
  pinMode(19, OUTPUT); //Failure led

  //Mic input
  pinMode(17, INPUT); //Read input from microphone (Digital)

}

void loop() {
  //OFF/ON BUTTON//////////////////////

  // If the button is pressed (buttonState is LOW) and the LCD is currently off
  if (digitalRead(0) == LOW && !lcdOn) {
    // Turn on the LCD backlight
    lcdOne.backlight();
    // Clear the LCD screen
    lcdOne.clear();
    // Set cursor to the beginning of the first line
    lcdOne.setCursor(0, 0);
    // Print "Press Button for" on the first line
    lcdOne.print("Press Button for");
    // Set cursor to the beginning of the second line
    lcdOne.setCursor(0, 1);
    // Print "New Game" on the second line
    lcdOne.print("New Game");

    lcdOn = true; // Set the LCD state to on
    gameStarted = true;
  }
  // If the button is pressed (buttonState is LOW) and the LCD is currently on
  else if (digitalRead(0) == LOW && lcdOn) {
    // Turn off the LCD backlight
    lcdOne.noBacklight();
    // Clear the LCD screen
    lcdOne.clear();
    // Set cursor to the beginning of the first line
    lcdOne.setCursor(0, 0);
    // Print "System Off" on the first line
    lcdOne.print("System Off");

    lcdOn = false; // Set the LCD state to off
    gameStarted = false;
  }

  delay(100); // Add a small delay to avoid overwhelming the loop

  //NEW GAME BUTTON//////////////////////////////// (later)
  if (gameStarted) {

    if (digitalRead(1) == LOW) {
      // Clear the LCD screen
      lcdOne.clear();
      lcdOne.print("Ready, Set, Go!");

      randomGame();

      
      //startGame();
    }
  }
}

//Function for Sing it!
bool singItCommand() {
  if (digitalRead(17) == HIGH) {
    return true; // Microphone input detected
  } else {
    return false; // No microphone input
  }
}


void randomGame() {
  lcdOne.clear();
  bool gameOver = false;

  while (!gameOver) {
    int randomNum = random(1, 4); // Generate a random number between 1 and 3
    
    // Print the game number on the LCD
    lcdOne.setCursor(0, 0);
    lcdOne.clear();
    lcdOne.print("Game ");
    lcdOne.print(randomNum);
    
    // Call the respective game function based on the random number
    switch(randomNum) {
      case 1:
        // Call game function 1 and set gameOver based on game result
        // gameOver = game1();
        break;
      case 2:
        // Call game function 2 and set gameOver based on game result
        // gameOver = game2();
        break;
      case 3:
        // Call game function 3 and set gameOver based on game result
        gameOver = game3();
        break;
      default:
        // Handle unexpected case
        break;
    }

    delay(2000); // Add a delay before selecting the next game
  }

  // Once the game loop exits, display a message or perform any necessary cleanup
  lcdOne.clear();
  lcdOne.print("Game Over!");
  //Add score as well
}

//Play it!
bool game1(){

}

//Whammy it!
bool game2(){

}

//Sing it!
bool game3() {
  // put your main code here, to run repeatedly:
  micState = singItCommand(); //Assign Boolean value according to function
  if(micState == 1){ //Light LED based on success or failure
    digitalWrite(12, HIGH);
  }
  else{
    digitalWrite(13, HIGH);
  }
  delay(1000); //Wait before accepting more input
}
 

