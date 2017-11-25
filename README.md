# esp8266-mqtt-matrix
Code for notifications via mqtt with Esp8266 and 8x8 max7219 driven led matrix


- You will need an Esp8266 board , five jumpers and an 8x8 max7219 driven led matrix.
- I use it with a mosquitto server, openhab 2.0 (with openhab cloud), and ifttt.
- My code is not storage efficient (pretty noob with c++),be aware it could not fit your device.
- This code uses librarys that are not mine , all credits to the developers that created them. Such as :
        https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi                                                               
        https://github.com/knolleary/pubsubclient                                                                                         
        https://github.com/wayoda/LedControl

- First release has only youtube and gmail icons.This web its nice for drawing new ones:                                                   
  https://xantorohara.github.io/led-matrix-editor/
- It works with one or more displays , eventhough the code is now working with only one.
- You are free to use it and edit it as you want , also i'll upload any provided change if it 
  performs better in any way.
- Schematics of the connection 
  
        Display<+++++>esp<---->wifi<----->mqtt + openhab 
                                                     |
                                                     |---------> internet(openhab cloud)<-----> ifttt
                              
- You will have to edit this parameters to suit your configuration.
      
      const char* ssid = "WLAN_XXXX"; // red wifi
      const char* password =  "PASSWORD"; // contraseña
      const char* mqttServer = "server.lan/"; // direccion servidor mqtt
      const int mqttPort = 1883; // puerto de escucha del servidor mqtt
      const char* mqttUser = "USER"; // usuario mqtt
      const char* mqttPassword = "USERPASS"; // contraseña mqtt
      const char* tp = "cmnd/EspNotifier"; // hilo de sub/pub
      LedControl lc=LedControl(14,12,13,1); // instancia la conexion con el panel ( pin_gpio_DIN,pin_gpio_CLK,pin_gpio_CS,numero_de_paneles)

