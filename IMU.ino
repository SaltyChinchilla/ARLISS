void IMUSetup(){
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
  
}

float imux = 0;
float imuy = 0;
float imuz = 0;

float IMULoop(int i){
    /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
//  Serial.print("X: ");
//  Serial.print(imux, 4);
//  Serial.print("\tY: ");
//  Serial.print(imuy, 4);
//  Serial.print("\tZ: ");
//  Serial.print(imuz, 4);
//  Serial.println("");

  imux = event.orientation.x;
  imuy = event.orientation.y;
  imuz = event.orientation.z;
  
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  
  float ax = acc.x();
  float ay = acc.y();
  float az = acc.z();
  
  if(i == 0){
    return imux;
  }else if(i == 1){
    float magnitude = sqrt(pow(ax,2) + pow(ay,2) + pow(az,2));
    return magnitude;
  }
}



int gyroCal;
int accelCal;
int magCal;

int displayCalStatus(void)
{
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  gyroCal = gyro;
  accelCal = accel;
  magCal = mag;

  return mag;
  
}

