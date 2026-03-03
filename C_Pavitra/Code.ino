#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myServo;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {A0,A1,A2,A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String correctPassword = "1415";
String enteredPassword = "";
int greenLED = 13;
int redLED = A4;
int buzzer = A5;
int attempts = 0;
void setup() {
  lcd.begin(16,2);
  lcd.print("Enter Password");
  myServo.attach(10);
  myServo.write(0);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  if(attempts >= 3){
    lcd.clear();
    lcd.print("System Locked!");
    delay(5000);
    attempts = 0;
    lcd.clear();
    lcd.print("Enter Password");
  }
  char key = keypad.getKey();
  if(key){
    enteredPassword += key;
    lcd.setCursor(0,1);
    lcd.print(enteredPassword);
  }
  if(enteredPassword.length() == 4){
    delay(300);
    lcd.clear();
    if(enteredPassword == correctPassword){
      lcd.print("Access Granted");
      digitalWrite(greenLED, HIGH);
      myServo.write(90);
      delay(3000);
      myServo.write(0);
      digitalWrite(greenLED, LOW);
      attempts = 0;
    }
    else{
      lcd.print("Access Denied");
      digitalWrite(redLED, HIGH);
      tone(buzzer, 1000);
      delay(2000);
      noTone(buzzer);
      digitalWrite(redLED, LOW);
      attempts++;
    }
    enteredPassword = "";
    delay(1000);
    lcd.clear();
    lcd.print("Enter Password");
  }
}
