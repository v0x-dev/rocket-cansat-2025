/*
   настройка пинов
   связь между платами
   настройка датчиков
   считывание данных с датчиков
   обработка данных
   отправка данных

*/
///////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TroykaMQ.h>
//#include <Wire.h>
#include <SoftwareSerial.h>
#include <basicMPU6050.h>
//////////////////////////////////////////////////////////////////////////
Adafruit_BMP280 bmp280;   //sda-a4  scl-a5      настроцка барометра
#define PIN_MQ8  A1
#define PIN_MQ2  A2
#define PIN_MQ135  A0
RF24   radio (9, 10);     //        настройка нрф
SoftwareSerial mySerial(2, 4); // RX, TX
basicMPU6050<> imu;//инициализация mpu6050
//////////////////////////////////////////////////////////////////////////
//int ADXL345 = 0x53; // The ADXL345 sensor I2C address  |||for ADXL345|||
//float X_out, Y_out, Z_out;  // Outputs

char dataToSend[20] = "Message 0";
/*
  struct mq8modulStruct {
  float Ratio_mq8;
  float LPG_mq8;
  } mq8modul;

  struct mq2modulStruct {
  float Ratio_mq2;
  float LPG_mq2;
  float Methane_mq2;
  float Smoke_mq2;
  float Hydrogen_mq2;
  } mq2modul;

  struct mq135modulStruct {
  float Ratio_mq135;
  float CO2_mq135;
  } mq135modul;
*/
struct dataStruct {
  float temp;
  float p;
  unsigned long t;
  float m;                //переменные которые отправляет нрф
  //float X_out;
  //float Y_out;            //adxl 345
  //float Z_out;

  float Xa_out;
  float Ya_out;            //mpu6050
  float Za_out;

  float Xg_out;
  float Yg_out;            //mpu6050
  float Zg_out;

  float temp_mpu;

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
////////////////////////////////////////////////////////////////////////////
MQ8 mq8(PIN_MQ8);
MQ2 mq2(PIN_MQ2);
MQ135 mq135(PIN_MQ135);




void setup() {
  Serial.begin(9600);
  mySerial.begin(11500);
  imu.setup(); //for mpu 6050

  mq8.calibrate();
  mq2.calibrate();
  mq135.calibrate();
  imu.setBias(); //калибровка mpu 6050
  /*
    Wire.begin(); // Initiate the Wire library
    // Set ADXL345 in measuring mode
    Wire.beginTransmission(ADXL345); // Start communicating with the device
    Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    Wire.endTransmission();*/

  Serial.println(F("BMP280"));
  while (!bmp280.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }

  Serial.print("Ro mq8 = ");
  Serial.print(mq8.getRo());
  Serial.print("  Ro mq2 = ");
  Serial.print(mq2.getRo());
  Serial.print("  Ro mq135 = ");
  Serial.println(mq135.getRo());


  radio.begin();
  radio.setChannel(27);
  radio.setDataRate  (RF24_1MBPS);
  radio.setPALevel  (RF24_PA_MAX);
  radio.openWritingPipe  (0x1234567890LL);

}
void loop() {



  /*
    Wire.beginTransmission(ADXL345);
    Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    data.X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
    data.X_out = data.X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
    data.Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
    data.Y_out = data.Y_out / 256;
    data.Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
    data.Z_out = data.Z_out / 256;

  */
  data.temp = bmp280.readTemperature();
  data.p = bmp280.readPressure() / 100.0F;
  data.t = millis();
  data.m = bmp280.readAltitude(1010.25);


  data.Ratio_mq8 = mq8.readRatio() ;
  data.LPG_mq8 = mq8.readHydrogen() ;

  data.Ratio_mq2 = mq2.readRatio() ;
  data.LPG_mq2 = mq2.readLPG() ;
  data.Methane_mq2 = mq2.readMethane() ;
  data.Smoke_mq2 = mq2.readSmoke() ;
  data.Hydrogen_mq2 = mq2.readHydrogen() ;

  data.Ratio_mq135 = mq135.readRatio() ;
  data.CO2_mq135 = mq135.readCO2() ;


  data.Xa_out = imu.ax()  ;
  data.Ya_out = imu.ay()  ;
  data.Za_out = imu.az()  ;

  data.Xg_out = imu.gx()  ;
  data.Yg_out = imu.gy()  ;
  data.Zg_out = imu.gz()  ;

  data.temp_mpu = imu.temp();


  radio.write(&data, sizeof(data));
  //(byte*)
  mySerial.write((byte*)&data, sizeof(data));
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.print(F("Temperature= "));
  Serial.print(data.temp);
  Serial.print(" *C ");

  Serial.print(F("Pressure = "));
  Serial.print(data.p);                    // вывод в сиреал
  Serial.print(" Pa ");

  Serial.print(F("Altitude= "));
  Serial.print(data.m);
  Serial.print(" m ");

  Serial.print("__MQ8sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq8.getRo());

  Serial.print("Ratio: ");
  Serial.print(data.Ratio_mq8);
  // выводим значения газов в ppm
  Serial.print(" LPG: ");
  Serial.print(data.Ratio_mq8);
  Serial.print(" ppm(%/10000) ");

  Serial.print("__MQ2sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq2.getRo());

  Serial.print("Ratio: ");
  Serial.print(data.Ratio_mq2);
  // выводим значения газов в ppm
  Serial.print(" LPG: ");
  Serial.print(data.LPG_mq2);
  Serial.print(" ppm ");
  Serial.print("Methane: ");
  Serial.print(data.Methane_mq2);
  Serial.print(" ppm ");
  Serial.print("Smoke: ");
  Serial.print(data.Smoke_mq2);
  Serial.print(" ppm ");
  Serial.print("Hydrogen: ");
  Serial.print(data.Hydrogen_mq2);
  Serial.print(" ppm ");

  Serial.print("__MQ135sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq135.getRo());

  Serial.print("Ratio: ");
  Serial.print(data.Ratio_mq135);
  // выводим значения газов в ppm
  //Serial.print("\tLPG: ");
  //Serial.print(mq135.readLPG());
  Serial.print(" CO2: ");
  Serial.print(data.CO2_mq135);
  Serial.print(" ppm");
  /*
    Serial.print(" ADXL345_axel_XYZ: ");
    Serial.print(data.X_out);
    Serial.print(" ");
    Serial.print(data.X_out);     //ADXL345 axel
    Serial.print(" ");
    Serial.print(data.X_out);*/

  Serial.print(" mpu_axel_XYZ: ");
  Serial.print(data.Xa_out);
  Serial.print(" ");
  Serial.print(data.Ya_out);    //mpu6050 axel
  Serial.print(" ");
  Serial.print(data.Za_out);

  Serial.print(" mpu_giro_XYZ: ");
  Serial.print(data.Xg_out);
  Serial.print(" ");
  Serial.print(data.Yg_out);    //mpu6050 giro
  Serial.print(" ");
  Serial.print(data.Zg_out);

  Serial.print(" mpu_temp: ");
  Serial.print(data.temp_mpu);

  Serial.println();
  //delay(0);
}
