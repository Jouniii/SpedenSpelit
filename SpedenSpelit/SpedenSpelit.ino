#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int pressedNumber = -2;          // painettu nappi
volatile int randomNumber = 0;            // Arvottu numero
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool checkGameStatus = false;    // Taulukoitten vertailu
volatile long arpa = 0;                   // 0-4 random numero  
volatile int speed = 1;     
volatile int randomNum[100];              
volatile int userNum[100];
volatile int pisteet = 0;                 //Pelin pisteet counter
bool juu = false;                         // Varsinaisen pelin loopin katkaisu

void setup()
{
  // Asetetaan Timer1
  Serial.begin(9600);
    TCCR1A = 0;                          // Normaalimoodi: Ei PWM-käyttöä
    TCCR1B = (1 << WGM12);               // CTC-moodi
    TCCR1B = (1 << CS12);                // Prescaler 256, 1 sek välein
    //TCCR1B = (1 << CS12) | (1 << CS10);  // Prescaler 1024, 4 sek välein
    OCR1A = 62499*speed;                 // Aseta vertailuarvo (62500 tikkiä) 1 Hz taajuudelle 16 MHz kellolla
    TIMSK1 = (1 << OCIE1A);              // Ota käyttöön Compare Match A -keskeytys
    sei();                               // Salli interruptit
    randomSeed(analogRead(0));
  Serial.println("Aloitetaanko?");
  initButtonsAndButtonInterrupts();

}

void loop()
{

/*if(Serial.available()>0){
  checkGameStatus = true;
  Serial.print(Serial.read());
  Serial.println("Testi ja status = true");
}
  if (checkGameStatus == true) // tää oli ennen while
  {
    int incomingByte=Serial.read();
    if(incomingByte == 53) //5
    {
      Serial.print("Aloitetaan, ja funktion aloitus ->");
      //Aloitetaan peli -funktio
      startTheGame();
      juu = true;
    }

    while(juu == true){ // looppi, ettei voi aloittaa ilman StartTheGame funktiota
      // check the game if 0<=buttonNumber<4
      if(incomingByte>=48 && incomingByte<53)
      {
        Serial.println("check game ajettu:");
        checkGame(incomingByte);
      }
    }
  }*/
  if (){//pelin alotus -> 6 nappia, peli alustetaan ja arpominen

  }

  while(juu == true){ // looppi, ettei voi aloittaa ilman StartTheGame funktiota
      // check the game if 0<=buttonNumber<4
      if(incomingByte>=48 && incomingByte<53)
      {
        Serial.println("check game ajettu:");
        checkGame(incomingByte);
      }
    }

}


ISR(TIMER1_COMPA_vect)
{
  int kerrat = 0; //montako kertaa timeri pyörähtänyt
  int index = 0;  //Taulukon indeksi
  
  if(newTimerInterrupt == true){
    //for(int i=0; i<=1; i++)
    //{
      arpa = random(48,52);
      randomNum[index]=arpa;
      Serial.println(randomNum[index]);
      kerrat++;
      index++;
      //i=0;
    //}

    if(kerrat==10)
    {
      speed-=0.1;
      kerrat=0;
    }
  }
}

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
  TCNT1 = 0; // Nollaa laskuri
}

void checkGame(byte nbrOfButton) 
{ 
  //Tarkistetaan pelin tila (verrataan taulukoita) jokaisen napin painalluksen jälkeen, jos väärin stopgame
  //Jos oikein, pelin pisteet +1
    if (userNum[nbrOfButton] == randomNum[nbrOfButton]) //tää kyl ainaki uusiks!!
    {
      pisteet++;

    } else {
      stopTheGame();
      juu = false;
    }
}


void initializeGame()
{
	// Nollataan kaikki muuttujat, joita tarvitaan numeroiden tallettamiseen
  // userNumbers- ja randNum taulukko nollataan
  // for loopilla sataseen nollaus molemmille taulukoille
  for(int i = 0; i<=100; i++)
  {
    userNum[i]=0;
    randomNum[i]=0;
  }
}

void startTheGame()
{
  // see requirements for the function from SpedenSpelit.h
  newTimerInterrupt = true;
  initializeGame();
  TCNT1 = 0;                           // Nollaa laskuri (valinnainen, jos halutaan varmistaa uudelleenkäynnistys alusta)
  TCCR1B |= (1 << CS12) | (1 << CS10); // Aseta prescaler takaisin (tässä 1024)
  TIMSK1 |= (1 << OCIE1A);             // Ota käyttöön Compare Match A -keskeytys
  Serial.println(" Start game funktio ");
} 

void stopTheGame(){
  TIMSK1 &= ~(1 << OCIE1A);                             // Poista käytöstä Timer1 Compare Match A -keskeytys
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Pysäytä Timer1
  TCNT1 = 0;                                            // Nollaa laskuri
  newTimerInterrupt = false;

  Serial.print("Game over! Pisteesi olivat: "); Serial.println(pisteet);
}

