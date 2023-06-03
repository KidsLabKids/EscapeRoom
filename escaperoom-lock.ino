// Include Arduino Wire library for I2C
#include <Wire.h>
// Include Keypad library
#include <Keypad.h>
 
// Length of password + 1 for null character
#define Password_Length 5
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "1827";

 
// Pin connected to lock relay input
int lockOutput = A0;
int ledgruen = A4;
int ledrot = A3;
 
// Counter for character entries
byte data_count = 0;
 
// Character to hold key input
char customKey;
 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 3;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
void setup() {
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);
  pinMode(ledgruen, OUTPUT);
  pinMode(ledrot, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledrot, HIGH);
  digitalWrite(lockOutput, HIGH);
}
 
void loop() {
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    data_count++;
    Serial.println(customKey);
  }
 
  // See if we have reached the password length
  if (data_count == Password_Length - 1) { 
    if (!strcmp(Data, Master)) {
      Serial.println("Richtig");
      // Password is correct
      digitalWrite(ledrot, LOW);
      digitalWrite(ledgruen, HIGH);
      delay(1000);
      // Turn off relay for 5 seconds
      digitalWrite(lockOutput, LOW);
      delay(5000);
      digitalWrite(lockOutput, HIGH);
      digitalWrite(ledrot, HIGH);
      digitalWrite(ledgruen, LOW);
    }
    else {
      Serial.println("Falsch");
      // Password is incorrect
      delay(1000);
    }
    // Clear data and LCD display
    clearData();
  }
}
 
void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}