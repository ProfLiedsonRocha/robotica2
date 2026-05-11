// ======================================================
// SEMÁFORO DE CRUZAMENTO COM PEDESTRES
// Arduino UNO
// ======================================================

// -------------------------
// PINOS DOS LEDS DOS CARROS
// -------------------------
int carroVermelho = 3;
int carroAmarelo = 4;
int carroVerde = 5;

// ------------------------------
// PINOS DOS LEDS DOS PEDESTRES
// ------------------------------
int pedestreVermelho = 6;
int pedestreVerde = 7;

// -------------------------
// SENSOR E BUZZER
// -------------------------
int sensorIR = 2;   // saída OUT do sensor IR
int buzzer = 8;

// ======================================================
// FUNÇÃO SETUP
// Essa parte roda apenas UMA VEZ quando o Arduino liga
// ======================================================
void setup() {

  // Define os LEDs como SAÍDA
  pinMode(carroVermelho, OUTPUT);
  pinMode(carroAmarelo, OUTPUT);
  pinMode(carroVerde, OUTPUT);

  pinMode(pedestreVermelho, OUTPUT);
  pinMode(pedestreVerde, OUTPUT);

  // Sensor IR como ENTRADA
  pinMode(sensorIR, INPUT);

  // Buzzer como SAÍDA
  pinMode(buzzer, OUTPUT);

  // ==================================================
  // ESTADO INICIAL DO SEMÁFORO
  // Carros: VERDE
  // Pedestres: VERMELHO
  // ==================================================

  digitalWrite(carroVerde, HIGH);
  digitalWrite(carroAmarelo, LOW);
  digitalWrite(carroVermelho, LOW);

  digitalWrite(pedestreVerde, LOW);
  digitalWrite(pedestreVermelho, HIGH);
}

// ======================================================
// LOOP
// Essa função fica repetindo para sempre
// ======================================================
void loop() {

  // Lê o estado do sensor IR
  int estadoSensor = digitalRead(sensorIR);

  // ==================================================
  // SE O SENSOR DETECTAR ALGO
  // ==================================================
  if (estadoSensor == LOW) {

    // ------------------------------------------------
    // ETAPA 1 - AVISO PARA OS CARROS
    // Verde desliga e amarelo acende
    // ------------------------------------------------

    digitalWrite(carroVerde, LOW);
    digitalWrite(carroAmarelo, HIGH);

    // Tempo de atenção
    delay(3000);

    // ------------------------------------------------
    // ETAPA 2 - CARROS PARAM
    // Vermelho dos carros acende
    // ------------------------------------------------

    digitalWrite(carroAmarelo, LOW);
    digitalWrite(carroVermelho, HIGH);

    // Pequeno tempo de segurança
    delay(2000);

    // ------------------------------------------------
    // ETAPA 3 - PEDESTRES PODEM PASSAR
    // ------------------------------------------------

    digitalWrite(pedestreVermelho, LOW);
    digitalWrite(pedestreVerde, HIGH);

    // ==================================================
    // BUZZER APITANDO DEVAGAR
    // ==================================================

    for (int i = 0; i < 10; i++) {

      tone(buzzer, 1000); // frequência do som
      delay(300);

      noTone(buzzer);
      delay(300);
    }

    // ==================================================
    // FASE FINAL
    // BUZZER APITA MAIS RÁPIDO
    // AVISANDO QUE O SINAL VAI FECHAR
    // ==================================================

    for (int i = 0; i < 15; i++) {

      tone(buzzer, 1200);
      delay(100);

      noTone(buzzer);
      delay(100);
    }

    // ------------------------------------------------
    // ETAPA 4 - FECHA PEDESTRES
    // ------------------------------------------------

    digitalWrite(pedestreVerde, LOW);
    digitalWrite(pedestreVermelho, HIGH);

    // Tempo de segurança
    delay(2000);

    // ------------------------------------------------
    // ETAPA 5 - ABRE PARA OS CARROS
    // ------------------------------------------------

    digitalWrite(carroVermelho, LOW);
    digitalWrite(carroVerde, HIGH);
  }
}