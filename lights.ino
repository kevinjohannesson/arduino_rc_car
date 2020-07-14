#define LIGHT_FL_PIN A0
#define LIGHT_FR_PIN A1
#define LIGHT_BL_PIN A2
#define LIGHT_BR_PIN A3

void lights(bool lightsOn) {
  if(lightsOn){
    analogWrite(LIGHT_FL_PIN, 255);
    analogWrite(LIGHT_FR_PIN, 255);
    analogWrite(LIGHT_BL_PIN, 255);
    analogWrite(LIGHT_BR_PIN, 255);
  }
  else {
    analogWrite(LIGHT_FL_PIN, 0);
    analogWrite(LIGHT_FR_PIN, 0);
    analogWrite(LIGHT_BL_PIN, 0);
    analogWrite(LIGHT_BR_PIN, 0);
  }
}
