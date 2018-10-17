
int x, y,z;    //X-Axis, Y-Axis and Z-Axis       
int piezoPin = 3;
#define BUTTON_PIN 2

boolean buttonState =false;
boolean prevButtonState =true;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
   pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  int buttonValue = digitalRead(BUTTON_PIN);

  if(buttonValue == HIGH)
  {
   if(buttonState != prevButtonState)
   {
    delay(200);
    buttonState = ! buttonState;
    prevButtonState = buttonState;
   }
    
  }
  else
  {
    prevButtonState =!buttonState;
  }

    
  
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
if(buttonState ==true)
  {
    tone(piezoPin,x,500);

  }
  else
  {
    analogWrite(piezoPin, 0);

  }


  
}
