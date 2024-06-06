const int BUTTON = 13;
const int L_1 = 1;
const int L_2 = 2;
const int L_3 = 3;
const int L_4 = 4;
const int L_5 = 5;
const int L_6 = 6;
const int L_7 = 7;

const int nums[7][7] = {
  {L_4, 0, 0, 0, 0, 0,0},
  {L_3, L_5, 0, 0, 0, 0,0},
  {L_3, L_4, L_5, 0, 0, 0,0},
  {L_1, L_3, L_5, L_7, 0, 0,0},
  {L_1, L_3, L_4, L_5, L_7, 0,0},
  {L_1, L_2, L_3, L_5, L_6, L_7,0},
  {L_1, L_2, L_3,L_4,L_5, L_6, L_7}
};

byte lastButtonState = LOW;

void turn(int num, byte state) {
  for (int i = 0; i < 7; i++) {
    int l = nums[num][i];
    if (l != 0){
    digitalWrite(nums[num][i], state);
    }
  }
}

void setup() {
  randomSeed(analogRead(0));

  pinMode(L_1, OUTPUT);
  pinMode(L_2, OUTPUT);
  pinMode(L_3, OUTPUT);
  pinMode(L_4, OUTPUT);
  pinMode(L_5, OUTPUT);
  pinMode(L_6, OUTPUT);
  pinMode(L_7, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {

  byte buttonState = digitalRead(BUTTON);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    turn(6, LOW);
    int nRandom = random(0, 6);
    turn(nRandom, HIGH);
  }

}