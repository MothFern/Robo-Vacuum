#include <Servo.h>
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

const int ena1 = 9;
const int drive1A = 4;
const int drive2A = 3;
const int buttonPin = 5;
int currentState;
bool toggle = 0;

Servo myservo;
Servo myservo2;

int pos = 0;
int pos2 = 0;
int buttonState = 0;
int spin_speed = 0;

//bool is_running = false; // motor is off to start
bool In1State = LOW; // Direction pin 1 is LOW (off) to start
bool In2State = LOW; // Direction pin 2 is LOW (off) to start


void setup() {

  Serial.begin(9600);
  myservo.attach(8);
  myservo2.attach(7);

  pinMode(ena1,OUTPUT);
  pinMode(drive1A,OUTPUT);
  pinMode(drive2A,OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  currentState = digitalRead(buttonPin);
  a = sr04.Distance();
  Serial.print(a);
  Serial.println("cm");

  if(currentState == LOW){
    toggle = !toggle;
    delay(300);
  }
  if(toggle == 0 && a>7){
    Serial.println(a);
    In1State = HIGH; In2State = LOW; spin_speed = 255;
    digitalWrite(drive1A, In1State);  
    digitalWrite(drive2A,In2State); 
    analogWrite(ena1,spin_speed);

    for(pos = 0; pos <=180; pos += 1){
      myservo.write(pos);
      myservo2.write(pos);
      delay(20);
    }
    for(pos = 180; pos >=0; pos-=1 ){
      myservo.write(pos);
      myservo2.write(pos);
      delay(20);
    }

  }else{
    digitalWrite(drive1A, LOW);  
    digitalWrite(drive2A,LOW); 
    analogWrite(ena1,0);
  }
}

