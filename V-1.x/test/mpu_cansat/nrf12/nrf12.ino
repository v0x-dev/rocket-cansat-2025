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

  if (radio.available()) {
    timer1 = millis();
    timer2 = millis();

    radio.read( &data, sizeof(data) );

    Serial.print("Xa= ");
    Serial.print(data.aX_out);
    Serial.print("   Ya= ");
    Serial.print(data.aY_out);
    Serial.print("   Za= ");
    Serial.print(data.aZ_out);

    Serial.print(F(" Temperature= "));
    Serial.print(data.temp);
    Serial.print(" *C   ");

    Serial.print(F("Pressure= "));
    Serial.print(data.p);
    Serial.print(" Pa   ");

    Serial.print(F("Altitude= "));
    Serial.print(data.m);
    Serial.print(" m  ");

    Serial.print(F("Time= "));
    Serial.print(data.t);
    Serial.print(" m.seconds ");
    //Serial.println();

    Serial.print( data.aX_out_mpu );
    Serial.print( " " );
    Serial.print( data.aY_out_mpu );
    Serial.print( " " );
    Serial.print( data.aY_out_mpu );
    Serial.print( "    " );

    // Gyro
    Serial.print( data.gX_out_mpu );
    Serial.print( " " );
    Serial.print( data.gY_out_mpu );
    Serial.print( " " );
    Serial.print( data.gZ_out_mpu );
    Serial.print( "    " );

    // Temp
    Serial.print( data.temp_mpu );
    Serial.println();

    /* Serial.println(data.temp);
      Serial.println(data.p);
      Serial.println(data.t);
      Serial.println(data.m);*/
  }

}
