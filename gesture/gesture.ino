#include <Servo.h>
const int servoPin=11;
const int trigPin1=7;
const int trigPin2=10;
const int trigPin3=11;
const int led = 3;
//echo pins
const int echoPin1=6;
const int echoPin2=9;
const int echoPin3=12;
//const int tloop=5;
const int forward=4;
const int backward=5;
Servo Servo1;
int tnum = 0;
int sway[2];
int i = 0;
int ind = 1;
int ind1 = 4;
int bright[4] = {0,50,150,255};
int angle[9]={0,20,40,60,90,120,140,160,180};
int choice;
void setup() {
  pinMode(forward,OUTPUT);
  pinMode(backward,OUTPUT);
  Serial.begin(9600);
  pinMode(1,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(1,LOW);
  Servo1.attach(servoPin);
  Servo1.write(0);
  choice=0;
  delay(1000);
}

void loop()

{ 
  
  //initializing the variales------------------------------------------------
  
  long duration1, inches1, cm1;
  long duration2,inches2, cm2;
  long duration3,inches3, cm3;
  
  //taking the reading from ultrasonic one-----------------------------------
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);
  
  //condition (if the hand is close enough)----------------------------------
  
  if (inches1<3&&(sway[1]!=1)&&sway[0]!=1)
  {
    sway[i]=1;
    tnum=0;
    i=1;
  }
  delay(100);
  
  //taking the input from ultrasonic two -------------------------------------
  
  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);
  
  //conditions----------------------------------------------------------------
    
  if (inches2<3&&(sway[0]!=2)&&(sway[1]!=2))
  { 
    sway[i]=2;
    tnum=0;
    i=1;
  }
  delay(100);

  //taking the input from ultrasonic three ----------------------------------
  
  pinMode(trigPin3, OUTPUT);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  pinMode(echoPin3, INPUT);
  duration3 = pulseIn(echoPin3, HIGH);
  inches3 = microsecondsToInches(duration3);
  cm3 = microsecondsToCentimeters(duration3);
  
  //conditions----------------------------------------------------------------
    
  if (inches3<3)
  { 
    choice=choice+1;
    choice=choice%2;
  }
  delay(100);
  

  //checking both the states of ultrasonics to take a descision-----------------
  
    if (sway[0]==1&&sway[1]==2&&choice==0)
      {
        if (ind<3)
          ind++;
        tnum=tloop+1;
      }
    if (sway[0]==2&&sway[1]==1&&choice==0)
    {
      if(ind>0)
        ind--;
      tnum=tloop+1;
    }
     
    analogWrite(3,bright[ind]);

    
    if (sway[0]==1&&sway[1]==2&&choice==1)
      {
        if (ind1<7)
          ind1++;
        tnum=tloop+1;
      }
    if (sway[0]==2&&sway[1]==1&&choice==1)
    {
      if(ind1>0)
        ind1--;
      tnum=tloop+1;
    }

    Servo1.write(angle[ind1]);
     
    
    //trigger memory-----------------------------------------------------------
    
      if (tnum>tloop)
    {
      sway[1]=0;
      sway[0]=0;
      tnum=0;
      i=0;
    }
    tnum++;
      //output stuff---------------------------------------------------------------
  
    Serial.println("tnum");
    Serial.println(tnum);
    Serial.print("choice");
    Serial.println(choice);
    Serial.print(sway[0]);
    Serial.print(" ");
    Serial.print(sway[1]);
    Serial.println(" ");
    Serial.print("brightness : ");
    Serial.println(bright[ind]);
    Serial.println(angle[ind1]);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
 return microseconds / 29 / 2;
}
