
//boolean newData = false;


//void setup() {
// Serial.begin(9600);
// Serial.println("<Arduino is ready>");
// 
// parseData();
// showParsedData();
//}


 
void parseData() {

    // split the data into its parts
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(dataReceived,",");      // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
  Serial.println(messageFromPC);
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  integerFromPC = atoi(strtokIndx);     // convert this part to an integer
  
  strtokIndx = strtok(NULL, ",");
  floatFromPC = atof(strtokIndx);     // convert this part to a float

}


void showParsedData() {
 Serial.print("Message ");
 Serial.println(messageFromPC);

 if( String(messageFromPC) ==  String("This is a test")){
  Serial.println("Hallo");
 }
 if (integerFromPC == 1234) {
    Serial.println("Toggling motor");
    isGoing = !isGoing;
  }
 Serial.print("Integer ");
 Serial.println(integerFromPC);
 Serial.print("Float ");
 Serial.println(floatFromPC);
}
