//https://github.com/vshymanskyy/TinyGSM/blob/master/examples/HttpClient/HttpClient.ino
                                                         

#define TINY_GSM_MODEM_SIM800
                                                         
#if !define(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 256
#endif

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

// Range to attempt to autobaud
// NOTE:  DO NOT AUTOBAUD in production code.  Once you've established
// communication, set a fixed baud rate using modem.setBaud(#).
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200


#define rxPin
#define txPin

//PIN to unlock SIM
#define GSM_PIN ""

// Your GPRS credentials, if any
//const char apn[]      = "YourAPN";
//const char gprsUser[] = "";
//const char gprsPass[] = "";

// Server details example
//const char server[]   = "vsh.pp.ua";
//const char resource[] = "/TinyGSM/logo.txt";
//const int  port       = 80;


SoftwareSerial sim800l(rxPin, txPin);

TinyGsm modem(sim800l);

TinyGsmClient client(modem);
HttpClient    http(client, server, port);

void setup(){
  
  Serial.begin(115200);
  delay(10);
  
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  // SerialAT.begin(9600);
  delay(6000);
  
  
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);
  
#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }
#endif
}

void loop(){
  
#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
  Serial.print(F("Connecting to "));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected()) { SerialMon.println("GPRS connected"); }
#endif
  
  
  Serial.print(F("Performing HTTP GET request..."));
  int err = http.get(resource);
  if (err != 0) {
    SerialMon.println(F("failed to connect"));
    delay(10000);
    return;
  }
  
  int status = http.responseStatusCode();
  Serial.print(F("Response status code: "));
  Serial.println(status);
  if (!status) {
    delay(10000);
    return;
  }
  
  
  
  
}
