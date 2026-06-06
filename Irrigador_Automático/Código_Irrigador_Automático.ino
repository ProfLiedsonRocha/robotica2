// =========================================
// IRRIGADOR AUTOMÁTICO
// =========================================

// Pino do sensor
#define sensor A0

// Pino do relé
#define rele 8

// Variável para armazenar a leitura
int leituraSensor;

// Variável para armazenar a porcentagem
int umidade;

void setup()
{
  // Inicia comunicação serial
  Serial.begin(9600);

  // Configura o relé como saída
  pinMode(rele, OUTPUT);

  // Garante que a bomba comece desligada
  digitalWrite(rele, LOW);

  Serial.println("Sistema de Irrigacao Iniciado");
}

void loop()
{
  // Lê o sensor
  leituraSensor = analogRead(sensor);

  // Converte para porcentagem
  umidade = map(leituraSensor, 1023, 0, 0, 100);

  // Mostra informações
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  // Verifica a necessidade de irrigação
  if (umidade <= 45)
  {
    Serial.println("Solo seco!");
    Serial.println("Ligando bomba...");

    digitalWrite(rele, HIGH);
  }
  else
  {
    Serial.println("Solo umido.");
    Serial.println("Desligando bomba...");

    digitalWrite(rele, LOW);
  }

  Serial.println("------------------");

  delay(1000);
}
