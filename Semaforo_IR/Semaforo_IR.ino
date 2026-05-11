/* Programa: Semáforo inteligente com IR.      */
/* Definições dos pinos para os LEDs e sensor. */
#define PIN_SENSOR 2
#define PIN_LED_VERDE_CAR 13
#define PIN_LED_AMARELO_CAR 12
#define PIN_LED_VERMELHO_CAR 11
#define PIN_LED_VERDE_PED 10
#define PIN_LED_VERMELHO_PED 9
/* Variável que seleciona o modo de operação   */
/* do semáforo 0: Modo aberto para carros e    */
/* 1: Modo travessia de pedestres.             */
int modo = 0;
void setup(){
/* Configura o pino do sensor como ENTRADA. */
pinMode(PIN_SENSOR, INPUT);
/* Configura os pinos 9 a 13 como SAÍDA.     */
for (int i = 9; i <= 13; i++) {
   pinMode(i, OUTPUT);
}
/* Ativa a função de interrupção no pino que */
/* o sensor está ligado.                     */
attachInterrupt(digitalPinToInterrupt(PIN_SENSOR),
sensorAcionado, FALLING);
}
void loop()
{
/* Switch com dois modos de operação: modo   */
/* aberto para carros e modo travessia de    */
/* pedestre. Enquanto o sensor não detectar */
/* um pedestre, o modo de operação permanece */
/* em 0, ou seja, aberto para a passagem dos */
/* carros. Caso o sensor detecte um pedestre,*/
/* a função attachInterrupt irá imediatamente*/
/* alterar o modo de operação para 1, ou     */
/* seja, entrará no modo de travessia de     */
/* pedestres.                                */
switch (modo) {
   case 0:
     modocarros();
     break;
   case 1:
     travessia();
     break;
}
}
/* Após o sensor detectar o pedestre, será     */
/*executada essa função, ela altera o modo de */
/* operação do semáforo.                       */
void sensorAcionado() {
modo = 1;
}
/* Função que ativa os LEDs para o modo        */
/* "Travessia de pedestres".                   */
void travessia() {
/* Aguarda +1 segundo após o sensor detectar */
/* o pedestre.                               */
delay(1000);
/* Aciona o amarelo do semáforo dos carros. */
digitalWrite(PIN_LED_VERDE_CAR, LOW);
digitalWrite(PIN_LED_AMARELO_CAR, HIGH);
delay(3000);
/* Abre o semáforo de pedestres.             */
digitalWrite(PIN_LED_VERDE_PED, HIGH);
digitalWrite(PIN_LED_VERMELHO_PED, LOW);
digitalWrite(PIN_LED_AMARELO_CAR, LOW);
digitalWrite(PIN_LED_VERMELHO_CAR, HIGH);
delay(5000);
/* Apaga o verde dos pedestres e começa      */
/* piscar o vermelho indicando que o tempo de*/
/* travessia está acabando.                  */
digitalWrite(PIN_LED_VERDE_PED, LOW);
for (int i = 0; i <= 5; i++){
   digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
   delay(300);
   digitalWrite(PIN_LED_VERMELHO_PED, LOW);
   delay(300);
}
/* Após a travessia de pedestre, altera para */
/* o modo de passagem de carros: 0.          */
modo = 0;
}
/* Função que ativa os LEDs para o modo        */
/* "Aberto para carros".                       */
void modocarros() {
digitalWrite(PIN_LED_VERDE_PED, LOW);
digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
digitalWrite(PIN_LED_VERDE_CAR, HIGH);
digitalWrite(PIN_LED_AMARELO_CAR, LOW);
digitalWrite(PIN_LED_VERMELHO_CAR, LOW);
}