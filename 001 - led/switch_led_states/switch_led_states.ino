// Definir los pines utilizados
const int ledPin = 13; // Pin para la luz LED
const int buttonPin = 2; // Pin para el botón

// Variable para almacenar el estado del botón
byte lastButtonState = LOW;
byte ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Configurar el pin de la luz LED como salida
  pinMode(buttonPin, INPUT); // Configurar el pin del botón como entrada
}

void loop() {
  // Leer el estado del botón
  byte buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      ledState = (ledState == HIGH) ? LOW: HIGH;
      digitalWrite(ledPin, ledState);
    }
  }
  delay(1);
}
