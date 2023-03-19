#include <Arduino.h>
#include "libwifi.h"
#include "Wifi.h"



const char * ssid = "ASUSDCGG";
const char * password = "3164173706Cc";
const char * host = "dweet.io";
const int puerto = 80;
//String server="dweet.io"; es redundante con host 
String url="/dweet.io/dweet/for/uceva02?temperatura=32.5";
 


//@author Diana Gomez
/**
 * @brief Esta es la funcion de configuracion del dispositivo
 * 
 * 
*/

 void setup() {
 pinMode(2,OUTPUT); //Coloco el pin 2 como salida
 Serial.begin(115200);
 Serial.println("Inicializando el dispositivo");
 conectarWifi(ssid, password);

 
}
/**
 * @brief Esta funcion con bucle infinito
 prueba
*/
void loop() {
  WiFiClient cliente;//creamos cliente TCP por wifi 
  
  //BLOQUE que raliza la conexion al servidor
  if(!cliente.connect(host, puerto)){
    Serial.println("Error conexion al host fallida");
    delay(2000);
    return;
  } 

  //Peticion (request) GET al servidor HTTP
  cliente.print("GET " +url+" HTTP/1.1\r\nHost: "+String(host)+"\r\n"+"Connection: close\r\n\r\n");
  //Tiempo al servidor a que responda la peticion(response)
  //delay(5000);// no funciona aqui porque bloquea wifi 
  unsigned long milisegundos = millis();//hora de inicio
  while (cliente.available()== 0){//preguntamos si no hay datos recibidos disponibles
      if(millis()-milisegundos > 5000){//millis hora actual  menos el instante anterior
      Serial.println("Se expiro el tiempo de la conexion");
      cliente.stop();
      }
   
   }
  while (cliente.available()){
    String linea = cliente.readStringUntil('\r');//lea string hasta que encuentre lo que esta en comilla simple
    Serial.println(linea);
  }
    Serial.println("Fin de conexion");
    cliente.stop();
    
    delay(2000);//espero 2s
}