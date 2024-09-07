#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Configurações do Firebase
#define FIREBASE_HOST "https://sensores-micro-29f70-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyC8N4eAvDDESX9SzhTqg0uVpMO0zsV5wRI"

// Configurações de Wi-Fi
const char* ssid = "Betolvi";
const char* password = "19231523";

// Objetos Firebase
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;  // Adicionando objeto FirebaseAuth

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi!");

  // Configurar Firebase
  firebaseConfig.api_key = FIREBASE_AUTH;
  firebaseConfig.database_url = FIREBASE_HOST;

  // Configurar autenticação se necessário
  firebaseAuth.user.email = "joicykelly2301@gmail.com";  // Email do usuário
  firebaseAuth.user.password = "abacaxiazul";            // Senha do usuário

  // Inicializar Firebase com configuração e autenticação
  Firebase.begin(&firebaseConfig, &firebaseAuth);  // Passar ambos os parâmetros
  
  // Opcional: Ativar reconexão automática
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Ler temperatura e umidade do DHT22
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  // Enviar temperatura para o Firebase
  if (Firebase.RTDB.setFloat(&firebaseData, "/sensors/temperature", temp)) {
    Serial.println("Temperatura enviada com sucesso.");
  } else {
    Serial.println("Erro ao enviar temperatura.");
  }

  // Enviar umidade para o Firebase
  if (Firebase.RTDB.setFloat(&firebaseData, "/sensors/humidity", hum)) {
    Serial.println("Umidade enviada com sucesso.");
  } else {
    Serial.println("Erro ao enviar umidade.");
  }

  // Exibir valores
  Serial.print("Umidade: ");
  Serial.print(hum);
  Serial.print(" %, Temperatura: ");
  Serial.print(temp);
  Serial.println(" ºC");

  // Delay de 5 segundos
  delay(5000);
}
