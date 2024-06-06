const int BUTTON = 13;

const int NUMS[6][7] = {
  {0, 0, 0, 1, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0},
  {1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1},
  {1, 1, 1, 0, 1, 1, 1},
};
const byte STATES[] = {LOW, HIGH};

byte lastButtonState = LOW;

void dice(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(i+1, STATES[NUMS[num][i]]);
  }
}

void setup() {
  randomSeed(analogRead(0));
  for (int i = 1; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON, INPUT);

}

void loop() {

  byte buttonState = digitalRead(BUTTON);
  if (buttonState != lastButtonState && buttonState == LOW) {
      int nRandom = random(0, 6);
      dice(nRandom);

  }
  lastButtonState = buttonState;
}