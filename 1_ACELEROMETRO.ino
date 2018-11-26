//Librerias de los Sensores MMA7631 y MPU6050
#include <math.h>
#include <Servo.h>
#include <Wire.h>


//Direccion I2C de la IMU
#define MPU 0x68
//Ratios de conversion
#define A_R 16384.0 // 32768/2
#define G_R 131.0 // 32768/250
 //Conversion de radianes a grados 180/PI
#define RAD_A_DEG = 57.295779


//Inicializacion de los Servomotores de cada grado de libertad
Servo servoMotor1;
Servo servoMotor2;
Servo servoPinzas;
Servo servoGiro;


//Inicializacion y preparacion del arduino para la conexion con
//los sensores y Servomotores
void setup() {
  Wire.begin(); // D2(GPIO4)=SDA / D1(GPIO5)=SCL
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  analogReference(EXTERNAL);
  Serial.begin(9600);
  servoMotor1.attach(13);
  servoMotor2.attach(12);
  servoPinzas.attach(11);
  servoGiro.attach(9);
}


//MPU-6050 da los valores en enteros de 16 bits
//Valores RAW
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
 
//Angulos
float Acc[2];
float Gy[3];
float Angle[3];

String valores;
long tiempo_prev;
float dt;


//Inicializacion de las variables del Acelerometro MMA6050
//Primer Acelerometro (Codo)
int xVal = 0;
int yVal = 0;
int zVal = 0;
//Segundo Acelerometro (Brazo)
int xVal2 = 0;
int yVal2 = 0;
int zVal2 = 0;
//Tercer Acelerometro (Muñeca/Pinzas)
int xVal3 = 0;
int yVal3 = 0;
int zVal3 = 0;
//Angulos de funcionamiento de los acelerometros
//Angulos del primer acelerometro
double angleYZ = 0;
double angleXZ = 0;
//Angulos del segundo acelerometro
double angleYZ2 = 0;
double angleXZ2 = 0;
//Angulo del tercer acelerometro
double angleYZ3 = 0;
double angleXZ3 = 0;



 void loop() {
     //Leer los valores del Acelerometro de la IMU
  xVal = analogRead(3);
  yVal = analogRead(4);
  zVal = analogRead(5);
  xVal2 = analogRead(6);
  yVal2 = analogRead(7);
  zVal2 = analogRead(8);
  xVal3 = analogRead(0);
  yVal3 = analogRead(1);
  zVal3 = analogRead(2);
    //Caracterización de los valores de los MMA7361
  xVal = map(xVal, 0, 1023, -500, 500);
  yVal = map(yVal, 0, 1023, -500, 500);
  zVal = map(zVal, 0, 1023, -500, 500);
  xVal2 = map(xVal2, 0, 1023, -500, 500);
  yVal2 = map(yVal2, 0, 1023, -500, 500);
  zVal2 = map(zVal2, 0, 1023, -500, 500);
  xVal3 = map(xVal3, 0, 1023, -500, 500);
  yVal3 = map(yVal3, 0, 1023, -500, 500);
  zVal3 = map(zVal3, 0, 1023, -500, 500);
    //Calculo de la posición angular del MMA7631
    //Acelerometro 1 (Codo)
  angleYZ = atan((double)yVal / (double)zVal);
  angleYZ = angleYZ*(57.2958);
  angleXZ = atan((double)xVal / (double)zVal);
  angleXZ = angleXZ*(57.2958);
    //Acelerometro 2 (Brazo)
  angleYZ2 = atan((double)yVal2 / (double)zVal2);
  angleYZ2 = angleYZ2*(57.2958);
  angleXZ2 = atan((double)xVal2 / (double)zVal2);
  angleXZ2 = angleXZ2*(57.2958);
    //Acelerometro 3 (Pinzas)
  angleYZ3 = atan((double)yVal3 / (double)zVal3);
  angleYZ3 = angleYZ3*(57.2958);
  angleXZ3 = atan((double)xVal3 / (double)zVal3);
  angleXZ3 = angleXZ3*(57.2958);

    //Condiciones de movimiento
  if(angleXZ>65){
    grado=0;
  }
  else{
    grado=1;
  }
  //Codo
  if(grado==0){
    servoMotor1.write(40);
    if(angleXZ2 <-50){
      servoMotor2.write(10);
    }
    else if(angleXZ2<-25 && angleXZ2>-50){
      servoMotor2.write(35);
    }
    else if(angleXZ2<0 && angleXZ2>-25){
      servoMotor2.write(60);
    }
    else if(angleXZ2<25 && angleXZ2>0){
      servoMotor2.write(85);
    }
    else if(angleXZ2<50 && angleXZ2>25){
      servoMotor2.write(110);
    }
    else if(angleXZ2>50){
      servoMotor2.write(125);
    }
  //Brazo
  }  
  else if(grado==1){
     if(angleXZ <-50){
      servoMotor1.write(150);
      servoMotor2.write(140);
     }
     else if(angleXZ>50){
      servoMotor1.write(90);
      servoMotor2.write(80);
     }
     else if(angleXZ<15 && angleXZ>-15){
      servoMotor1.write(130);
      servoMotor2.write(120);
     }
     else if(angleXZ<-15 && angleXZ>-50){
      servoMotor1.write(150);
      servoMotor2.write(140);
     }
     else if(angleXZ>15 && angleXZ<50){
      servoMotor1.write(110);
      servoMotor2.write(100);
     }
  }
  //Muñeca/Pinzas
  if(angleXZ3 <0){
    servoPinzas.write(135);
  }
  if(angleXZ3>0){
    servoPinzas.write(70);
  }
  
 //Toma de datos Acelerometro/Giroscopio MPU6050
  Wire.beginTransmission(MPU);
   Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x3B, se piden 6 registros
   AcX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   AcY=Wire.read()<<8|Wire.read();
   AcZ=Wire.read()<<8|Wire.read();
 
   //A partir de los valores del acelerometro, se calculan los angulos Y, X
   //respectivamente, con la formula de la tangente.
   Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
   Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
 
   //Leer los valores del Giroscopio
   Wire.beginTransmission(MPU);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x43, se piden 6 registros
   GyX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   GyY=Wire.read()<<8|Wire.read();
   GyZ=Wire.read()<<8|Wire.read();
 
   //Calculo del angulo del Giroscopio
   Gy[0] = GyX/G_R;
   Gy[1] = GyY/G_R;
   Gy[2] = GyZ/G_R;

   dt = (millis() - tiempo_prev) / 1000.0;
   tiempo_prev = millis();
 
   //Aplicar el Filtro Complementario
   Angle[0] = 0.98 *(Angle[0]+Gy[0]*dt) + 0.02*Acc[0];
   Angle[1] = 0.98 *(Angle[1]+Gy[1]*dt) + 0.02*Acc[1];

   //Integración respecto del tiempo paras calcular el YAW
   Angle[2] = Angle[2]+Gy[2]*dt;

  servoGiro.write(Angle[2]+90);

  //Visualizacion de los datos suministrados por
  //acelerometros y giroscopio

  //Codo
  Serial.write("yz:");
  Serial.print(angleYZ);
  Serial.write("\n");

  Serial.write("xz:");
  Serial.print(angleXZ);
  Serial.write("\n");
  //Brazo
  Serial.write("yz2:");
  Serial.print(angleYZ2);
  Serial.write("\n");

  Serial.write("xz2:");
  Serial.print(angleXZ2);
  Serial.write("\n");
  //Muñeca/Pinzas
  Serial.write("yz3:");
  Serial.print(angleYZ3);
  Serial.write("\n");

  Serial.write("xz3:");
  Serial.print(angleXZ3);
  Serial.write("\n");
  //Giroscopio/Hombro
  valores = String(Angle[2]);  
  Serial.println(valores);
  Serial.write("\n");
  
  delay(400);
 }
