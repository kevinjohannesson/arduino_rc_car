#include <Servo.h>

// BUTTONS

int up_button = 2;
int down_button = 4;
int left_button = 5;
int right_button = 3;
int start_button = 6;
int select_button = 7;
int joystick_button = 8;
int joystick_axis_x = A0;
int joystick_axis_y = A1;
int buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, joystick_button};

unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// STEERING
Servo steeringServo;
byte offset = 2; // for alignment

// LIGHTS
#define LIGHT_FL_PIN A2
#define LIGHT_FR_PIN A3
#define LIGHT_BL_PIN A4
#define LIGHT_BR_PIN A5

byte lightButtonState = 1;
byte prev_lightButtonState = 1;
byte lightState = LOW;

unsigned long prev_lightButtonDebounceTime = 0;

// ACCELERATION

#define MOT_A1_PIN 10
#define MOT_A2_PIN 11

byte accelerationButtonState = 1;             // the current reading from the input pin
byte prev_accelerationButtonState = 1;   // the previous reading from the input pin

byte accelerationPWM = 50;

// ACCELERATION REVERSE

byte reverseButtonState = 1;
byte prev_reverseButtonState = 1;
byte reversePWM = 50;

// TRANSMISSION

byte transmissionButtonState = 1;
byte prev_transmissionButtonState = 1;
unsigned long prev_transmissionButtonDebounceTime = 0;  // the last time the output pin was toggled


void setup() {
  // Servo
  steeringServo.attach(9);
  steeringServo.write(90 + offset);

  // DRV8833
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);

  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);

  // LIGHTS
  pinMode(LIGHT_FL_PIN, OUTPUT); 
  pinMode(LIGHT_FR_PIN, OUTPUT); 
  pinMode(LIGHT_BL_PIN, OUTPUT); 
  pinMode(LIGHT_BR_PIN, OUTPUT);  

  // Joystick shield
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  Serial.begin(9600);
}

void lights() {
  // Read the button state:
  byte reading = digitalRead(left_button);
  
  if (reading != prev_lightButtonState) {
    // reset the debouncing timer
    prev_lightButtonDebounceTime = millis();
  }

  if ((millis() - prev_lightButtonDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != lightButtonState) {
      lightButtonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (lightButtonState == HIGH) {
        lightState = !lightState;
      }
    }
  }

  // save the reading. 
  prev_lightButtonState = reading;
  
  // set the LED:
  digitalWrite(LIGHT_FL_PIN, lightState);
  digitalWrite(LIGHT_FR_PIN, lightState);
  digitalWrite(LIGHT_BL_PIN, lightState);
  digitalWrite(LIGHT_BR_PIN, lightState);
}

void steering() {
  int reading = analogRead(joystick_axis_x);
  int servoPosition = map(reading, 0, 656, 45 + offset, 135 + offset);
  steeringServo.write(servoPosition);
}

void acceleration() {
  
  accelerationButtonState = digitalRead(right_button);
  reverseButtonState = digitalRead(down_button);

  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  if (accelerationButtonState == LOW) {
    // accelerate forward
    analogWrite(MOT_A2_PIN, accelerationPWM);
    digitalWrite(MOT_A1_PIN, LOW);
  } 
  else if (reverseButtonState == LOW){
    // accelerate reverse
    analogWrite(MOT_A2_PIN, -reversePWM);
    digitalWrite(MOT_A1_PIN, HIGH);
  }
  else {
    // turn motors off:
    digitalWrite(MOT_A1_PIN, LOW);
    digitalWrite(MOT_A2_PIN, LOW);
  }

}


void transmission() {
  
  byte reading = digitalRead(up_button);

  // If the switch changed, due to noise or pressing:
  if (reading != prev_transmissionButtonState) {
    // reset the debouncing timer
    prev_transmissionButtonDebounceTime = millis();
  }

  if ((millis() - prev_transmissionButtonDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != transmissionButtonState) {
      transmissionButtonState = reading;

      if (transmissionButtonState == HIGH) {
        accelerationPWM += 10;
        if(accelerationPWM > 250) { 
          accelerationPWM = 10; 
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  prev_transmissionButtonState = reading;

}


void loop() {
  acceleration();
  steering();
  transmission();
  lights(); 
}
