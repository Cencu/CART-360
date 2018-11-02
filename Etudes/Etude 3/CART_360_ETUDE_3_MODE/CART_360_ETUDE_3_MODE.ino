/**********************ETUDE 2 CART 360 2017*******************************
   WELCOME!
   THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
   WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS).
   THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
   THERE ARE 5 POSSIBLE MODES
   0 ==  reset    ==   led off == also resets
   1 ==  live     ==   led BLUE
   2 ==  record   ==   led RED
   3 ==  play     ==   led GREEN
   4 ==  looper   ==   led PURPLE

   ADDITIONALLY - WHEN THE USER CHANGES MODE,
   THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

   PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
   DO NOT ADD ANY MORE FUNCTION DEFINITIONS
   ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
   THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
   PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
   GOOD LUCK!
*/
// behavior of the resistor ladder (keyboard), mode selector and what is occurring
// on the Arduino as a voltage. How does the input become audible sound?  */
// The analog read input returns a value of 1023. For any voltage between 0V and 5V, analogRead
//   will return a number porportional to the voltage. Since we do not change the voltage that's supplied
//  to the pin, we add resistors to manipulate the voltage supplied, therefore changing the voltage
// supplied to the buttons. Since the analog pin is transmitting integers, we can then create parameters
// to play on each button, since the buttons are connected by the ladder, we set parameters depending
// on the voltage inputted to each button, we then set the tone to the piezo pin and the frequency we
// would like to play.


/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes[MAX_NOTES];
boolean switchMode = false;
/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change the loop - it establishes the flow of the program
   We call here 3 functions repeatedly:
   1: chooseMode(): this function will determine the mode that your program is in
   based on if the button (linked to the BUTTON_MODE_PIN) was pressed
   2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
   3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{

  chooseMode();
  setRGB();
  selectMode();
}

/******************CHOOSEMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Read the value from the Button (linked to the BUTTON_MODE_PIN) and
   if is being pressed then change the mode variable.
   REMEMBER:
   mode == 0 is reset
   mode == 1 is live
   mode == 2 is record
   mode == 3 is play
   mode == 4 is loopMode
   Every time the user presses the button, the program will go to the next mode,
   once it reaches 4, it should go back to mode == 0.
   (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode() {
  mode = digitalRead(BUTTON_MODE_PIN);


  if (BUTTON_MODE_PIN == HIGH) {
    switchMode = true;
  }
  if (switchMode == true) {
    mode = mode + 1;
  }
  Serial.println(mode);

}


/******************SETRGB(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Depending on the value of the mode variable:
   if the mode is 0 - RGB LED IS OFF
   if the mode is 1 - RGB LED IS BLUE
   if mode is 2 - RGB LED IS RED
   if mode is 3 - RGB LED IS GREEN
   if mode is 4 - RGB LED iS PURPLE
   YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB() {

  if (mode == 0 ) {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, LOW);

  }
  if (mode == 1) {
    digitalWrite(LED_PIN_B, HIGH);

  } else {
    digitalWrite(LED_PIN_B, LOW);

  } if (mode == 2) {
    digitalWrite(LED_PIN_R, HIGH);
  } else {
    digitalWrite(LED_PIN_R, LOW);

  }  if (mode == 3) {
    digitalWrite(LED_PIN_G, HIGH);
  } else {
    digitalWrite(LED_PIN_G, LOW);

  } if (mode == 4) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_B, HIGH);

  } else {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_B, LOW);

  }


}
/**********************SELECTMODE() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
   There are 4 possibilities
   1: reset(): this function will reset any arrays etc, and will do nothing else
   2: live(): this function will play the corresponding notes
   to the user pressing the respective buttons.
   NOTE:: the notes played are NOT stored
   3: record(): this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   4: play(): this function will playback any notes stored in the array that were recorded
   in the previous mode
   5: loopMode(): this function will playback any notes stored in the array that were recorded,
   BUT unlike the previous mode, you can choose in which sequence the notes are played.
   REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode() {
  if (mode == 0) {
    reset();

  }
  else if (mode == 1) {
    live();
  }
  else if (mode == 2) {
    record();
  }

  else if (mode == 3) {
    play();
  }

  else if (mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  if (mode == 0) {

  }
}
/******************LIVE(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   NOTE:: the notes played are NOT stored
   SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
   THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live() {
  if (mode == 1) {
    int analogVal = analogRead(A0);

    if (analogVal > 1 && analogVal < 10) {
      tone(3, 300, duration);
    }

    if (analogVal > 1 && analogVal < 10) {
      tone(3, 300, duration);

    }  if (analogVal > 10 && analogVal < 100) {
      tone(3, 600, duration);

    } if (analogVal > 110 && analogVal < 500) {
      tone(3, 900, duration);

    } if (analogVal > 510 && analogVal < 1000) {
      tone(3, 1200, duration);

    } if (analogVal > 1000 && analogVal < 1100) {
      tone(3, 1500, duration);
    }
  }
}
/******************RECORD(): IMPLEMENT **********************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
   AND - output the note to the buzzer using the tone() function
   THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record() {
  if (mode == 0) {
    int analogVal = analogRead(A0);

    if (analogVal > 1 && analogVal < 10) {
      countNotes = 1;
    } if (countNotes == 1) {
      tone(3, 300, duration);
    }
    notes[MAX_NOTES] = countNotes;
    countNotes++;
  }

}
/******************PLAY(): IMPLEMENT ************************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ each value IN ORDER
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play() {
  if (mode == 3) {

  }
}

/******************LOOPMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper() {
  if (mode == 4) {

  }
}

/**************************************************************************/
