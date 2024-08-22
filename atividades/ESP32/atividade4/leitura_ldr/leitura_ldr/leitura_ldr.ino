const int ldrPin = 34; // Pino onde o LDR está conectado
int ldrValue = 0;      // Variável para armazenar o valor lido

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  delay(1000);          // Aguarda a inicialização

  // Configura o pino LDR como entrada
  pinMode(ldrPin, INPUT);
}

void loop() {
  // Lê o valor do LDR
  ldrValue = analogRead(ldrPin);

  // Imprime o valor no monitor serial
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Aguarda um pouco antes de ler novamente
  delay(1000);
}
