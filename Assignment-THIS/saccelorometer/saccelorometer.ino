int x, y,z;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

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
  
}
