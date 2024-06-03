#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largura do LED
#define SCREEN_HEIGHT 64 // Altura do LED
#define OLED_RESET     -1 // Reset pin # (ou deixe -1 se compartilhar o reset com o microcontrolador)
#define SCREEN_ADDRESS 0x3C ///< Endereço I2C do display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SENSOR_PIN 34 // Pino do sensor de distância
#define RELAY_PIN 15  // Pino do relé

// Parâmetros da caixa de água (ajuste conforme necessário)
float h = 100.0; // Altura da caixa de água em cm
float radius = 50.0;  // Raio para caixa cilíndrica em cm
float length = 100.0; // Comprimento para caixa retangular em cm
float width = 50.0;   // Largura para caixa retangular em cm
float R = 50.0;       // Raio maior para tronco de cone em cm
float r = 30.0;       // Raio menor para tronco de cone em cm

// Limiar de volume de água para ligar a bomba
float minVolume = 100000.0; // Exemplo: 100 litros

// Função para calcular o volume de um cilindro
float calculateCylinderVolume(float height) {
  return PI * pow(radius, 2) * height;
}

// Função para calcular o volume de um prisma retangular
float calculateRectangularVolume(float height) {
  return length * width * height;
}

// Função para calcular o volume de um tronco de cone
float calculateTruncatedConeVolume(float height) {
  return (PI / 3) * height * (pow(R, 2) + R*r + pow(r, 2));
}

// Função para inicializar o display OLED
void initDisplay() {
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Não faz nada mais
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Inicializando...");
  display.display();
  delay(2000);
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Desliga a bomba inicialmente

  // Inicializa o display OLED
  initDisplay();
}

void loop() {
  int sensorReading = analogRead(SENSOR_PIN);
  float distance = sensorReading / 4096.0 * 100.0; // Converta para distância em cm, ajuste conforme necessário
  
  // Calcule a altura da coluna de água
  float waterHeight = h - distance;
  
  // Escolha entre as funções de cálculo de volume conforme a forma da caixa de água
  float volume;
  // Para caixa cilíndrica
  // volume = calculateCylinderVolume(waterHeight);
  // Para caixa retangular
  // volume = calculateRectangularVolume(waterHeight);
  // Para tronco de cone
  volume = calculateTruncatedConeVolume(waterHeight);
  
  // Atualiza o display OLED
  display.clearDisplay();
  display.setCursor(0,10);
  display.print("Litros: ");
  display.print(volume / 1000); // Converte cm³ para litros
  display.display();

  // Verifica se o volume está abaixo do limiar
  if(volume < minVolume) {
    digitalWrite(RELAY_PIN, HIGH); // Liga a bomba
  } else {
    digitalWrite(RELAY_PIN, LOW); // Desliga a bomba
  }
  
  delay(1000); // Aguarde um pouco antes de verificar novamente
}