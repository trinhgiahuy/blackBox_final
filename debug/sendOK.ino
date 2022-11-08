#include <SoftwareSerial.h>
#include <MPU6050.h>
SoftwareSerial SerialGSM(9,8);
//TinyGsm modem(SerialGSM);
MPU6050 mpu;
float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;

//char accx[15], accy[15], accz[15];
//Register for 2G pack
//char lati[15], longti[15], gpsspeed[15];

//String accData;
//String gpsData;
//String queryParams;

void remove_spaces(char * str){
    char * back = str;
    do{
        if(*back != ' ')
            *str++ = *back;
    }while(*back++ != '\0');
}

String execute_AT(String AT){
    Serial.println("Inside exec AT");
    boolean answer = false;
    String response;
    SerialGSM.println(AT);
    delay(4000);
    Serial.println(SerialGSM.available());
    do{
        if(SerialGSM.available() > 0){
            Serial.println("GOT answer");
            answer = true;
            response = SerialGSM.readString();
        }
    }while(answer == false);
    Serial.println("GOT response: ");
    Serial.println(response);
    return response;
}

void get_SQLServer(String queryParams){
//void get_SQLServer(String la, String ln, String gpsSpeed, String accX, String accY, String accZ){
    Serial.println(queryParams);
    execute_AT("AT+CFUN=1");
    execute_AT("AT+CGATT=1");
    execute_AT("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
    execute_AT("AT+SAPBR=3,1,\"APN\",\"m3-world\"");  
    execute_AT("AT+SAPBR=0,1");
    execute_AT("AT+SAPBR=1,1");
    execute_AT("AT+SAPBR=2,1");
    execute_AT("AT+HTTPINIT");
    execute_AT("AT+HTTPPARA=\"CID\",1");
    
    //String params="?lat="+la+"&lng="+ln+"&speed="+gpsSpeed+"&accX="+accX+"&accY="+accY+"&accZ="+accZ+"&name=blackBox1\"";
    //execute_AT("AT+HTTPPARA=\"URL\",\"119.82.141.196/testUpload.php"+params);
    //Serial.println("AT+HTTPPARA=\"URL\",".concat(queryParams));
    
    //execute_AT("AT+HTTPPARA=\"URL\",".concat(queryParams));
    //CASE queryParams have ""
    //execute_AT("AT+HTTPPARA=\"URL\","+queryParams);

    //execute_AT("AT+HTTPPARA=\"URL\","+queryParams+"\"")
    
    //CASE queryParams do not have ""
//    String temp="AT+HTTPPARA=\"URL\",\""+queryParams+"\""
    execute_AT("AT+HTTPPARA=\"URL\",\"119.82.141.196/testUpload.php"+(String)(queryParams));
    
    //execute_AT("AT+HTTPPARA=\"URL\",\"119.82.141.196/testUpload.php?lat=10.784451&lng=106.657540&speed=0.06&accX=8.49&accY=-0.34&accZ=-3.47&name=blackBox1\"");
    execute_AT("AT+HTTPACTION=0");

    execute_AT("AT+HTTPREAD");
}

void setup(){
  Serial.begin(9600);
  SerialGSM.begin(4800);
  
  //Can comment this line if AT work normally 
  //testATCommand();

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  
  //checkNetwork();
  Serial.println("Execute get_SQLServer()");
   
  //GOI TU HAM 
  String queryData = getData();

  //NEU GUI 1 string queryData nay thi server nhan dc
  //String queryData="?lat=10.784451&lng=106.657540&speed=0.06&accX=8.49&accY=-0.34&accZ=-3.47&name=blackBox1\"";
  get_SQLServer(String(queryData));
  Serial.println("Done. Wait for HTTP response");
  
}

float laTi;
float longTi;
float gpsSpeed;

String getData(){
  
  float laTi=10.784451;
  float longTi=106.657540;
  float gpsSpeed=0.06;
  String gpsData=String("?lat=")+String(laTi)+String("&lng=")+String(longTi)+String("&speed=")+String(gpsSpeed);

  /*
  dtostrf(laTi,11,6,lati);
  remove_spaces(lati);
  dtostrf(longTi,12,6,longti);
  remove_spaces(longti);
  dtostrf(gpsSpeed,6,2,gpsspeed);
  remove_spaces(gpsspeed);
   
  gpsData.concat(lati);
  gpsData.concat("&lng=");
  gpsData.concat(longti);
  gpsData.concat("&speed=");
  gpsData.concat(gpsspeed);
  */
  
  Serial.print("gpsData: ");
  Serial.println(gpsData);
  
  Vector rawAccel = mpu.readRawAccel();
  float accx=(float)(rawAccel.XAxis)/16384.0*9.8066;
  float accy=(float)(rawAccel.YAxis)/16384.0*9.8066;
  float accz=(float)(rawAccel.ZAxis)/16384.0*9.8066;

  /*
  dtostrf(accX,7,4,accx);
  remove_spaces(accx);
  dtostrf(accY,7,4,accy);
  remove_spaces(accy);
  dtostrf(accZ,7,4,accz);
  remove_spaces(accz);
  */
  
  String accData=String("&accX=")+String(accx)+String("&accY=")+String(accy)+String("&accZ=")+String(accz);
  /*
  accData.concat(accx);
  accData.concat("&accY=");
  accData.concat(accy);
  accData.concat("&accZ=");
  accData.concat(accz);
  accData.concat("&name=blackBox1\"");
  */
  Serial.print("accData: ");
  Serial.println(accData);

  String queryParams=gpsData+accData+String("&name=blackBox1\"");
  Serial.print("queryParams returned: ");
  Serial.println(queryParams);

  return queryParams;
}
void loop(){


}
