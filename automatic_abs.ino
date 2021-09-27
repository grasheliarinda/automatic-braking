//Timer
#include <timer.h>
#include <timerManager.h>
#include "timer.h"
Timer a; //maju
Timer b;
Timer c;
float interval = 0.2 ;// detik
unsigned long maju= 0 ; 
unsigned long waktumaju= 7 ;//detik 

//ABS
#include <Servo.h>
#include <Wire.h>
Servo m1;

int rem = 60;       ////////////ganti///////////  
int jalan = 107;     ////////////ganti///////////  
int remminus = 6;
 
//Ultrasonic
#define trigPin 3
#define echoPin 4
long duration;
float distance;
float jarak;


//RPM Sensor
float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;


void setup() { 
  Serial.begin(9600);
   
  // Ultrasonic
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
        

   //ABS
    m1.attach(8); 
    a.setInterval(300);
    a.setCallback(bacaRPM);
  
    b.setInterval(10);
    b.setCallback(Brake);
  
    a.start();
    b.start();
    

}

void INTERRUPT()
{
  REV++;
}

void bacaRPM(){               
  TIME = millis() - PREVIOUS;          
  RPM_VALUE = (REV/TIME) * 60000;       
  PREVIOUS = millis();                  
  REV = 0;
  attachInterrupt(0, INTERRUPT, RISING);
}

void loop() {
  
//MAJU
  if (distance >=200) {
    rem=60;               ////gantiii
    m1.write(jalan);   
    Serial.print ("JALAN ") ;
    Serial.print(jalan); 
    }

//ABS    
  else if (distance <=200) {
    Serial.print ("STOP ") ;
    if (rem >=0) {
    b.update() ;
    }
  }
  
  a.update();
  //ULTRASONIC
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration*0.034/2 +1;
  distance = jarak + (0.76/100 *jarak); ///Jarak telah dikalibrasi
  
  Serial.print(" Jarak:  ");
  Serial.print(distance,1);
  Serial.print(" cm");
  String RPM = String(" RPM: ") + RPM_VALUE;
  Serial.println(RPM);
  delay(100);
  
} 

void Brake() {
    m1.write(rem);
    Serial.print(rem);
    rem = rem - remminus;
}
