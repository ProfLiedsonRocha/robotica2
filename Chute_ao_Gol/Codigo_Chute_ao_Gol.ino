//Aula - Projeto Chute ao Gol

// Inclui a biblioteca que permite controlar servomotores
#include <Servo.h>

// Cria um objeto chamado goleiro para controlar o servo
Servo goleiro;

// Define o pino analógico onde o joystick está conectado
const int pinoJoystickX = A0;

// Variável que guarda a posição atual do servo
int posicaoAtual = 90;

// Variável que controla a velocidade do goleiro
// Quanto maior o valor, mais rápido ele se move
int velocidade = 10;

void setup()
{
  // Conecta o servo ao pino digital 9
  goleiro.attach(9);

  // Coloca o goleiro em pé na posição inicial
  goleiro.write(posicaoAtual);
}

void loop()
{
  // Lê a posição do joystick
  // O valor varia de 0 a 1023
  int leituraX = analogRead(pinoJoystickX);

  // Converte a leitura do joystick para ângulos do servo
  // Esquerda = 180°
  // Centro = 90°
  // Direita = 0°
  int posicaoDesejada = map(leituraX, 0, 1023, 180, 0);

  // Se a posição atual for menor que a desejada,
  // aumenta a posição de acordo com a velocidade
  if (posicaoAtual < posicaoDesejada)
  {
    posicaoAtual += velocidade;
  }

  // Se a posição atual for maior que a desejada,
  // diminui a posição de acordo com a velocidade
  else if (posicaoAtual > posicaoDesejada)
  {
    posicaoAtual -= velocidade;
  }

  // Evita que o servo ultrapasse os limites
  posicaoAtual = constrain(posicaoAtual, 0, 180);

  // Move o servo para a posição calculada
  goleiro.write(posicaoAtual);

  // Pequena pausa para estabilizar o movimento
  delay(10);
}
