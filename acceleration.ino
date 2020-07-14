// ACCELERATION

#define MOT_A1_PIN 5
#define MOT_A2_PIN 6

byte accelerationPWM = 50;


void acceleration() {
  if(isGoing){
//    Serial.println("h");
    analogWrite(MOT_A2_PIN, accelerationPWM);
    digitalWrite(MOT_A1_PIN, LOW);
  }
  else {
    digitalWrite(MOT_A1_PIN, LOW);
    digitalWrite(MOT_A2_PIN, LOW);
  }
//  
//  accelerationButtonState = digitalRead(right_button);
//  reverseButtonState = digitalRead(down_button);
//
//  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
//  if (accelerationButtonState == LOW) {
//    // accelerate forward
//    analogWrite(MOT_A2_PIN, accelerationPWM);
//    digitalWrite(MOT_A1_PIN, LOW);
//  } 
//  else if (reverseButtonState == LOW){
//    // accelerate reverse
//    analogWrite(MOT_A2_PIN, -reversePWM);
//    digitalWrite(MOT_A1_PIN, HIGH);
//  }
//  else {
//    // turn motors off:
//    digitalWrite(MOT_A1_PIN, LOW);
//    digitalWrite(MOT_A2_PIN, LOW);
//  }

}
