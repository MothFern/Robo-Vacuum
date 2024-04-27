#include "SR04.h"
#include <Servo.h>
Servo myservo;

int pos = 0;

#define TRIG_PIN 4
#define ECHO_PIN 5
#define TRIG_PIN2 7
#define ECHO_PIN2 6

SR04 sensor_one= SR04(ECHO_PIN, TRIG_PIN);
SR04 sensor_two= SR04(ECHO_PIN2, TRIG_PIN2);
int current_distance = 0;
long a;
long b;

int greatest_distance = 0;
int go_angle = 0;
int previous_distance = 0;


void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  greatest_distance = 0;
  go_angle = 0;
  previous_distance = 0;
  for(pos = 0;pos <= 180; pos+=2){
    myservo.write(pos);
    delay(15);
    a = sensor_one.Distance();
    b = sensor_two.Distance();
    if(a > greatest_distance){
      greatest_distance = a;
      go_angle = pos;
    }else{
      previous_distance = a;
    }
    if(b > greatest_distance){
      greatest_distance = b;
      go_angle = pos;
    }else{
      previous_distance = b;
    }
    }
  for(pos = 180; pos>=0; pos-=2){
    myservo.write(pos);
    delay(15);
    a = sensor_one.Distance();
    b = sensor_two.Distance();
    if(a > greatest_distance){
      greatest_distance = a;
      go_angle = pos;
    }else{
      previous_distance = a;
    }
    if(b > greatest_distance){
      greatest_distance = b;
      go_angle = pos;
    }else{
      previous_distance = b;
    }
  }
  Serial.println("The go_angle is: ");
  Serial.print(go_angle);
  Serial.print(",");
  Serial.println(greatest_distance);
}
