#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TroykaMQ.h>
#include <SoftwareSerial.h>
#include <basicMPU6050.h>

Adafruit_BMP280 bmp280;
#define PIN_MQ8 A1
#define PIN_MQ2 A2
#define PIN_MQ135 A0
RF24 radio(9, 10);
SoftwareSerial mySerial(2, 4);
basicMPU6050<> imu;

char dataToSend[20] = "Message 0";
struct dataStruct {
  float temp, p, m, X_out, Y_out, Z_out;
  float Xa_out, Ya_out, Za_out, Xg_out, Yg_out, Zg_out, temp_mpu;
  float Ratio_mq8, LPG_mq8, Ratio_mq2, LPG_mq2, Methane_mq2, Smoke_mq2, Hydrogen_mq2;
  float Ratio_mq135, CO2_mq135;
  unsigned long t;
} data;

MQ8 mq8(PIN_MQ8);
MQ2 mq2(PIN_MQ2);
MQ135 mq135(PIN_MQ135);

void setup() {
  Serial.begin(9600);
  mySerial.begin(11500);
  imu.setup();
  mq8.calibrate();
  mq2.calibrate();
  mq135.calibrate();
  imu.setBias();

  while (!bmp280.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("BMP280 Error!"));
    delay(2000);
  }
  Serial.print("Ro mq8 = ");
  Serial.print(mq8.getRo());
  Serial.print(" Ro mq2 = ");
  Serial.print(mq2.getRo());
  Serial.print(" Ro mq135 = ");
  Serial.println(mq135.getRo());

  radio.begin();
  radio.setChannel(27);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(0x1234567890LL);
}

void loop() {
  data.temp = bmp280.readTemperature();
  data.p = bmp280.readPressure() / 100.0F;
  data.t = millis();
  data.m = bmp280.readAltitude(1010.25);
  data.Ratio_mq8 = mq8.readRatio();
  data.LPG_mq8 = mq8.readHydrogen();
  data.Ratio_mq2 = mq2.readRatio();
  data.LPG_mq2 = mq2.readLPG();
  data.Methane_mq2 = mq2.readMethane();
  data.Smoke_mq2 = mq2.readSmoke();
  data.Hydrogen_mq2 = mq2.readHydrogen();
  data.Ratio_mq135 = mq135.readRatio();
  data.CO2_mq135 = mq135.readCO2();
  data.Xa_out = imu.ax();
  data.Ya_out = imu.ay();
  data.Za_out = imu.az();
  data.Xg_out = imu.gx();
  data.Yg_out = imu.gy();
  data.Zg_out = imu.gz();
  data.temp_mpu = imu.temp();

  radio.write(&data, sizeof(data));
  mySerial.write((byte*)&data, sizeof(data));

  Serial.print(F("Temp= "));
  Serial.print(data.temp);
  Serial.print(" *C, Pressure= ");
  Serial.print(data.p);
  Serial.print(" Pa, Altitude= ");
  Serial.print(data.m);
  Serial.print(" m, MQ8: Ratio= ");
  Serial.print(data.Ratio_mq8);
  Serial.print(" LPG= ");
  Serial.print(data.LPG_mq8);
  Serial.print(" ppm, MQ2: Ratio= ");
  Serial.print(data.Ratio_mq2);
  Serial.print(" LPG= ");
  Serial.print(data.LPG_mq2);
  Serial.print(" ppm, Methane= ");
  Serial.print(data.Methane_mq2);
  Serial.print(" ppm, Smoke= ");
  Serial.print(data.Smoke_mq2);
  Serial.print(" ppm, Hydrogen= ");
  Serial.print(data.Hydrogen_mq2);
  Serial.print(" ppm, MQ135: Ratio= ");
  Serial.print(data.Ratio_mq135);
  Serial.print(" CO2= ");
  Serial.print(data.CO2_mq135);
  Serial.print(" ppm, MPU Accel XYZ= ");
  Serial.print(data.Xa_out);
  Serial.print(" ");
  Serial.print(data.Ya_out);
  Serial.print(" ");
  Serial.print(data.Za_out);
  Serial.print(", MPU Gyro XYZ= ");
  Serial.print(data.Xg_out);
  Serial.print(" ");
  Serial.print(data.Yg_out);
  Serial.print(" ");
  Serial.print(data.Zg_out);
  Serial.print(", MPU Temp= ");
  Serial.println(data.temp_mpu);
}
