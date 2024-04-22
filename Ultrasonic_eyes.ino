#include "SR04.h"
#include <Servo.h>
Servo myservo;

int pos = 0;

#define TRIG_PIN 12
#define ECHO_PIN 11
#define TRIG_PIN2 7
#define ECHO_PIN2 6

SR04 sensor_one= SR04(ECHO_PIN, TRIG_PIN);
SR04 sensor_two= SR04(ECHO_PIN2, TRIG_PIN2);
int current_distance = 0;
long a;
long b;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  for(pos = 0;pos <= 180; pos+=1){
    myservo.write(pos);
    delay(20);
    a = sensor_one.Distance();
    b = sensor_two.Distance();
    if(a < 7.62){
      current_distance = a;
      Serial.println("Ahh I hit a wall!");
    }else if(b< 7.62){
      if(current_distance > b){
        current_distance = b;
        Serial.println("Ahh I hit a wall!");
      }
    }else{
      Serial.println("Kuska I will find you! ");
    }
  }
  for(pos = 180; pos >=0; pos-=1){
    myservo.write(pos);
    delay(20);
    a = sensor_one.Distance();
    b = sensor_two.Distance();
    if(a < 7.62){
      current_distance = a;
      Serial.println("Ahh I hit a wall!");
    }else if(b< 7.62){
      if(current_distance > b){
        current_distance = b;
        Serial.println("Ahh I hit a wall!");
      }
    }else{
      Serial.println("Kuska I will find you! ");
    }
  }
}
