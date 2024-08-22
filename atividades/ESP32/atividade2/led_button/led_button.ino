const int buttonPin = 14;  
const int ledPin = 12; 
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado");
    digitalWrite(ledPin, HIGH);
  } else{
    Serial.println("Botão não pressionado");
    digitalWrite(ledPin, LOW);
  }

  delay(100);

}
