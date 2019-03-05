/*
   2,3 cervena LED
   4,5 zlta LED
   6,7 zelena LED
   8,9 tlacidla
   10,11 senzory otvarania
   12 senzor otrasu
   13 bzuciak
   A0 - snimac pohybu
   A1 - start/koniec tlacidlo

*/

const unsigned long timeToDeactivation = 10000; // V milisekundach
unsigned long tajm;


short score = 0;
const byte redLed1 = 2;
const byte redLed2 = 3;
const byte yellowLed1 = 4;
const byte yellowLed2 = 5;
const byte greenLed1 = 6;
const byte greenLed2 = 7;
const byte leftBtn = 8;
const byte rightBtn = 9;
const byte leftSens = 10;
const byte rightSens = 11;
const byte tiltSens = 12;
const byte bzuciak = 13;

boolean doNotBzuciak = false;

void setup() {
  for (int i = 2; i <= 7; ++i) {
    pinMode(i, OUTPUT);
  }
  for (int i = 8; i <= 12; ++i) {
    pinMode(i, INPUT);
  }
  pinMode(bzuciak, OUTPUT);
}

void loop() {
  
  // Kontroluje rozopnute magnety
  if ((digitalRead(leftSens) == LOW) || (digitalRead(rightSens) == LOW)) {
    tajm = millis();
    while ((millis() - tajm) < timeToDeactivation) {
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
        for (int i = 0; i < 3; i++) {
          digitalWrite(bzuciak, HIGH);
          digitalWrite(greenLed1, HIGH);
          digitalWrite(greenLed2, HIGH);
          delay(200);
          digitalWrite(bzuciak, LOW);
          digitalWrite(greenLed1, LOW);
          digitalWrite(greenLed2, LOW);
          delay(200);
        }
        doNotBzuciak = true;
        break;
      }
    }
    if (!doNotBzuciak) {
      digitalWrite(bzuciak, HIGH);
      digitalWrite(redLed1, HIGH);
      digitalWrite(redLed2, HIGH);
      delay(5000);
      digitalWrite(bzuciak, LOW);
      digitalWrite(redLed1, LOW);
      digitalWrite(redLed2, LOW);
    }
    // Reset values
    doNotBzuciak = false;
    score = 0;
  };

  // Kontroluje otrasy
  if (digitalRead(tiltSens) == LOW) {
    for (int i = 0; i < 3; ++i) {
      digitalWrite(bzuciak, HIGH);
      digitalWrite(yellowLed1, HIGH);
      digitalWrite(yellowLed2, HIGH);
      delay(500);
      digitalWrite(bzuciak, LOW);
      digitalWrite(yellowLed1, LOW);
      digitalWrite(yellowLed2, LOW);
      delay(200);
    }
  };

/* // Kontroluje pohyb
  do {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    delay(500);
  } while (digitalRead(A0)== LOW);
  */
} 

int scan_button(int pin) {
  if (digitalRead(pin)) {
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(yellowLed2, HIGH);
    delay(20);
    while (digitalRead(pin)) {}
    digitalWrite(yellowLed1, LOW);
    digitalWrite(yellowLed2, LOW);
    delay(20);
    return 1;
  }
  return 0;
}
