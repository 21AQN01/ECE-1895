//Bop-It: Final
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Initialize the LCD screen
int playerScore = 0; //Variable to keep track of the user's score
bool isFailed = 0; //State to determine whether or not the player has successfully completed an action

//CODE DOES NOT YET INCLUDE:
//Incorrect input resulting in a failure
//Time running out resulting in a failure
//Debouncing

void setup() {
  //Initialize random number seed:
  randomSeed(analogRead(0));
  //Initialize LCD screen:
  lcd.init();
  lcd.backlight();

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
void displayLCDText(String text){
  lcd.clear(); //
  lcd.setCursor(0, 0);
  lcd.print(text);
  //Could add more functionality here in order to center the displayed text, cause it to scroll, etc.
}

//Function that is called when the game is ended:
void endGame(){
  isFailed = 1; //Set the isFailed variable to 1, indicating that the game has ended
  digitalWrite(2, LOW); //Set all LEDs in the Play-It! command OFF
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  displayLCDText("Score: " + String(playerScore)); //Display the current score at the end of the game
  for(int i=0; i<3; i++){ //Have the failed LED and the score flash several times
    displayLCDText("Score: " + String(playerScore));
    digitalWrite(A2, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(A2, LOW);
    delay(1000);
  }
  displayLCDText("Game Over!"); //Display a "Game Over!" message on the LCD screen
  delay(4000);
  lcd.clear();
}

//Function called when a new game has began:
void beginGame(){
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
  displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
  while(isFailed == 0){ //Enter a loop which randomly generates a command to tell the user:
    int pickCommand = random(4);
    if(pickCommand == 1){
      singIt();
    }
    else if(pickCommand == 2){
      whammyIt();
    }
    else if(pickCommand == 3){
      playIt();
    }
  }
}

//Function for "Sing-It!" command:
void singIt(){
  displayLCDText("Sing-It!"); //Display the command on the LCD screen
  while(1){ //Enter a loop while waiting for input
    if(digitalRead(8) == HIGH){ //If input is read from the microphone, increment the score, flash the pass LED and move to the next command
      playerScore+=1;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      break;
    }

    if(digitalRead(3) == HIGH){ //If the reset button is pressed, the game is exited
      endGame();
      break;
    }
  }
  //Must incorporate timer componant
}

void whammyIt(){
  displayLCDText("Whammy-It!"); //Display the command on the LCD screen
  int initialRead = analogRead(A3); //Initial analog reading of the potentiometer
  int voltageDiff = initialRead + 5; //Initial tone of the Piezo buzzer
  tone(7, voltageDiff); //Play an initial tone from the Piezo buzzer
  delay(500);

  while(1){
    int currentRead = analogRead(A3); //Wait for the potentiometer's value to be changed significantly
    if((currentRead - initialRead) >= 200){ //If it is moved in either direction, the action is passed, score is incremented, and the new tone plays
      voltageDiff += (currentRead - initialRead);
      tone(7, voltageDiff);

      playerScore += 1;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      noTone(7);
      break;
    }
    else if((initialRead - currentRead >= 200)){ //Here so the potentiometer could be turned either way
      voltageDiff += (initialRead - currentRead);
      tone(7, voltageDiff);
      
      playerScore += 1;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      noTone(7);
      break;
    }

    if(digitalRead(3) == HIGH){ //Reset button is pressed and game has ended
      noTone(7);
      endGame();
      break;
    }
  }
  //Must incorporate timer componant
}

void playIt(){  //Display the command on the LCD screen
  displayLCDText("Play-It!");
  delay(1000);
  int exitFlag = 0;
  int buttonsPressed = 0;
  int prevButton = 0;
  
  while(1){
    int buttonSequence = random(4);
    if(buttonSequence == 1){
      if(prevButton == 1){
        continue;
      }
      prevButton = 1;
      digitalWrite(5, HIGH);
      while(1){
        if(digitalRead(A0) == HIGH){
          buttonsPressed += 1;
          digitalWrite(5, LOW);
          tone(7, 440);
          delay(1000);
          noTone(7);
          break;
        }

        if(digitalRead(3) == HIGH){
          endGame();
          exitFlag = 1;
          break;
        }
      }
    }
    else if(buttonSequence == 2){
      if(prevButton == 2){
        continue;
      }
      prevButton = 2;
      digitalWrite(6, HIGH);
      while(1){
        if(digitalRead(0) == HIGH){
          buttonsPressed += 1;
          digitalWrite(6, LOW);
          tone(7, 494);
          delay(1000);
          noTone(7);
          break;
        }

        if(digitalRead(3) == HIGH){
          endGame();
          exitFlag = 1;
          break;
        }
      }
    }
    else if(buttonSequence == 3){
      if(prevButton == 3){
        continue;
      }
      prevButton = 3;
      digitalWrite(2, HIGH);
      while(1){
        if(digitalRead(1) == HIGH){
          buttonsPressed += 1;
          digitalWrite(2, LOW);
          tone(7, 523);
          delay(1000);
          noTone(7);
          break;
        }

        if(digitalRead(3) == HIGH){
          endGame();
          exitFlag = 1;
          break;
        }
      }
    }

    if(exitFlag ==1){
      break;
    }
    if(buttonsPressed == 3){
      playerScore+=1;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      break;
    }
    //Must incorporate timer componant
  }
}
