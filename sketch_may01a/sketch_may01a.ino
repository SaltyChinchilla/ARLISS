#include <SPI.h>
#include "Adafruit_GFX.h" //Graphics lib
#include "Adafruit_HX8357.h" //TouchScreen lib
#include <RH_RF95.h> //Radio lib
//IMU stuffs
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_GPS.h>

const int chipSelect = 4;
#define GPSECHO false //Turn off GPS debug info

boolean usingInterrupt = false;
Adafruit_GPS GPS(&Serial1);

float pi = 3.14;



//Set up for the Feather M0
#ifdef ARDUINO_SAMD_FEATHER_M0
   #define STMPE_CS 6
   #define TFT_CS   9
   #define TFT_DC   10
   #define SD_CS    5
#endif

#define TFT_RST -1

//Start the screen
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

int cx = tft.width() / 2;
int cy = tft.height() / 2;
//Radio stuff
#define RFM95_CS      12
#define RFM95_IRQ     5
#define RFM95_RST     6

#define RF95_FREQ 900.0
RH_RF95 rf95(RFM95_CS, RFM95_IRQ);
#define LED 13

//IMU Starup
Adafruit_BNO055 bno = Adafruit_BNO055(55);

float heading;
void setup() {
  Serial.begin(9600);
  
  //RadioSetup();
  IMUSetup();
  GPSsetup();
  
  
  splashStartup(20);
  pinMode(A0,INPUT);
  backSetup();
  
  
  //delay(100000);
}
int timer = 0;
int cal = 13;
void loop() {
  float loc = GPSloop();
  
  //RadioLoop();
  heading = IMULoop();
  //output Cal Data
  if(cal != displayCalStatus()){
    cal = displayCalStatus();
    dispData(cal,152,70,0);
  }
  //things that update ofter
  if(millis() - timer > 100){
    timer = millis();
    dispData(heading,100,30,0);

    //GPS
    dispData(loc,120,50,3);
    //dispData(loc[1],160,50,0);
  }
  


  
}


