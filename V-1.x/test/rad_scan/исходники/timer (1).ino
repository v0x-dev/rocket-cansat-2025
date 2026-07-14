#include <iarduino_RTC.h>  

iarduino_RTC time(RTC_DS1307);  

int relay1 = 3;
int relay2 = 4;

String rt = "50";
String TimeON = "06";
String TimeOFF = "09";

String TimeON1 = "18";
String TimeOFF1 = "22";

void setup() {
  digitalWrite(relay2,HIGH);
  digitalWrite(relay1,HIGH);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
    delay(300);                                             
    Serial.begin(9600);                                     
    time.begin();
}

void loop() {


    if(millis()%1000==0){                                  
    Serial.println(rt);      // Выводим время.
    delay(1);                                             
  } 
  rt = time.gettime("H");
  if (rt == TimeON)
{
  digitalWrite(relay1, LOW);
}
  if (rt == TimeOFF)
{
  digitalWrite(relay1, HIGH);
  delay(2000);
}
 
  if (rt == TimeON1)
{
  digitalWrite(relay1, LOW);
}
  if (rt == TimeOFF1)
{
  digitalWrite(relay1, HIGH);
  delay(2000);
}
 
}
