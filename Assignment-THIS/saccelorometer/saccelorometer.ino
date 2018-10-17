const int xPin = A0;
const int yPin = A2;
const int zPin = A1;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  xPin = analogRead(0);       // read analog input pin 0
  yPin = analogRead(2);       // read analog input pin 1
  zPin = analogRead(1);       // read analog input pin 1
  Serial.print("accelerations are x, y, z: ");
  Serial.print(xPin, DEC);    // print the acceleration in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(yPin, DEC);    // print the acceleration in the Y axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.println(zPin, DEC);  // print the acceleration in the Z axis
  delay(100);              // wait 100ms for next reading
}
