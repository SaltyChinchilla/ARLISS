#include <Motor.h>
#include <Servo.h>
#include <Navigator.h>
#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <PID_v1.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GPS.h>
#include <RH_RF95.h>
#include "Adafruit_HTU21DF.h"

const int chipSelect = 4;
#define GPSECHO false //Turn off GPS debug info

boolean usingInterrupt = false;
Adafruit_GPS GPS(&Serial1);
int LED_GREEN = 8;

float pi = 3.141592653;

//Radio setup
#define RFM95_CS      12
#define RFM95_IRQ     5
#define RFM95_RST     6

#define RF95_FREQ 900.0
RH_RF95 rf95(RFM95_CS, RFM95_IRQ);
#define LED 13

//Setup PID for Direction
double Setpoint, Input, Output;
double consKp=80, consKi=0, consKd=0.50;
PID directionPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, AUTOMATIC);

//Setup Motors
Motor motorL(12,13,11);
Motor motorR(6,9,10);

//Setup IMU
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//Setup SeedServo
Servo seedServo;

//Setup Temp and Humidy
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  pinMode(LED_GREEN,OUTPUT);
  //Serial Setup
  Serial.begin(9600);
  seedServo.attach(5);
  seedServo.write(90);

  IMUSetup();
  GPSsetup();
  THsetup();
  Setpoint = 180;

  directionPID.SetMode(AUTOMATIC);
  directionPID.SetOutputLimits(-255,255);

  
}

//stage bools
bool falling = true; //stage 1
bool standby = true; //stage 1.1
bool mapping = true; //stage 2
bool seeding = true; //Stage 3

void loop() {
//  if(falling){
//    falling = Falling_loop(falling);
//  }else if(standby){
//    standby = standby_loop(standby, 3600000);
//  }

  Input = IMULoop(0);
  Setpoint = 180;
  directionPID.Compute();
  
  if(displayCalStatus() > 0){
    motorR.drive(Output);
    motorL.drive(-Output);
  }else{
    //motorR.drive(0);
    //motorL.drive(0);
  }
  
  Serial.print(Input); Serial.print(',');
  //Serial.println(getHumidity());
  Serial.println(displayCalStatus());
}
