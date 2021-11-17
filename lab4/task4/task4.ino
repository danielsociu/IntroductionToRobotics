#include <EEPROM.h>

const int displayCount = 4;
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int pinSw = 2;
const int pinX = A0;
const int pinY = A1;

const int dataPin = 12; // DS
const int latchPin = 11; //STCP = STorage Clock Pin latch
const int clockPin = 10; // SHCP = SHift register Clock Pin (clock)

const int numberStates = 2;
volatile unsigned long lastButtonTime = 0;
volatile int state = 0; // current state
const int joystickThreshold = 100;
const int defaultJoystick = 512;
bool joyXMoved = false;
bool joyYMoved = false;
int xValue = 512;
int yValue = 512;

const int buttonTimer = 150; // Timer till considers repressing of button
int dpBlinkTimer = 300; 
int currentDisplay = 0;
int maxDigit = 10;

int displayDigits[4] = {
  segD1, segD2, segD3, segD4
};

// current number displayed
int displayDigitsValues[4] = {
  0, 0, 0, 0
};

int registers[8];

bool dpArray[4][4] = {
  {1, 0, 0 , 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

int digitArray[16] = {
  //A B C D E F G DP
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

void writeReg(int digit)
{
  // Writes the digit to the display (more exactly we write to the 74hc595 memory that changes the current digit display segment)
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void showDigit(int displayNumber) {
  // Shows one digit at a time multiplexing
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int digits[], bool *dp)
{
  // Writes the whole number
  int displayDigit = 0;
  int digit;

  for (int displayDigit = 0; displayDigit < displayCount; displayDigit++) {
    digit = digitArray[digits[displayDigit]];
    if (dp != nullptr) {
      digit += dp[displayDigit];
    }
    showDigit(displayDigit);
    delay(5);
    writeReg(digit);
  }
}

void updateJoystick (int joyPin, int& updatedValue, bool& joyMoved, int maxValue) {
  // Checks if there are any changes to the joystick
  int jValue = analogRead(joyPin);
  if (abs (defaultJoystick - jValue) > joystickThreshold && joyMoved == false) {
    if (jValue > defaultJoystick) {
      updatedValue = (updatedValue + 1) % maxValue;
    } else {
      updatedValue -= 1;
      if (updatedValue < 0) {
        updatedValue = maxValue - 1;
      }
    }
    joyMoved = true;
  }
}

void stateSwapISR() {
  // The ISR function for the joystick button
  unsigned long buttonTime = millis();
  if (buttonTime - lastButtonTime > buttonTimer) {
    state = (state + 1) % numberStates;
    lastButtonTime = millis();
  }
}

void checkDisplayDigitsValues() {
  // Checks the EEPROM for the number stored
  for(int i = 0; i < displayCount; i++) {
    int readValue = EEPROM.read(i);
    if (readValue < 10) {
      displayDigitsValues[i] = readValue;
    }
  }
}

void writeDisplayDigitsValues() {
  // Stores the number in the EEPROM
  for (int i = 0; i < displayCount; i++) {
    EEPROM.update(i, displayDigitsValues[i]);
  }
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
  }
  Serial.begin(9600);
  checkDisplayDigitsValues();
  attachInterrupt(digitalPinToInterrupt(pinSw), stateSwapISR, LOW);
}

void loop() {
  bool *currentDp = nullptr;

  if (state == 0) {
    updateJoystick(pinX, currentDisplay, joyXMoved, displayCount);
    if (millis() % (2 * dpBlinkTimer) < dpBlinkTimer) {
      currentDp = dpArray[currentDisplay];
    }
  }

  if (state == 1) {
    updateJoystick(pinY, displayDigitsValues[currentDisplay], joyYMoved, maxDigit);
    currentDp = dpArray[currentDisplay];
  }

  // Resetting the joystick if it's released
  int valueX = analogRead(pinX);
  int valueY = analogRead(pinY);
  if (abs (valueX - defaultJoystick) < joystickThreshold && joyXMoved == true) {
    joyXMoved = false;
  }
  if (abs (valueY - defaultJoystick) < joystickThreshold && joyYMoved == true) {
    joyYMoved = false;
  }
  writeNumber(displayDigitsValues, currentDp);
  // Saves the number to EEPROM
  writeDisplayDigitsValues();
}
