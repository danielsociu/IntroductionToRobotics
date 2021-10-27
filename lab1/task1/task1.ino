#define ledRed 11
#define ledGreen 10
#define ledBlue 9
const int potRed = A0;
const int potGreen = A1;
const int potBlue = A2;

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
  // put your main code here, to run repeatedly:
  int potValueRed = analogRead(potRed);
  int potValueGreen = analogRead(potGreen);
  int potValueBlue = analogRead(potBlue);

  set_RGB(potValueRed / 4, potValueGreen / 4, potValueBlue / 4);

  Serial.print("(");
  Serial.print(potValueRed / 4);
  Serial.print(", ");
  Serial.print(potValueGreen / 4);
  Serial.print(", ");
  Serial.print(potValueBlue / 4);
  Serial.println(")");

}

void set_RGB(int red, int green, int blue)
{
  // Sets the values for the RGB led with the global leds ledRed, ledGreen, ledBlue
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue); 
}
