/* Sensor de Umidade do Solo */
/* Definições de pinos para o sensor e para os LEDs */
#define pino_Sensor A0
#define pino_LED_Verde 3
#define pino_LED_Vermelho 4
/* Porcentagem de umidade mínima para iniciar a irrigação */
int Valor_Critico = 45;
/* Variável para armazenar o valor analógico do sensor */
int ValAnalogIn;
void setup() {
/* Inicia a comunicação serial com a velocidade de 9600
bauds */
Serial.begin(9600);
/* Configura os pinos dos LEDs como saída */
pinMode(pino_LED_Verde, OUTPUT);
pinMode(pino_LED_Vermelho, OUTPUT);
} /* Fim Setup */
void loop() {
/* Realiza a leitura do sensor e armazena o valor na variável ValAnalogIn */
ValAnalogIn = analogRead(pino_Sensor);
/* Converte o valor analógico para porcentagem */
int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);
/* Imprime o valor em Porcento no monitor Serial */
Serial.print(Porcento);
/* Imprime o símbolo junto ao valor encontrado */
Serial.println("%");
/* Se a porcentagem for menor ou igual ao valor definido */
if (Porcento <= Valor_Critico) {
   /* Imprime a frase no monitor serial */
   Serial.println("Umidade baixa!");
   /* Acende o LED Vermelho */
   digitalWrite(pino_LED_Vermelho, HIGH);
   /* Apaga o LED Verde */
   digitalWrite(pino_LED_Verde, LOW);
} /* Fim if */
  /* Se não... */
else {
   /* Imprime a frase no monitor serial */
   Serial.println("Umidade Adequada...");
   /* Acende o LED Verde */
   digitalWrite(pino_LED_Verde, HIGH);
   /* Apaga o LED Vermelho */
   digitalWrite(pino_LED_Vermelho, LOW);
} /* Fim else */
/* Aguarda 1 segundo para reinicializar a nova leitura */
delay (1000);
}/* Fim Loop */
