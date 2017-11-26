#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "LedControl.h"
#include <pgmspace.h>
#include "MaxMatrix.h"
#include "pgmspace.h"

///////////////             ///////////////
//////////////  variables  ///////////////
/////////////             ///////////////

//////////// constantes  ///////////////
const char* ssid = "WLAN_2DB1"; // red wifi
const char* password =  "913458620abcd"; // contraseña
const char* mqttServer = "192.168.1.2"; // direccion servidor mqtt
const int mqttPort = 1883; // puerto de escucha del servidor mqtt
const char* mqttUser = "jesus"; // usuario mqtt
const char* mqttPassword = "cometa1997"; // contraseña mqtt
const char* tp = "cmnd/sonoffA"; // hilo de sub/pub

PROGMEM const unsigned char CH[] = {
3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

int data = 14;    // DIN pin of MAX7219 module
int load = 13;    // CS pin of MAX7219 module
int clock = 12;  // CLK pin of MAX7219 module

int maxInUse = 1;  //how many MAX7219 are connected

MaxMatrix m(data, load, clock, maxInUse); // define Library

byte buffer[10];

char string1[] = "  Preparado  ";  // Scrolling Text

String k=""; // instancia la conversion de byte* a string (linea )

LedControl lc=LedControl(14,12,13,1); // instancia la conexion con el panel ( pin_gpio_DIN,pin_gpio_CLK,pin_gpio_CS,numero_de_paneles)

unsigned long delayTime=900; // delay para transiciones

byte you1[] = { // simbolo youtube abajo
  B00000000,
  B01111110,
  B11101111,
  B11100111,
  B11100011,
  B11100111,
  B11101111,
  B01111110};


byte you2[] = {// simbolo youtube arriba
  B01111110,
  B11101111,
  B11100111,
  B11100011,
  B11100111,
  B11101111,
  B01111110,
  B00000000};
  
  byte gmail1[] = {// simbolo gmail
  B00000000,
  B10000001,
  B10000001,
  B10011001,
  B10111101,
  B11100111,
  B11000011,
  B00000000};

WiFiClient espClient; // crea el cliente wifi
PubSubClient client(espClient); // crea el cliente mqtt


void you1GO()// convertimos youtube abajo (array de byte) a lineas del panel
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setColumn(0,i,you1[i]);
    
  }
}
void you2GO()// convertimos youtube arriba (array de byte) a lineas del panel
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setColumn(0,i,you2[i]);
    
  }
}
void gmailGO()// convertimos gmail (array de byte) a lineas del panel
{
  for (int i = 0; i <8 ; i++)  
  {
    lc.setColumn(0,i,gmail1[i]);
    
  }
}
void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(maxInUse*8, 0, buffer);
  m.setColumn(maxInUse*8 + buffer[0], 0);
  
  for (int i = 0; i < buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

// Extract characters from Scrolling text
void printStringWithShift(char* s, int shift_speed){
  while (*s != 0){
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
 
void setup() {
 
  Serial.begin(115200); // Iniciamos serial
  m.init(); // module MAX7219
  m.setIntensity(5); // LED Intensity 0-15
  lc.shutdown(0,false);    //Iniciamos la matriz led #1  
  lc.setIntensity(0,10);    //Intensidad de los led en la matriz #1
  lc.clearDisplay(0);      //Apagamos todos los led de la matriz #1
  WiFi.begin(ssid, password); // Nos conectamos al wifi
 
  while (WiFi.status() != WL_CONNECTED) { // hasta que no este conectado se imprime  "Connecting to wifi"
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network"); // se ha conectado
 
  client.setServer(mqttServer, mqttPort); // instanciamos el server
  client.setCallback(callback);// instanciamos la subscripcion 
 
  reconnect(); // nos conectamos al server
  m.shiftLeft(false, true);
  printStringWithShift(string1, 100);  // Send scrolling Text

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      
      // ... and resubscribe
      client.subscribe(tp);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void youtube(){
  if (k == "youtube" ) 
{
  Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  for (int i=0; i <= 4; i++){
     you1GO();
     delay(900);
     you2GO();
     delay(900);
   }
  lc.clearDisplay(0);
}
  
}
void gmail(){
  if (k == "gmail" )  
{
  Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  for (int i=0; i <= 5; i++){
    gmailGO();
     delay(900);
     lc.clearDisplay(0);
     delay(900);
   }
  lc.clearDisplay(0);
}
  
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  k="";
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  for (int i = 0; i < length; i++) {
    k = k + (char)payload[i];
  }
  Serial.println(k);
  youtube();
  gmail();
  Serial.println(" Command: ");
  Serial.println(k);
  Serial.println();
  Serial.println("-----------------------");
}

 
void loop() {
  if (WiFi.status() != WL_CONNECTED){
  WiFi.begin(ssid, password);
  }
  if (!client.connected()) {
        reconnect();
  }
  client.loop();
}
