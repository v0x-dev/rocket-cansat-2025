#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <basicMPU6050.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

Adafruit_BMP280 bmp280;   //sda-a4  scl-a5
basicMPU6050<> imu;
RF24   radio (9, 10);
const int PIN_CHIP_SELECT = 4;
int ADXL345 = 0x53;
//int temperature;
//int pressure;
//int altitude;

char dataToSend[20] = "Message 0";

struct dataStruct {
  float temp;
  float p;
  unsigned long t;
  float m;
  float aX_out;
  float aY_out;
  float aZ_out;

  float aX_out_mpu;
  float aY_out_mpu;
  float aZ_out_mpu;

  float gX_out_mpu;
  float gY_out_mpu;
  float gZ_out_mpu;

  float temp_mpu;

} data;

void setup() {
  Serial.println(F("BMP280"));
  //pinMode (10, OUTPUT);
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
  Wire.endTransmission();
  imu.setup();
  imu.setBias();
  /*while (!bmp280.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
    }*/

  // pinMode(2, OUTPUT);
  // digitalWrite(2, 1);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(27);
  radio.setDataRate  (RF24_1MBPS);
  radio.setPALevel  (RF24_PA_MAX);
  radio.openWritingPipe  (0x1234567890LL);

}
void loop() {
  imu.updateBias();
  //temperature =
  //pressure =
  //altitude = bmp280.readAltitude(1010.25);

  data.temp = bmp280.readTemperature();
  data.p = bmp280.readPressure() / 100.0F;
  data.t = millis();
  data.m = bmp280.readAltitude(1010.25);
  data.temp -= 5;

  data.aX_out_mpu = imu.ax();
  data.aY_out_mpu = imu.ay();
  data.aZ_out_mpu = imu.az();

  data.gX_out_mpu = imu.gx();
  data.gY_out_mpu = imu.gy();
  data.gZ_out_mpu = imu.gz();

  data.temp_mpu = imu.temp();


  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  data.aX_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  data.aX_out = data.aX_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  data.aY_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  data.aY_out = data.aY_out / 256;
  data.aZ_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  data.aZ_out = data.aZ_out / 256;

  radio.write(&data, sizeof(data));


  Serial.print("Xa= ");
  Serial.print(data.aX_out);
  Serial.print("   Ya= ");
  Serial.print(data.aY_out);
  Serial.print("   Za= ");
  Serial.print(data.aZ_out);

  Serial.print(F("   Temperature = "));
  Serial.print(data.temp);
  Serial.print(" *C   ");

  Serial.print(F("Pressure = "));
  Serial.print(data.p);
  Serial.print(" Pa   ");

  Serial.print(F("Altitude = "));
  Serial.print(data.m);
  Serial.print(" m");

  Serial.println();


  Serial.print( imu.ax() );
  Serial.print( " " );
  Serial.print( imu.ay() );
  Serial.print( " " );
  Serial.print( imu.az() );
  Serial.print( "    " );

  // Gyro
  Serial.print( imu.gx() );
  Serial.print( " " );
  Serial.print( imu.gy() );
  Serial.print( " " );
  Serial.print( imu.gz() );
  Serial.print( "    " );

  // Temp
  Serial.print( imu.temp() );
  Serial.println();
}
//delay(0);
