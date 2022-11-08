#include <SoftwareSerial.h>

//Define SMS phone number to send SMS
String SMS = "";
String number = "+84xxxxxxxx";


SoftwareSerial SerialGSM(9,8);
//TinyGsm modem(SerialGSM);


//Register for 2G pack
void setup(){
  Serial.begin(9600);
  SerialGSM.begin(9600);
  
  //Can comment this line if AT work normally 
  testATCommand();
  
  delay(5000);
  
  checkNetwork();
  
  delay(5000);
  
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a Call");

  callNumber();
  
}

void loop(){
/*
  if(Serial.available() > 0){
    switch (Serial.read())
    {
      case 's':
        sendSMS();
        break;
      case 'r':
        receiveSMS();
        break;
      case 'c':
        callNumber();
        Serial.print("Calling number ...");
        break;
    }
  }
  
  if (SerialGSM.available() > 0){
    Serial.write(SerialGSM.read());
  }
  */
}


void testATCommand(){
  
  Serial.println("------------------ CHECK AT COMMAND ---------------");
  
  //Once the handshake test is successful, it will back to OK
  SerialGSM.println("AT");
  updateSerial();
  delay(1000);
  
  SerialGSM.println("ATE1");
  updateSerial();
  
  //Checks Signal Strength, value range from 0-31(best)
  SerialGSM.println("AT+CSQ");
  updateSerial();
  delay(1000);
  
  //Read SIM information (confirm if SIM is plugged)
  SerialGSM.println("AT+CCID");
  updateSerial();
  delay(5000);
  
  Serial.println("------------------  FINISH ---------------");
  
}

void checkNetwork(){
  
  Serial.println("------------------ CHECK NETWORK ---------------");
  //Check if it has registered in the network
  SerialGSM.println("AT+CREG?");
  updateSerial();
  delay(1000);

  //Return module name and revision
  SerialGSM.println("ATI");
  updateSerial();
  delay(1000);
  
  //Check which network connecting to
  SerialGSM.println("AT+COPS?");
  updateSerial();
  delay(1000);
  
  //Return list of operators present in network
  SerialGSM.println("AT+COPS?");
  updateSerial();
  delay(1000);
  
  //Return battery status [Battery level, actual voltage (mV)]
  SerialGSM.println("AT+CBC");
  updateSerial();
  delay(5000);
  
  Serial.println("------------------  FINISH ---------------");
}

void sendSMS(){

  //Selects the SMS message format as text
  SerialGSM.println("AT+CMGF=1");
  
  //Set SMS number
  SerialGSM.println("AT+CMGS=\"" + number + "\"\r");
  
  //Send SMS
  SerialGSM.print(SMS);
  
  SerialGSM.println(char(26));    //ASCII code of CTRL+Z
    
}

void receiveSMS(){
  //Selects the SMS message format as text
  SerialGSM.println("AT+CMGF=1");
  updateSerial();
  
  SerialGSM.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
  
}

void callNumber()
{  
  Serial.println("Loop call");
  SerialGSM.print(F("ATD"));
  SerialGSM.print(number);
  SerialGSM.print(F(";\r\n"));
  //updateSerial();
  
  //Hang up after 20 seconds
  delay(20000);
  SerialGSM.println("ATH");
  //updateSerial();
  Serial.println("Finish Call");
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SerialGSM.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(SerialGSM.available()) 
  {
    Serial.write(SerialGSM.read());//Forward what Software Serial received to Serial Port
  }
}
