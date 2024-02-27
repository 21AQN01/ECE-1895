#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define BUTTON_COUNT 3
#define BUTTON_PIN_START 12
#define GREEN_LED_PIN 13
#define RED_LED_PIN 14

LiquidCrystal_I2C lcdOne(0x27, 16, 2); // Initialize LCD object - Assuming 16x2 display

bool lcdOn = false; // Variable to track the state of the LCD
bool gameStarted = false;
int randomButton; // Variable to store the randomly selected button
unsigned long gameStartTime; // Variable to store the time when the game started
bool correctButtonPressed = false; // Flag to track if the correct button was pressed

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // LCD setup
  lcdOne.init(); // Initialize the LCD with the I2C interface

  // Digital inputs
  pinMode(0, INPUT_PULLUP); // OFF/ON button
  pinMode(1, INPUT_PULLUP); // "New Game" button

  // Digital outputs for LEDs
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BUTTON_PIN_START + i, INPUT_PULLUP);
    pinMode(BUTTON_PIN_START + i + 2, OUTPUT);
    digitalWrite(BUTTON_PIN_START + i + 2, LOW); // Ensure LEDs are initially off
  }

  // LED pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

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
      startGame();
    }
  }

  //Check if the game has started and enough time has passed
  if (gameStarted && millis() - gameStartTime > 5000 && !correctButtonPressed) {
    // Turn off the LED if the player didn't press the correct button within 5 seconds
    digitalWrite(BUTTON_PIN_START + randomButton + 2, LOW);
  }
}

void startGame() {
//   Serial.println("Game started");
//   // Generate random LED pattern
//   randomButton = random(BUTTON_COUNT); // Generate a random button to light up
//   digitalWrite(BUTTON_PIN_START + randomButton + 2, HIGH); // Turn on the corresponding LED
//   gameStartTime = millis(); // Record the start time of the game

//   // Wait for player input
//   unsigned long timeout = 5000; // Timeout duration (in milliseconds)
//   unsigned long startTime = millis(); // Record the start time of waiting

//   while (millis() - startTime < timeout) {
//     // Check for button press
//     for (int i = 0; i < BUTTON_COUNT; i++) {
//       if (digitalRead(BUTTON_PIN_START + i) == LOW) {
//         if (i == randomButton) {
//           correctButtonPressed = true; // Set flag if correct button is pressed
//           flashLED(GREEN_LED_PIN); // Flash green LED
//         } else {
//           flashLED(RED_LED_PIN); // Flash red LED
//         }
//         break;
//       }
//     }
//     if (correctButtonPressed) {
//       break; // Exit the loop if the correct button was pressed
//     }
//   }

//   // Reset flags and turn off the LED
//   correctButtonPressed = false;
//   digitalWrite(BUTTON_PIN_START + randomButton + 2, LOW);
// }

// void flashLED(int pin) {
//   Serial.println("LED flashed");
//   digitalWrite(pin, HIGH); // Turn on the LED
//   delay(100); // Delay to keep the LED on
//   digitalWrite(pin, LOW); // Turn off the LED
}
