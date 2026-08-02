/* Programa: Sensor de Presença - PIR */
/* Definindo os pinos digitais para o LED e o Sensor */
int Pino_Sensor = 8;
int Pino_LED = 13;
void setup()
{
/* Configura o pino do sensor como entrada */
pinMode(Pino_Sensor, INPUT);
/* Configura o pino do LED como saída */
pinMode(Pino_LED, OUTPUT);
}
void loop()
{
/* Se o sensor detectar presença */
if (digitalRead(Pino_Sensor) == HIGH) {
   /* Ligue o LED */
   digitalWrite(Pino_LED, HIGH);
   /* Permanece com o LED ligado por 5 segundos */
   delay(5000);
   /* Senao... */
} else {
   /* Mantém o LED desligado */
   digitalWrite(Pino_LED, LOW);
}
/* Pequena pausa para retomar o monitoramento */
delay(100);
}
