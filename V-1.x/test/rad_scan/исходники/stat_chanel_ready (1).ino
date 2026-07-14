#include <YoutubeApi.h>

/*******************************************************************
 *  An example of bot that echos back any messages received        *
 *                                                                 *
 *  written by Giacarlo Bacchio (Gianbacchio on Github)            *
 *  adapted by Brian Lough                                         *
 *******************************************************************/


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


//------------LED------------//
#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   D1 to DIN,
   D3 to CS,
   D2 to CLK */
   
DigitLedDisplay ld = DigitLedDisplay(5, 0, 4);



//------- Replace the following! ------
char ssid[] = "YOUR_WIFI_SSID"; // your network SSID (name)
char password[] = "YOUR_WIFI_PASSWORD";  // your network key
#define API_KEY "YOUR_YOUTUBE_API_KEY"  // your google apps API Token
#define CHANNEL_ID "--------------" // makes up the url of channel 



//------------LED------------//

/////////////////////////////////






WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

int api_mtbs = 60000; //mean time between api requests
long api_lasttime;   //last time api request has been done

long subs = 0;

void setup() {

  Serial.begin(9600);

//------------LED------------//

  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);



  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


}

void loop() {


  ld.printDigit(api.channelStats.subscriberCount);
  delay(500);



  if (millis() > api_lasttime + api_mtbs)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      Serial.println("---------Stats---------");
      Serial.print("Subscriber Count: ");
      Serial.println(api.channelStats.subscriberCount);
      Serial.print("View Count: ");
      Serial.println(api.channelStats.viewCount);
      Serial.print("Comment Count: ");
      Serial.println(api.channelStats.commentCount);
      Serial.print("Video Count: ");
      Serial.println(api.channelStats.videoCount);
      // Probably not needed :)
      //Serial.print("hiddenSubscriberCount: ");
      //Serial.println(api.channelStats.hiddenSubscriberCount);
      Serial.println("------------------------");

    }
    api_lasttime = millis();
  }




  ld.clear();

 
  
}
