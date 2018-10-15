#include <math.h>
#include <Servo.h>
Servo servoMotor1;
Servo servoMotor2;
Servo servoPinzas;

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  servoMotor1.attach(13);
  servoMotor2.attach(12);
  servoPinzas.attach(11);
}
int xVal = 0;
int yVal = 0;
int zVal = 0;
int xVal2 = 0;
int yVal2 = 0;
int zVal2 = 0;
int xVal3 = 0;
int yVal3 = 0;
int zVal3 = 0;
double angleYZ = 0;
double angleXZ = 0;
double angleYZ2 = 0;
double angleXZ2 = 0;
double angleYZ3 = 0;
double angleXZ3 = 0;

float grado = 0;


 void loop() {
  xVal = analogRead(0);
  yVal = analogRead(1);
  zVal = analogRead(2);
  xVal2 = analogRead(3);
  yVal2 = analogRead(4);
  zVal2 = analogRead(5);
  xVal3 = analogRead(6);
  yVal3 = analogRead(7);
  zVal3 = analogRead(8);
  
  xVal = map(xVal, 0, 1023, -500, 500);
  yVal = map(yVal, 0, 1023, -500, 500);
  zVal = map(zVal, 0, 1023, -500, 500);
  xVal2 = map(xVal2, 0, 1023, -500, 500);
  yVal2 = map(yVal2, 0, 1023, -500, 500);
  zVal2 = map(zVal2, 0, 1023, -500, 500);
  xVal3 = map(xVal3, 0, 1023, -500, 500);
  yVal3 = map(yVal3, 0, 1023, -500, 500);
  zVal3 = map(zVal3, 0, 1023, -500, 500);
  
  angleYZ = atan((double)yVal / (double)zVal);
  angleYZ = angleYZ*(57.2958);
  angleXZ = atan((double)xVal / (double)zVal);
  angleXZ = angleXZ*(57.2958);

  angleYZ2 = atan((double)yVal2 / (double)zVal2);
  angleYZ2 = angleYZ2*(57.2958);
  angleXZ2 = atan((double)xVal2 / (double)zVal2);
  angleXZ2 = angleXZ2*(57.2958);

  angleYZ3 = atan((double)yVal3 / (double)zVal3);
  angleYZ3 = angleYZ3*(57.2958);
  angleXZ3 = atan((double)xVal3 / (double)zVal3);
  angleXZ3 = angleXZ3*(57.2958);

  if(angleXZ <-50){
    servoMotor1.write(40);
  }
  if(angleXZ>50){
    servoMotor1.write(140);
  }
  if(angleXZ<15 && angleXZ>-15){
    servoMotor1.write(90);
  }
  if(angleXZ<-15 && angleXZ>-50){
    servoMotor1.write(70);
  }
  if(angleXZ>15 && angleXZ<50){
    servoMotor1.write(110);
  }

//servoMotor1.write(angleXZ+90);
  
  if(angleXZ2 <-50){
    servoMotor2.write(40);
  }
  if(angleXZ2>50){
    servoMotor2.write(140);
  }
  if(angleXZ2<15 && angleXZ2>-15){
    servoMotor2.write(90);
  }
  if(angleXZ2<-15 && angleXZ2>-50){
    servoMotor2.write(70);
  }
  if(angleXZ2>15 && angleXZ2<50){
    servoMotor2.write(110);
  }
//servoMotor2.write(angleXZ2+90);

  if(angleXZ3 <0){
    servoPinzas.write(90);
  }
  if(angleXZ3>0){
    servoPinzas.write(135);
  }
  
  Serial.write("yz:");
  Serial.print(angleYZ);
  Serial.write("\n");

  Serial.write("xz:");
  Serial.print(angleXZ);
  Serial.write("\n");

  Serial.write("yz2:");
  Serial.print(angleYZ2);
  Serial.write("\n");

  Serial.write("xz2:");
  Serial.print(angleXZ2);
  Serial.write("\n");

  Serial.write("yz3:");
  Serial.print(angleYZ3);
  Serial.write("\n");

  Serial.write("xz3:");
  Serial.print(angleXZ3);
  Serial.write("\n");
  
  delay(400);
 }

