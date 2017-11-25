#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "LedControl.h"
#include <pgmspace.h>

///////////////             ///////////////
//////////////  variables  ///////////////
/////////////             ///////////////

//////////// constantes  ///////////////
const char* ssid = "WLAN_XXXX"; // red wifi
const char* password =  "PASSWORD"; // contraseña
const char* mqttServer = "server.lan/"; // direccion servidor mqtt
const int mqttPort = 1883; // puerto de escucha del servidor mqtt
const char* mqttUser = "USER"; // usuario mqtt
const char* mqttPassword = "USERPASS"; // contraseña mqtt
const char* tp = "cmnd/EspNotifier"; // hilo de sub/pub


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
  
  byte gmail[] = {// simbolo gmail
  B00000000,
  B11000011,
  B11100111,
  B11111111,
  B11011011,
  B11000011,
  B11000011,
  B00000000};

WiFiClient espClient; // crea el cliente wifi
PubSubClient client(espClient); // crea el cliente mqtt


void you1GO()// convertimos youtube abajo (array de byte) a lineas del panel
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,you1[i]);
    
  }
}
void you2GO()// convertimos youtube arriba (array de byte) a lineas del panel
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,you2[i]);
    
  }
}
void gmailGO()// convertimos gmail (array de byte) a lineas del panel
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,gmail[i]);
    
  }
}
 
void setup() {
 
  Serial.begin(115200); // Iniciamos serial
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
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
