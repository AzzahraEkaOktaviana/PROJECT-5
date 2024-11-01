#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10     // Pin SDA dihubungkan ke pin D10 Arduino
#define RST_PIN 9     // Pin RST dihubungkan ke pin D9 Arduino
int sda = A4;
int scl = A5;

MFRC522 rfid(SS_PIN, RST_PIN); // Inisialisasi instance dari MFRC522
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C 0x27, LCD 16x2

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial
  SPI.begin();         // Mulai komunikasi SPI
  rfid.PCD_Init();     // Inisialisasi modul RFID

  // Inisialisasi LCD
  lcd.init();               
  lcd.backlight();          
  lcd.setCursor(0, 0);    
  lcd.print("Scan a card...");
  Serial.println("Scan a card...");
}

void loop() {
  // Cek apakah ada kartu baru yang didekatkan ke reader RFID
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Cek apakah bisa membaca kartu
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Hapus tampilan LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UID Kartu:");

  // Tampilkan UID kartu di LCD dan Serial Monitor
  Serial.print("UID Kartu: ");
  lcd.setCursor(0, 1);  // Pindah ke baris kedua LCD
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    
    // Tampilkan juga di LCD
    lcd.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Hentikan komunikasi dengan kartu
  rfid.PICC_HaltA();
}