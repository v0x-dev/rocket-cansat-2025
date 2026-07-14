#include <SPI.h>
#include <Adafruit_BMP280.h>
//#include <nRF24L01.h>
//#include <RF24.h>
#include <Wire.h>

Adafruit_BMP280 bmp280;   //sda-a4  scl-a5

//RF24   radio (9, 10);
const int PIN_CHIP_SELECT = 4;
int ADXL345 = 0x53;
//int temperature;
//int pressure;
//int altitude;

//char dataToSend[20] = "Message 0";

struct dataStruct {
  float temp;
  float p;
  unsigned long t;
  float m;
  float X_out;
  float Y_out;
  float Z_out;
} data;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280"));
  //pinMode (10, OUTPUT);
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
  Wire.endTransmission();
  /*while (!bmp280.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);*/
  }
  // pinMode(2, OUTPUT);
  // digitalWrite(2, 1);
  
  /*radio.begin();
  radio.setChannel(27);
  radio.setDataRate  (RF24_1MBPS);
  radio.setPALevel  (RF24_PA_MAX);
  radio.openWritingPipe  (0x1234567890LL);*/


void loop() {
  //temperature =
  //pressure =
  //altitude = bmp280.readAltitude(1010.25);

  data.temp = bmp280.readTemperature();
  data.p = bmp280.readPressure() / 100.0F;
  data.t = millis();
  data.m = bmp280.readAltitude(1010.25);
  data.temp -= 5;

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

  //radio.write(&data, sizeof(data));


  Serial.print("Xa= ");
  Serial.print(data.X_out);
  Serial.print("   Ya= ");
  Serial.print(data.Y_out);
  Serial.print("   Za= ");
  Serial.print(data.Z_out);

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
  //delay(0);
}
