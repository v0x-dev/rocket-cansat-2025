#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//int text;
#define RXtime 200
#define RXtimeLost 2000

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

unsigned long timer1;
unsigned long timer2;
RF24 radio (9, 10);

//int temperature;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(27);
  radio.setDataRate  (RF24_1MBPS);
  radio.setPALevel  (RF24_PA_HIGH);
  radio.openReadingPipe (1, 0x1234567890LL);
  radio.startListening ();

}
void loop() {

  if (-timer1 + millis() >= RXtimeLost) {
    Serial.println("************RX LOST************");
    timer1 = millis();
    timer2 = millis();
  }


  if (radio.available() ) {
    timer1 = millis();
    timer2 = millis();
    radio.read( &data, sizeof(data) );

    if (data.temp >= 5) {

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
      /*
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
    }
    /* Serial.println(data.temp);
      Serial.println(data.p);
      Serial.println(data.t);
      Serial.println(data.m);*/
  }

}
