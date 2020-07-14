#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[32]; // this must match dataToSend in the TX
bool newData = false;

void RF(){
  getData();
  showData();
}

//==============

void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    parseData();
    newData = true;
  }
}
 
void parseData() {
  // split the data into its parts
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(dataReceived, ","); // parse from the start
  accelerationPWM = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  steeringAngle = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  lightsOn = atoi(strtokIndx);     // convert this part to an integer
}

void showData() {
  if (newData == true) {
    Serial.println("Data received ");
    Serial.print("accelerationPWM: ");
    Serial.println(accelerationPWM);
    Serial.print("steeringAngle: ");
    Serial.println(steeringAngle);
    Serial.print("lightsOn: ");
    Serial.println(lightsOn);
    newData = false;
  }
}
