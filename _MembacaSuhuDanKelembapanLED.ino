#include <DHT.h>

#define DHTPIN 2       // Pin yang terhubung ke sensor DHT
#define DHTTYPE DHT22  // Ganti dengan DHT11 jika menggunakan sensor DHT11
#define LEDPIN 13      // Pin untuk LED, misalnya pin 1

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(LEDPIN, OUTPUT);  // Set LED pin sebagai output
  digitalWrite(LEDPIN, LOW); // Awalnya LED dimatikan
}

void loop() {
  float humidity = dht.readHumidity();      // Membaca kelembaban
  float temperature = dht.readTemperature(); // Membaca suhu dalam Celcius

  // Jika gagal membaca sensor
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Menampilkan hasil ke Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  delay(500);
  // Cek suhu, nyalakan LED jika suhu >= 30 derajat Celcius
  if (temperature >= 27.0) {
    digitalWrite(LEDPIN, HIGH);  // Nyalakan LED
    delay(500);
    digitalWrite(LEDPIN, LOW); // Tunggu 2 detik sebelum pembacaan berikutnya
  } 
}

