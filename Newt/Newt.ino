//Newt
//
//云台驱动程序
//范子睿
//版本 3.0.4

#include <Servo.h>
Servo servoT;
Servo servoP;

#define L 9

byte input;

int t;
int p;

const int t0 = 60;
const int p0 = 90;
const int tR = 100;
const int pR = 140;
const int tMax = t0 + 90;
const int tMin = tMax - tR;
const int pMax = p0 + 60;
const int pMin = pMax - pR;

void setup() {
  servoT.attach(10);
  servoP.attach(11);

  pinMode(L,OUTPUT);

  Serial.begin(9600);
 
  servoT.write(t0);
  servoP.write(p0);  
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();

    if (input == 5) {
      t = t0;
      p = p0;
    }
    else if (input == 9) {
      digitalWrite(L, HIGH);
    }
    else {
      if (input >= 100) {
        input -= 100;
       
        if (input / 10 == 2) {
          t += input % 10 - 1;
        }
        else {
          p += input % 10 - 1;
        }

        t = constrain(t, tMin, tMax);
        p = constrain(p, pMin, pMax);

        digitalWrite(L, LOW);
      }
      else {
        t = tMin + tR * (input % 10) / 10;
        p = pMin + pR * (input / 10) / 10;
        
        digitalWrite(L, HIGH);
      }
    }

    servoT.write(t);
    servoP.write(p);
  }
  
  delay(10);
}
