# esp8266-mqtt-matrix
Code for notifications via mqtt with Esp8266 and 8x8 max7219 driven led matrix


- You will need an Esp8266 board , five jumpers and an 8x8 max7219 driven led matrix.
- I use it with a mosquitto server, openhab 2.0 (with openhab cloud), and ifttt.
- Dont forget to install openhab cloud bidding , enable your items through the PAPER UI , and connect it to ifttt.
- My code is not storage efficient (pretty noob with c),be aware it could not fit your device.
- This code uses librarys that are not mine , all credits to the developers that created them. Such as :
        https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi                                                               
        https://github.com/knolleary/pubsubclient                                                                                         
        https://github.com/wayoda/LedControl

- First release has only youtube and gmail icons.This web is neat for drawing new ones:                                                   
  https://xantorohara.github.io/led-matrix-editor/
- It works with one or more displays , eventhough the code is now working with only one.
- You are free to use it and edit it as you want , also i'll upload any provided change if it 
  performs better in any way.
- Schematics of the connection:
  
        Display<+++++>esp<---->wifi<----->mqtt + openhab
                                                     ^
                                                     |
                                                     |
                                                  internet(openhab cloud)<-----> ifttt
                                                                                    ^
                   new Gmail--------------------------------------------------------|                      
                   new Youtube video -----------------------------------------------|                      
                                                     
                              
- You will have to edit this parameters to suit your configuration.
      
      const char* ssid = "WLAN_XXXX"; // red wifi
      const char* password =  "PASSWORD"; // contraseña
      const char* mqttServer = "server.lan/"; // direccion servidor mqtt
      const int mqttPort = 1883; // puerto de escucha del servidor mqtt
      const char* mqttUser = "USER"; // usuario mqtt
      const char* mqttPassword = "USERPASS"; // contraseña mqtt
      const char* tp = "cmnd/EspNotifier"; // hilo de sub/pub
      int data = 14;    // DIN pin of MAX7219 module
      int load = 13;    // CS pin of MAX7219 module
      int clock = 12;  // CLK pin of MAX7219 module
      int maxInUse = 1;  //how many MAX7219 are connected

# SerialToMatrix

- You will need an Esp8266 board , five jumpers and an 8x8 max7219 driven led matrix.
- My code is not storage efficient (pretty noob with c),be aware it could not fit your device.
- This code uses librarys that are not mine , all credits to the developers that created them. Such as :
        https://github.com/t3chguy/arudino-maxmatrix-library                                                                            
        
- It works with one or more displays , eventhough the code is now working with only one.
- You are free to use it and edit it as you want , also i'll upload any provided change if it 
  performs better in any way.
  
- You will have to edit this parameters to suit your configuration.

         int data = 14;    // DIN pin of MAX7219 module
         int load = 13;    // CS pin of MAX7219 module
         int clock = 12;  // CLK pin of MAX7219 module
         int maxInUse = 1;  //how many MAX7219 are connected
         
- Scheme
        
        Serial:
        Please enter something: 
                hello world
        Please enter speed: 
                70
                ||
                 ------------------------------->Matrix(showing "hello world" at speed "70")


