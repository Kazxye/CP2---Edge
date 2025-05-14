// Sistema de Monitoramento Ambiental - Vinheria Agnello
// Implementação dos requisitos do Checkpoint 02

// Como no tinkercad não se tem o sensor DHT11 estou simulando suas leituras da seguinte forma:
// 
// - A luminosidade é simulada com um LDR no pino A1.
// - A temperatura é simulada com uma entrada analógica (A2), mapeada de 0 a 40°C.
// - A umidade é simulada com outra entrada analógica (A0), mapeada de 0 a 100%.

#include <LiquidCrystal.h>

const int ledVerdePin = 13;
const int ledAmareloPin = 12;
const int ledVermelhoPin = 11;
const int buzzerPin = 10;
const int ldrPin = A1;
const int tempPin = A2;
const int umidPin = A0;

const int displayRS = 9, displayEN = 8, displayD4 = 7, displayD5 = 6, displayD6 = 5, displayD7 = 4;
LiquidCrystal lcd(displayRS, displayEN, displayD4, displayD5, displayD6, displayD7);

const float TEMP_MIN = 10.0;
const float TEMP_MAX = 15.0;
const int UMID_MIN = 50;
const int UMID_MAX = 70;

const int LUZ_ESCURO = 300;
const int LUZ_MEIA_LUZ = 700;

const int NUM_LEITURAS = 5;
float leituras_temp[NUM_LEITURAS];
int leituras_umid[NUM_LEITURAS];
int leituras_luz[NUM_LEITURAS];
int indice_leituras = 0;
bool buffer_cheio = false;

unsigned long tempo_anterior = 0;
const unsigned long INTERVALO = 5000;

float temperatura = 0.0;
int umidade = 0;
int luminosidade = 0;

float lerTemperatura() {
  int valorSensor = analogRead(tempPin);
  return map(valorSensor, 0, 1023, 0, 40);  // Simula leitura de temperatura
}

int lerUmidade() {
  int valorSensor = analogRead(umidPin);
  return map(valorSensor, 0, 1023, 0, 100);  // Simula leitura de umidade
}

// Calcula as médias móveis dos sensores
void calcularMedias() {
  float soma_temp = 0;
  int soma_umid = 0;
  int soma_luz = 0;
  int total_amostras = buffer_cheio ? NUM_LEITURAS : indice_leituras; // Usa todas as amostras se o buffer estiver cheio, senão usa só as preenchidas

  
  for (int i = 0; i < total_amostras; i++) {
    soma_temp += leituras_temp[i];
    soma_umid += leituras_umid[i];
    soma_luz += leituras_luz[i];
  }
  
  temperatura = soma_temp / total_amostras;
  umidade = soma_umid / total_amostras;
  luminosidade = soma_luz / total_amostras;
}

void verificarLuminosidade() {
  digitalWrite(ledVerdePin, LOW);
  digitalWrite(ledAmareloPin, LOW);
  digitalWrite(ledVermelhoPin, LOW);
  
  if (luminosidade < LUZ_ESCURO) {
    digitalWrite(ledVerdePin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente escuro");
    digitalWrite(buzzerPin, LOW);
  }
  else if (luminosidade < LUZ_MEIA_LUZ) {
    digitalWrite(ledAmareloPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0, 1);
    lcd.print("luz");
    digitalWrite(buzzerPin, LOW);
  }
  else {
    digitalWrite(ledVermelhoPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente muito");
    lcd.setCursor(0, 1);
    lcd.print("claro");
    digitalWrite(buzzerPin, HIGH);  // Alerta sonoro para excesso de luz
  }
}

void verificarTemperatura() {
  if (temperatura >= TEMP_MIN && temperatura <= TEMP_MAX) {
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");
  } 
  else {
    digitalWrite(ledAmareloPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temperatura < TEMP_MIN ? "Temp. Baixa" : "Temp. Alta");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");
  }
}

void verificarUmidade() {
  if (umidade >= UMID_MIN && umidade <= UMID_MAX) {
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidade);
    lcd.print("%");
  } 
  else {
    digitalWrite(ledVermelhoPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(umidade < UMID_MIN ? "Umidade. Baixa" : "Umidade. Alta");
    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidade);
    lcd.print("%");
  }
}

void setup() {
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledAmareloPin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vinheria Agnello");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");

  Serial.begin(9600);

  for (int i = 0; i < NUM_LEITURAS; i++) {
    leituras_temp[i] = 0;
    leituras_umid[i] = 0;
    leituras_luz[i] = 0;
  }

  delay(2000);  // Tempo para leitura da mensagem de inicialização
}

void loop() {
  // Coleta novas leituras dos sensores
  float nova_temp = lerTemperatura();
  int nova_umid = lerUmidade();
  int nova_luz = analogRead(ldrPin);

  // Armazena as leituras no buffer circular
  leituras_temp[indice_leituras] = nova_temp;
  leituras_umid[indice_leituras] = nova_umid;
  leituras_luz[indice_leituras] = nova_luz;

  indice_leituras++;
  if (indice_leituras >= NUM_LEITURAS) {
    indice_leituras = 0;
    buffer_cheio = true;
  }

  calcularMedias();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C, Umidade: ");
  Serial.print(umidade);
  Serial.print("%, Luminosidade: ");
  Serial.println(luminosidade);

  unsigned long tempo_atual = millis();

  // Exibição rotativa a cada 5 segundos entre luminosidade, temperatura e umidade
  if (tempo_atual - tempo_anterior >= INTERVALO || tempo_anterior == 0) {
    tempo_anterior = tempo_atual;
    static int estado_display = 0;
    estado_display = (estado_display + 1) % 3;

    switch (estado_display) {
      case 0:
        verificarLuminosidade();
        break;
      case 1:
        verificarTemperatura();
        break;
      case 2:
        verificarUmidade();
        break;
    }
  }

  delay(1000);  // Delay pequeno para estabilidade e tempo entre leituras
}
