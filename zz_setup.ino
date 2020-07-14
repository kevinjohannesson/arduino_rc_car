void setup() {
  // Servo
  steeringServo.attach(SERVO_PIN);
  steeringServo.write(90 + offset);

  // DRV8833
//  pinMode(MOT_A1_PIN, OUTPUT);
//  pinMode(MOT_A2_PIN, OUTPUT);
//
//  digitalWrite(MOT_A1_PIN, LOW);
//  digitalWrite(MOT_A2_PIN, LOW);
//
//  // LIGHTS
  pinMode(LIGHT_FL_PIN, OUTPUT); 
  pinMode(LIGHT_FR_PIN, OUTPUT); 
  pinMode(LIGHT_BL_PIN, OUTPUT); 
  pinMode(LIGHT_BR_PIN, OUTPUT);  

  // RF
  Serial.begin(115200);
  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
 
}
