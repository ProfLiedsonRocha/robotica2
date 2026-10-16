
#include <Servo.h>

// Servos
Servo servoBase;
Servo servoBraco;
Servo servoAntebraco;
Servo servoGarra;

// Joystick
const int joystickX = A0;
const int joystickY = A1;

// Botoes do Joystick Shield V1.A
const int botaoA = 2;
const int botaoB = 3;
const int botaoC = 4;
const int botaoD = 5;

// Angulos iniciais
int anguloBase = 90;
int anguloBraco = 90;
int anguloAntebraco = 90;
int anguloGarra = 90;

// Limites do joystick
const int limiteInferior = 300;
const int limiteSuperior = 700;

// Limites dos servos
const int anguloMinimo = 0;
const int anguloMaximo = 180;

// Controle da garra
const int passoGarra = 2;

void setup() {
  // Pinos dos servos
  servoBase.attach(9);
  servoBraco.attach(10);
  servoAntebraco.attach(11);
  servoGarra.attach(12);

  // Botoes com resistores pull-up internos
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(botaoC, INPUT_PULLUP);
  pinMode(botaoD, INPUT_PULLUP);

  // Posicoes iniciais
  servoBase.write(anguloBase);
  servoBraco.write(anguloBraco);
  servoAntebraco.write(anguloAntebraco);
  servoGarra.write(anguloGarra);

  delay(500);
}

void loop() {
  int X = analogRead(joystickX);
  int Y = analogRead(joystickY);

  // =================================
  // BASE - D9 - EIXO X
  // =================================

  if (X < limiteInferior) {
    if (anguloBase > anguloMinimo) {
      anguloBase--;
      servoBase.write(anguloBase);
    }
  }
  else if (X > limiteSuperior) {
    if (anguloBase < anguloMaximo) {
      anguloBase++;
      servoBase.write(anguloBase);
    }
  }

  // =================================
  // BRACO - D10 - EIXO Y
  // =================================

  if (Y > limiteSuperior) {
    if (anguloBraco < anguloMaximo) {
      anguloBraco++;
      servoBraco.write(anguloBraco);
    }
  }
  else if (Y < limiteInferior) {
    if (anguloBraco > anguloMinimo) {
      anguloBraco--;
      servoBraco.write(anguloBraco);
    }
  }

  // =================================
  // ANTEBRACO - D11 - EIXO Y
  // =================================

  if (Y > limiteSuperior) {
    if (anguloAntebraco < anguloMaximo) {
      anguloAntebraco++;
      servoAntebraco.write(anguloAntebraco);
    }
  }
  else if (Y < limiteInferior) {
    if (anguloAntebraco > anguloMinimo) {
      anguloAntebraco--;
      servoAntebraco.write(anguloAntebraco);
    }
  }

  // =================================
  // GARRA - D12 - BOTOES A E B
  // =================================

  // Botao A: fecha a garra
  if (digitalRead(botaoA) == LOW) {
    if (anguloGarra < anguloMaximo) {
      anguloGarra += passoGarra;

      if (anguloGarra > anguloMaximo) {
        anguloGarra = anguloMaximo;
      }

      servoGarra.write(anguloGarra);
    }
    delay(20);
  }

  // Botao B: abre a garra
  if (digitalRead(botaoB) == LOW) {
    if (anguloGarra > anguloMinimo) {
      anguloGarra -= passoGarra;

      if (anguloGarra < anguloMinimo) {
        anguloGarra = anguloMinimo;
      }

      servoGarra.write(anguloGarra);
    }
    delay(20);
  }

  delay(20);
}
