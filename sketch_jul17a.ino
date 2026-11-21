#include <SPI.h>
#include <LoRa.h>             // Sandeep Mistry LoRa Library

// ESP32-C6 Hardware Pin Mapping
#define SCK     6   // GPIO6[cite: 1]
#define MISO    4   // GPIO4[cite: 1]
#define MOSI    5   // GPIO5[cite: 1]
#define SS      7   // GPIO7 (Chip Select)[cite: 1]
#define RST     0   // GPIO0[cite: 1]
#define DIO0    1   // GPIO1[cite: 1]

// Match your module's frequency (433E6, 868E6, or 915E6)
#define BAND    433E6

int counter = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Hardware Reset Pulse
    pinMode(RST, OUTPUT);
    digitalWrite(RST, LOW);
    delay(10);
    digitalWrite(RST, HIGH);
    delay(10);

    // Initialize SPI bus and LoRa pins
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);

    Serial.println("Initializing LoRa Transmitter...");
    if (!LoRa.begin(BAND)) {
        Serial.println("❌ LoRa initialization failed!");
        while (1); 
    }

    LoRa.setSyncWord(0xF3); // Explicit sync word
    LoRa.setTxPower(14);    // Lower power slightly to prevent receiver blinding on a desk
    Serial.println("✅ LoRa TX Ready!");
}

void loop() {
    String message = "Hello LoRa #" + String(counter);

    Serial.print("📡 Transmitting: ");
    Serial.println(message);

    // Send LoRa packet
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();

    counter++;
    delay(2000); // Send every 2 seconds
}
