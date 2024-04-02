#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Initialize the LCD screen
int playerScore = 0; //Variable to keep track of the user's score
bool isFailed = false; //State to determine whether or not the player has successfully completed an action
unsigned long actionStartTime; // Time when the current action started
const long actionDuration = 7000; // Maximum duration for each action in milliseconds

SoftwareSerial mySoftwareSerial(10, 9); // RX, TX for DF player
DFRobotDFPlayerMini myDFPlayer; //Initalize variable for df player

void setup() {
  //Initialize random number seed:
  randomSeed(analogRead(0));
  //Initialize LCD screen:
  lcd.init();
  lcd.backlight();

  //Initalize DF player
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  myDFPlayer.volume(10); // Set volume value (max is 30).
  myDFPlayer.play(1); //Play the background sound continuously

  //Initialize input pins:
  pinMode(8, INPUT); //Pin for reading digital microphone input
  pinMode(3, INPUT); //Pin for beginning a new game
 
  pinMode(0, INPUT); //Red Play-It! button input
  pinMode(1, INPUT); //Yellow Play-It! button input
  pinMode(A0, INPUT); //Green Play-It! button input

  //Initialize output pins:
  pinMode(2, OUTPUT); //Yellow Play-It! light output
  pinMode(5, OUTPUT); //Green Play-It! light output
  pinMode(6, OUTPUT); //Red Play-It! light output
  pinMode(7, OUTPUT); //Piezo buzzer output

  pinMode(A1, OUTPUT); //Correct input indication
  pinMode(A2, OUTPUT); //Incorrect input indication
}

//Repeating function:
void loop() {
  if(digitalRead(3) == HIGH){ //If the reset button is pressed (Pin 9):
    beginGame(); //Call the function to begin a new game
  }
}

//Function to display LCD text formatted correctly:
void displayLCDText(String text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
   //Could add more functionality here in order to center the displayed text, cause it to scroll, etc.
}

//Function that is called when the game is ended:
void endGame() {
  isFailed = true; //Set the isFailed variable to 1, indicating that the game has ended
  digitalWrite(2, LOW); //Set all LEDs in the Play-It! command OFF
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  displayLCDText("Score: " + String(playerScore)); //Display the current score at the end of the game
  for(int i = 0; i<3; i++) { //Have the failed LED and the score flash several times
    displayLCDText("Score: " + String(playerScore));
    digitalWrite(A2, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(A2, LOW);
    delay(1000);
  }
  displayLCDText("Game Over!");//Display a "Game Over!" message on the LCD screen
  delay(4000);
  lcd.clear();
}

//Function called when a new game has began:
void beginGame() {
  isFailed = 0; //The game has not ended yet
  lcd.clear(); //Clear any text that may be remaining on the LCD screen
  playerScore = 0; //Reset the player's score upon beginning each new game

  //Introductory message:
  displayLCDText("New Game!");
  delay(1000);
  displayLCDText("3");
  delay(1000);
  displayLCDText("2");
  delay(1000);
  displayLCDText("1");
  delay(1000);
  displayLCDText("GO!");
  delay(1000);
  
  while(!isFailed) {
    actionStartTime = millis(); //added time components
    int pickCommand = random(1, 4); //Enter a loop which randomly generates a command to tell the user:
    switch(pickCommand) { 
      case 1:
        singIt();
        break;
      case 2:
        whammyIt();
        break;
      case 3:
        playIt();
        break;
    }
    if(millis() - actionStartTime > actionDuration) {
      endGame();
    }
  }
}

//Play sound randomly after an action
void afterAction() {
    int sound = random(5, 10); 
    myDFPlayer.play(sound);
    delay(1000); 
}

//Check time to avoid auto GameOver :(
void checkTime() {
  if (millis() - actionStartTime > actionDuration) {
    endGame();
  }
}

//Function for "Sing-It!" command:
void singIt() {
  myDFPlayer.play(2); // Play the "singit" sound
  delay(1000); // Wait for the "Sing it!" sound to finish, adjust delay as needed based on the sound length
  myDFPlayer.pause(); // Pause the background music

  displayLCDText("Sing-It!");
  while(!isFailed) {
    checkTime();
    if(digitalRead(8) == HIGH) { //If input is read from the microphone, increment the score, flash the pass LED and move to the next command
      playerScore++;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      break;
    }

    if(digitalRead(3) == HIGH) { //If the reset button is pressed, the game is exited
      endGame();
      break;
    }
  }

  afterAction();  //play sound after the action sing it
}

void whammyIt() {
    myDFPlayer.play(3); // Play the "whammy it" sound
    displayLCDText("Whammy-It!"); //Display the command on the LCD screen
    int initialRead = analogRead(A3); //Initial analog reading of the potentiometer
    //tone(7, initialRead + 5); //Play an initial tone from the Piezo buzzer
    unsigned long startTime = millis(); //start timer

    while (millis() - startTime <= 7000) {
        int currentRead = analogRead(A3); //Play an initial tone from the Piezo buzzer
        if (abs(currentRead - initialRead) >= 200) { //If it is moved in either direction, the action is passed, score is incremented, and the new tone plays
            playerScore++;
            displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
            digitalWrite(A1, HIGH);
            delay(1000);
            lcd.clear();
            digitalWrite(A1, LOW);
            noTone(7);
            break;
        } else if (digitalRead(A0) == HIGH || digitalRead(0) == HIGH || digitalRead(1) == HIGH) { 
            noTone(7);
            endGame();
            return;
        }
    }

    if (millis() - startTime > 7000) {
        noTone(7);
        endGame();
    }
    afterAction(); 
}

void playIt() { //Display the command on the LCD screen
    myDFPlayer.play(4); // Play the "play it" sound
    displayLCDText("Play-It!");
    delay(1000);

    unsigned long startTime = millis();  //Start the timer for the action
    int buttonsPressed = 0;
    int prevButton = -1;  //Start with an impossible button value

    while (buttonsPressed < 3 && millis() - startTime <= 7000) {
        int buttonSequence = random(1, 4);
        if (buttonSequence == prevButton) {  //Avoid repeating the same button immediately
            continue;
        }

        prevButton = buttonSequence;

        //Turn off all LEDs first
        digitalWrite(2, LOW); //yellow LED off
        digitalWrite(5, LOW); //Green LED off
        digitalWrite(6, LOW); //Red LED off

        //Light up the corresponding LED
        if (buttonSequence == 1) digitalWrite(5, HIGH); //Green LED
        else if (buttonSequence == 2) digitalWrite(6, HIGH); //Red LED
        else if (buttonSequence == 3) digitalWrite(2, HIGH); //Yellow LED

        unsigned long actionStartTime = millis();
        bool buttonPressed = false;

        while (millis() - actionStartTime < 7000 && !buttonPressed) {
            if ((buttonSequence == 1 && digitalRead(A0) == HIGH) ||
                (buttonSequence == 2 && digitalRead(0) == HIGH) ||
                (buttonSequence == 3 && digitalRead(1) == HIGH)) {
                buttonsPressed++;
                buttonPressed = true;
                //tone(7, 440 + 54 * buttonSequence); // Play a different tone for each button
                delay(1000);
                noTone(7);
            }
        }

        // Turn off the LEDs after each button press or if the time for a single press exceeds
        digitalWrite(2, LOW); //yellow LED off
        digitalWrite(5, LOW); //Green LED off
        digitalWrite(6, LOW); //Red LED off
    }

    if (buttonsPressed == 3) {
        playerScore++;
        displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
        digitalWrite(A1, HIGH);
        delay(1000);
        lcd.clear();
        digitalWrite(A1, LOW);
    } else {
        endGame();
    }
    afterAction(); 
}

