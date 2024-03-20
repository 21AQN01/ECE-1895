//Bop-It: Final
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int playerScore = 0;
bool isFailed = 0; //State to determine whether or not the player has successfully completed an action

//Code does not yet include:
//-Incorrect input resulting in a failure
//-Time running out resulting in a failure

void setup() {
  //Initialize random number seed:
  randomSeed(analogRead(0));
  //Initialize LCD screen:
  lcd.init();
  lcd.backlight();

  //Initialize input pins:
  pinMode(8, INPUT); //Pin for reading digital microphone input
  pinMode(9, INPUT); //Pin for beginning a new game
  pinMode(A0, INPUT); //Pin for ending a game

  pinMode(0, INPUT); //Red Play-It! button input
  pinMode(1, INPUT); //Yellow Play-It! button input
  pinMode(10, INPUT); //Green Play-It! button input

  //Initialize output pins:
  pinMode(2, OUTPUT); //Yellow Play-It! light output
  pinMode(5, OUTPUT); //Green Play-It! light output
  pinMode(6, OUTPUT); //Red Play-It! light output
  pinMode(7, OUTPUT); //Piezo buzzer output

  pinMode(A1, OUTPUT); //Correct input indication
  pinMode(A2, OUTPUT); //Incorrect input indication
}

void loop() {
  if(digitalRead(9) == HIGH){ //If the reset button is pressed (Pin #9):
    beginGame(); //Call the function to begin a new game
  }
}

void displayLCDText(String text){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
  //Could add more functionality here in order to center the displayed text, cause it to scroll, etc.
}

void endGame(){
  isFailed = 1;
  digitalWrite(2, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  displayLCDText("Score: " + String(playerScore));
  for(int i=0; i<3; i++){
    displayLCDText("Score: " + String(playerScore));
    digitalWrite(A2, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(A2, LOW);
    delay(1000);
  }
  displayLCDText("Game Over!");
  delay(4000);
  lcd.clear();
}

void beginGame(){
  isFailed = 0;
  lcd.clear();
  playerScore = 0; //Reset the player's score upon beginning each new game

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
  //Above line should be used after any change to the score is made, or the game has finished
  while(isFailed == 0){
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

void singIt(){
  displayLCDText("Sing-It!");
  while(1){
    if(digitalRead(8) == HIGH){
      playerScore+=1;
      displayLCDText("Score: " + String(playerScore)); //Line to display the current score of the player
      digitalWrite(A1, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(A1, LOW);
      break;
    }

    if(digitalRead(9) == HIGH  || digitalRead(0) == HIGH || digitalRead(1) == HIGH || digitalRead(10) == HIGH){
      endGame();
      break;
    }
  }
  //Must incorporate timer componant
}

void whammyIt(){
  displayLCDText("Whammy-It!");
  int initialRead = analogRead(A3); //Initial analog reading of the potentiometer
  int voltageDiff = initialRead + 5; //Initial tone of the piezo buzzer
  tone(7, voltageDiff);
  delay(500);

  while(1){
    int currentRead = analogRead(A3);
    if((currentRead - initialRead) >= 200){
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
    else if((initialRead - currentRead >= 200)){
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

    if(digitalRead(9) == HIGH || digitalRead(0) == HIGH || digitalRead(1) == HIGH || digitalRead(10) == HIGH){
      noTone(7);
      endGame();
      break;
    }
  }
  //Must incorporate timer componant
}

void playIt(){
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
        if(digitalRead(10) == HIGH){
          buttonsPressed += 1;
          digitalWrite(5, LOW);
          tone(7, 440);
          delay(1000);
          noTone(7);
          break;
        }

        if(digitalRead(9) == HIGH){
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

        if(digitalRead(9) == HIGH){
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

        if(digitalRead(9) == HIGH){
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
