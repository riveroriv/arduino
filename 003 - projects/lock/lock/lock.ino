#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

char password[4] = { '5', '4', '3', '2' }, pile[4], confirm[4];
char AUTH_KEY = '#', CHANGE_KEY = '*';
bool inRepeat = false, inVerify = false;
int posRepeat = 0, posVerify = 0, posMessage = 0;
String message = "";

void screen() {
  lcd.clear();
  for (int i = 0; i < 4; i++) {
    char d = pile[i];
    lcd.setCursor(6 + i, 0);
    lcd.print(d ? d : '_');
  }

  lcd.setCursor(posMessage, 1);
  lcd.print(message);
}
void reset() {
  for (int i = 0; i < 4; i++) pile[i] = '\0';
  screen();
}
void addKey(char key) {
  for (int i = 0; i < 3; i++) pile[i] = pile[i + 1];
  pile[3] = key;
  screen();
  if (inVerify)
    posVerify++;
  if (inRepeat)
    posRepeat++;
}
bool isValid() {
  for (int i = 0; i < 4; i++)
    if (pile[i] == '\0') return false;
  return true;
}
bool repeat() {
  for (int i = 0; i < 4; i++) {
    if (pile[i] == '\0' || confirm[i] != pile[i]) return false;
  }
  return true;
}
void change() {
  for (int i = 0; i < 4; i++) password[i] = confirm[i];
}
void saveNew() {
  for (int i = 0; i < 4; i++) confirm[i] = pile[i];
}
void setMessage(String m) {
  posMessage = abs((16 - m.length()) / 2);
  message = m;
  screen();
}
bool authenticate() {
  for (int i = 0; i < 4; i++) {
    if (pile[i] == '\0' || password[i] != pile[i]) return false;
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  setMessage("TYPE PIN");
}

void loop() {
  char key = keypad.getKey();
  if (key && key != AUTH_KEY and key != CHANGE_KEY) {
    if (posRepeat < 4 && posVerify < 4) {
      addKey(key);
      if (inRepeat && posRepeat == 4) {
        if (repeat()) {
          setMessage("REPEAT OLD PIN");
          inVerify = true;
        } else {
          setMessage("DOESN'T MATCH");
          delay(3000);
          setMessage("TYPE PIN");
        }
        inRepeat = false;
        posRepeat = 0;
        posVerify = 0;
        reset();
      } else if (inVerify && posVerify == 4) {
        bool auth = authenticate();
        if (auth) {
          change();
          setMessage("CHANGED !");
        } else
          setMessage("GET OUT !");

        delay(3000);
        inVerify = false;
        posVerify = 0;
        setMessage("TYPE PIN");

        reset();
      }
    }
  } else if (key == AUTH_KEY && !(inRepeat || inVerify)) {
    bool auth = authenticate();
    if (auth)
      setMessage("NICE !");
    else
      setMessage("GET OUT !");

    delay(3000);
    setMessage("TYPE PIN");
    reset();
  } else if (key == CHANGE_KEY && !(inRepeat || inVerify)) {
    if (!isValid()) {
      setMessage("4 DIGITOS !");
      delay(3000);

      setMessage("TYPE PIN");
    } else {
      saveNew();
      setMessage("REPEAT NEW PIN");
      inRepeat = true;
      posRepeat = 0;
    }
    reset();
  }
}