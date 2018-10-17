
int x, y,z;    //X-Axis, Y-Axis and Z-Axis       
int piezoPin = 3;
      

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop()
{
  //Read each pin so we can see where the values are being mapped to 
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  //Print the locations in the Serial Monitor 
  Serial.print(x,DEC);
  Serial.print(" ");
  Serial.print(y,DEC);
  Serial.print(" ");
  Serial.print(z,DEC);
  Serial.println(" ");
  delay(100);

tone(piezoPin,1000,500);
  
}
