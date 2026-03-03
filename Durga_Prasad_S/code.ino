#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address 0x27 (most common)
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo lockServo;
int servoPin = 10;
int buzzerPin = 11;

// Password
String password = "1234";
String inputPassword = "";

// Keypad setup
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

void setup() {
  lcd.init();
  lcd.backlight();

  lockServo.attach(servoPin);
  lockServo.write(0);   // Door locked position

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Door Locked");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);

    if (key == '#') {   // Enter key
      checkPassword();
    }
    else if (key == '*') {  // Clear key
      inputPassword = "";
      lcd.clear();
      lcd.print("Cleared");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Password");
    }
    else {
      inputPassword += key;
      lcd.setCursor(0, 1);
      lcd.print(inputPassword);
    }
  }
}

void checkPassword() {
  lcd.clear();

  if (inputPassword == password) {
    lcd.print("Access Granted");
    lockServo.write(90);   // Unlock door
    delay(3000);
    lockServo.write(0);    // Lock again
  }
  else {
    lcd.print("Wrong Password");
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
      delay(200);
    }
  }

  inputPassword = "";
  delay(2000);
  lcd.clear();
  lcd.print("Enter Password");
}
