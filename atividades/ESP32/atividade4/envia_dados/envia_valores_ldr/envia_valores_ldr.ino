#include <WiFi.h>

const char* ssid = "esp32";         
const char* password = "ABACAXIAZUL"; 
const char* serverIP = "192.168.43.162"; 
const int port = 80;                    

const int ldrPin = 34; 
int ldrValue = 0;      

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando à rede");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à rede Wi-Fi");
}

void loop() {
  WiFiClient client;
  if (client.connect(serverIP, port)) {
    Serial.println("Conectado ao servidor");
    ldrValue = analogRead(ldrPin);
    client.println(ldrValue);
    Serial.println(ldrValue);
  } else {
    Serial.println("Falha ao conectar ao servidor");
  }

  delay(2000); 
}