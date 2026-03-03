#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234"; 
String input = "";

int servoPin = 10;
int buzzer = 11;

void setup() {
  myServo.attach(servoPin);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  myServo.write(0);  // Locked position
  lcd.setCursor(0,0);
  lcd.print("Enter Password");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.setCursor(input.length(), 1);
    lcd.print("*");
    input += key;

    if (input.length() == 4) {
      delay(300);

      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        tone(buzzer, 1000, 200);

        myServo.write(90);  
        delay(3000);

        myServo.write(0); 
      } 
      else {
        lcd.clear();
        lcd.print("Wrong Password");
        tone(buzzer, 500, 500);
        delay(2000);
      }

      input = "";
      lcd.clear();
      lcd.print("Enter Password");
    }
  }
}
