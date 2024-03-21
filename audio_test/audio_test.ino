#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(9, 10); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  pinMode(3, INPUT);
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.setTimeOut(5000);
  

  delay(200);
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  delay(200);
}

void loop()
{
  if (digitalRead(3) == HIGH) { // has pullup so LOW read is pushed
    delay(200);
    myDFPlayer.play(1); // play track one on dfplayer
}
}