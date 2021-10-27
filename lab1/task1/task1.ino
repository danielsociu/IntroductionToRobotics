#define ledRed 11
#define ledGreen 10
#define ledBlue 9
const int potRed = A0;
const int potGreen = A1;
const int potBlue = A2;
const int minAnalogValue = 0;
const int maxAnalogValue = 1023;
const int minRGBOutputValue = 0;
const int maxRGBOutputValue = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  pinMode(potRed, INPUT);
  pinMode(potGreen, INPUT);
  pinMode(potBlue, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // reading the values of the potentiometers
  int potValueRed = analogRead(potRed);
  int potValueGreen = analogRead(potGreen);
  int potValueBlue = analogRead(potBlue);

  // converting the values of the potentiometers to RGB range
  int redValue = map(potValueRed, minAnalogValue, maxAnalogValue, minRGBOutputValue, maxRGBOutputValue);
  int greenValue = map(potValueGreen, minAnalogValue, maxAnalogValue, minRGBOutputValue, maxRGBOutputValue);
  int blueValue = map(potValueBlue, minAnalogValue, maxAnalogValue, minRGBOutputValue, maxRGBOutputValue);

  print_RGB(redValue, greenValue, blueValue);

  set_RGB(redValue, greenValue, blueValue);
}

void set_RGB(int red, int green, int blue)
{
  // Sets the values for the RGB led with the global leds ledRed, ledGreen, ledBlue
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue); 
}

void print_RGB(int red, int green, int blue)
{
  Serial.print("(");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.print(blue);
  Serial.println(")");
}
