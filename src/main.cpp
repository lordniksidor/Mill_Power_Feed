# include <Arduino.h>

// testing a stepper motor with a Pololu A4988 driver board or equivalent

// this version uses millis() to manage timing rather than delay()
// and the movement is determined by a pair of momentary push switches
// press one and it turns CW, press the other and it turns CCW

byte directionPin = 9;
byte stepPin = 8;
byte enablePin = 6;


byte buttonCWpin = A2;
byte buttonCCWpin = A3;

boolean buttonCWpressed = false;
boolean buttonCCWpressed = false;

byte ledPin = 13;

unsigned long curMillis;
unsigned long prevStepMillis = 0;
unsigned long millisBetweenSteps = 25; // milliseconds

void readButtons() {
   
    buttonCCWpressed = false;
    buttonCWpressed = false;
   
    if (digitalRead(buttonCWpin) == HIGH) {
        buttonCWpressed = true;
    }
    if (digitalRead(buttonCCWpin) == HIGH) {
        buttonCCWpressed = true;
    }

    millisBetweenSteps = map(analogRead(A0), 0, 1024, 1000, 20);
}

void singleStep() {
    if (curMillis - prevStepMillis >= millisBetweenSteps) {
            // next 2 lines changed 28 Nov 2018
        //prevStepMillis += millisBetweenSteps;
        prevStepMillis = curMillis;
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
    }
}
void actOnButtons() {
    if (buttonCWpressed == true) {
        digitalWrite(directionPin, LOW);
        singleStep();
    }
    if (buttonCCWpressed == true) {
        digitalWrite(directionPin, HIGH);
        singleStep();
    }
}


void setup() {

     Serial.begin(9600);
     Serial.println("Starting Stepper Demo with millis()");

     pinMode(directionPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(ledPin, OUTPUT);
     
     pinMode(buttonCWpin, INPUT_PULLUP);
     pinMode(buttonCCWpin, INPUT_PULLUP);
     
}

void loop() {
   
    curMillis = millis();
    readButtons();
    actOnButtons();
   
}

