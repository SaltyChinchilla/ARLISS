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

float IMULoop(){
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
  
  
  delay(100);
  return imux;
}

int gyroCal;
int accelCal;
int magCal;

int displayCalStatus(void)
{
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

//  Serial.print("Sys:");
//  Serial.print(system, DEC);
//  Serial.print(" G:");
//  Serial.print(gyro, DEC);
//  Serial.print(" A:");
//  Serial.print(accel, DEC);
//  Serial.print(" M:");
//  Serial.println(mag, DEC);

  gyroCal = gyro;
  accelCal = accel;
  magCal = mag;

  return mag;
  
}

