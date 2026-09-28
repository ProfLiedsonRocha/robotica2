/* Programa de controle do braço robótico com joystick Shield */
/* Inclui a biblioteca Servo */
#include <Servo.h>
/* Declaração das variáveis */
int btA = 2;
int btB = 3;
int btC = 4;
int btD = 5;
int potA0 = 0;
int potA1 = 0;
int incremento = 0;
char escolha = "";
/* Definição dos ângulos iniciais dos servos (esses valores podem
variar de montagem para montagem) */
int angBase = 90;
int angDir = 90;
int angEsq = 90;
int angGuarra = 90;
/* Declaração dos servos */
Servo servo_9;
Servo servo_10;
Servo servo_11;
Servo servo_12;
void setup() {
/* Configuração do modo de operação das portas para os botões */
pinMode(btA, INPUT);
pinMode(btB, INPUT);
pinMode(btC, INPUT);
pinMode(btD, INPUT);
/* Configuração das portas de operação dos servos */
servo_9.attach(9);
servo_10.attach(10);
servo_11.attach(11);
servo_12.attach(12);
/* Define os ângulos inicias dos servos em 90 graus */
servo_9.write(90);
servo_10.write(90);
servo_11.write(90);
servo_12.write(90);
}
void loop() {
/* Coleta os valores analógicos dos potenciômetros */
potA0 = analogRead(A0);
potA1 = analogRead(A1);
/* Identifica qual botão será pressionado */
if (digitalRead(btA) == 0) {
   escolha = 'A';
}
if (digitalRead(btB) == 0) {
   escolha = 'B';
}
if (digitalRead(btC) == 0) {
   escolha = 'C';
}
if (digitalRead(btD) == 0) {
   escolha = 'D';
}
/* Após um botão ser pressionado, entrará em um dos quatro modos de
     operação (A, B, C e D) */
switch (escolha) {
   case 'A':
     /* Se o joystick for deslocado para a esquerda, abrirá a garra. */
     if (potA0 > 700 && angGuarra < 100) {
       servo_12.write(angGuarra);
       angGuarra = angGuarra + 1;
       delay(50);
     }
     /* Se o joystick for deslocado para a direita, fechará a garra. */
     if (potA0 < 300 && angGuarra > 60) {
       servo_12.write(angGuarra);
       angGuarra = angGuarra - 1;
       delay(50);
     }
     break;
   case 'B':
/* Se o joystick for deslocado para a frente, abaixará o braço. */
     if (potA1 > 700 && angDir < 180) {
       servo_10.write(angDir);
       angDir = angDir + 1;
       delay(50);
     }
     /* Se o joystick for deslocado para a trás, levantará o braço. */
     if (potA1 < 300 && angDir > 50) {
       servo_10.write(angDir);
       angDir = angDir - 1;
       delay(50);
     }
     break;
   case 'C':
     /* Se o joystick for deslocado para a direita, o braço
       girará no sentido horário. */
     if (potA0 < 300 && angBase < 180) {
       servo_9.write(angBase);
       angBase = angBase + 1;
       delay(50);
     }
     /* Se o joystick for deslocado para a esquerda, o braço
       girará no sentido anti-horário. */
     if (potA0 > 700 && angBase > 0) {
       servo_9.write(angBase);
       angBase = angBase - 1;
       delay(50);
     }
     break;
   case 'D':
     /* Se o joystick for deslocado para a frente, levantará o
antebraço. */
     if (potA1 > 700 && angEsq < 180) {
       servo_11.write(angEsq);
       angEsq = angEsq + 1;
       delay(50);
     }
 /* Se o joystick for deslocado para a trás, abaixará o antebraço.
*/
     if (potA1 < 300 && angEsq > 90) {
       servo_11.write(angEsq);
       angEsq = angEsq - 1;
       delay(50);
     }
     break;
}
}
