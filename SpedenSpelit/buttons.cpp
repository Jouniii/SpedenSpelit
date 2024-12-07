#include "buttons.h"
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int buttonPressed = 0;

// Debounce-aika millisekunteina
const unsigned long debounceDuration = 50; 
volatile unsigned long lastDebounceTime = 0;
//volatile int lkm = 0;

void initButtonsAndButtonInterrupts(void) {
  // Ota käyttöön PCINT2-väylän keskeytykset
  PCICR = 0x04;
  PCMSK2 = 0b01111100;
  interrupts();

  // Määrittele napit ja aktivoi sisäinen pull-up-vastukset
  const byte pin2 = 2;
  const byte pin3 = 3;
  const byte pin4 = 4;
  const byte pin5 = 5;
  const byte pin6 = 6;

  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);
}

ISR(PCINT2_vect) {
  unsigned long currentTime = millis();

  // Tarkista debounce-tilanne
  if (currentTime - lastDebounceTime > debounceDuration) {
    lastDebounceTime = currentTime; // Päivitä viimeisin napin painallusaika

    // Tarkista painettu nappi ja tulosta viesti
    if (digitalRead(2) == LOW) { 
      Serial.println("Painoit nappia 2!");
    }
    if (digitalRead(3) == LOW) { 
      Serial.println("Painoit nappia 3!");
    }
    if (digitalRead(4) == LOW) { 
      Serial.println("Painoit nappia 4!");
    }
    if (digitalRead(5) == LOW) { 
      Serial.println("Painoit nappia 5!");
    }
    if (digitalRead(6) == LOW) { 
      Serial.println("Painoit nappia 6!");
    }
  }
}

