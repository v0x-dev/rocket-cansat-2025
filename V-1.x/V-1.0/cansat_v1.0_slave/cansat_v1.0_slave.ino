
//////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
//////////////////////////////////////////////////////////////////////
SoftwareSerial mySerial(7, 8); // RX, TX
//////////////////////////////////////////////////////////////////////
const int PIN_CHIP_SELECT = 4;
struct dataStruct {
  float temp;
  float p;
  unsigned long t;
  float m;                //переменные которые отправляет нрф
  float X_out;
  float Y_out;
  float Z_out;

  float Ratio_mq8;
  float LPG_mq8;

  float Ratio_mq2;
  float LPG_mq2;
  float Methane_mq2;
  float Smoke_mq2;
  float Hydrogen_mq2;

  float Ratio_mq135;
  float CO2_mq135;
} data;
void setup() {
  Serial.begin(9600);
  mySerial.begin(11500);


  if (!SD.begin(PIN_CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  Serial.print(F("Temperature = "));
  Serial.print(data.temp);
  Serial.print(" *C   ");

  Serial.print(F("Pressure = "));
  Serial.print(data.p);                    // вывод в сиреал
  Serial.print(" Pa   ");

  Serial.print(F("Altitude = "));
  Serial.print(data.m);
  Serial.print(" m");

  Serial.print("|||MQ2sensor||| :  ");

  // Serial.print("Ro = ");
  // Serial.print(mq8.getRo());

  Serial.print("  Ratio: ");
  Serial.print(data.Ratio_mq8);
  // выводим значения газов в ppm
  Serial.print("LPG: ");
  Serial.print(data.Ratio_mq8);
  Serial.print(" ppm ( %/10000)");

  Serial.print("|||MQ2sensor||| :  ");

  // Serial.print("Ro = ");
  //Serial.print(mq2.getRo());

  Serial.print("\tRatio: ");
  Serial.print(data.Ratio_mq2);
  // выводим значения газов в ppm
  Serial.print("\tLPG: ");
  Serial.print(data.LPG_mq2);
  Serial.print(" ppm");
  Serial.print("\tMethane: ");
  Serial.print(data.Methane_mq2);
  Serial.print(" ppm");
  Serial.print("\tSmoke: ");
  Serial.print(data.Smoke_mq2);
  Serial.print(" ppm");
  Serial.print("\tHydrogen: ");
  Serial.print(data.Hydrogen_mq2);
  Serial.print(" ppm");

  Serial.print("|||MQ135sensor||| :  ");

  //Serial.print("Ro = ");
  //Serial.print(mq135.getRo());

  Serial.print("Ratio: ");
  Serial.print(data.Ratio_mq135);
  // выводим значения газов в ppm
  //Serial.print("\tLPG: ");
  //Serial.print(mq135.readLPG());
  Serial.print("\tCO2: ");
  Serial.print(data.CO2_mq135);
  Serial.print(" ppm");

  Serial.println();

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.print(F("Temperature = "));
    dataFile.print(data.temp);
    dataFile.print(" *C   ");

    dataFile.print(F("Pressure = "));
    dataFile.print(data.p);                    // вывод в сиреал
    dataFile.print(" Pa   ");

    dataFile.print(F("Altitude = "));
    dataFile.print(data.m);
    dataFile.print(" m");

    dataFile.print("|||MQ2sensor||| :  ");

    //dataFile.print("Ro = ");
    //dataFile.print(mq8.getRo());

    dataFile.print("  Ratio: ");
    dataFile.print(data.Ratio_mq8);
    // выводим значения газов в ppm
    dataFile.print("LPG: ");
    dataFile.print(data.Ratio_mq8);
    dataFile.print(" ppm ( %/10000)");

    dataFile.print("|||MQ2sensor||| :  ");

    //dataFile.print("Ro = ");
    //dataFile.print(mq2.getRo());

    dataFile.print("\tRatio: ");
    dataFile.print(data.Ratio_mq2);
    // выводим значения газов в ppm
    dataFile.print("\tLPG: ");
    dataFile.print(data.LPG_mq2);
    dataFile.print(" ppm");
    dataFile.print("\tMethane: ");
    dataFile.print(data.Methane_mq2);
    dataFile.print(" ppm");
    dataFile.print("\tSmoke: ");
    dataFile.print(data.Smoke_mq2);
    dataFile.print(" ppm");
    dataFile.print("\tHydrogen: ");
    dataFile.print(data.Hydrogen_mq2);
    dataFile.print(" ppm");

    dataFile.print("|||MQ135sensor||| :  ");

    //dataFile.print("Ro = ");
    //dataFile.print(mq135.getRo());

    dataFile.print("Ratio: ");
    dataFile.print(data.Ratio_mq135);
    // выводим значения газов в ppm
    //dataFile.print("\tLPG: ");
    //dataFile.print(mq135.readLPG());
    dataFile.print("\tCO2: ");
    dataFile.print(data.CO2_mq135);
    dataFile.print(" ppm");

    dataFile.println();
    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");

  }
}
