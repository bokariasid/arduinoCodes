#include <GSM.h>
#include <WideTextFinder.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include <LiquidCrystal.h>
SMSGSM sms;
LiquidCrystal lcd(12, 11, 5, 4, 10, 13);
#define trigPin 9
#define echoPin 8
#define led 6
#define led2 7
boolean started;
char phone[]="+919600425075";
char message[180];
char pos;
char *p;
void setup() {
  lcd.begin(16, 2);    
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  lcd.print("Distance:");
}

void loop() {
  lcd.setCursor(0, 1);
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Stop:");
    lcd.setCursor(0, 1);
    //lcd.print(distance);
    delay(1000);
    lcd.clear();
    sendOTP(phone);
    
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    delay(1000);
    lcd.clear();
  }
    //Serial.print(distance);
 
}

void sendOTP(char phone[13])
{

  Serial.println("GSM Testing to send SMS");
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true; 
  }
  else Serial.println("\nstatus=IDLE");
 
  if(started){
    char *text;
    text="Water Filled Upto Threshold";
    if (sms.SendSMS(phone, text))// number to which you want to send the sms and the sms text//
    Serial.println("\nSMS sent OK");
   
  }
}
void receiveOTP(char number[13])
{
pos=sms.IsSMSPresent(SMS_UNREAD);
 
 Serial.println((int)pos);
 
 if((int)pos>0&&(int)pos<=20){
 
   Serial.print("NEW MESSAGE, POS=");
 
   Serial.println((int)pos);
 
   message[0]='\0';
 
   sms.GetSMS((int)pos,number,message,180);
   Serial.println(message);
   if
   //char *final = encipher(message,key,0);
   //Serial.println(final);
   //p=strstr(final,"PASSWORD");
 
   if(){
 
     Serial.println("PSWD OK");
    digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);               // wait for a second
    digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
    
   }
   else
    {Serial.println("Unauthorised Access At Phone!!");
    Serial.println("lighting LED2");
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);               // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    }
   sms.DeleteSMS((int)pos);
 }
 
}delay(5000);
 
}

