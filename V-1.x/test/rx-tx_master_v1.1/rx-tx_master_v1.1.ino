#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 4);
struct Str {
  float temp;
  float p;
  unsigned long t;
  float m;                //переменные которые отправляет нрф
  float X_out;
  float Y_out;            //adxl 345
  float Z_out;

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
} ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(11500);

Str buf;

  buf.temp = 0;
  buf.p = 0;
  buf.t = 0;
  buf.m = 0;


  buf.Ratio_mq8 = 0;
  buf.LPG_mq8 = 0;

  buf.Ratio_mq2 = 0;
  buf.LPG_mq2 = 0;
  buf.Methane_mq2 = 0;
  buf.Smoke_mq2 = 0;
  buf.Hydrogen_mq2 = 0;

  buf.Ratio_mq135 = 0;
  buf.CO2_mq135 = 0;


  buf.Xa_out = 0  ;
  buf.Ya_out = 0  ;
  buf.Za_out = 0  ;

  buf.Xg_out = 0  ;
  buf.Yg_out = 0  ;
  buf.Zg_out = 0  ;

  buf.temp_mpu = 0;
}

void loop() {
  /*buf.temp = 0;
  buf.p = 0;
  buf.t = 0;
  buf.m = 0;


  buf.Ratio_mq8 = 0;
  buf.LPG_mq8 = 0;

  buf.Ratio_mq2 = 0;
  buf.LPG_mq2 = 0;
  buf.Methane_mq2 = 0;
  buf.Smoke_mq2 = 0;
  buf.Hydrogen_mq2 = 0;

  buf.Ratio_mq135 = 0;
  buf.CO2_mq135 = 0;


  buf.Xa_out = 0  ;
  buf.Ya_out = 0  ;
  buf.Za_out = 0  ;

  buf.Xg_out = 0  ;
  buf.Yg_out = 0  ;
  buf.Zg_out = 0  ;

  buf.temp_mpu = 0;// put your main code here, to run repeatedly:
*/
/*
  buf.temp = buf.temp+1 ;
  buf.p = buf.p +1 ;
  buf.t = buf.t+1 ;
  buf.m = buf.m+1 ;


  buf.Ratio_mq8 = buf.Ratio_mq8 + 1 ;
  buf.LPG_mq8 = buf.LPG_mq8 + 1 ;

  buf.Ratio_mq2 = buf.Ratio_mq2 + 1 ;
  buf.LPG_mq2 = buf.LPG_mq2 + 1 ;
  buf.Methane_mq2 = buf.Methane_mq2 + 1 ;
  buf.Smoke_mq2 = buf.Smoke_mq2 + 1 ;
  buf.Hydrogen_mq2 = buf.Hydrogen_mq2 + 1 ;

  buf.Ratio_mq135 = buf.Ratio_mq135 + 1 ;
  buf.CO2_mq135 = buf.CO2_mq135 + 1 ;


  buf.Xa_out = buf.Xa_out + 1 ;
  buf.Ya_out = buf.Ya_out + 1 ;
  buf.Za_out = buf.Za_out + 1 ;

  buf.Xg_out = buf.Xg_out + 1 ;
  buf.Yg_out = buf.Yg_out + 1 ;
  buf.Zg_out = buf.Zg_out + 1 ;

  buf.temp_mpu = buf.temp_mpu + 1 ;
*/
  //*
    buf.temp++;
    buf.p ++;
    buf.t ++;
    buf.m ++;


    buf.Ratio_mq8 ++;
    buf.LPG_mq8 ++;

    buf.Ratio_mq2 ++;
    buf.LPG_mq2 ++;
    buf.Methane_mq2 ++;
    buf.Smoke_mq2 ++;
    buf.Hydrogen_mq2 ++;

    buf.Ratio_mq135++;
    buf.CO2_mq135++;


    buf.Xa_out ++  ;
    buf.Ya_out ++  ;
    buf.Za_out ++  ;

    buf.Xg_out ++ ;
    buf.Yg_out ++  ;
    buf.Zg_out ++  ;

    buf.temp_mpu ++;//*/

Str buf;

  mySerial.write((byte*)&data, sizeof(1024));
  delay(2000);

  Serial.print(F("Temperature= "));
  Serial.print(buf.temp);
  Serial.print(" *C ");

  Serial.print(F("Pressure = "));
  Serial.print(buf.p);                    // вывод в сиреал
  Serial.print(" Pa ");

  Serial.print(F("Altitude= "));
  Serial.print(buf.m);
  Serial.print(" m ");

  Serial.print("__MQ8sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq8.getRo());

  Serial.print("Ratio: ");
  Serial.print(buf.Ratio_mq8);
  // выводим значения газов в ppm
  Serial.print(" LPG: ");
  Serial.print(buf.Ratio_mq8);
  Serial.print(" ppm(%/10000) ");

  Serial.print("__MQ2sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq2.getRo());

  Serial.print("Ratio: ");
  Serial.print(buf.Ratio_mq2);
  // выводим значения газов в ppm
  Serial.print(" LPG: ");
  Serial.print(buf.LPG_mq2);
  Serial.print(" ppm ");
  Serial.print("Methane: ");
  Serial.print(buf.Methane_mq2);
  Serial.print(" ppm ");
  Serial.print("Smoke: ");
  Serial.print(buf.Smoke_mq2);
  Serial.print(" ppm ");
  Serial.print("Hydrogen: ");
  Serial.print(buf.Hydrogen_mq2);
  Serial.print(" ppm ");

  Serial.print("__MQ135sensor: ");

  //Serial.print("Ro = ");
  //Serial.print(mq135.getRo());

  Serial.print("Ratio: ");
  Serial.print(buf.Ratio_mq135);
  // выводим значения газов в ppm
  //Serial.print("\tLPG: ");
  //Serial.print(mq135.readLPG());
  Serial.print(" CO2: ");
  Serial.print(buf.CO2_mq135);
  Serial.print(" ppm");
  /*
    Serial.print(" ADXL345_axel_XYZ: ");
    Serial.print(buf.X_out);
    Serial.print(" ");
    Serial.print(buf.X_out);     //ADXL345 axel
    Serial.print(" ");
    Serial.print(buf.X_out);*/

  Serial.print(" mpu_axel_XYZ: ");
  Serial.print(buf.Xa_out);
  Serial.print(" ");
  Serial.print(buf.Ya_out);    //mpu6050 axel
  Serial.print(" ");
  Serial.print(buf.Za_out);

  Serial.print(" mpu_giro_XYZ: ");
  Serial.print(buf.Xg_out);
  Serial.print(" ");
  Serial.print(buf.Yg_out);    //mpu6050 giro
  Serial.print(" ");
  Serial.print(buf.Zg_out);

  Serial.print(" mpu_temp: ");
  Serial.print(buf.temp_mpu);

  Serial.println();
}
