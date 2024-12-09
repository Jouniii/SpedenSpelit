#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile int index = 0;                   // ISR käytössä
volatile int kerrat = 0;                  //montako kertaa timeri pyörähtänyt
volatile int speed = 1;                   // Pelin nopeuskerroin
volatile int randomNum[100];              // Arvottujen lukujen taulukko
volatile int pisteet = 0;                 // Pelin pisteet counter
bool juu = false;                         // Varsinaisen pelin loopin katkaisu
int edelLKM;                              // LKM kierroksista edellinen luku


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("Aloitetaanko?");
  initButtonsAndButtonInterrupts();
  initializeLeds();
  initializeDisplay();
}

void loop()
{
  if (button == 6 && juu == false){           // pelin alotus -> 6 nappia, pelin aloitus aliohjelma kutsutaan
    startTheGame();
    juu = true;                               // Varsinaisen pelin aloitus boolean

  }

  if(juu == true){                            // Odotetaan "juu"-booleania, ettei peliä voida aloittaa ennen aikoja
    if (lkm > edelLKM){                       // Kun nappia painetaan, kutsutaan checkGame aliohjelmaa
      checkGame();
      edelLKM = lkm;                          // Asetetaan arvot yhtä suuriksi
    }
  }
}


ISR(TIMER1_COMPA_vect)
{
  if(newTimerInterrupt == true){              // Aloitetaanko arvottujen lukujen tulostus
    Serial.println(randomNum[index]);
    index++;
  }
  if(kerrat==2){                             // Pelin nopeutus
    speed=0.5;
    kerrat=0;
  }
  kerrat++;
}

void checkGame() { 
  if (userNum[lkm] == randomNum[lkm]){        // Käyttäjän nappien, ja arvottujen lukujen vertaus.
    pisteet++;
  } else {
    stopTheGame();
    juu = false;
  }
}

void startTheGame()
{
  initializeGame();                           // Pelin alustus
  initializeTimer();                          // Timer1 alustus
  newTimerInterrupt = true;                   // ISR funktiolle lupa aloittaa
} 

void stopTheGame(){
  TIMSK1 &= ~(1 << OCIE1A);                             // Poista käytöstä Timer1 Compare Match A -keskeytys
  //TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Pysäytä Timer1
  TCNT1 = 0;                                            // Nollaa laskuri
  newTimerInterrupt = false;
  Serial.print("Game over! Pisteesi olivat: "); Serial.println(pisteet);
  pisteet = 0;
}

void initializeTimer(void)
{
  TCNT1 = 0;                           // Nollaa laskuri
  TCCR1A = 0;                          // Normaalimoodi: Ei PWM-käyttöä
  TCCR1B = (1 << WGM12);               // CTC-moodi
  TCCR1B = (1 << CS12);                // Prescaler 256, 1 sek välein
  OCR1A = 62499*speed;                 // Aseta vertailuarvo (62500 tikkiä) 1 Hz taajuudelle 16 MHz kellolla
  TIMSK1 = (1 << OCIE1A);              // Ota käyttöön Compare Match A -keskeytys
  sei();                               // Salli interruptit
}

void initializeGame()
{
  int arpa;
  for(int i = 0; i<=99; i++)
  {
    userNum[i]=0;
    arpa = random(2,6);
    randomNum[i]=arpa;
  }
}
