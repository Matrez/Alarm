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

bool outOfTime = true;
bool wrongPin = false;

void setup() {
  for (int i = 2; i <= 7; ++i) {
    pinMode(i, OUTPUT);
  }
  for (int i = 8; i <= 12; ++i) {
    pinMode(i, INPUT);
  }
  pinMode(bzuciak, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Kontroluje rozopnute magnety
  if ((digitalRead(leftSens) == LOW) || (digitalRead(rightSens) == LOW)) {
    tajm = millis();
    while ((millis() - tajm) < timeToDeactivation) {
      delay (150);
      switch (score) {
        case 0:
          if (scan_button_with_yellow_led(leftBtn)) {
            Serial.println("Case 0: Stlacene spravne");
            score++;
            break;
          } else if (scan_button_with_yellow_led(rightBtn)) {
            Serial.println("Case 0: Stlacene zle");
            wrongPin = true;
            score++;
            break;
          }
        case 1:
          if (scan_button_with_yellow_led(rightBtn)) {
            Serial.println("Case 1: Stlacene spravne");
            score++;
            break;
          } else if (scan_button_with_yellow_led(leftBtn)) {
            Serial.println("Case 1: Stlacene zle");
            wrongPin = true;
            score++;
            break;
          }
        case 2:
          if (scan_button_with_yellow_led(leftBtn)) {
            Serial.println("Case 2: Stlacene spravne");
            score++;
            break;
          } else if (scan_button_with_yellow_led(rightBtn)) {
            Serial.println("Case 2: Stlacene zle");
            wrongPin = true;
            score++;
            break;
          }
      }
      // Ak sa stlacili 3x tlacidla a pin bol DOBRY
      // Volny pristup v aute
      if (score == 3 && !wrongPin) {
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
        digitalWrite(yellowLed1, HIGH);
        digitalWrite(yellowLed2, HIGH);

        while (true) {
          bool closedDoors;
          if ((digitalRead(leftSens) == HIGH) && (digitalRead(rightSens) == HIGH)) {
            closedDoors = true;
          } else {
            closedDoors = false;
          }

          if (scan_button(leftBtn) || scan_button(rightBtn)) {
            if (closedDoors) {
              Serial.println("Dvere su zavrete");
              digitalWrite(yellowLed1, LOW);
              digitalWrite(yellowLed2, LOW);
              digitalWrite(greenLed1, HIGH);
              digitalWrite(greenLed2, HIGH);
              delay(3000);
              digitalWrite(greenLed1, LOW);
              digitalWrite(greenLed2, LOW);
              break;
            } else {
              Serial.println("Najprv treba zavriet dvere");
              digitalWrite(yellowLed1, LOW);
              digitalWrite(yellowLed2, LOW);
              digitalWrite(redLed1, HIGH);
              digitalWrite(redLed2, HIGH);
              digitalWrite(bzuciak, HIGH);
              delay(2000);
              digitalWrite(redLed1, LOW);
              digitalWrite(redLed2, LOW);
              digitalWrite(bzuciak, LOW);
              digitalWrite(yellowLed1, HIGH);
              digitalWrite(yellowLed2, HIGH);
            }
          }
        }
        outOfTime = false;
        break;
      }
      // Ak sa stlacili 3x tlacidla a pin bol ZLY
      if (score == 3 && wrongPin) {
        wrongPinSound(true);
        wrongPin = false;
        outOfTime = false;
        break;
      }
    }
    wrongPinSound(outOfTime);
    // Reset values
    wrongPin = false;
    outOfTime = true;
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

void wrongPinSound(bool condition) {
  // Ak sa zadal nespravny PIN, zabzuci
  if (condition) {
    digitalWrite(bzuciak, HIGH);
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, HIGH);
    delay(5000);
    digitalWrite(bzuciak, LOW);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
  }
}

int scan_button(int pin) {
  if (digitalRead(pin)) {
    delay(50);
    while (digitalRead(pin)) {}
    delay(50);
    return 1;
  }
  return 0;
}


int scan_button_with_yellow_led(int pin) {
  if (digitalRead(pin)) {
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(yellowLed2, HIGH);
    delay(50);
    while (digitalRead(pin)) {}
    digitalWrite(yellowLed1, LOW);
    digitalWrite(yellowLed2, LOW);
    delay(50);
    return 1;
  }
  return 0;
}
