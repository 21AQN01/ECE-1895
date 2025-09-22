### This project was created by Yun Dong, Anh Nguyen, and Lillian Jones.
# Tune-It! / Bop-It Guitar

**Tune-It!** is a rhythm-based interactive game inspired by Guitar Hero, designed to test players’ reflexes, timing, and accuracy. Players follow game prompts using physical inputs like buttons, a whammy bar, and a microphone, while receiving visual and audio feedback.

<img width="563" height="750" alt="image" src="https://github.com/user-attachments/assets/ef62361b-3b82-4c63-9cea-3af120181a73" />

---

## Features

- **Game Inputs**
  - Play-It: Press one of three colored buttons corresponding to LED signals.  
  - Whammy-It: Move a potentiometer (whammy bar) up or down.  
  - Sing-It: Vocal input via a microphone; measures volume to register success.  

- **Outputs**
  - 16x2 LCD displays commands and score.  
  - LED indicators: Green = correct input, Red = incorrect/slow response.  
  - Piezo buzzer: Audio feedback for actions and successes.  

- **Start/Reset button** for easy game control.  
- Score tracking with real-time feedback.

---

## How It Works

1. Press the start/reset button to begin a new game.  
2. Countdown appears on the LCD: `3 → 2 → 1 → GO!`.  
3. Random commands appear: `Sing-It!`, `Whammy-It!`, `Play-It!`.  
4. Correct input increments score and flashes the green LED.  
5. Game continues with new commands until the reset button is pressed.  
6. Final score displayed with a "Game Over!" message.

---

## Hardware Setup

| Component | Pin |
|-----------|-----|
| Microphone | 8 (digital input) |
| Reset Button | 3 (digital input) |
| Red Button | 0 (digital input) |
| Yellow Button | 1 (digital input) |
| Green Button | A0 (digital input) |
| Red LED | 6 (output) |
| Yellow LED | 2 (output) |
| Green LED | 5 (output) |
| Correct Indicator LED | A1 (output) |
| Incorrect Indicator LED | A2 (output) |
| Piezo Buzzer | 7 (output) |
| Potentiometer | A3 (analog input) |
| LCD Display | I2C 0x27, 16x2 |

---

## CAD & Enclosure

The guitar enclosure was designed in CAD and fabricated using a combination of **3D printing** and **laser cutting**:

- Body & Neck: Modeled after a real guitar and 3D printed.  
- Head: Generic design, 3D printed.  
- Top & Bottom Plates: Laser cut for precision.  
- Took multiple days to design and 1 day to print all components.  
- Enclosure ensures proper fitting and accessibility for buttons, LEDs, and LCD.
<img width="436" height="521" alt="image" src="https://github.com/user-attachments/assets/708e9c2a-29e3-4998-987d-fcf97b9601d3" />
<img width="975" height="583" alt="image" src="https://github.com/user-attachments/assets/accef6bf-a397-40b6-b74a-fa1b2caa6290" />
<img width="756" height="601" alt="image" src="https://github.com/user-attachments/assets/602462de-63e0-4d1d-8a9b-a75b704b5e24" />

---

## PCB Design

### First PCB
- Designed based on an initial schematic with potentiometer, buttons, LEDs.  
- Issues: Surface mount headers for LCD and power made soldering difficult; first board was not fully functional.
<img width="586" height="427" alt="image" src="https://github.com/user-attachments/assets/3bf7f2d5-35a1-4bd1-87ad-fc937eac35f8" />
<img width="563" height="403" alt="image" src="https://github.com/user-attachments/assets/700de179-2d95-4e0c-bcf7-fa1cce713ea9" />

### Second PCB
- Designed using Altium, referencing the breadboard prototype.  
- Short, direct traces for reliability; correct mapping to the ATmega microcontroller.  
- Fully functional, verified connections, and successfully integrated with game inputs/outputs.
<img width="975" height="723" alt="image" src="https://github.com/user-attachments/assets/aaf91e59-d65f-4a88-91d0-afeb102b99cf" />
<img width="481" height="420" alt="image" src="https://github.com/user-attachments/assets/828920f8-9597-44e5-95c1-40e37811a65c" />

---

## Development Process

1. Conceptualization: Brainstormed ways to replicate Guitar Hero in a standalone device.  
2. Prototyping: Breadboard used to test buttons, LEDs, potentiometer, microphone, and code.  
3. PCB & Enclosure: Designed PCBs and CAD models; iterated to resolve hardware issues.  
4. Integration & Testing: Verified all components worked together; fine-tuned game mechanics.  
<img width="622" height="1090" alt="image" src="https://github.com/user-attachments/assets/4163d427-7c2f-4991-b88e-c8c1d8fc8cb1" />

---

## Testing & Verification

- Breadboard tests confirmed correct functionality of all inputs and outputs.  
- LCD, LEDs, and piezo buzzer feedback verified for accuracy and timing.  
- PCB V2 successfully implemented all game features.  
- Enclosure tested for fit and accessibility; buttons, switches, and LCD properly aligned.  
- DFPlayer Mini was not fully functional in the first iteration, but core game mechanics were successfully implemented.

---

## Budget and Cost Analysis

| Item | Quantity (per board) | Unit cost ($) | Cost for 10,000 ($) |
|------|--------------------|---------------|-------------------|
| PCB Manufacturing | 1 | 0.50 | 5,006 |
| PCB Assembly | 1 | 1.15 | 11,515.95 |
| ATmega328P-PU | 1 | 2.89 | 28,900 |
| Buttons | 3 | 0.50 | 5,000 |
| 22 pF Capacitors | 2 | 1.81*2 = 3.62 | 36,200 |
| 10 uF Capacitor | 1 | 0.42 | 4,200 |
| Voltage Regulator (5V) | 1 | 0.60 | 6,000 |
| 9V Battery Connector | 1 | 0.42 | 4,200 |
| Switch | 1 | 0.87 | 8,700 |
| LEDs | 6 | 0.18*6 = 1.08 | 10,800 |
| Crystal Oscillator | 1 | 0.44 | 4,400 |
| Speaker | 1 | 3.99 | 39,900 |
| Buzzer | 1 | 0.58 | 5,800 |
| Jumper wires | 1 (30 bulk) | 2.10 | 21,000 |
| Enclosure | 1 | 5 | 50,000 |
| 10k Resistors | 6 | 0.1*6 = 0.6 | 6,000 |
| 100k Resistors | 2 | 0.17*2 = 0.34 | 3,400 |

**Total to produce 10,000 units:** $248,021.95  

---

## Links to Videos

- Testing breadboard (working without timing but with sounds): [YouTube](https://youtube.com/shorts/ZvjabpFPRp4?si=z9kmK86fL2h-j8cQ)  
- Fully functional breadboard (with timing but without sounds): [YouTube](https://youtube.com/shorts/_fQz-6a7OFs?si=PFWReO9ZfohJncGU)  
- Working project Success states: [YouTube](https://www.youtube.com/watch?v=ZkiNbDorZsc)  
- Working project Failure states: [YouTube](https://www.youtube.com/watch?v=272fVPoI4m8)  

---

## Built With

- Arduino IDE / C++  
- LiquidCrystal_I2C library  
- Altium PCB design  
- 3D CAD software & laser cutting  
- Standard Arduino components (LEDs, buttons, potentiometer, microphone, piezo buzzer)  

---

## How to Play

1. Connect all components according to the hardware table above.  
2. Upload `bopit_final.ino` to an Arduino board.  
3. Press **start/reset** to begin the game.  
4. Follow LCD prompts and respond using buttons, potentiometer, or microphone.  
5. Score points and enjoy!
