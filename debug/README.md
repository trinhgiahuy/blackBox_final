Debug files' description
========================

## Debug 2 Serials Link

**Reference using 2 Serial**

https://www.instructables.com/Homemade-Realtime-GPS-Tracker-SIM800L-Ublox-NEO-6M/ => https://github.com/buliko/SIM800L-NEO6M-homemade-tracker/blob/master/arduino/tracker.ino



Alternative using SPI

https://stackoverflow.com/questions/30671161/gps-ublox-6-neo6-communication-with-microcontroller-using-spi?fbclid=IwAR2yPGFFkYXUMWzYxADXfQCi6K2N2oqYKWD3_1PUJN-BfQJm7HQKZt46O9A

https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/issues/10?fbclid=IwAR1_FnZKZd6oZQfzkTbCrLfcv61xoDmxjcq3i3FurRyX_bDSYdmM-TlZlNA

https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800

https://www.circuitbasics.com/basics-of-the-spi-communication-protocol/

https://github.com/MajenkoLibraries/SoftSPI


Interactive SIM800L
===
File [BasicInteractiveDebug.ino](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/debug/BasicInteractiveDebug.ino) create an interactive mode for debugging AT command for SIM800L.

Run these commands 

And check for ideal expected value in [sim800L_debug.md](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/debug/sim800L_debug.md)

```md
AT+CFUN=1
AT+CGREG=1
AT+CREG=1
AT+CGATT=1
AT+CMEE=1
AT+CREG? 
AT+CIPSTATUS=?
AT+SAPBR=3,1,"CONTYPE","GPRS"
AT+SAPBR=3,1,"APN","m3-world"
AT+SAPBR=1,1
AT+HTTPINIT 
AT+HTTPPARA="URL","119.82.141.196/testUpload.php?lat=10.784451&lng=106.657540&speed=0.06&accX=8.49&accY=-0.34&accZ=-3.47&name=blackBox1"
AT+HTTPPARA=CID,1
AT+HTTPACTION=1
AT+HTTPREAD
AT+HTTPTERM
```

Script running with fixed data
====

File [sendOK.ino](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/debug/sendOK.ino) will run these AT command in function `xecute_AT` and try send data with fixing GPS values 

check for ideal expected value in [sendOKLog.md](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/debug/sendOKLog.md)
