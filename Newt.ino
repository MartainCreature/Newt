//Newt
//
//云台驱动程序
//范子睿
//版本 2.1.0

#include <Servo.h>
Servo servoT;
Servo servoP;

#define L 9

byte input;

int dirT;
int dirP;

int t;
int p;

const int tO = 60;
const int pO = 90;
const int tMax = tO + 80;
const int tMin = tO - 10;
const int pMax = pO + 60;
const int pMin = pO - 60;

void setup() {
  servoT.attach(10);
  servoP.attach(11);

  pinMode(L,OUTPUT);

  Serial.begin(9600);
 
  servoT.write(t);
  servoP.write(p);  
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();

    if (input == 5) {
      t = tO;
      p = pO;
    }
    else if (input == 9) {
      digitalWrite(L, HIGH);
    }
    else {
      dirT = input % 10;
      dirP = input / 10;

      t += dirT - 2;
      p += dirP - 2;

      t = constrain(t, tMin, tMax);
      p = constrain(p, pMin, pMax);

      digitalWrite(L, LOW);
    }

    servoT.write(t);
    servoP.write(p);
  }
  
  delay(10);
}
