

// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[32]; // this must match dataToSend in the TX
bool newData = false;


bool isGoing = false;


// simple parse demo
char receivedChars[] = "This is a test, 1234, 45.3" ;

char messageFromPC[32] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

char recvChar;
char endMarker = '>';

//===========

//void setup() {
//
//    Serial.begin(9600);
////pinMode(10, OUTPUT);
//    Serial.println("SimpleRx Starting");
//    radio.begin();
//    radio.setDataRate( RF24_250KBPS );
//    radio.openReadingPipe(1, thisSlaveAddress);
//    radio.startListening();
//}

//=============

//void loop() {
//    getData();
//    showData();
//}

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

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived);
        if (integerFromPC == 1234) {
          Serial.println("Toggling lights");
//          lightsOn = !lightsOn;
          
        }
        
//        showParsedData();
        
        
        newData = false;
    }
}
