

// Definición de la matriz del teclado
char tecla[4][4] = {
  {'1','2','3','A'}, 
  {'4','5','6','B'}, 
  {'7','8','9','C'}, 
  {'*','0','#','D'}
};

// Contraseña actual
char pass[4] = {'5','4','3','2'};

// Pila para almacenar las últimas teclas ingresadas
char pila[4] = {'\0', '\0', '\0', '\0'};

// Definición de teclas especiales
const char NEW_KEY = '*';
const char AUTH_KEY = '#';
char last = '\0';

// Pines de los LEDs
const int LR = 3;
const int LA = 4;
const int LV = 13;

void setup() {
  for (int i = 5; i <= 8; i++) pinMode(i, OUTPUT);
  for (int i = 9; i <= 12; i++) pinMode(i, INPUT_PULLUP);
  
  pinMode(LA, OUTPUT);				
  pinMode(LV, OUTPUT);				
  pinMode(LR, OUTPUT);				
  
  Serial.begin(9600);
}

char leTeclado() {
  for (byte col = 0; col < 4; col++) {
    digitalWrite(8 - col, LOW); // Activar la columna actual
    
    for (byte lin = 0; lin < 4; lin++) {
      if (digitalRead(12 - lin) == LOW) {
        while (digitalRead(12 - lin) == LOW); // Esperar hasta que se suelte la tecla
        return tecla[lin][col]; // Retornar el valor de la tecla
      }
    }
    digitalWrite(8 - col, HIGH); // Desactivar la columna actual
  }
  return '\0'; // Ninguna tecla fue presionada
}

void reset() { 
  for (int i = 0; i < 4; i++) pila[i] = '\0';
}

void addKey(char key) {
  for (int i = 0; i < 3; i++) pila[i] = pila[i + 1];
  pila[3] = key;

  for (int i = 0; i < 4; i++) Serial.print(pila[i]);
  Serial.println();
}

bool change() {
  for (int i = 0; i < 4; i++) {
    if (pila[i] == '\0') return false;
  }

  for (int i = 0; i < 4; i++) pass[i] = pila[i];
  return true;
}

bool auth() {
  for (int i = 0; i < 4; i++) {
    if (pila[i] == '\0' || pass[i] != pila[i]) return false;
  }
  return true;
}

void loop() {
  digitalWrite(LR, HIGH);
  char tec = leTeclado();
  
  if (tec != '\0' && tec != last) {
    Serial.println(tec);
    if (tec == AUTH_KEY) {
      if (auth()) {
        Serial.println("authenticated");
        digitalWrite(LR, LOW);
        digitalWrite(LV, HIGH);
        delay(2000);
        digitalWrite(LV, LOW);
      } else {
        Serial.println("auth failed");
      }
      reset();
    } else if (tec == NEW_KEY) {
      if (change()) {
        Serial.println("changed");
        digitalWrite(LR, LOW);
        digitalWrite(LA, HIGH);
        delay(2000);
        digitalWrite(LA, LOW);
      } else {
        Serial.println("change failed");
      }
      reset();
    } else {
      addKey(tec);
    }
    last = tec;
  } else if (tec == '\0') {
    last = '\0';
  }
  delay(100);
}
