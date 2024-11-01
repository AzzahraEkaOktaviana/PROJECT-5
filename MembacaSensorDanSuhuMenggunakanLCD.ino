#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2       // Pin data DHT11/DHT22
#define DHTTYPE DHT11  // Ganti dengan DHT22 jika menggunakan DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C biasanya 0x27 atau 0x3F

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Membaca Sensor...");
}

void loop() {
  // Membaca suhu dan kelembaban
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Jika pembacaan gagal, tampilkan pesan error
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error     ");
    return;
  }

  // Menampilkan hasil di Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Menampilkan hasil di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(2000); // Pembaruan setiap 2 detik
}

