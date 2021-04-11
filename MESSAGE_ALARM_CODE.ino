#include <SoftwareSerial.h>
SoftwareSerial SIM900(2, 3);
String textForSMS;

int gyroscopsensor = 10;
int buzzer = 9;
int red = 7;
int green = 8;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600); 
  pinMode(gyroscopesensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);

  delay(100);

}

void loop() {


  if ( digitalRead(gyroscopesensor) == HIGH) //
  {
    textForSMS =  "\I might need help. Reach quickly.";

    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(8000);
  }
  if ( digitalRead(gyroscopesensor) == LOW) //
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    delay(1000);
  }

}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
  SIM900.println("AT + CMGS = \"+91(remaining 10 digits)\"");  // recipient's mobile number, in international format

  delay(1000);
  SIM900.println(message);                         // message to send

  SIM900.println((char)26);                   
  delay(1000);
  SIM900.println();
}


