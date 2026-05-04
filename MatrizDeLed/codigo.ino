/* =================== MATRIZ DO CORAÇÃO =================== */
#include "LedControl.h"

/* (DIN, CLK, CS, número de displays) */
LedControl lc = LedControl(8, 10, 9, 1);

/* Tempo entre batimentos */
int tempo = 300;

/* Coração pequeno */
byte Coracao_Peq[] = {
B00001100,
B00011110,
B00111110,
B01111100,
B01111100,
B00111110,
B00011110,
B00001100
};

/* Coração grande */
byte Coracao_Gra[] = {
B00011110,
B00111111,
B01111111,
B11111110,
B11111110,
B01111111,
B00111111,
B00011110
};

/* =================== MATRIZ DO NOME =================== */
#include <MatrizLed.h>

MatrizLed Display;

/* =================== SETUP ÚNICO =================== */
void setup() {
  // Matriz coração
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  // Matriz nome
  Display.begin(7, 6, 5, 1);
  Display.setIntensidad(10);
  Display.borrar();
}

/* =================== LOOP ÚNICO =================== */
void loop() {

  // 1️⃣ Mostra o nome
    Display.escribirFraseScroll("NOME DA MAE", 80);

  piscarCoracao();

}

void piscarCoracao() {
    // 2️⃣ Depois anima o coração
  for (int i = 0; i < 5; i++) {
    desenharCoracao(Coracao_Peq);
    delay(tempo);
    desenharCoracao(Coracao_Gra);
    delay(tempo);
  }
}

/* =================== FUNÇÃO =================== */
void desenharCoracao(byte desenho[]) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, desenho[i]);
  }
}
