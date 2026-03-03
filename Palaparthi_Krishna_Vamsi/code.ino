#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define PASSWORD "1234"

Servo servo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0,1,2,3};
byte colPins[COLS] = {4,5,6,7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputPassword = "";

void setup() {
  servo.attach(9);
  servo.write(0); 

  lcd.begin(16,2);
  lcd.print("Enter Password");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.setCursor(inputPassword.length(),1);
    lcd.print("*");   
    inputPassword += key;
  }

  if (inputPassword.length() == 4) {
    
    if (inputPassword == PASSWORD) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Access Granted");
      lcd.setCursor(0,1);
      lcd.print("Welcome ");   
      
      servo.write(90);   
      delay(5000);
      servo.write(0);    
    } 
    else {
      lcd.clear();
      lcd.print("Wrong Password");
      delay(2000);
    }

    inputPassword = "";
    lcd.clear();
    lcd.print("Enter Password");
  }
}