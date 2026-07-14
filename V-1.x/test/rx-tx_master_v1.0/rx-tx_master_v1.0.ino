// Пример отправки и приёма структуры через Serial
// ОТПРАВИТЕЛЬ
// Ардуины соединены так:
// отправитель D11 -> приёмник D10
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 4); // RX, TX
struct Str {
  byte val_b;
  int val_i;
  long val_l;
  float val_f;
};
void setup() {
  Serial.begin(9600);
  mySerial.begin(11500);
}
void loop() {
  // буфер на отправку
  Str buf;
  // заполняем
  buf.val_b = 123;
  buf.val_i = 12345;
  buf.val_l = 123456;
  buf.val_f = 123.45;
  // отправляем родным write()
  // указываем ему буфер-структуру, но приводим тип к byte*
  // размер можно указать через sizeof()
  mySerial.write((byte*)&buf, sizeof(buf));
  delay(2000);
  Serial.println(buf.val_b);
  Serial.println(buf.val_i);
  Serial.println(buf.val_l);
  Serial.println(buf.val_f);
}
