
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <NTPClient.h>
#include <WiFiUDP.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "bell-671a7.firebaseio.com"  
#define FIREBASE_AUTH "zR461TwhWJT8Y8cDtApePVRZfQ74z33OBLueH9rs"  
#define WIFI_SSID "Ranjith G K"  
#define WIFI_PASSWORD "naturalnaveen" 



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);



void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);  
  
  // connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting");  
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print(".");  
    delay(500);  
  }  
  Serial.println();  
  Serial.print("connected to : ");
  Serial.println( WIFI_SSID);
  //Serial.println(WiFi.localIP());  
    
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  

  timeClient.begin(); 

}

int n;
void loop() {
  String str1 = "konguEngineeringCollege/Normal/bellCount";
  n = Firebase.getInt(str1);
  Serial.print("Number of bell Timings : " );
  Serial.println(n);
  if(Firebase.failed())
  {
    Serial.println("Getting n failed");
    Serial.println(Firebase.error());
  
  }
 
 
  String str2 = "konguEngineeringCollege/Normal/timing/";

  for(int i=0;i<n;i++)
  {
    String str3 = str2 + i;
    Serial.println(str3);
    String str4 = Firebase.getString(str3);
    
   /* int db_time = str4.toInt();
    Serial.println(db_time);    */
    Serial.println(str4);
    Serial.println();
    delay(500);
  }
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();



    timeClient.update();
    int h = timeClient.getHours() + 5;
    int m = timeClient.getMinutes() + 30;

    if(m>=60)
    {
      h = h+1;
      m = m - 60;
    }
    Serial.println("Time after adding 5");

    Serial.print(h);
    Serial.println(m);


    
    String time_string = String(timeClient.getFormattedTime());
    Serial.println("Time before adding 5");
    Serial.println(time_string);
  // Serial.print(h,':' , m':'timeClient.getSeconds());
 /*   Serial.print(h);
    Serial.print(':');
    Serial.print(m);
    Serial.print(':');
    Serial.println(timeClient.getSeconds());   */

  


   // if(str4 == 
  
  delay(1000);
  // put your main code here, to run repeatedly:

}
