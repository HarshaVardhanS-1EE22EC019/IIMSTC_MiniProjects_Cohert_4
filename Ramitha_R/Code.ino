#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;
int servoPin = 10;   
int buzzer = 11;   
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
String correctPassword = "0004";
String enteredPassword = "0123";
void setup() {
  lcd.init();
  lcd.backlight();
  myServo.attach(servoPin);
  pinMode(buzzer, OUTPUT);
  myServo.write(0);   
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {  
      if (enteredPassword == correctPassword) {
        lcd.clear();
        lcd.print("Access Granted");
        tone(buzzer, 1000, 200);
        delay(300);
        myServo.write(90);   
        delay(3000);
        myServo.write(0);    
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        tone(buzzer, 300, 500);
        delay(1000);
      }
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key == '*') {  
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {
      enteredPassword += key;
      lcd.setCursor(0,1);
      lcd.print(enteredPassword);
    }
  }
}
