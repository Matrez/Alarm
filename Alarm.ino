/*
   2,3 cervena LED
   4,5 zlta LED
   6,7 zelena LED
   8,9 tlacidla
   10,11 senzory otvarania
   12 senzor otrasu
   13 bzuciak

*/

const unsigned long timeToDeactivation = 10000; // V milisekundach
unsigned long time;

const short leftBtn = 8;
const short rightBtn = 9;
short score = 0;
const short bzuciak = 13;

boolean doNotBzuciak = false;

void setup() {
  for (int i = 2; i <= 7; ++i) {
    pinMode(i, OUTPUT);
  }
  for (int i = 8; i <= 12; ++i) {
    pinMode(i, INPUT);
  }
  pinMode(13, OUTPUT);
}

void loop() {
  // Kontroluje rozopnute magnety
  if ((digitalRead(10) == LOW) || (digitalRead(11) == LOW)) {
    time = millis();
    while ((millis() - time) < timeToDeactivation) {
      switch (score) {
        case 0:
          if (scan_button(leftBtn)) {
            score++;
            break;
          }
        case 1:
          if (scan_button(rightBtn)) {
            score++;
            break;
          }
        case 2:
          if (scan_button(leftBtn)) {
            score++;
            break;
          }
      }
      if (score == 3) {
        for (int i = 0; i < 5; i++) {
          digitalWrite(bzuciak, HIGH);
          delay(500);
          digitalWrite(bzuciak, LOW);
          delay(500);
        }
        doNotBzuciak = true;
      }
    }
    if (!doNotBzuciak) {
      digitalWrite(bzuciak, HIGH);
      delay(5000);
      digitalWrite(bzuciak, LOW);
    }
    // Reset values
    doNotBzuciak = false;
    score = 0;
  };

  // Kontroluje otrasy
  if (digitalRead(12) == LOW) {
    for (int i = 0; i < 3; ++i) {
      digitalWrite(13, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      delay(500);
    }
  };
}

int scan_button(int pin) {
  if (digitalRead(pin)) {
    delay(20);
    while (digitalRead(pin)) {}
    delay(20);
    return 1;
  }
  return 0;
}
