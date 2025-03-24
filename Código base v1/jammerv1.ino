#include <SPI.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN  8
#define SCK_PIN  4
#define MISO_PIN 5
#define MOSI_PIN 6

RF24 radio(CE_PIN, CSN_PIN);

// Bluetooth opera de 2.402 GHz a 2.480 GHz (79 canais de 1 MHz)
// Canais do NRF24L01 vão de 2400 MHz a 2525 MHz (1 canal = 1 MHz)
const uint8_t canais_bluetooth[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 
  63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80
};
const int num_canais = sizeof(canais_bluetooth) / sizeof(canais_bluetooth[0]);
int canal_atual = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setAutoAck(false);
  radio.setRetries(0, 0);
  Serial.println("Scanner e interferência em toda a faixa Bluetooth iniciados...");
}

void loop() {
  radio.setChannel(canais_bluetooth[canal_atual]);
  radio.startListening();
  
  delay(5);  // Reduz o tempo de detecção para aumentar a cobertura

  if (radio.testCarrier()) {  // Se detectar um sinal forte no canal
    Serial.print("Interferindo no canal: ");
    Serial.println(canais_bluetooth[canal_atual]);

    radio.stopListening();
    while (radio.testCarrier()) {  
      radio.write("Jamming", 7);
      delay(2);  // Menor delay para maior taxa de interferência
    }
  }

  // Avança para o próximo canal
  canal_atual = (canal_atual + 1) % num_canais;
}
