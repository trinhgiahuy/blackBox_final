blackbox-piPico
===============

The repository contains necessary files for project. The project is my work since late August 2022

It includes building blackbox for motorcycle from source, create SQL Server database and virtualize result on web

***Alpha model***

![image](https://user-images.githubusercontent.com/65078173/194704509-ba1b04b7-01cb-47b9-b26c-84190c8388d8.png)

![image](https://user-images.githubusercontent.com/65078173/194704528-cdb4389e-dd85-4cd7-9735-53938d7234e6.png)

Table of contents
=================
<!--ts-->

  * [Arduino files](#arduino-files)
  * [Hardware](#hardware)
  * [OLD Circuit and PCB Schematic](#old-circuit-and-pcb-schematic)
     * [UPDATED Schematic](#updatd-schematic)
  * [SQL Server](#sql-server)
     * [Installation](#installation)
     * [Create User](#create-user)
     * [PHP files](#php-files)
  * [Debug and Troubleshoot](#debug-and-troubleshoot)
  * [Author](#author)
<!--te-->


Arduino files
============

- RECOMMEND: **invertGPS_to_GSM.ino**
This code uses NMEAGPS library for GPS  and AlfSofSerial for GSM as **UPDATED** schemantic

- **final_v1.ino**
This code uses SIM800L AT command consecutively to upload data to server 

- **OK_lib.ino**
This code use TinyGSM library to upload data to server

Hardware
============

- DFRduino Nano
- SIM800L module
- MPU6050
- Ublox-NEO6m + External GPS
- Charging circuit TP4056
- Charging batteries 3.7V
- LM2596 3A
- DC-DC Boost Converter XL6009
- LEDs
- 330 Ohm resistors
- 1k Ohm resistors
- 10k Ohm resistors
- 4700uF capacitor

**OLD** Circuit and PCB Schematic
============

![image](https://user-images.githubusercontent.com/65078173/194696929-791c887d-03b3-4f9d-9a40-777e35631ec0.png)
![image](https://user-images.githubusercontent.com/65078173/194696960-1753fb4b-3b0a-4011-8fa3-bedc44a1a8bf.png)

```
//-----------------
//   Choose a serial port for the GPS device:
//
//   BEST: For a Mega, Leonardo or Due, use the extra hardware serial port
//#define gpsPort Serial1

//   2nd BEST:  For other Arduinos, use AltSoftSerial on the required pins
//                 (8&9 for an UNO)
// #include <AltSoftSerial.h>
// AltSoftSerial gpsPort;  // pin 8 to GPS TX, pin 9 to GPS RX

//   3rd BEST:  If you can't use those specific pins (are you sure?),
//                 use NeoSWSerial on any two pins @ 9600, 19200 or 38400
//   WORST:  SoftwareSerial is NOT RECOMMENDED

//-----------------
```

UPDATED Schematic:
------------------

For using AltSoftSerial, it requires pin 8 & 9 in UNO, thus the pins is updated as below

```md
ALtSoftSerial for SIM800L pin
D8 (Rx) --- SIM Tx
D9 (Tx) --- SIM Rx

NeoSWSerial for Neo6M-GPS. **NOTE**: This requires level-shift
D10 (Rx) --- GPS Tx
D11 (Tx) --- GPS RX

```

SQL Server
============

Installation
-------------------

```shell
root@voiceai2:~# apt-get install php7.4 php7.4-dev php7.4-xml -y --allow-unauthenticated
...

Creating config file /etc/php/7.4/cli/php.ini with new version
...
Creating config file /etc/php/7.4/apache2/php.ini with new version
libapache2-mod-php7.4: php8.1 module already enabled, not enabling PHP 7.4
Setting up php-pear (1:1.10.13+submodules+notgz+2022032202-2+ubuntu20.04.1+deb.sury.org+1) ..                                                                                                .
Setting up po-debconf (1.0.21) ...
Setting up php7.4 (1:7.4.30-5+ubuntu20.04.1+deb.sury.org+1) ...
Setting up debhelper (12.10ubuntu1) ...
Setting up dh-autoreconf (19) ...
Setting up pkg-php-tools (1.38) ...
Processing triggers for libc-bin (2.31-0ubuntu9.7) ...
Processing triggers for man-db (2.9.1-1) ...
Processing triggers for install-info (6.7.0.dfsg.2-5) ...
Processing triggers for php7.4-cli (1:7.4.30-5+ubuntu20.04.1+deb.sury.org+1) ...
Processing triggers for libapache2-mod-php7.4 (1:7.4.30-5+ubuntu20.04.1+deb.sury.org+1) ...

root@voiceai2:~# sudo su
root@voiceai2:~# curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   983  100   983    0     0   3254      0 --:--:-- --:--:-- --:--:--  3254
OK
root@voiceai2:~# curl https://packages.microsoft.com/config/ubuntu/20.04/prod.list > /etc/apt                                                                                                /sources.list.d/mssql-release.list
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100    89  100    89    0     0    406      0 --:--:-- --:--:-- --:--:--   404

root@voiceai2:~# exit
exit
root@voiceai2:~# sudo apt-get update

root@voiceai2:~# sudo ACCEPT_EULA=Y apt-get install msodbcsql17

root@voiceai2:~# sudo ACCEPT_EULA=Y apt-get install mssql-tools

root@voiceai2:~# source ~/.bashrc

root@voiceai2:~# sudo pecl install sqlsrv

Warning: foreach() argument must be of type array|object, null given in Command.php on line 2                                                                                                49
PHP Warning:  foreach() argument must be of type array|object, null given in /usr/share/php/P                                                                                                EAR/Command.php on line 249

Warning: foreach() argument must be of type array|object, null given in Command.php on line 2                                                                                                49
PHP Warning:  foreach() argument must be of type array|object, null given in /usr/share/php/P                                                                                                EAR/Command.php on line 249
...
XML Extension not found
```

[SOLVE PECL XML extension not found](https://bobcares.com/blog/pecl-xml-extension-not-found/)

```shell
root@voiceai2:~# sudo apt-get install php-xml php7.0-xml
...
Build complete.
Don't forget to run 'make test'.

running: make INSTALL_ROOT="/tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1" install
Installing shared extensions:     /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr/lib/php/20190902/
running: find "/tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1" | xargs ls -dils
398714   4 drwxr-xr-x 3 root root   4096 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1
398761   4 drwxr-xr-x 3 root root   4096 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr
398762   4 drwxr-xr-x 3 root root   4096 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr/lib
398763   4 drwxr-xr-x 3 root root   4096 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr/lib/php
398764   4 drwxr-xr-x 2 root root   4096 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr/lib/php/20190902
398759 428 -rwxr-xr-x 1 root root 436008 Sep  1 20:01 /tmp/pear/temp/pear-build-rootQVQGPC/install-sqlsrv-5.10.1/usr/lib/php/20190902/sqlsrv.so

Build process completed successfully
Installing '/usr/lib/php/20190902/sqlsrv.so'
install ok: channel://pecl.php.net/sqlsrv-5.10.1
configuration option "php_ini" is not set to php.ini location
You should add "extension=sqlsrv.so" to php.ini

```

```shell
sudo pecl install pdo_sqlsrv
..
Build complete.
Don't forget to run 'make test'.

running: make INSTALL_ROOT="/tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1" install
Installing shared extensions:     /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr/lib/php/20190902/
running: find "/tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1" | xargs ls -dils
398725   4 drwxr-xr-x 3 root root   4096 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1
398774   4 drwxr-xr-x 3 root root   4096 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr
398775   4 drwxr-xr-x 3 root root   4096 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr/lib
398776   4 drwxr-xr-x 3 root root   4096 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr/lib/php
398777   4 drwxr-xr-x 2 root root   4096 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr/lib/php/20190902
398772 432 -rwxr-xr-x 1 root root 440528 Sep  1 20:19 /tmp/pear/temp/pear-build-rootsryWo3/install-pdo_sqlsrv-5.10.1/usr/lib/php/20190902/pdo_sqlsrv.so

Build process completed successfully
Installing '/usr/lib/php/20190902/pdo_sqlsrv.so'
install ok: channel://pecl.php.net/pdo_sqlsrv-5.10.1
configuration option "php_ini" is not set to php.ini location
You should add "extension=pdo_sqlsrv.so" to php.ini
```
  
---
## SWITCH PHP 8. to 7.4

[Instr](https://stackoverflow.com/questions/67045511/cannot-switch-php-version-from-8-0-to-7-4-on-ubutnu-20-04)


```
root@voiceai2:~# sudo a2enmod php7.4
Considering dependency mpm_prefork for php7.4:
Considering conflict mpm_event for mpm_prefork:
Considering conflict mpm_worker for mpm_prefork:
Module mpm_prefork already enabled
Considering conflict php5 for php7.4:
Enabling module php7.4.
To activate the new configuration, you need to run:
  systemctl restart apache2

```

DISABLE PHP8.1 and REstart Apache2

![image](https://user-images.githubusercontent.com/65078173/187929631-ddf3d756-cea3-4739-95a8-a2aed3e37b54.png)

Create User 
-----------

Login as sa and grant system admin role to user

```shell
1> USE testdb
2< GO;
Changed database context to 'testdb'.
1> CREATE LOGIN huy WITH PASSWORD='Huyblackbox1@';
2> CREATE USER huy FOR LOGIN huy
3> ALTER SERVER ROLE sysadmin ADD MEMBER huy;
3> GO
```

Login as user huy

`root@voiceai2:~# sqlcmd -S 127.0.0.1 -U SA -P 'Blackbox1@'`

Direct to to context `testdb` and create table mydb as user huy

```sql
create table mydb(dateUploaded datetime, lat float(24), lng float(24), speed float(10), accX float(24), accY float(24), accZ float(24), name varchar(24) NOT NULL);
```

PHP-files
---------

[text_upload.php](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/test_upload.php) is called in Arduino to upload data to database

[test_export.php](https://github.com/trinhgiahuy/blackbox-piPico/blob/main/test_export.php) currently return the latest data by Dateuploaded by group id. Useful for software software virtualization

Debug and Troubleshoot
======================

See [debug](https://github.com/trinhgiahuy/blackbox-piPico/tree/main/debug) for more information

Author
======

* Huy Trinh
* Phuc Tran


