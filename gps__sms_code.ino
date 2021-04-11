#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float lattitude,longitude; // create variable for latitude and longitude object 
float a[2];//array to store gps data;
float *p;//pointer to point the array location
SoftwareSerial gpsSerial(8,9);//connect tx pin of gps to arduino digital pin 10 and connect rx pin of gps to arduino digital pin 11
SoftwareSerial gsmSerial(6,7);////connect tx pin of gsm to arduino digital pin 8 and connect rx pin of gps to arduino digital pin 9
TinyGPSPlus gps;// create gps object
void setup(){
lcd.begin(16,2);
delay(1000);
Serial.begin(9600); // connect serial
delay(1000);
gpsSerial.begin(9600); // connect gps sensor
delay(1000);
gsmSerial.begin(9600); // connect gsm sensor
delay(1000);// delay is required here in most of the cases for stability of program
lcd.clear();
lcd.print("Vehicle Tracking");
lcd.setCursor(0,1);
lcd.print("    System      ");
gsmSerial.println("AT+CNMI=2,2,0,0,0");// AT Command to receive a live SMS
Serial.println("AT+CNMI=2,2,0,0,0");
delay(3000);// delay is required here in most of the cases for stability of program
lcd.clear();
lcd.print("Initializing...");
delay(3000);
lcd.clear();
lcd.print("System Ready");
delay(1000);
}
/*---------------------------------------------------------------------------------------*/ 
void loop(){
  while(gsmSerial.available()){
   gsmSerial.read();
}
  while(Serial.available()){
   Serial.read();
}
 get_gsm(); 
}


float *get_gps()
{
   gpsSerial.listen();
   //Serial.println("INSIDE get_gps");
   while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
      break;
      }
  
   
  
}
a[0]=lattitude;
a[1]=longitude;
return a;
}
/*---------------------------------------------------------------------------------------*/
void get_gsm()
{
  
   gsmSerial.listen();
   
  
   
   while(gsmSerial.available()>0)
   {Serial.println("INSIDE gsmSerial.available");
  
    if(gsmSerial.find("Track"))
    {Serial.println("INSIDE track");
     gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     gsmSerial.println("AT+CMGS=\"+917896369815\"\r"); // Replace x with mobile number
     delay(1000);
     p=get_gps();
     gsmSerial.listen();
     Serial.print("Your Car Location: ");
     gsmSerial.print("Your Car Location: ");
     Serial.print("LATTITUDE="); Serial.print(*p,6);
     gsmSerial.print("LATTITUDE=");gsmSerial.print(*p,6);gsmSerial.print(",");// The SMS text you want to send
     Serial.print("LONGITUDE="); Serial.print(*(p+1),6);
     gsmSerial.print("LONGITUDE=");gsmSerial.print(*(p+1),6);// The SMS text you want to send
     delay(100);
     gsmSerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
     delay(1000);
     lcd.clear();
     lcd.clear();
     lcd.print("Lat:");
     lcd.print(*p,6);
     lcd.setCursor(0,1);
     lcd.print("Long:");
     lcd.print(*(p+1),6);
     delay(3000);
     lcd.clear();
     lcd.print("Message Sent");
     delay(2000);
     lcd.clear();
     lcd.print("System Ready");
     delay(1000);
    }
   
   }
}
