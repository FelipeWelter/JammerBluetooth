1. Usando o Próprio NRF24L01 para Escanear Canais

O NRF24L01 pode verificar a presença de sinais fortes em diferentes canais usando a função testCarrier(). 

Como funciona?
O código troca de canal constantemente , verificando se há um sinal forte.

Se houver atividade , ele imprime o número do canal no monitor serial .

Após escanear todos os canais, ele reinicia o processo.

O código abaixo escaneia os canais do Bluetooth (2 a 80) e mostra onde há atividade:

Código para Escanear Canais Bluetooth com ESP32-C3 + NRF24L01

#include <SPI.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN  8

RF24 radio(CE_PIN, CSN_PIN);

const uint8_t canais_bluetooth[] = { 
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
    63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80
};

const int num_canais = sizeof(canais_bluetooth) / sizeof(canais_bluetooth[0]);

void setup() {
    Serial.begin(115200);
    SPI.begin();
    radio.begin();
    radio.setAutoAck(false);
    radio.setPALevel(RF24_PA_HIGH);
    Serial.println("Escaneando canais Bluetooth...");
}

void loop() {
    for (int i = 0; i < num_canais; i++) {
        radio.setChannel(canais_bluetooth[i]);
        radio.startListening();
        delay(5);

        if (radio.testCarrier()) {  // Se detectar um sinal forte no canal
            Serial.print("Sinal detectado no canal: ");
            Serial.println(canais_bluetooth[i]);
        }

        radio.stopListening();
    }
    Serial.println("Escaneamento completo! Reiniciando...");
    delay(1000);
}
