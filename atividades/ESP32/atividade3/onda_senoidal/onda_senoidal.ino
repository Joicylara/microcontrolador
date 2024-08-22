#include <math.h>

const int dacPin = 25;         
const int samples = 100;      
const int amplitude = 127;    
const int offset = 128;        
const int delayTime = 1;      
// esta dando 100ms, devido o delay*samples, para realizar o ciclo

void setup() {
  // Nada para configurar no setup para o DAC
}

void loop() {
  for (int i = 0; i < samples; i++) {
    
    int sineValue = amplitude * sin(2 * PI * i / samples) + offset;
    dacWrite(dacPin, sineValue);
    delay(delayTime);
  }
}
