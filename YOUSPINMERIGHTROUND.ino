#include "SR04.h"
#include <Servo.h>

Servo servo1;  // BLUE
Servo servo2;  // GREEN
Servo servo3;  // ORANG
Servo scanServo;
// twelve servo objects can be created on most boards

int globalPos = 0;
int driveTime = 0;

int startpos1 = 80;    
int startpos2 = 100;
int startpos3 = 20;

int pos1 = 0;    
int pos2 = 0;
int pos3 = 0;

int motor1dir = 1;
int motor2dir = 1;
int motor3dir = 1;

int serv1 = 11;
int serv2 = 9;
int serv3 = 10;

int ena1 = 3;
int ena2 = 4;
int ena3 = 2;
int drive1a = 50;
int drive1b = 51;
int drive2a = 48;
int drive2b = 49;
int drive3a = 53;
int drive3b = 52;

int trigPin1 = 40;
int echoPin1 = 6;
int trigPin2 = 41;
int echoPin2 = 7;

int scanServ = 12;

unsigned long a = 0;
unsigned long b = 0;

int goAngle = 0;
unsigned long leastDist;

SR04 sensor1= SR04(echoPin1, trigPin1);
SR04 sensor2= SR04(echoPin2, trigPin2);

void setup() {
  servo1.attach(serv1);  // attaches the servo on pin 9 to the servo object
  servo2.attach(serv2);
  servo3.attach(serv3);
  scanServo.attach(scanServ);

  Serial.begin(9600);

  pinMode(ena1, OUTPUT);
  pinMode(ena2, OUTPUT);
  pinMode(ena3, OUTPUT);
  pinMode(drive1a, OUTPUT);
  pinMode(drive1b, OUTPUT);
  pinMode(drive2a, OUTPUT);
  pinMode(drive2b, OUTPUT);
  pinMode(drive3a, OUTPUT);
  pinMode(drive3b, OUTPUT);

  servo1.write(startpos1);
  servo2.write(startpos2);
  servo3.write(startpos3);
}

void drive(int globalPos, int driveTime) {
    Serial.print(globalPos);
    Serial.print(" ");
    
    pos1 = (startpos1 + globalPos) % 180;
    Serial.print(pos1);
    Serial.print(" ");
    pos2 = (startpos2 + globalPos) % 180;
    Serial.print(pos2);
    Serial.print(" ");
    pos3 = (startpos3 + globalPos) % 180;
    Serial.print(pos3);
    Serial.print(" ");

    if ((startpos1 + globalPos) % 360 < 180) {
      digitalWrite(drive1a, HIGH);
      digitalWrite(drive1b, LOW);
      analogWrite(ena1, 255);
      Serial.print(" 1Forwards");
    } else if ((startpos1 + globalPos) % 360 > 180) {
      digitalWrite(drive1a, LOW);
      digitalWrite(drive1b, HIGH);
      analogWrite(ena1, 255);
      Serial.print(" 1Backwards");
    }

    if ((startpos2 + globalPos) % 360 < 180) {
      digitalWrite(drive2a, HIGH);
      digitalWrite(drive2b, LOW);
      analogWrite(ena2, 255);
      Serial.print(" 2Forwards");
    } else if ((startpos2 + globalPos) % 360 > 180) {
      digitalWrite(drive2a, LOW);
      digitalWrite(drive2b, HIGH);
      analogWrite(ena2, 255);
      Serial.print(" 2Backwards");
    }

    if ((startpos3 + globalPos) % 360 < 180) {
      digitalWrite(drive3a, HIGH);
      digitalWrite(drive3b, LOW);
      analogWrite(ena3, 255);
      Serial.print(" 3Forwards");
    } else if ((startpos3 + globalPos) % 360 > 180) {
      digitalWrite(drive3a, LOW);
      digitalWrite(drive3b, HIGH);
      analogWrite(ena3, 255);
      Serial.print(" 3Backwards");
    }
    
    servo1.write(pos1);              
    delay(20);                      
    servo2.write(pos2);             
    delay(20);
    servo3.write(pos3);             
    delay(20);

    Serial.println(" end");

    delay(driveTime);

    digitalWrite(drive1a, LOW);
    digitalWrite(drive1b, LOW);
    analogWrite(ena1, 255);
    digitalWrite(drive2a, LOW);
    digitalWrite(drive2b, LOW);
    analogWrite(ena2, 255);
    digitalWrite(drive3a, LOW);
    digitalWrite(drive3b, LOW);
    analogWrite(ena3, 255);
}

int findAngle() {
  leastDist = 1000;  
  int pos = 0;

  scanServo.write(180);
  delay(50);

  for(int i = 180;i >= 0; i-=2){
    pos = pos + 1;
    scanServo.write(i);
    delay(15);
    a = sensor1.Distance();
    b = sensor2.Distance();

    Serial.print(a);
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" ");
    Serial.println(goAngle);

    if(a < leastDist){
      leastDist = a;
      goAngle = pos;
    }
    if(b < leastDist){
      leastDist = b;
      goAngle = pos + 180;
    }
  }

  scanServo.write(0);
  return goAngle;
}

void spinMeRightRoundBabyRightRoundLikeARecordBabyRightRoundRoundRound(int spinTime, int spinDir) {
  servo1.write(110);
  servo2.write(10);
  servo3.write(0);

  if (spinDir == 1) {
    digitalWrite(drive1a, HIGH);
    digitalWrite(drive1b, LOW);
    analogWrite(ena1, 255);
    digitalWrite(drive2a, HIGH);
    digitalWrite(drive2b, LOW);
    analogWrite(ena2, 255);
    digitalWrite(drive3a, LOW);
    digitalWrite(drive3b, HIGH);
    analogWrite(ena3, 255);
  } else if (spinDir == -1) {
    digitalWrite(drive1a, LOW);
    digitalWrite(drive1b, HIGH);
    analogWrite(ena1, 255);
    digitalWrite(drive2a, LOW);
    digitalWrite(drive2b, HIGH);
    analogWrite(ena2, 255);
    digitalWrite(drive3a, HIGH);
    digitalWrite(drive3b, LOW);
    analogWrite(ena3, 255);
  }

    delay(spinTime);

    digitalWrite(drive1a, LOW);
    digitalWrite(drive1b, LOW);
    analogWrite(ena1, 255);
    digitalWrite(drive2a, LOW);
    digitalWrite(drive2b, LOW);
    analogWrite(ena2, 255);
    digitalWrite(drive3a, LOW);
    digitalWrite(drive3b, LOW);
    analogWrite(ena3, 255);
}
void loop() {
  globalPos = findAngle();
  Serial.println(globalPos);

  drive(globalPos, 1000);
  delay(5000);

  // drive(0, 1000);
  // delay(1000);
  // drive(90, 1000);
  // delay(1000);
  // drive(180, 1000);
  // delay(1000);
  // drive(270, 1000);
  // delay(1000);

  // spinMeRightRoundBabyRightRoundLikeARecordBabyRightRoundRoundRound(1000, 1);
  // delay(1000);
  // spinMeRightRoundBabyRightRoundLikeARecordBabyRightRoundRoundRound(1000, -1);
  // delay(1000);


}


