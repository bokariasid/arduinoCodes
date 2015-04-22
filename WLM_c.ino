
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 10, 13);
#define trigPin 9
#define echoPin 8
#define led 6
#define led2 7

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
