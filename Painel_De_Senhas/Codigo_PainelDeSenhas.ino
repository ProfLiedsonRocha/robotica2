/*****************************************************/
/* Aula - Painel de Senhas com display OLED        */
/*****************************************************/

// Inclusão das bibliotecas
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

// Cria o objeto do display OLED
Adafruit_SSD1306 display(128, 64, &Wire);

// Variável da senha
int senha = 0;

// Definição dos pinos
#define botaoUp 3
#define botaoDown 2
#define buzzer 8

void setup() {

  // Inicializa o display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Configuração dos botões
  pinMode(botaoUp, INPUT_PULLUP);
  pinMode(botaoDown, INPUT_PULLUP);

  // Configuração do buzzer
  pinMode(buzzer, OUTPUT);

  // Cor do texto
  display.setTextColor(WHITE);

  // Limpa display
  display.clearDisplay();
}

void loop() {

  // Limpa display
  display.clearDisplay();

  // Título
  display.setCursor(18, 0);
  display.setTextSize(1);
  display.print("PAINEL DE SENHAS");

  // Moldura
  display.drawRoundRect(0, 10, 128, 47, 10, WHITE);

  // Texto inferior
  display.setCursor(20, 57);
  display.print("Robotica Parana");

  // Texto SENHA
  display.setCursor(35, 15);
  display.setTextSize(2);
  display.print("SENHA");

  // Número da senha
  display.setCursor(48, 35);

  if (senha < 10) {
    display.print("00");
    display.print(senha);
  }
  else if (senha < 100) {
    display.print("0");
    display.print(senha);
  }
  else {
    display.print(senha);
  }

  // Botão aumentar
  if (digitalRead(botaoUp) == LOW) {

    senha++;

    if (senha > 999) {
      senha = 999;
    }

    tone(buzzer, 262, 250);
    delay(250);

    tone(buzzer, 2093, 400);
    delay(400);
  }

  // Botão diminuir
  if (digitalRead(botaoDown) == LOW) {

    senha--;

    if (senha < 0) {
      senha = 0;
    }

    tone(buzzer, 262, 250);
    delay(250);

    tone(buzzer, 2093, 400);
    delay(400);
  }

  // Atualiza display
  display.display();
}
