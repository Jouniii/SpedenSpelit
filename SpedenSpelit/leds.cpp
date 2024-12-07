#include "leds.h"

void initializeLeds() {
pinMode(A2, OUTPUT); // Asetetaan A2-nasta ulostuloksi
pinMode(A3, OUTPUT); // Asetetaan A3-nasta ulostuloksi
pinMode(A4, OUTPUT); // Asetetaan A4-nasta ulostuloksi
pinMode(A5, OUTPUT); // Asetetaan A5-nasta ulostuloksi
}

void setLed(byte ledNumber) {
  switch (ledNumber) {
    case 0:
      digitalWrite(A2, HIGH); // Sytytetään LED A2
      break;
    case 1:
      digitalWrite(A3, HIGH); // Sytytetään LED A3
      break;
    case 2:
      digitalWrite(A4, HIGH); // Sytytetään LED A4
      break;
    case 3:
      digitalWrite(A5, HIGH); // Sytytetään LED A5
      break;
    default:
      break; // Jos ledNumber ei ole 0, 1, 2 tai 3, ei tehdä mitään
  }
}

void clearAllLeds() {
digitalWrite(A2, LOW); // Sammutetaan LED A2
digitalWrite(A3, LOW); // Sammutetaan LED A3
digitalWrite(A4, LOW); // Sammutetaan LED A4
digitalWrite(A5, LOW); // Sammutetaan LED A5
}

void setAllLeds() {
digitalWrite(A2, HIGH); // Sytytetään LED A2
digitalWrite(A3, HIGH); // Sytytetään LED A3
digitalWrite(A4, HIGH); // Sytytetään LED A4
digitalWrite(A5, HIGH); // Sytytetään LED A5
}
void show1() {
  for (int num = 0; num < 16; num++) {  // Toistetaan 16 kertaa
    digitalWrite(A2, (num & 1) ? HIGH : LOW); // Jos num:n 0. bitti on 1, A2 syttyy
    digitalWrite(A3, (num & 2) ? HIGH : LOW); // Jos num:n 1. bitti on 1, A3 syttyy
    digitalWrite(A4, (num & 4) ? HIGH : LOW); // Jos num:n 2. bitti on 1, A4 syttyy
    digitalWrite(A5, (num & 8) ? HIGH : LOW); // Jos num:n 3. bitti on 1, A5 syttyy
    delay(500); // Odotetaan 500 millisekuntia ennen seuraavaa toistoa
    clearAllLeds(); // Sammutetaan kaikki LEDit
  }
}


void show2(int rounds) {
  int delayTime = 1000; // Alustetaan viive 1000 ms:ksi

  for (int i = 0; i < rounds; i++) {
    //for (int j = 0; j <= i; j++) {
      //setLed(j);}
      digitalWrite(A2, LOW); // Sammutetaan A2
      delay(delayTime);
      digitalWrite(A2, HIGH); // Sytytetään A2
      delay(delayTime);
      digitalWrite(A3, HIGH); // Sytytetään A3
      delay(delayTime);
      digitalWrite(A4, HIGH); // Sytytetään A4
      delay(delayTime);
      digitalWrite(A5, HIGH); // Sytytetään A5
      delay(delayTime);

    delayTime = max(100, delayTime - 300); // Vähennetään viivettä 300 ms joka kierroksella, mutta vähintään 100 ms
    clearAllLeds(); // Sammutetaan kaikki LEDit
  }
}