#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include<Wire.h>

const int rs = 3, en = 2, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//GSM Module initialisation
SoftwareSerial SIM900(1, 6); //TX RX

int low = A0;
int medium = A1;
int full = A2;
int motorOn = 7;
int motorStatus = 5;

void setup() {

SIM900.begin(9600);
Serial.begin(9600);
lcd.begin(16, 2);

pinMode(low, INPUT);
pinMode(medium, INPUT);  
pinMode(full, INPUT);
pinMode(motorOn,OUTPUT);
pinMode(motorStatus, OUTPUT);
}

void loop() {
lcd.setCursor(0, 0);
lcd.write("Water Management");

//Reading The input from the pins
int l = digitalRead(low);
int m = digitalRead(medium);
int f = digitalRead(full);
int mStatus = digitalRead(motorOn);
  
if(l == 1 && m == 1 && f == 1 ){
 
  digitalWrite(motorOn, LOW);
  lcd.setCursor(0,1);
  lcd.print("Tank is FULL  ");
  SIM900.print("AT+CMGF=1\r"); 
  SIM900.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("The tank is at Full Capacity");// recipient's mobile number
  Serial.println("The Motor is OFF");
  Serial.println("   ");
}

else if(l == 1 && m == 1 && f == 0 ){

  digitalWrite(motorOn, HIGH);
  lcd.setCursor(0,1);
  lcd.print("Tank is Medium");
  SIM900.print("AT+CMGF=1\r"); 
  SIM900.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("The tank is at Medium Capacity");// recipient's mobile number
  Serial.println("The Motor is ON");
  Serial.println("   ");
 
} 

else if( l == 1 && m == 0 && f == 0){
  
  digitalWrite(motorOn, HIGH);
  lcd.setCursor(0,1);
  lcd.print("Tank is LOW   ");

  SIM900.print("AT+CMGF=1\r"); 
  SIM900.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("AT + CMGS = \"+263784600988\"");// recipient's mobile number
  Serial.println("The tank is at Minimum Capacity");// recipient's mobile number
  Serial.println("The Motor is ON");
  Serial.println("   ");
}


} 
