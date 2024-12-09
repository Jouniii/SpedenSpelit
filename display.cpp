#include "display.h"

  const int resetPin = 12;       // Reset (RST)
  const int shiftClockPin = 11;  // Shift Clock (SHCP)
  const int latchClockPin = 10;  // Latch Clock (STCP)
  const int outEnablePin = 9;    // Output Enable (OE)
  const int serialInputPin = 8;  // Serial Input (DS) 

  //segmenttikartta
  const uint8_t segmentMap[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};


void initializeDisplay(void){
    pinMode(resetPin, OUTPUT);
    pinMode(shiftClockPin, OUTPUT);
    pinMode(latchClockPin, OUTPUT);
    pinMode(outEnablePin, OUTPUT);
    pinMode(serialInputPin, OUTPUT);

    // Asetetaan alkuarvot
    digitalWrite(resetPin, LOW);         // Komponentin reset pois päältä
    delay(10);
    digitalWrite(resetPin, HIGH);
    digitalWrite(shiftClockPin, LOW);     // ShiftClockin oletustila
    digitalWrite(latchClockPin, LOW);     // LatchClockin oletustila
    digitalWrite(outEnablePin, LOW);      // Aktivoi ulostulot (OE aktiivinen LOW:lla)
    digitalWrite(serialInputPin, LOW);    // Serial Input oletustila
}


void writeByte(uint8_t bits,bool last){
    uint8_t bitPattern = segmentMap[bits];

  for(int i = 7; i >= 0; i--){
      // lähetetään bitti kerrallaan
      uint8_t bit = (bitPattern >> i) & 0x01; // poimitaan nykyinen bitti
      digitalWrite(serialInputPin, bit); // asetetaan bitti datalinjalle
      digitalWrite(shiftClockPin, HIGH); // kelloimpulssi
      delayMicroseconds(1); // asetetaan pieni viive vakauttamiseksi
      digitalWrite(shiftClockPin, LOW);
      } 

      // jos "last" on true, päivitetään näytön tila
      if(last){
        digitalWrite(latchClockPin, LOW);
        delayMicroseconds(1); // viive vakauttamiseksi
        digitalWrite(latchClockPin, HIGH);
      }


}



void writeHighAndLowNumber(uint8_t tens,uint8_t ones){
  //ensimmäiseen näyttöön kymmenet
  writeByte(tens, false);
  //toiseen näyttöön ykköset
  writeByte(ones, true);
}

void showResult(byte result){

  uint8_t tens = result / 10;
  uint8_t ones = result % 10;
  writeHighAndLowNumber(tens, ones);
}
