SQL command to get latest information of group by id of black box

```sql
1>  select * from mydb where dateUploaded in (select max(dateUploaded) from mydb group by name)
2> go
dateUploaded            lat            lng            speed          accX           accY           accZ           name
----------------------- -------------- -------------- -------------- -------------- -------------- -------------- ------------------------
2022-09-08 22:25:13.023      10.784451      106.65754   5.9999999E-2      8.4899998          -0.34          -3.47 blackBox1
...
```

Another issue, drop params, when printout or cannot print:

![image](https://user-images.githubusercontent.com/65078173/189707423-a1c200f5-5400-4be7-a251-226bee01777c.png)

READ NORMALLY FROM MPU6050 only file

![image](https://user-images.githubusercontent.com/65078173/189707273-4bba71b2-41a0-4ba6-affa-8dd9ec1ac9da.png)

## [~~SIM800 Issue~~](https://arduino.stackexchange.com/questions/90709/sim800l-cannot-wait-for-network)

From [this](https://arduino.stackexchange.com/questions/80428/sim800l-module-on-arduino-nano), GND of battery must shared with Arduino for common potential.. Add capacitor to Vcc-GND, minimize wire length


```sql
create table mydb(dateUploaded datetime, lat float(24), lng float(24), speed float(10), accX float(24), accY float(24), accZ float(24), name varchar(24) NOT NULL);
```
inspirational idea: **[Arduino with sim800l and Ublox Neo 6m module. On the server side php and mysql.](https://github.com/Neumi/gsm-gps-tracker)**

Example request

```ino
119.82.141.196/testUpload.php?lat=10.784451&lng=106.657540&speed=0.06&accX=8.49&accY=-0.34&accZ=-3.47&name=blackBox1
```
--- SIM800L---
[Real project suggestion & sketch](https://www.teachmemicro.com/sim800-network-test-troubleshoot/#:~:text=If%20the%20power%20to%20the,means%20it's%20connected%20through%20GPRS.)

Thêm mạch sạc pin: [TP4056](https://hshop.vn/products/mach-sac-pin-lithium1a-v2), mạch tăng áp [xl6009](https://hshop.vn/products/mach-tang-op-dc-xl6009) 

![image](https://user-images.githubusercontent.com/65078173/188273041-a5b03298-350e-40d5-a9b2-6169ccb0c8e6.png)



[Pin 3.7V Lithium](https://pin.net.vn/shop/pin-lithium-polymer-1200mah-3-7v-503759):  CS 4:  Hẻm 23 đường Hòa Hưng- P.12- Q.10- TP. Hồ Chí Minh.

[APN Vinaphone](https://dichvu3gvinaphone.vn/huong-dan-cai-dat-diem-truy-cap-apn-vinaphone/)

---
PASS SQL SERVER: Blackbox1@

[Best Server Side Solution for real-time gps](https://stackoverflow.com/questions/2528779/what-is-the-best-server-side-solution-for-a-real-time-gps-tracking-system)


**[CONNECT SERVER USING SERVER's IP](https://stackoverflow.com/questions/71114274/arduino-send-get-request-to-server-on-local-network)**

```ino
char server[] = 119.82.141.196;

//TODO: REMEMBER TO OPEN PORT 80 IN SERVER
// connect to web server on port 80:

if(client.connect(server, 80)>0) {
  // if connected:
  Serial.println("Connected to server");
  ...
}
```

### [Dynamic web server](https://iosoft.blog/2021/09/26/pico-wireless-web-esp32/)

Report back live data captured by the pico, we need method to return dynamically-changing value

3 main ways: **server-side includes(SSI), AJAX, and on-demand page creation**


---

## [4 methods for powering sim800L](https://www.youtube.com/watch?v=j2mM4ssH8nk&ab_channel=Clgproject)

- Using capacitor: 2200uF/10V (A Must for stablize the voltage supply)
- Method 3: Use buck converter (12V- ~4.1 4.2V)

[Future approach, SIM800L is quite obsolete now...](https://forum.arduino.cc/t/how-to-power-sim800l-chip/700304/7)


## Document

[Arduino Pro Mini](https://docs.arduino.cc/retired/boards/arduino-pro-mini)

[DFRduino Nano](https://wiki.dfrobot.com/Arduino_Nano_328__SKU__DFR0010_#target_1)



**[Ref Circuit Diagram](https://www.circuito.io/app?components=10218,11022,11028,316349,975601)**

**[Resetting Arduino from 3.3V Source circuit](https://create.arduino.cc/projecthub/ruchir1674/how-to-interface-gps-module-neo-6m-with-arduino-8f90ad)

Things to buy

- 3.3V regulator
- 100nF ceramic capacitor (tụ gốm)
- Electrolytic Decoupling Capacitors - 10uF/25V
- 1k Ohm resistor
- 10k Ohm resistor x 7

From https://www.exploreembedded.com/wiki/Setting_up_GPRS_with_SIM800L

- NPN transistor ( BD137 or other)
- 1k Ohm resistor

From nshop

- Anten GSM/GPRS/3G
- Cáp chuyển đổi IPEX U.FL sang SMA cái dài 15cm
- Jack pin 9V

---

### Other GITHUB proj

**[GPS Datalogger, Spatial Analysis, and Azure IoT Hub](https://create.arduino.cc/projecthub/ShawnCruise/gps-datalogger-spatial-analysis-and-azure-iot-hub-072956)**

- Resistor 10k Ohm
- Resistor 221 Ohm
- GPIO button
- Side switch
- 

**[MuellerA/Longan-Nano_Ubox-Neo-6M](https://github.com/MuellerA/Longan-Nano_Ubox-Neo-6M)**




### For multiple repos install 

https://gist.github.com/benhurott/a85be9e534622d9e4e6acb4765bd4b38

**[NEO 6M with SD Card](https://create.arduino.cc/projecthub/adrianos_botis/gps-neo-6m-portable-tracker-with-micro-sd-card-module-8374d8)**

[A simple tutorial for troubleshooting GPSs on Arduino](https://github.com/StuartsProjects/GPSTutorial)



## Des

Bản dùng module SIM:

+ Module sensor với accelerator + GPS location
+ Module SIM
+ MCU: Nano.

Work flow: Gửi data trực tiếp theo thgian về server.

Bản lưu data local:

+ Rasbp Pico
+ Module sensor với accelerator + GPS location.

Work flow: Lấy data với khoảng tgian nhất định và lưu local tại Pico (gắn SD card 32gb) (Mua thêm SD card để test)


## Other

[Khai niem 2G 2.5G 3G](https://www.bkaii.com.vn/tin-nganh-2/103-khai-niem-co-ban-ve-1g-2g-gsm-2-5g-gprs-3g-4g)


## Hardware list

Edge side

For Nano from DFRbot: DFRuino select the alternate Processor labelled **"ATmega328P (Old Bootloader)"** (works with my v3.1 board).

[DFRuino Nano Doc](https://wiki.dfrobot.com/Arduino_Nano_328__SKU__DFR0010_)





ID1 (OFFLINE)

- Pi Pico
- Location Module u-Blox GPS: [NEO-6M GPS](https://microcontrollerslab.com/neo-6m-gps-module-raspberry-pi-pico-micropython/)

- Sim Module: [SIM800L](https://www.theelectronics.co.in/2021/09/raspberry-pi-pico-with-sim800l-module.html)

https://arduinotoday.blogspot.com/2022/02/send-data-to-server-using-sim800l-gprs.html




- [jakhax/raspberry-pi-sim800l-gsm-module](https://github.com/jakhax/raspberry-pi-sim800l-gsm-module)
- https://www.instructables.com/Raspberry-Pi-With-a-GSM-Module/
- Try use this library: https://github.com/vshymanskyy/TinyGSM
- 

M2 X 6mm Screws

Design and print 3D


Server side

- Ubuntu Server

## Customer:
- VPBank
- FE Credit 
- PTI Insurance

---
### DRAFT

* [u-blox MAX-7Q GPS-GNSS Module - from SIQMA ROBOTICS - have pins out](https://store.siqma.com/ublox-max-7q-gps-gnss-module.html)

- Adafruit Triple-Axis Accelerometer MMA8451
