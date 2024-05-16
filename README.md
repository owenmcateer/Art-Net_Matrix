# Art-Net Matrix
Control a MAX7219 LED Matrix display over Art-Net DMX with a Wifi ESP8266/Arduino


## Hardware requirements
1) ESP8266 or Arduino with Wifi 
2) MAX7219 Dot Matrix (https://www.aliexpress.com/item/1005006661467477.html)

## Setup
1) Install the required libraries listed below.
2) Wiring: `DIN = D6` `CS = D8` `CLK = D5` (editable in code)
3) Set Wifi credentials `ssid` and `pwd`
4) Set Wifi IP and Subnet (optional)
5) Set DMX universe and net
6) Compile and upload
7) Use any Art-Net client to send image data. ie. [MadMapper](https://madmapper.com/)  
[See MadMapper fixture settings](./MadMapper-fixture-settings.png)

## Required libraries
### LedControl
**Author**: [Eberhard Fahle](https://github.com/wayoda/)  
An Arduino library for the MAX7219 and MAX7221  
https://wayoda.github.io/LedControl/  
https://github.com/wayoda/LedControl

### ArtNet
**Author**: [Hideaki Tai](https://github.com/hideakitai)  
Art-Net Sender/Receiver for Arduino (Ethernet, WiFi)  
https://github.com/hideakitai/ArtNet
