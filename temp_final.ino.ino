#define TINY_GSM_MODEM_SIM800
#include <TinyGPS++.h>
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>

//GPS configuration
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
bool gpsIsFix = false;
int ledGPSPin = 13;
TinyGPSPlus gps;
SoftwareSerial SerialGPS(RXPin, TXPin);


//GSM configuration
SoftwareSerial SerialGSM(9,8);
TinyGsm modem(SerialGSM);
TinyGsmClient client(modem);

//MPU configuration
MPU6050 mpu;
float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;
int ledGSMPin = 12;
int ledGreenPin = 11;

//Network configuration
const char apn[]  = "VINAPHONE";
const char user[] = ""; 
const char pass[] = "";

//Server configuration
const char server[] = "119.82.141.196";
const char resource[] = "/logger_h.php";

void setup(){

  Serial.begin(9600);
  delay(10);
  
  SerialGPS.begin(GPSBaud);
  SerialGSM.begin(9600);
  
  //Initialize MPU6050
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

}

int errWaitNetwork=0;

void loop(){
  
  //CHECK GPS FIX
  checkGPSFix();
  if(!gpsIsFix){
    Serial.println("GPS is not fixed");
    delay(3000);
    return;
  }
  
  Serial.println("GPS is fixed now!");
  //SerialGPS.listen();
  getGPSAndSend();
  
}

void checkGPSFix(){
  
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  Serial.println();
  
  smartDelay(1000);
  
  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    gpsIsFix = false;
    ledBlynk(ledGPSPin, true, false);
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    gpsIsFix = true;
    ledBlynk(ledGPSPin, false, false);
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (SerialGPS.available())
      gps.encode(SerialGPS.read());
  } while (millis() - start < ms);
}


void getGPSAndSend() {
  
  smartDelay(1000);
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Vector rawAccel = mpu.readRawAccel();
         
    String locationString = "?lat=" + String(gps.location.lat(), 6) + 
    "&lng=" + String(gps.location.lng(), 6) + 
    "&speed=" + String(gps.speed.kmph(), 2) + 
    "&accX=" + String(rawAccel.XAxis/16384.0*9.8066) +
    "&accY=" + String(rawAccel.YAxis/16384.0*9.8066) +
    "&accZ=" + String(rawAccel.ZAxis/16384.0*9.8066) ;
 
    locationString += "&name=blackBox1";
    
    Serial.print("Trying to send data to Server: ");
    Serial.println(locationString);

    sendDataToServer(locationString);
   
    // If neccessary delay 1 min for the update
    //Default the sendDataToServer may take upto 1 min
    //delay(60000);
  }
  else
  {
    Serial.print("Invalid GPS position...");
  }
}
  
void sendDataToServer(String queryParams){
  
  SerialGSM.listen();
  Serial.print("Waiting for network...");

  //CODE LED GREEN BLYNKING ( SEARCHING NETWORK)
  ledBlynk(ledGSMPin,true,false);
  if (!modem.waitForNetwork()) {
    Serial.println(" Fail wait for network");
    errWaitNetwork+=1;
    Serial.print("Error times: ");
    Serial.println(errWaitNetwork);
    if(errWaitNetwork==3){
      //Both blynking, restart modem
      ledBlynk(ledGSMPin,true,true);
      ledBlynk(ledGPSPin,true,true);
      Serial.println("Error 5 times. Modem restart...");
      modem.restart();
    }
    return;
  }
  ledBlynk(ledGSMPin,false,false);
  Serial.println(" OK");
  Serial.print("Connecting to: ");
  Serial.print(apn);
  if(!modem.gprsConnect(apn,user,pass)){
    Serial.println(" Fail gprs connect"); 
    return; 
  }

  Serial.println(" OK");
  Serial.print("Connecting to: ");
  Serial.print(server);
  if(!client.connect(server,80)){
    Serial.println(" Fail server connect");
    return;  
  }
  Serial.println("OK");
  while (client.connected()){
    //MAKE A HTTP GET REQUEST:
    client.print(String("GET ")+resource+queryParams+" HTTP/1.0\r\n");
    client.print(String("Host: ")+server+"\r\n");
    client.print("Connection: close\r\n\r\n");
  }

  client.stop();
  Serial.println("Server disconnected");

  //Consider disconnect from GPRS ??
  //modem.gprsDisconnect();
  //Serial.println("GPRS disconnected");

}
/*
void getAcceleration(){

  accX=rawAccel.XAxis/16384.0*9.8066;
  accY=rawAccel.YAxis/16384.0*9.8066;
  accZ=rawAccel.ZAxis/16384.0*9.8066
  
  Serial.print(" Xraw = ");
  Serial.print(accX);
  Serial.print(" m/s^2 ");
  Serial.print(" Yraw = ");
  Serial.print(accY);
  Serial.print(" m/s^2 ");
  Serial.print(" Zraw = ");
  Serial.print(accZ);
  Serial.print(" m/s^2 ");
}
*/


void ledBlynk(int led_pin,bool blynk, bool fast){
  pinMode(led_pin,OUTPUT);
  int delayTime;
  if(fast){
    delayTime = 100;
  }else{
    delayTime = 500;  
  }
  digitalWrite(led_pin,HIGH);

  if (blynk){
    delay(delayTime);  
    digitalWrite(led_pin,LOW);
    delay(delayTime);
  }
}
