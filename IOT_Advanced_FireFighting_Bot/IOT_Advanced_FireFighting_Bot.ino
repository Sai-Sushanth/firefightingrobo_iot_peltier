#define BLYNK_TEMPLATE_ID "TMPLxUfMVhxo"
#define BLYNK_DEVICE_NAME "Fire fighting robot"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXX"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define s1 D0 //  servo motor 1
//#define s2 2 // servo motor 2
#define IN1 D3
#define IN2 D4
#define IN3 D5
#define IN4 D6
#define motor D7
#define trig D8 
#define echo D9
#define sw D2
   
bool motorval =0;//PORAA PUKAAAAAAAAAAA
bool pumpval =0;
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
char auth[] = "eFS1MuPfTWmSNCa0Xn8_wTRrDtVHO3TT"; //Enter your Blynk application auth token
char ssid[] = "Airtel"; //Enter your WIFI name
char pass[] = "fullmoon"; //Enter your WIFI passowrd
int temp;
Servo servo1;// obj 1
//Servo servo2;// obj2 not used 
void setup()
{
  servo1.attach(s1);
 // servo2.attach(s2);
//  lcd.begin();
//  lcd.print("CMREC");
//  Blynk.virtualWrite(V5,"CMREC");
//  lcd.setCursor(0,1);
//  lcd.print("BATCH-C15");
//  delay(2000);
//  lcd.clear();
//  lcd.print("FIRE FIGHTING");
//  Blynk.virtualWrite(V5,"FIRE FIGHTING");
//  lcd.setCursor(0,1);
//  delay(2000);
//  lcd.clear();
//  delay(1000);
//  lcd.clear();    
//  lcd.print("SYSTEM READY....");
//  Blynk.virtualWrite(V5,"SYSTEM READY....");
//  delay(1000);
  pinMode(IN1, OUTPUT);
  digitalWrite(IN1,LOW);
  delay(100);
  pinMode(IN2,OUTPUT);
  digitalWrite(IN2,LOW);
  delay(100);
  pinMode(IN3,OUTPUT);
  digitalWrite(IN3,LOW);
  delay(100);
  pinMode(IN4,OUTPUT);
  digitalWrite(IN4,LOW);
  delay(100);
  pinMode(motor,OUTPUT);
  digitalWrite(motor,LOW);
  delay(100);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V0) 
{
  forward = param.asInt();
}
BLYNK_WRITE(V1) 
{
  backward = param.asInt();
}
BLYNK_WRITE(V2) 
{
  left = param.asInt();
}
BLYNK_WRITE(V3) 
{
  right = param.asInt();
}
BLYNK_WRITE(V8)
{
  motorval = (param.asInt()); 
}

void smartcar() 
{
  if (forward == 1) 
  {
    carforward();
    Serial.println("carforward");
  } 
  else if (backward == 1) 
  {
    carbackward();
    Serial.println("carbackward");
  } 
  else if (left == 1) 
  {
    carturnleft();
    Serial.println("carfleft");
  } 
  else if (right == 1) 
  {
    carturnright();
    Serial.println("carright");
  } 
  else if (forward == 0 && backward == 0 && left == 0 && right == 0) 
  {
    carStop();
    Serial.println("carstop"); 
  }
}




void loop() 
{
  Blynk.run();
  if(sw==0){
  smartcar();
  }
  else if(sw==1)
  {
    automatic();
    }
}
void automatic()
{
   digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


 int duration = pulseIn(echo , HIGH);
  int distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  

  if ( distance < 20 )
  {
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , LOW);
    delay(100);
  }
  else
  {
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , LOW);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , LOW);
  }
 
}

void carforward() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carbackward() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnleft() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
