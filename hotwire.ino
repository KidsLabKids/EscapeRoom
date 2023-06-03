#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int sensor = A1;
int start = A0;
int ziel = A2;
bool hotwire = false;
int buzzer = 11;

void setup() 
{
    lcd.begin(16, 2);
    lcd.setPWM(REG_BLUE, 0);
    lcd.setPWM(REG_GREEN, 255);
    lcd.setPWM(REG_RED, 255);
    lcd.print(" Heisser Draht! ");
    lcd.setPWM(REG_BLUE, 0);
    lcd.setCursor(0, 1);
    lcd.print("Bitte auf Start");
}

void fadeout(unsigned char color)
{

    for(int i=0; i<255; i++)
    {
        lcd.setPWM(color, i);
        delay(5);
    }

    delay(500);
}

void fadein(unsigned char color)
{
   for(int i=254; i>=0; i--)
   {
       lcd.setPWM(color, i);
       delay(3);
   }

    delay(500);
}

void loop() {
    int sensorValue = analogRead(sensor);
    int startValue = analogRead(start);
    int zielValue = analogRead(ziel);
    //lcd.clear();
    //lcd.print("St: ");
    //lcd.print(startValue);
    //lcd.print("ZL: ");
    //lcd.print(zielValue);
    //lcd.print("Se: ");
    //lcd.print(sensorValue);
    //breath(REG_RED);
    //reath(REG_GREEN);
    if (sensorValue > 10) {
      hotwire = false;
      lcd.setPWM(REG_BLUE, 0);
      lcd.setPWM(REG_GREEN, 0);
      lcd.setPWM(REG_RED, 255);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Erwischt!");
      lcd.setCursor(0, 1);
      lcd.print("Zur");
      lcd.print("\xF5");
      lcd.print("ck zum Start");
      digitalWrite(buzzer, HIGH);   // turn the LED off by making the voltage LOW
      delay(200);
      digitalWrite(buzzer, LOW);   // turn the LED off by making the voltage LOW

    }
    if (startValue > 10) {
      hotwire = true;
      lcd.setPWM(REG_BLUE, 255);
      lcd.setPWM(REG_GREEN, 0);
      lcd.setPWM(REG_RED, 0);
      lcd.clear();
      lcd.print("   Los gehts!");
    }
    if (zielValue > 10) {
      if (hotwire == true) {
        lcd.setPWM(REG_BLUE, 0);
        lcd.setPWM(REG_GREEN, 255);
        lcd.setPWM(REG_RED, 0);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ziel! Naechster");
        lcd.setCursor(0, 1);
        lcd.print("Tipp: Katzenbild");
        delay(20000);
      } else {

      }
    }
    delay(100);

}