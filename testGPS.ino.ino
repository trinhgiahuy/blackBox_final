#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

/*
* Small debug file for checking GPS is fix or not
* Hardware debug: LED conncted to D13 and 330Ohm resistor
* Software debug: Serial monitor printout
*/

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
int ledGPSPin = 13;
// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

bool gpsIsFix = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
}


void loop() {
  checkGPSFix();
  if(!gpsIsFix){
    Serial.println("GPS is not fixed");
    delay(3000);
    return;
  }
  Serial.println("GPS is fixed now!");
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
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
