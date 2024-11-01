#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 8

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Gantilah UID_TAG dan UID_KTP dengan UID sebenarnya dari tag RFID dan KTP Anda
byte UID_TAG[4] = {0xC7, 0x77, 0x43, 0x3F}; // Gantilah dengan UID Tag RFID Anda
byte UID_KTP[7] = {0x4, 0x4A, 0x62, 0xE2, 0x2B, 0x77, 0x80}; // Gantilah dengan UID KTP Anda

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Tempelkan kartu untuk scanning...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Membaca UID kartu yang dipindai
  if (isSameUID(UID_TAG, mfrc522.uid.uidByte)) {
    Serial.println("Status: Deny");
    blinkLED(3000);  // Blink LED selama 3 detik
  }
  else if (isSameUID(UID_KTP, mfrc522.uid.uidByte)) {
    Serial.println("Status: Allow");
    solidLED(3000);  // Nyalakan LED solid selama 3 detik
  } else {
    Serial.println("Kartu tidak dikenal");
  }

  mfrc522.PICC_HaltA();
}

// Fungsi untuk membandingkan dua UID
bool isSameUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}

// Fungsi untuk LED berkedip
void blinkLED(int duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}

// Fungsi untuk LED menyala terus
void solidLED(int duration) {
  digitalWrite(LED_PIN, HIGH);
  delay(duration);
  digitalWrite(LED_PIN, LOW);
}