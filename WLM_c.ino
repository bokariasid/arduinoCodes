#include <GSM.h>
#include <WideTextFinder.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include <LiquidCrystal.h>
SMSGSM sms;
//2 is receive pin of arduino for the gsm module
//3 is transfer pin of arduino for the gsm module
LiquidCrystal lcd(12, 11, 5, 4, 10, 13);
#define trigPin 9
#define echoPin 8
#define led 6
#define led2 7
boolean started;
char phone[]="+919600425075";
char *message;
char pos;
char *p;
void setup() {
  lcd.begin(16, 2);    
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);  
}

void loop(){
  message = receiveOTP(phone);  
    if(compare(message,"OFF")){
      long t = 1000*60*5;
      suspendSystem(t);   
    }
    else if(compare(message,"ON")){
      startSystem();
    }
    else if(compare(message,"Stop")){
      stopSystem();
    }
    else if(compare(message,"WATER LEVEL")){
      //indicateWaterLevel();     
    }
    else{
      startSystem();
    }
}

void sendOTP(char phone[13],char *text)
{

  Serial.println("GSM Testing to send SMS");
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true; 
  }
  else Serial.println("\nstatus=IDLE");
 
  if(started){       
    if (sms.SendSMS(phone, text))// number to which you want to send the sms and the sms text//
    Serial.println("\nSMS sent OK");
   
  }
}
char  *receiveOTP(char number[13])
{
  char *m;
pos=sms.IsSMSPresent(SMS_UNREAD);
 
 Serial.println((int)pos);
 
 if((int)pos>0&&(int)pos<=20){
 
   Serial.print("NEW MESSAGE, POS=");
 
   Serial.println((int)pos);
 
   m[0]='\0';
 
   sms.GetSMS((int)pos,number,m,180);
   Serial.println(m);
 }
 return m;
}
void suspendSystem(long t){   
  delay(t);
}
boolean compare(char *mainStr, char *compStr){
  int i=0;
  while(mainStr){
    if(mainStr[i] != compStr[i])
    {
      return false;
    }
  }
  return true;
}

void startSystem(){
  lcd.setCursor(0, 1);
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
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
    delay(1000);
    lcd.clear();
    char *u = "Tank Filled";
    sendOTP(phone,u);
    long t = 1000*60*2;
    suspendSystem(t);
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
}

void stopSystem(){
      digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
      digitalWrite(led2,LOW);
      lcd.print("Stop:");
}

void indicateWaterLevel(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  char *dist;
  itoa(distance,dist,10);
  sendOTP(phone,dist);
}
