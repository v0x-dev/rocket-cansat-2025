#include "DHT.h"

// Определение пина, к которому подключен DHT11
#define DHTPIN 2     
// Определение типа используемого датчика
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  // Чтение показаний с датчика
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Проверка на ошибки при чтении
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Ошибка чтения с DHT11");
    return;
  }

  // Вывод данных на последовательный монитор
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print("%  Температура: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Задержка между измерениями
  delay(2000); 
}
