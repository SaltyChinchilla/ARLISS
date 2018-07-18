#include <Motor.h>
#include <Servo.h>
//#include <Navigator.h>
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
Motor motorL(13,12,11);
Motor motorR(9,6,10);

//Setup IMU
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//Setup SeedServo
Servo seedServo;

//Setup Temp and Humidy
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

//log files
String latlog;
String lonlog;
String humidlog;
String clog;

String Accel;

void setup() {
  pinMode(LED_GREEN,OUTPUT);
  //Serial Setup
  Serial.begin(9600);
  seedServo.writeMicroseconds(1450);
  seedServo.attach(5);
  

  IMUSetup();
  GPSsetup();
  THsetup();
  SDsetup();
  //Setup log files
  latlog = fileSetup("lat");
  lonlog = fileSetup("lon");
  humidlog = fileSetup("hum");
  clog = fileSetup("clog");
  Accel = fileSetup("acel");
  
  
  Setpoint = 180;

  directionPID.SetMode(AUTOMATIC);
  directionPID.SetOutputLimits(-255,255);

  
}

//stage bools
bool falling = false; //stage 1
bool standby = false; //stage 1.1
bool mapping = true; //stage 2
bool process = false; //stage 2.1
bool seeding = true; //Stage 3

int pnts[2] = {10, 7};
void loop() {
  //Test for gps lock and IMU cal status
  GPSloop(0);
  seedServo.writeMicroseconds(1450);
  if(displayCalStatus() == 3 && 0 == 1){
    if(falling){
      falling = Falling_loop(falling);
    }else if(standby){
      standby = standby_loop(standby, 3600000);
    }else if(mapping){
      Serial.println("making map");
      mapping = make_hmap();
      mapping = false;
      write_to_SD(2,clog);   
    }else if(process){
      //pnts = process_hmap();
//      pnts[2] = {2, 7};
      process = false;
      write_to_SD(3,clog);
    }else{
      Serial.println("seeding fo real");
      seeding = seed2(pnts);
      write_to_SD(4,clog);
    }
  }
  write_to_SD(IMULoop(1),Accel);
}
