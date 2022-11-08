```
Execute get_SQLServer()
gpsData: ?lat=10.78&lng=106.66&speed=0.06
accData: &accX=-8.99&accY=1.58&accZ=0.16
queryParams returned: ?lat=10.78&lng=106.66&speed=0.06&accX=-8.99&accY=1.58&accZ=0.16&name=blackBox1"
?lat=10.78&lng=106.66&speed=0.06&accX=-8.99&accY=1.58&accZ=0.16&name=blackBox1"
Inside exec ATAT+CFUN=1
1
GOT answer
GOT response: 
⸮
Inside exec ATAT+CGATT=1
63
GOT answer
GOT response: 

+CME ERROR: unknown

SMS Ready

*PSUTTZ: 2022,9,14,4,55,1
+CGREG: 1

+CTZV: +28,0

*PSUTTZ: 2022,9,14,4,55,19,"+28",0

DST: 0

+CIEV: 10,"45202","VinaPhone","", 0, 0

Inside exec ATAT+SAPBR=3,1,"CONTYPE","GPRS"
6
GOT answer
GOT response: 

OK

Inside exec ATAT+SAPBR=3,1,"APN","m3-world"
6
GOT answer
GOT response: 

OK

Inside exec ATAT+SAPBR=0,1
37
GOT answer
GOT response: 

+CME ERROR: operation not allowed

Inside exec ATAT+SAPBR=1,1
6
GOT answer
GOT response: 

OK

Inside exec ATAT+SAPBR=2,1
36
GOT answer
GOT response: 

+SAPBR: 1,1,"10.217.5.125"

OK

Inside exec ATAT+HTTPINIT
6
GOT answer
GOT response: 

OK

Inside exec ATAT+HTTPPARA="CID",1
6
GOT answer
GOT response: 

OK

Inside exec ATAT+HTTPPARA="URL","119.82.141.196/testUpload.php?lat=10.78&lng=106.66&speed=0.06&accX=-8.99&accY=1.58&accZ=0.16&name=blackBox1"
6
GOT answer
GOT response: 

OK

Inside exec ATAT+HTTPACTION=0
6
GOT answer
GOT response: 

OK

Inside exec ATAT+HTTPREAD
31
GOT answer
GOT response: 

OK

+HTTPACTION: 0,200,55

Done. Wait for HTTP response

```
