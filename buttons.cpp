#include "buttons.h"
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


// Debounce-aika millisekunteina
const unsigned long debounceDuration = 50; 
volatile unsigned long lastDebounceTime = 0;
volatile int lkm = -1;
volatile int button;
volatile int userNum[100];
int tarkistus;

void initButtonsAndButtonInterrupts(void) {
  // Ota käyttöön PCINT2-väylän keskeytykset
  PCICR = 0x04;
  PCMSK2 = 0b01111100;
  interrupts();

  // Määrittele napit ja aktivoi sisäinen pull-up-vastukset
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
}

ISR(PCINT2_vect) {
  unsigned long currentTime = millis();
  

  // Tarkista debounce-tilanne
  if (currentTime - lastDebounceTime > debounceDuration) {
    lastDebounceTime = currentTime; // Päivitä viimeisin napin painallusaika

    // Tarkista painettu nappi ja tulosta viesti
    if (digitalRead(2) == LOW) {
      Serial.println("Painoit nappia 2"); 
      button = 2;
      lkm++;
    }
    if (digitalRead(3) == LOW) { 
      Serial.println("Painoit nappia 3");
      button = 3;
      lkm++;
    }
    if (digitalRead(4) == LOW) { 
      Serial.println("Painoit nappia 4");
      button = 4;
      lkm++;
    }
    if (digitalRead(5) == LOW) { 
      Serial.println("Painoit nappia 5");
      button = 5;
      lkm++;
    }
    if (digitalRead(6) == LOW) { 
      Serial.println("Painoit nappia 6");
      button = 6;
    } 
    
  }
  userNum[lkm]=button;
}

/*void tarkistus(){
  if (newTimerInterrupt == true){
    if(button!=0){
      if(button!=0){
        userNum[lkm]=button;
      }
      button=0;
    }
  }else if (newTimerInterrupt == false){
    return;
  }
}*/

