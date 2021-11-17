#define pinA 2
#define pinB 3
#define pinC 4
#define pinD 5
#define pinE 6
#define pinF 7
#define pinG 8
#define pinDP 9
#define segSize 8
#define pinBuzzer 10

#define maxReadings 20

const int antennaPin = A5; // the pin of the antenna
int readingLimit = 300; // the limit for reading from the analog antenna
int val = 0; // value read from the antenna

int readings[maxReadings]; // readings from which we make an average
int index = 0;
int total = 0; // total sum of readings
int average = 0;
int number = 0;

const int noOfDigits = 10;
int dpState = 0;

int aux = 0;

int segments[segSize] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP };

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};


void displayNumber(byte digit, byte decimalPoint) {
  // lights a number to the 7 segment digit display.
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
  
}

void setup() {
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinBuzzer, OUTPUT);
  pinMode(antennaPin, INPUT);
  displayNumber(number, dpState);
  Serial.begin(9600);
  for (int i = 0; i < maxReadings; i++)
    readings[i] = 0;
}



void loop() {
  val = analogRead(antennaPin);
  
  if(val >= 1){
    val = constrain(val, 1, readingLimit);  // we make sure it's in the interval
    val = map(val, 1, readingLimit, 1, 1023); // remaping the value read to 1-1023

    total -= readings[index]; // making the sum for average          
    readings[index] = val; // read from the sensor
    total += readings[index];
    index = (index + 1);

    if (index >= maxReadings)               
      index = 0;

    average = total / maxReadings;
    number = map(average, 1, 1023, 0, 9); // we map the number accordingly
    }
    
  displayNumber(number, dpState);
  
  if (number <= 0) { // tone the buzzer based on the number displayed and the average of the EMF income
    noTone(pinBuzzer);
  } else {
    tone(pinBuzzer, average);
  }
  Serial.println(average);
}
