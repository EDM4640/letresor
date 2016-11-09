//LE TRÉSOR - TP1
//BRUNEAU, Madeleine && CUSSON,Vincent && TÉTRAULT,Pascale && THÉRIAULT-BOIVIN,Louis.


#include <Adafruit_NeoPixel.h>
#include <Chrono.h>

#define PIN            6

#define NUMPIXELS      60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// au départ, l'état de chaque LED est à zéro - elles sont éteintes.

boolean ligth1 = false;
boolean ligth2 = false;
boolean ligth3 = false;
boolean ligth4 = false;

boolean gameOver = false;
boolean win = false;

// La boîte possède 4 boutons

int section1[] = {5, 11};
int section2[] = {21, 27};
int section3[] = {36, 42};
int section4[] = {51, 57};

int randomButton[16];

int etapes = 0;

Chrono myChrono;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // Attendre que le port Serial se connecte. Ligne de code utile seulement pour le microcontrôleur Leonardo.

  }

  pixels.begin(); // Cette ligne initialise la librairie NeoPixel
  pixels.show();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  int debut = 0;
  int fin = 0;
  melanger();

}
void loop() {

  // Les LED sont contrôllées de deux façons. Les 28 LED passent du vert, au jaune au rouge selon un chrono pour illustrer
  // le temps qui passe. Chaque section est contrôllée par un bouton de manière aléatoire, lorsqu'un bouton est enfoncé, la/les lignes
  // au(x)quel(les) il est associé devienne(nt) bleue(s).
  // Ci-bas, la composition du chrono.

  Serial.println( myChrono.elapsed());
  if (myChrono.hasPassed(10) ) {
    gameOver = false;
    etapes = 0;

  }
  if (myChrono.hasPassed(4000) ) {
    etapes = 1;
  }
  if (myChrono.hasPassed(6000) ) {
    etapes = 2;
  }
  if (myChrono.hasPassed(8000) ) {
    etapes = 3;
  }

  //Le chrono recommence à 0 dès qu'il passe 10 secondes / 10000 millis.

  if (myChrono.hasPassed(10000) ) {
    myChrono.restart();
    melanger();
    etapes = 0;
    gameOver = false;
    win = false;

  }

  if (win == true && myChrono.hasPassed(10000) ) {
    etapes = 0;
    myChrono.restart();
    melanger();
//    gameOver = true;
//    win = false;

  }

  // Si le jeu est gagné - que les 4 lignes de LED deviennent bleues, les LED s'allument pour former un bonhomme sourire.

  Serial.println(etapes);

  if (win == true) {
    etapes = 4;
    Serial.println(etapes);
  }


  if (etapes == 0 ) {
    ligthWaiting(0, 30, 0);

  }

  // On associe chaque étape à une couleur (vert, jaune, rouge).

  else if (etapes == 1 ) {
    ligthWaiting(30, 30, 0);
  }
  else if (etapes == 2 ) {
    ligthWaiting(30, 0, 0);
  }
  else if (etapes == 3) {
    gameOver = true;
    ligth1 = false;
    ligth2 = false;
    ligth3 = false;
    ligth4 = false;
    clearit();
    pasContent();


  }
  else if (etapes == 4) {
    gameOver = true;
    ligth1 = false;
    ligth2 = false;
    ligth3 = false;
    ligth4 = false;
    clearit();
    content();
  }


  /** DYNAMIQUE DE JEUX **/
  //


  if ( digitalRead(2) == LOW && gameOver == false) {
    ligth1 = randomButton[0];
    ligth2 = randomButton[1];
    ligth3 = randomButton[2];
    ligth4 = randomButton[3];
  }



  if ( digitalRead(3) == LOW && gameOver == false) {
    ligth1 = randomButton[4];
    ligth2 = randomButton[5];
    ligth3 = randomButton[6];
    ligth4 = randomButton[7];

  }




  if ( digitalRead(4) == LOW && gameOver == false) {
    ligth1 = randomButton[8];
    ligth2 = randomButton[9];
    ligth3 = randomButton[10];
    ligth4 = randomButton[11];
  }




  if ( digitalRead(5) == LOW && gameOver == false) {
    ligth1 = randomButton[12];
    ligth2 = randomButton[13];
    ligth3 = randomButton[14];
    ligth4 = randomButton[15];
  }


  //**Boolean a Lumiere**//

  if (ligth1 == true) {
    ligthOpen(section1);
  }
  if (ligth2 == true) {
    ligthOpen(section2);
  }

  if (ligth3 == true) {
    ligthOpen(section3);
  }

  if (ligth4 == true) {
    ligthOpen(section4);

  }

  if (ligth1 == true && ligth2 == true && ligth3 == true && ligth4 == true && win == false) {
    win = true;
  }

  //  if (win == true && myChrono.hasPassed(10000) ) {
  //    etapes = 0;
  //    myChrono.restart();
  //    melanger();
  //  }





}



void ligthOpen(int nLigth[] ) {
  for (int i = nLigth[0]; i < nLigth[1]; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    pixels.show();
  }

}

void ligthWaiting(int r, int g, int b ) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, r, g, b);
    pixels.show();
  }

}


void ligthClose(int nLigth[] ) {
  for (int i = nLigth[0]; i < nLigth[1]; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }

}

void pasContent() {

  pixels.setPixelColor(5, 255, 0, 0);
  pixels.setPixelColor(10, 255, 0, 0);
  pixels.setPixelColor(22, 255, 0, 0);
  pixels.setPixelColor(23, 255, 0, 0);
  pixels.setPixelColor(24, 255, 0, 0);
  pixels.setPixelColor(25, 255, 0, 0);
  pixels.setPixelColor(51, 255, 0, 0);
  pixels.setPixelColor(56, 255, 0, 0);

}

void content() {

  pixels.setPixelColor(6, 255, 255, 255);
  pixels.setPixelColor(7, 255, 255, 255);
  pixels.setPixelColor(8, 255, 255, 255);
  pixels.setPixelColor(9, 255, 255, 255);
  pixels.setPixelColor(21, 255, 255, 255);
  pixels.setPixelColor(26, 255, 255, 255);
  pixels.setPixelColor(52, 255, 255, 255);
  pixels.setPixelColor(55, 255, 255, 255);


}

void clearit() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0); // Moderately bright green color.
    pixels.show();
  }
}

void melanger() {

  randomSeed(analogRead(10));

  int conteurdetrue = 0;
  int conteurde3 = 0;

  for (int i = 0; i < 16; i++) {

    int aleatoire = 0;

    aleatoire = random(0, 2);

    if (aleatoire == 0) {
      conteurde3++;
      if (conteurde3 < 4) {
        randomButton[i] = 3;
      }
      else {
        randomButton[i] = 0;
      }
    }
    else if (aleatoire == 1 && conteurdetrue < 4) {
      conteurdetrue ++;
      randomButton[i] = true;
    }

    Serial.print(randomButton[i]);
  }




}
