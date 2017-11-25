# esp8266-mqtt-matrix
Code for notifications via mqtt with Esp8266 and 8x8 max7219 driven led matrix


- You will need an Esp8266 board , five jumpers and an 8x8 max7219 driven led matrix.
- I use it with a mosquitto server, openhab 2.0 (with openhab cloud), and ifttt.
- My code is not storage efficient (pretty noob with c++),be aware it could not fit your device.
- This code uses librarys that are not mine , all credits to the developers that created them. Such as :
        https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi                                                               
        https://github.com/knolleary/pubsubclient                                                                                         
        https://github.com/wayoda/LedControl

- First realise has only youtube and gmail icons.This web its nice for drawing new ones:                                                   
  https://xantorohara.github.io/led-matrix-editor/
- It works with one or more displays , eventhow the code is now working with only one.
- You are free to use it and edit it as you want , also i'll upload any provided change if it 
  performs better in any way.
