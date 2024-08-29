#include <Arduino.h>
#include <PID_v1.h>

#define SOUND_SPEED 0.034
const int trigger = 5;  
const int echo = 18;
const int pwm = 4; 

// Variáveis do sensor ultrassônico
long distance;  
float altura_agua;      

// Configuração do PID
double setpoint = 5.0;    
double input, output;      
double Kp = 2.5, Ki = 6.0, Kd = 1.2; 

const double altura_recipiente = 22.90; 
const double base_recipiente = 0;   

// Instancia o objeto PID com as variáveis e parâmetros definidos
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
 
  Serial.begin(115200);

 
  pinMode(trigger, OUTPUT);  
  pinMode(echo, INPUT);      
  pinMode(pwm, OUTPUT);      

  
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(20, 255); 

  
  analogWrite(pwm, 0);

  // Mensagem inicial para o usuário
  Serial.println("Digite valores entre 0 e 20 cm:");
}

void loop() {
  // Verifica se há algum dado disponível na comunicação serial
  if (Serial.available() > 0) {
    // Lê o valor desejado de nível via serial
    double userInput = Serial.parseFloat();
    
    // Verifica se o valor está dentro dos limites permitidos
    if (userInput >= base_recipiente && userInput <= altura_recipiente) {
      setpoint = userInput + 1;  
      Serial.print("Altura desejada: ");
      Serial.print(setpoint);
      Serial.println(" cm");
    } else {
      // Mensagem de erro se o valor estiver fora dos limites.
      Serial.println("Nível fora dos limites entre 0 e 20 cm.");
    }
  }

  // Limpa o buffer serial para evitar leituras incorretas.
  while (Serial.available() > 0) {
    Serial.read();
  }

  // Medir o nível de água com o sensor ultrassônico
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  distance = pulseIn(echo, HIGH);  // Mede o tempo do pulso de retorno.
  
  // Cálculo da altura da água com base no tempo do pulso
  altura_agua = altura_recipiente - (distance * SOUND_SPEED / 2);
  
  // Exibe o nível de água atual no monitor serial
  Serial.print("Altura da água: ");
  Serial.print(altura_agua);
  Serial.println(" cm");


  input = altura_agua; 
  myPID.Compute();

  
  if (abs(setpoint - altura_agua) <= 0.1 || setpoint < altura_agua) {  
    output = 100; 
  }

  int pwmOutput = max(20.0, output); 
  analogWrite(pwm, pwmOutput);

  Serial.print("PWM Output: ");
  Serial.println(pwmOutput);

  delay(1000); 
}
