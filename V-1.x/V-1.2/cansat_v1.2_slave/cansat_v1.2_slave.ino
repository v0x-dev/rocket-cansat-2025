#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

//////////////////////////////////////////////////////////////////////
SoftwareSerial mySerial(4, 2); // RX, TX
//////////////////////////////////////////////////////////////////////
const int PIN_CHIP_SELECT = 4;

struct dataStruct {
  float temp, p, m;
  unsigned long t;
  float X_out, Y_out, Z_out;
  float Xa_out, Ya_out, Za_out;
  float Xg_out, Yg_out, Zg_out;
  float temp_mpu;
  float Ratio_mq8, LPG_mq8;
  float Ratio_mq2, LPG_mq2, Methane_mq2, Smoke_mq2, Hydrogen_mq2;
  float Ratio_mq135, CO2_mq135;
} data;

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);

  if (!SD.begin(PIN_CHIP_SELECT)) {
    Serial.println("SD card initialization failed!");
    while (1);  // Остановка, если карта не найдена
  }
  Serial.println("SD card initialized.");
}

void loop() {
  if (mySerial.readBytes((byte*)&data, sizeof(data))) {
    printDataToSerial();
    logDataToSD();
  }
}

void printDataToSerial() {
  Serial.print(F("Temp: ")); Serial.print(data.temp); Serial.print(" *C, ");
  Serial.print(F("Pressure: ")); Serial.print(data.p); Serial.print(" Pa, ");
  Serial.print(F("Altitude: ")); Serial.print(data.m); Serial.print(" m, ");
  Serial.print(F("MPU6050 Accel XYZ: "));
  Serial.print(data.Xa_out); Serial.print(", ");
  Serial.print(data.Ya_out); Serial.print(", ");
  Serial.print(data.Za_out); Serial.print(" | ");
  Serial.print("Gases: MQ2 - ");
  Serial.print("LPG: "); Serial.print(data.LPG_mq2); Serial.print(" ppm, ");
  Serial.print("Methane: "); Serial.print(data.Methane_mq2); Serial.print(" ppm, ");
  Serial.print("MQ135 CO2: "); Serial.print(data.CO2_mq135); Serial.print(" ppm");
  Serial.println();
}

void logDataToSD() {
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(F("Temp: ")); dataFile.print(data.temp); dataFile.print(" *C, ");
    dataFile.print(F("Pressure: ")); dataFile.print(data.p); dataFile.print(" Pa, ");
    dataFile.print(F("Altitude: ")); dataFile.print(data.m); dataFile.print(" m, ");
    dataFile.print("Gases: MQ2 - ");
    dataFile.print("LPG: "); dataFile.print(data.LPG_mq2); dataFile.print(" ppm, ");
    dataFile.print("Methane: "); dataFile.print(data.Methane_mq2); dataFile.print(" ppm, ");
    dataFile.print("MQ135 CO2: "); dataFile.print(data.CO2_mq135); dataFile.print(" ppm");
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error opening datalog.txt");
  }
}
