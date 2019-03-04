/*
 * 2,3 cervena LED
 * 4,5 zlta LED
 * 6,7 zelena LED
 * 8,9 tlacidla
 * 10,11 senzory otvarania
 * 12 senzor otrasu
 * 13 bzuciak
 *
*/

void setup() {
  for (int i = 2; i <= 7; ++i) {
    pinMode(i, OUTPUT);
  }
  for (int i = 8; i <= 12 ; ++i) {
    pinMode(i, INPUT);
  }
  pinMode(13, OUTPUT);
}

void loop() {
  // Kontroluje rozopnute magnety
  if ((digitalRead(10) == LOW) || (digitalRead(11) == LOW)) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
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
