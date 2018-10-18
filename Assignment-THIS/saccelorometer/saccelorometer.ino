
int x;//Center is 345
int preX;
int currentX;
int y;//Center is 
int preY;
int z;   
int preZ; 
//X-Axis, Y-Axis and Z-Axis  
//X = Side to side
//Z = Up and Down
//Y = Front and backwards
//<345  = down
//> 345 = up 


int xLoc;
int yLoc;
int zLoc;
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

  preX = 345;
  currentX = x - preX;

  if (currentX == currentX +15) {
    currentX += analogRead(0);
  }
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
  Serial.println(currentX,DEC);
 // Serial.println(xLoc,DEC);

  delay(100);
if(buttonState ==true)
  {
    tone(piezoPin,x,1000);
    delay(100);

  }
  else
  {
    noTone(piezoPin);

  }

  
}


void mapLoc() {
 // sound-x
  //sound-y
 // sound-z
  if (x < 50) {
//    piexoPin = 1
  }
  if (x >50 && x <100) {
  
    
  }
  



}
