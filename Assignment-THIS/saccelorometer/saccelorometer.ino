<<<<<<< HEAD
=======
int x, y,z;
>>>>>>> 3de3a4756c68957ffa833bf542f229200a299cd2

const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

<<<<<<< HEAD
void loop() {
  // print the sensor values:
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();
  // delay before next reading:
  delay(100);
=======
void loop()
{
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  Serial.print(x,DEC);
  Serial.print(" ");
  Serial.print(y,DEC);
  Serial.print(" ");
  Serial.print(z,DEC);
  Serial.println(" ");
  delay(100);
  
>>>>>>> 3de3a4756c68957ffa833bf542f229200a299cd2
}
