```md
Testing GSM SIM800L
AT+CFUN=1


OK

AT+CGREG=1


OK

AT+CREG=1


OK

AT+CGATT=1


OK

AT+CMEE=1


OK

 AT+CREG? 


+CREG: 1,1

OK

AT+CIPSTATUS=?


OK

AT+SAPBR=3,1,"CONTYPE","GPRS"


OK

AT+SAPBR=3,1,"APN","m3-world"


OK

AT+SAPBR=1,1


OK

AT+HTTPINIT 


OK

AT+HTTPPARA="URL","119.82.141.196/testUpload.php?lat=10.784451&lng=106.657540&speed=0.06&accX=8.49&accY=-0.34&accZ=-3.47&name=blackBox1"


OK

AT+HTTPPARA=CID,1


OK

AT+HTTPACTION=1


OK


+HTTPACTION: 1,200,55

AT+HTTPREAD


+HTTPREAD: 55
Finish settingServer is connected
Statement executed. 

OK

AT+HTTPTERM


OK


```
