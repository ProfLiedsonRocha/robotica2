/*******************************/
/* Aula - Robô Ultrassônico */
/* o sensor HC-SR04.           */
/*******************************/

#include <Ultrasonic.h>

/* ===== Definição dos pinos do sensor ultrassônico ===== */
#define pino_Trig 11
#define pino_Echo 12

/* ===== Potência dos motores (0 a 255) ===== */
int potencia = 200;

/* ===== Definição dos pinos IN1 a IN4 da ponte H ===== */
/* Precisam ser portas com PWM (~) para controle de velocidade */
#define IN1 10   // Porta PWM ~10
#define IN2 9    // Porta PWM ~9
#define IN3 6    // Porta PWM ~6
#define IN4 5    // Porta PWM ~5

/* ===== Cria o objeto do sensor ultrassônico ===== */
Ultrasonic Sensor(pino_Trig, pino_Echo);

/* ===== Variável que armazena a distância medida ===== */
int distancia;

/* ===================================================== */
/* Funções de controle dos motores                       */
/* ===================================================== */

/* Move para frente */
void Frente(int Vel_A, int Vel_B) {
  /* Motor A */
  analogWrite(IN1, Vel_A);
  analogWrite(IN2, 0);
  /* Motor B */
  analogWrite(IN3, Vel_B);
  analogWrite(IN4, 0);
}

/* Move para trás */
void Re(int Vel_A, int Vel_B) {
  /* Motor A */
  analogWrite(IN1, 0);
  analogWrite(IN2, Vel_A);
  /* Motor B */
  analogWrite(IN3, 0);
  analogWrite(IN4, Vel_B);
}

/* Giro no sentido horário */
void GiroHorario(int Vel_A, int Vel_B) {
  /* Motor A */
  analogWrite(IN1, Vel_A);
  analogWrite(IN2, 0);
  /* Motor B */
  analogWrite(IN3, 0);
  analogWrite(IN4, Vel_B);
}

/* Giro no sentido anti-horário */
void GiroAntiHorario(int Vel_A, int Vel_B) {
  /* Motor A */
  analogWrite(IN1, 0);
  analogWrite(IN2, Vel_A);
  /* Motor B */
  analogWrite(IN3, Vel_B);
  analogWrite(IN4, 0);
}

/* Para o chassi */
void Pare() {
  /* Motor A */
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  /* Motor B */
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

/* ===================================================== */
/* Função de manobra (corrigida)                         */
/* Sequência: parar → dar ré → girar → parar            */
/* ===================================================== */
void Manobre() {
  // 1. Para o robô antes de manobrar
  Pare();
  delay(200);

  // 2. Dá ré para se afastar do obstáculo
  Re(potencia * 0.7, potencia * 0.7);
  delay(400);

  // 3. Para novamente antes de girar
  Pare();
  delay(100);

  // 4. Escolhe um lado aleatório e gira por tempo FIXO
  if (random(0, 2) == 0) {
    GiroAntiHorario(potencia * 0.6, potencia * 0.6);
  } else {
    GiroHorario(potencia * 0.6, potencia * 0.6);
  }
  delay(500);   // <-- tempo fixo de giro (essencial!)

  // 5. Para após o giro
  Pare();
  delay(150);
}

/* ===================================================== */
/* Setup                                                 */
/* ===================================================== */
void setup() {
  Serial.begin(9600);

  // Inicia com os motores parados
  Pare();

  // Aguarda 3 segundos antes de começar
  delay(3000);
}

/* ===================================================== */
/* Loop principal                                        */
/* ===================================================== */
void loop() {
  // Lê a distância do sensor
  distancia = Sensor.read();

  // Filtro: ignora leituras inválidas (0 cm ou > 400 cm)
  if (distancia == 0 || distancia > 400) {
    Frente(potencia, potencia);
    delay(50);
    return;
  }

  // Se a distância for menor ou igual a 40 cm, manobra
  if (distancia <= 40) {
    Manobre();
  }
  // Senão, segue em frente
  else {
    Frente(potencia, potencia);
  }

  // Pequena pausa para estabilizar as leituras do sensor
  delay(50);
}
