
//include external file where the notes are defined
//taken from Etude 3 template
#include "pitches.h"

int keyC [] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C5};
int keyEb [] = {NOTE_E4,NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5};
int keyA [] = {NOTE_A4,NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_E4, NOTE_FS5, NOTE_GS4, NOTE_E5};

int noteDuration [] = {1000/8, 1000/4, 1000/2,1000/2, 1000, 1000/2, 1000/4, 1000/8};

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

float currentEstX;
float currentEstY;
float currentEstZ;

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
int durationY;
int switchZ;

//define button states
boolean switchZState = false;
boolean prevSwitchZState = true;

boolean switchYState = false;
boolean prevSwitchYState = true;

boolean switchXState = false;
boolean prevSwitchXState = true;


void setup() {
  
  // initialize the serial communications
  Serial.begin(9600);

  //initialise button pin mode
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{

  accHandling();
  musicHandler();


}


//future handling of accelerometer will be done in this function
void accHandling(){
  
  
  //Read each analog pin and assign respective pin to the variable
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);

 // filter the sensor's result:
 //passing the results for a weighted average
 currentEstX = filter(x, weight, prevEstX);
 currentEstY = filter(y, weight, prevEstY);
 currentEstZ = filter(z, weight, prevEstZ);
 
 //save current state for future use
 prevEstX= currentEstX;
 prevEstY= currentEstY;
 prevEstZ= currentEstZ;

soundX = map(currentEstX, leftX+20, rightX-20, 0, 8);
durationY = map(currentEstY, frontY-20, backY+20, 0, 5);
switchZ = map(currentEstZ, upZ, downZ, 10, 0);
delay(10);
 //Print the averaged readings of the accelerometer to the monitor
//  Serial.print("x ");
//  Serial.print(currentEstX,DEC);
//  Serial.print(" y ");
//  Serial.print(currentEstY,DEC);
//  Serial.print(" z ");
//  Serial.println(currentEstZ,DEC);
//  delay(100);
  
  
  
  }

void musicHandler(){
  
    if (switchZ <2)
  {
    if (switchZState != prevSwitchZState)
    {
      delay(300);
      switchZState = ! switchZState;
      prevSwitchZState = switchZState;
    }

  }
  else
  {
    prevSwitchZState = !switchZState;
  }

 if (currentEstX <= leftX+10)
  {
    if (switchXState != prevSwitchXState)
    {
      delay(200);
      switchXState = ! switchXState;
      prevSwitchXState = switchXState;
    }

  }
  else
  {
    prevSwitchXState = !switchXState;
  }

  
 if (currentEstY <= backY+10)
  {
    if (switchYState != prevSwitchYState)
    {
      delay(200);
      switchYState = ! switchYState;
      prevSwitchYState = switchYState;
    }

  }
  else
  {
    prevSwitchYState = !switchYState;
  }

  
  if (switchZState == false)
  {   
    if(switchXState == true){
  
      tone(CENTRAL_SPEAKER, keyEb[soundX], noteDuration[durationY]);
      delay(noteDuration[durationY]*1.3);
    } else if (switchXState == true){
      tone(CENTRAL_SPEAKER, keyA[soundX], noteDuration[durationY]);
      delay(noteDuration[durationY]*1.3);
      
      } else {
        tone(CENTRAL_SPEAKER, keyC[soundX], noteDuration[durationY]);
        delay(noteDuration[durationY]*1.3);
        
      }
    
  }

  else
  {
 
    noTone(CENTRAL_SPEAKER);
  }
  
  }
  
//filter function averaging raw readings from the sensor
//(code taken from the class slides - Weighted Average Section)
float filter (float rawValue, float w, float lastValue) {
 float result = w * rawValue + (1.0-w)*lastValue; 
 return result;
}


