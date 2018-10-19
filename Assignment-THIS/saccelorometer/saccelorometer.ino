
//include external file where the notes are defined
//taken from Etude 3 template
#include "pitches.h"

int keyC [] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5};

//define the pins for the button and the main speaker
#define BUTTON_PIN 2
#define CENTRAL_SPEAKER 3

//declare variables for the 3 axis that will be assigned to the 3 axis of the accelerometer
int x;
int y;
int z;

//define variables used on the noise filter
const float weight = 0.5;
float prevEstX = 0.0;
float prevEstY = 0.0;
float prevEstZ = 0.0;

//tresshold readings of all axis readings (center of accelerometer)
int tresholdX = 350;
int tresholdY = 354;
int tresholdZ = 447;

//peak opposites for each axis
int leftX = 420;
int rightX = 280;
int frontY = 274;
int backY = 425;
int upZ = 447;
int downZ = 303;

//declare the variables that will be mapped and finally used to generate the sounds
int soundX;
int soundY;
int switchZ;

//define button states
boolean buttonState = false;
boolean prevButtonState = true;

void setup() {
  
  // initialize the serial communications
  Serial.begin(9600);

  //initialise button pin mode
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  
//Read each analog pin and assign respective pin to the variable
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);

 // filter the sensor's result:
 //passing the results for a weighted average
 float currentEstX = filter(x, weight, prevEstX);
 float currentEstY = filter(y, weight, prevEstY);
 float currentEstZ = filter(z, weight, prevEstZ);
 
 //save current state for future use
 prevEstX= currentEstX;
 prevEstY= currentEstY;
 prevEstZ= currentEstZ;

soundX = map(currentEstX, leftX, rightX, 0, 6);

 //Print the averaged readings of the accelerometer to the monitor
  Serial.print("x ");
  Serial.print(currentEstX,DEC);
  Serial.print(" y ");
  Serial.print(currentEstY,DEC);
  Serial.print(" z ");
  Serial.println(currentEstZ,DEC);
  delay(500);

 //read button value abd switch its state
  int buttonValue = digitalRead(BUTTON_PIN);

  if (buttonValue == HIGH)
  {
    if (buttonState != prevButtonState)
    {
      delay(100);
      buttonState = ! buttonState;
      prevButtonState = buttonState;
    }

  }
  else
  {
    prevButtonState = !buttonState;
  }

  
  if (buttonState == true)
  {
    
      tone(CENTRAL_SPEAKER, keyC[soundX], 1000);
           //delay(100);
    } 

  else
  {
 
    noTone(CENTRAL_SPEAKER);
  }


}


//future handling of accelerometer will be done in this function
void accHandling(){
  
  
  
  
  
  
  }
  
//filter function averaging raw readings from the sensor
//(code taken from the class slides - Weighted Average Section)
float filter (float rawValue, float w, float lastValue) {
 float result = w * rawValue + (1.0-w)*lastValue; 
 return result;
}
