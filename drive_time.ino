void drive_time(float t,float dir){
  Setpoint = dir;
  while(abs(Input - Setpoint) > 3){
     directionPID.Compute();
     motorR.drive(Output);
     motorL.drive(-Output);
     //Serial.println(Input);
     Input = IMULoop(0);
  }
  
  long current_time = millis();
  while (abs(millis()-current_time)<t){
    while(abs(Input - Setpoint) > 3){
      directionPID.Compute();
      motorR.drive(Output);
      motorL.drive(-Output);
     //Serial.println(Input);
      Input = IMULoop(0);
    }
    motorR.drive(255);
    motorL.drive(255);
    Input = IMULoop(0);
    
  }
  Serial.println("done driving");
  motorR.drive(0);
  motorL.drive(0);
}

bool drive_to_waypoint(float lat, float lon){
  float current_lat = GPSloop(0);
  float current_lon = GPSloop(1);

  float heading = getGPSBearing(current_lat, current_lon,lat,lon);
  Setpoint = heading;
  while(getGPSDistance(current_lat,current_lon,lat,lon) < .5){
    if(abs(Input - Setpoint) > 10){
      directionPID.Compute();
      motorR.drive(Output);
      motorL.drive(-Output);
      Input = IMULoop(0);
    }else{
      motorR.drive(255);
      motorL.drive(255);
    }
  }
  motorR.drive(0);
  motorL.drive(0);
  return true;

  
}

