#define buttonPin 2
#define greenPedestrianLed 4
#define redPedestrianLed 5
#define greenLed 8
#define yellowLed 9
#define redLed 10 
#define buzzerPin 11

// States
int programState = 1;

bool buttonState;
bool lastButtonState = HIGH;

bool greenPedestrianLedState;
bool redPedestrianLedState;
bool greenLedState;
bool yellowLedState;
bool redLedState;

// Variables
bool reading;
unsigned long lastDebounceTime = 0;
int debounceDelay = 50;

unsigned long programOneTrigger;
unsigned long programTwoTrigger;
unsigned long programThreeTrigger;

// Configs
int delayFirstSecondProgram = 10000;
int secondProgramDuration = 3000;
int thirdProgramDuration = 10000;
int fourthProgramDuration = 5000;

int beepingIntervalProgramThree = 500;
int beepingIntensity = 1000;
int beepingIntervalProgramFour = 250;
int blinkingInterval = 250;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenPedestrianLed, OUTPUT);
  pinMode(redPedestrianLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(buttonPin);
  if (lastButtonState != reading) {
    lastDebounceTime = millis();
  }
  // if the button was in a state for more than debounceDelay
  if (millis() - lastDebounceTime > debounceDelay) {
      if (reading != buttonState) {
          buttonState = reading;
          // if the button was pressed (on pressdown), HIGH implies releasing the button
          if (buttonState == LOW && programState == 1) {
              programState = 2;
              programOneTrigger = millis();
          }
      }
  }
  lastButtonState = reading;

  greenPedestrianLedState = LOW;
  redPedestrianLedState = LOW;
  greenLedState = LOW;
  yellowLedState = LOW;
  redLedState = LOW;
  
  if (programState == 1) {
    greenLedState = HIGH;
    redPedestrianLedState = HIGH;
    lightLeds(greenPedestrianLed, greenPedestrianLedState, 
              redPedestrianLed, redPedestrianLedState, 
              greenLed, greenLedState, 
              yellowLed, yellowLedState, 
              redLed, redLedState);
  }

  if (programState == 2) {
    // We execute the three stages of the program's second state (wait x seconds, execute for y seconds and then move on at x+y seconds)
    if (millis() - programOneTrigger > delayFirstSecondProgram + secondProgramDuration) {
      programState = 3;
      programTwoTrigger = millis();
    } else if (millis() - programOneTrigger > delayFirstSecondProgram) {
      yellowLedState = HIGH;
      redPedestrianLedState = HIGH;
    } else {
      greenLedState = HIGH;
      redPedestrianLedState = HIGH;
    }
    lightLeds(greenPedestrianLed, greenPedestrianLedState, 
              redPedestrianLed, redPedestrianLedState, 
              greenLed, greenLedState, 
              yellowLed, yellowLedState, 
              redLed, redLedState);
  }

  if (programState == 3) {
    if (millis() - programTwoTrigger > thirdProgramDuration) {
      programState = 4;
      programThreeTrigger = millis();
      noTone(buzzerPin);
    } else {
      redLedState = HIGH;
      greenPedestrianLedState = HIGH;
      intervalBeeping(buzzerPin, beepingIntensity, beepingIntervalProgramThree);
    } 
    lightLeds(greenPedestrianLed, greenPedestrianLedState, 
              redPedestrianLed, redPedestrianLedState, 
              greenLed, greenLedState, 
              yellowLed, yellowLedState, 
              redLed, redLedState);
  }

  if (programState == 4) {
    if (millis() - programThreeTrigger > fourthProgramDuration) {
      programState = 1;
      noTone(buzzerPin);
    } else {
      redLedState = HIGH;
      lightLeds(greenPedestrianLed, greenPedestrianLedState, 
              redPedestrianLed, redPedestrianLedState, 
              greenLed, greenLedState, 
              yellowLed, yellowLedState, 
              redLed, redLedState);
      intervalBlinking(greenPedestrianLed, blinkingInterval);
      intervalBeeping(buzzerPin, beepingIntensity, beepingIntervalProgramFour);
    }
  }

  Serial.print("Current program: ");
  Serial.println(programState);
  
}

void intervalBeeping(int pin, int intensity, int interval) {
  // makes the buzzer beep
  if (millis() % interval < (interval / 2)) {
    tone(pin, intensity);
  } else {
    noTone(pin);
  }
}

void intervalBlinking(int pin, int interval) {
  // makes the led at pin to blink
  int ledState = HIGH;
  if (millis() % interval < (interval / 2)) {
    digitalWrite(pin, ledState);
  } else {
    digitalWrite(pin, !ledState);
  }
}

void lightLeds(int led1, int state1, int led2, int state2, int led3, int state3, int led4, int state4, int led5, int state5) {
  digitalWrite(led1, state1);
  digitalWrite(led2, state2);
  digitalWrite(led3, state3);
  digitalWrite(led4, state4);
  digitalWrite(led5, state5);
}
