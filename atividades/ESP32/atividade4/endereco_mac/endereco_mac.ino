#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(2000); // Aguarda um tempo para a inicialização do Serial

  // Iniciar o módulo Wi-Fi
  WiFi.mode(WIFI_STA); // Configura o ESP32 em modo station
  delay(1000); // Aguarda mais um pouco para garantir que o Wi-Fi esteja inicializado

  // Obter e imprimir o endereço MAC do ESP32
  Serial.println("ESP32 MAC Address: ");
  String macAddress = WiFi.macAddress();
  Serial.println(macAddress);
}

void loop() {
  // O loop pode ficar vazio
}
