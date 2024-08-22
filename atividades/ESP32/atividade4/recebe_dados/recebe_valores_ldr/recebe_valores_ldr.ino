#include <WiFi.h>

const char* ssid = "esp32";         
const char* password = "ABACAXIAZUL"; 

]]
WiFiServer server(80); 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando à rede");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à rede Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.begin(); 
}

void loop() {
  WiFiClient client = server.available(); 

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.print("Recebido: ");
        Serial.println(data);
      }
    }

  }
}
