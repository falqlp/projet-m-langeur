#include <SPI.h>
#include <LiquidCrystal_74HC595.h>
#include <EEPROM.h>
#include <Adafruit_MotorShield.h>
#include "pump-control.h"
#include "keyboard.h"
#include <Keypad.h>
#include "screen.h"

#define DS 11
#define SHCP 13
#define STCP 12
#define RS 1
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal_74HC595 lcd(DS, SHCP, STCP, RS, E, D4, D5, D6, D7);

const int prog[5][3] = {{0, 1, 2},
{3, 4, 5},
{6, 7, 8},
{9, 10, 11},
{12, 13, 14}};

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *redPump = AFMS.getMotor(1);
Adafruit_DCMotor *greenPump = AFMS.getMotor(2);
Adafruit_DCMotor *bluePump = AFMS.getMotor(3);

const byte ROWS = 4; // quatre lignes
const byte COLS = 4; // quatre colonnes

char keys[ROWS][COLS] = {
  {'1','2','3','F'},
  {'4','5','6','E'},
  {'7','8','9','D'},
  {'A','0','B','C'}
};

// Connecter les broches des lignes du clavier aux broches numériques de l'Arduino
byte rowPins[ROWS] = {5, 4, 3, 2}; 
// Connecter les broches des colonnes du clavier aux broches numériques de l'Arduino
byte colPins[COLS] = {9, 8, 7, 6}; 

// Initialiser la bibliothèque Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char oldChar = "";
boolean editMode = false;


 
void setup() {
  Serial.begin(9600);
  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  updateDisplay();
}
 
void loop() {
  char input = getNewInput(keypad.getKey(), oldChar);
  if(input){
    if(editMode){
      handleEditModeInput(input);
    }else{
      handleNotEditModeInput(input);
    }
    updateDisplay();
  }
  delay(50);
}

void updateDisplay() {
  display(lcd, editMode);
}

void handleNotEditModeInput(char key) {
    switch (key) {
      case 'A':
        launchProg(prog[0], redPump, greenPump, bluePump);
        break;
      case 'B':
        launchProg(prog[1],  redPump,  greenPump,  bluePump);
        break;
      case 'C':
        launchProg(prog[2],  redPump,  greenPump,  bluePump);
        break;
      case 'D':
        launchProg(prog[3],  redPump,  greenPump,  bluePump);
        break;
      case 'E':
        launchProg(prog[4],  redPump,  greenPump,  bluePump);
        break;
      case 'F':
        editMode = true;
        break;
      default:
        Serial.println(key);
        break;
    }
}

void handleEditModeInput(char key) {
    switch (key) {
      case 'A':
        editProgram(prog[0]);
        break;
      case 'B':
        editProgram(prog[1]);
        break;
      case 'C':
        editProgram(prog[2]);
        break;
      case 'D':
        editProgram(prog[3]);
        break;
      case 'E':
        editProgram(prog[4]);
        break;
      case 'F':
      default:
        editMode = false;
        break;
    }
}

void editProgram(int program[3]){
  String values = getValues();
  Serial.println(program[0]);
  for (int i = 0; i < 3; i++) {
    EEPROM.put(program[i], values.substring(i * 2, (i * 2) + 2).toInt());
  }
  updateDisplay();
}

String getValues() {
  String values = "";
  displayEditModeSelectedProgram(values);
  while (values.length() < 6) {
    char input = getNewInput(keypad.getKey(), oldChar);
    if (input) {
      if (isDigit(input)) {
        values += input;
        displayEditModeSelectedProgram(values);
      } else {
        return;
      }
    }
    delay(50);
  }
  return values;
}