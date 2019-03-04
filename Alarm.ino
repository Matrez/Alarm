/*
   2,3 cervena LED
   4,5 zlta LED
   6,7 zelena LED
   8,9 tlacidla
   10,11 senzory otvarania
   12 senzor otrasu
   13 bzuciak

*/

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if ((digitalRead(10) == LOW) || (digitalRead(11) == LOW)) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  };


  if (digitalRead(12) == LOW) {
    digitalWrite(13, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(500);
  };

}
